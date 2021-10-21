//
// Created by wjl on 2021/10/18.
//

#ifndef CPPCOMMON_DISPLAYINFO_H
#define CPPCOMMON_DISPLAYINFO_H
#include <vector>
#include "ui/Rect.h"

namespace cppcommon {
    struct DisplayInfo {
        const U16String deviceName;
        const Rect screenRect;
        const Rect screenWorkRect;
        const int dpi;
        const float scaleFactor;
        const float textScaleFactor;

#if defined(CPP_CMMN_OS_WIN)
        DisplayInfo(const MONITORINFOEXW &monitorInfo, int dpi, float textScaleFactor);
#endif
    };

    std::vector<DisplayInfo> GetDisplayInfos();
}

#endif //CPPCOMMON_DISPLAYINFO_H
