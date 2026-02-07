#pragma once
#include <cstddef>

namespace Hooks {
    namespace CurlHook {
        extern int (*OG_SETOPT)(void*, int, void*);
        void* SetupHook(void*);
        int SetOptHook(void* handle, int option, void* args);
    }
}