//
// Created by wjl on 2021/10/21.
//

#ifndef CPPCOMMON_PROCESSDEFS_H
#define CPPCOMMON_PROCESSDEFS_H
#include "base/BaseDefs.h"

namespace cppcommon {
#if defined(CPP_CMMN_OS_WIN)
    typedef HANDLE process_handle_t;
#endif
}

#endif //CPPCOMMON_PROCESSDEFS_H
