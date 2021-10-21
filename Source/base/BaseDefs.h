//
// Created by wjl on 2021/10/18.
//

#ifndef CPPCOMMON_BASEDEFS_H
#define CPPCOMMON_BASEDEFS_H
#include "base/Configuration.h"
#include <cassert>
#include <memory>
#include <string>

//windows
#if defined(CPP_CMMN_OS_WIN)
#ifdef _DEBUG
#define _CPP_CMMN_DEBUG 1
#else
#define _CPP_CMMN_DEBUG 0
#endif

#define CPP_CMMN_WIN_TRUE(b) ((b) != FALSE)
#define CPP_CMMN_WIN_HRESULT_OK(hr) ((hr) == S_OK)

//other os
#elif
#define _CPP_CMMN_DEBUG 0

#endif

#if _CPP_CMMN_DEBUG
#define CPP_CMMN_DCHECK(cond) assert(cond)

#else
#define CPP_CMMN_DCHECK(cond)

#endif

#define CPP_CMMN_ZERO_STRUCT(s) memset(&s, 0, sizeof(s))

namespace cppcommon {
    typedef std::wstring U16String;

    class Noncopyable {
    public:
        Noncopyable() = default;
        Noncopyable(const Noncopyable &) = delete;
        const Noncopyable & operator=(const Noncopyable &other) = delete;
    };
}

#endif //CPPCOMMON_BASEDEFS_H
