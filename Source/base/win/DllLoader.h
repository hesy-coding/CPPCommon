//
// Created by wjl on 2021/10/18.
//

#ifndef CPPCOMMON_DLLLOADER_H
#define CPPCOMMON_DLLLOADER_H
#include "base/BaseDefs.h"

namespace cppcommon {
    class DllLoader : public Noncopyable {
    public:
        explicit DllLoader(const U16String &path) {
            _dll = LoadLibraryW(path.c_str());
        }

        ~DllLoader() {
            FreeLibrary(_dll);
            _dll = nullptr;
        }

        template<class FunctionType>
        FunctionType GetProcAddress(const std::string &name) const {
            return _dll ? reinterpret_cast<FunctionType>(::GetProcAddress(_dll, name.c_str())) : nullptr;
        }

        explicit operator bool() const {
            return valid();
        }

        bool valid() const {
            return _dll;
        }

    private:
        mutable HMODULE _dll;
    };
}
#endif //CPPCOMMON_DLLLOADER_H
