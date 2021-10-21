//
// Created by wjl on 2021/10/18.
//

#ifndef CPPCOMMON_CONFIGURATION_H
#define CPPCOMMON_CONFIGURATION_H
//#define _CPP_CMMN_WINDOWS 1

//windows
#ifdef _MSC_VER
#define CPP_CMMN_OS_WIN

#endif

#if defined(CPP_CMMN_OS_WIN)
#include <winsdkver.h>
#if defined(_WIN32_WINNT)
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0601

#if defined(WINVER)
#undef WINVER
#endif
#define WINVER _WIN32_WINNT

#include <sdkddkver.h>
#include <windows.h>
#endif

#endif //CPPCOMMON_CONFIGURATION_H
