//
// Created by wjl on 2021/10/21.
//

#include "ProcessUtils.h"

namespace cppcommon {
    process_handle_t GetCurrentProcessHandle() {
        return ::GetCurrentProcess();
    }
}