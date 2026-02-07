#include <pthread.h>
#include "includes/opts.h"
#include "includes/hooks.h"

// most cleanest main.cpp i probably ever did
__attribute__((constructor))
void Main() {
    pthread_t ptid;
    if (ue_hook::USE_PR) { // TODO: add ue hooks & eos
        if (eos_hook::USE_EOS) {

        }
    } else {
        pthread_create(&ptid, nullptr, Hooks::CurlHook::SetupHook, nullptr);
    }
}