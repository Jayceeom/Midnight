#include <dlfcn.h>
#include <cstring>
#include "includes/hooks.h"
#include "includes/dobby/dobby.h"
#include "includes/logger.h"
#include "includes/url.h"
#include "includes/opts.h"

// ud hooks
namespace Hooks {
    namespace CurlHook {
        int (*OG_SETOPT)(void*, int, void*) = nullptr;
        void* SetupHook(void*) {
            LOGI("Loading Unreal lib...");
            void* handle = dlopen("libUE4.so", 2);
            if (!handle) {
                LOGE("Failed to load Unreal lib!");
                return nullptr;
            }

            void* SetOptSym = dlsym(handle, "curl_easy_setopt");
            if (!SetOptSym) {
                LOGE("Failed to find curl_easy_setopt symbol.");
                dlclose(handle);
                return nullptr;
            }

            if (DobbyHook(SetOptSym, (void*)SetOptHook, (void**)&OG_SETOPT) == 0) {
                LOGI("Successfully hooked curl_easy_setopt!");
            } else {
                LOGE("Failed to hook curl_easy_setopt!");
            }

            return nullptr;
        }

        int SetOptHook(void* handle, int option, void* args) {
            if (!OG_SETOPT)
                return -1;

            if (option == 10002 && args != nullptr) { // url hook
                const char* UrlCStr = static_cast<const char*>(args);
                if (UrlCStr) {
                    Url url = Url::ParseUrl(UrlCStr);
                    if (Url::ShouldRedirect(url.host)) {
                        char* newUrl = ::strdup(Url::CreateUrl(BACKEND_URL, url.pathAndQuery).c_str());
                        return OG_SETOPT(handle, option, newUrl);
                    }
                }
            } else if (option == 64 && BYPASS_SSL) { // SSL Bypass
                return OG_SETOPT(handle, option, reinterpret_cast<void*>(static_cast<intptr_t>(0)));
            }

            return OG_SETOPT(handle, option, args);
        }
    }
}