#pragma once
#include <string>
#include <cstdint>

constexpr const char* BACKEND_URL = "http://192.168.1.69:8080";
constexpr bool BYPASS_SSL = true; // only works with curl versions (aka if it doesnt use processrequest i cba bypassing ssl for this)

namespace ue_hook {
    constexpr bool USE_PR = false; // only enable this if ur doing 18.40+
    constexpr uintptr_t PR_ADDR = 0x0; // set this to the correct address (processrequest)
    constexpr uintptr_t GETURL_ADDR = 0x70; // set this to the correct address (geturl its mostly 0x70 until like s25/26+)
    constexpr uintptr_t SETURL_ADDR = 0x0; // set this to the correct address (seturl)
}

namespace eos_hook {
    constexpr bool USE_EOS = false; // only enable this if ur doing s22+
    constexpr uintptr_t PR_ADDR = 0x0; // set this to the correct address (processrequest)
    constexpr uintptr_t GETURL_ADDR = 0x0; // set this to the correct address (geturl)
    constexpr uintptr_t SETURL_ADDR = 0x0; // set this to the correct address (seturl)
}