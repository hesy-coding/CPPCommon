//
// Created by wjl on 2021/10/18.
//

#ifndef CPPCOMMON_CLEARACTION_H
#define CPPCOMMON_CLEARACTION_H
#include "base/BaseDefs.h"
#include <functional>
#include <utility>

namespace cppcommon {
    class ClearAction : public Noncopyable {
    public:
        explicit ClearAction(std::function<void()> func): _action(std::move(func)) {}

        ~ClearAction() {
            if (_action) {
                _action();
            }
        }
    private:
        std::function<void()> _action;
    };
}
#endif //CPPCOMMON_CLEARACTION_H
