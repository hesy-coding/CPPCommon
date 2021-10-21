//
// Created by wjl on 2021/10/18.
//

#include "DisplayInfo.h"
#include "base/BaseDefs.h"
#include "base/win/DllLoader.h"
#if defined(CPP_CMMN_OS_WIN)
#include <roapi.h>
#include <winstring.h>
#include <windows.ui.viewmanagement.h>
#endif
#include "base/ClearAction.h"
#include "base/process/ProcessUtils.h"

namespace cppcommon {
    namespace internal {
        static const float DEFAULT_TEXT_SCALE_FACTOR = 1.0f;
        static float GetTextScaleFactor() {
#if defined(CPP_CMMN_OS_WIN)
            ::RoInitialize(RO_INIT_MULTITHREADED);
            ClearAction _([=] {
                ::RoUninitialize();
            });

            HSTRING_HEADER header;
            HSTRING classId;
            auto sourceString = RuntimeClass_Windows_UI_ViewManagement_UISettings;
            if (!CPP_CMMN_WIN_HRESULT_OK(::WindowsCreateStringReference(sourceString, wcslen(sourceString), &header, &classId))) {
                return DEFAULT_TEXT_SCALE_FACTOR;
            }

            IInspectable *inspectable = nullptr;
            if (!CPP_CMMN_WIN_HRESULT_OK(::RoActivateInstance(classId, &inspectable))) {
                return DEFAULT_TEXT_SCALE_FACTOR;
            }

            ::ABI::Windows::UI::ViewManagement::IUISettings2* uiSettings = nullptr;
            if (!CPP_CMMN_WIN_HRESULT_OK(inspectable->QueryInterface(__uuidof(uiSettings), reinterpret_cast<void**>(&uiSettings)))) {
                return DEFAULT_TEXT_SCALE_FACTOR;
            }

            double factor = 0;
            if (!CPP_CMMN_WIN_HRESULT_OK(uiSettings->get_TextScaleFactor(&factor))) {
                return DEFAULT_TEXT_SCALE_FACTOR;
            }

            return static_cast<float>(factor);
#elif
            return DEFAULT_TEXT_SCALE_FACTOR;
#endif
        }

        static int DEFAULT_DPI = 96;
        static float GetScalingFactorForDPI(int dpi) {
            return static_cast<float>(dpi) / static_cast<float>(DEFAULT_DPI);
        }

//        static float GetScaleFactorForDPI(int dpi, bool includeAccessibility) {
//            auto scale = GetScalingFactorForDPI(dpi);
//            return includeAccessibility ? scale * GetTextScaleFactor() : scale;
//        }

        typedef HRESULT (WINAPI *GetDpiForMonitorProc)(HMONITOR, int, UINT *, UINT *);
        static bool GetMonitorDPI(HMONITOR monitor, int &dpi) {
            DllLoader dll(L"shcore.dll");
            if (!dll) {
                return false;
            }

//            auto func = reinterpret_cast<GetDpiForMonitorProc>(dll.GetProcAddress("GetDpiForMonitor"));
            auto func = dll.GetProcAddress<GetDpiForMonitorProc>("GetDpiForMonitor");
            UINT dx = 0, dy = 0;
            if (!func || !CPP_CMMN_WIN_HRESULT_OK(func(monitor, 0, &dx, &dy))) {
                return false;
            }

            CPP_CMMN_DCHECK(dx == dy);
            dpi = static_cast<int>(dx);
            return true;
        }

        typedef UINT (WINAPI *GetSystemDpiForProcessProc)(HANDLE);
        static bool GetCurrentDPI(int &dpi) {
            DllLoader dll(L"user32.dll");
            if (!dll) {
                return false;
            }

            auto func = dll.GetProcAddress<GetSystemDpiForProcessProc>("GetSystemDpiForProcess");
            if (!func) {
                return false;
            }

            auto process = GetCurrentProcessHandle();
            dpi = static_cast<int>(func(process));
            return true;
        }

//        static int GetDPI(HMONITOR monitor) {
//            int dpi = 0;
//            if (GetMonitorDPI(monitor, dpi)) {
//                return dpi;
//            }
//
//            return ::GetDpiForSystem();
//        }

        static BOOL CALLBACK MonitorEnumCallback(
                HMONITOR monitor,
                HDC hdc,
                LPRECT rect,
                LPARAM param
        ) {
            MONITORINFOEXW  monitorInfo;
            CPP_CMMN_ZERO_STRUCT(monitorInfo);
            monitorInfo.cbSize = sizeof(monitorInfo);
            ::GetMonitorInfoW(monitor, &monitorInfo);

            int dpi = 0;
            if (!GetMonitorDPI(monitor, dpi) || !GetCurrentDPI(dpi)) {
                dpi = ::GetDeviceCaps(::GetDC(nullptr), LOGPIXELSX);
//                return TRUE;
            }

            auto *displayInfos = reinterpret_cast<std::vector<DisplayInfo> *>(param);
            displayInfos->emplace_back(monitorInfo,
                                       dpi,
                                       GetTextScaleFactor());
            return TRUE;
        }
    }
}

namespace cppcommon {
    DisplayInfo::DisplayInfo(const MONITORINFOEXW &monitorInfo, int dpi, float textScaleFactor)
    : deviceName(monitorInfo.szDevice),
      screenRect(monitorInfo.rcMonitor),
      screenWorkRect(monitorInfo.rcWork),
      dpi(dpi),
      scaleFactor(internal::GetScalingFactorForDPI(dpi)),
      textScaleFactor(textScaleFactor) {

    }

    std::vector<DisplayInfo> GetDisplayInfos() {
        std::vector<DisplayInfo> infos;
        auto ret = EnumDisplayMonitors(nullptr, nullptr,
                                       internal::MonitorEnumCallback,
                                       reinterpret_cast<LPARAM>(&infos));
        CPP_CMMN_DCHECK(CPP_CMMN_WIN_TRUE(ret));
        CPP_CMMN_DCHECK(!infos.empty());
        return infos;
    }
}