//
// Created by 夜游 on 2017/12/4.
//

#include "IOUniformer.h"
#include "SymbolFinder.h"
#include <dlfcn.h>
#include <stddef.h>
#include <fcntl.h>
#include <dirent.h>
#include <fb/fbjni.h>

extern "C" {
#include <HookZz/include/hookzz.h>
}

static inline void
hook_function(void *handle, const char *symbol, void *new_func, void **old_func) {
    void *addr = dlsym(handle, symbol);
    if (addr == NULL) {
        return;
    }
    ZzHookReplace(addr, new_func, old_func);
}

HOOK_DEF(void*, dlopen, const char *filename, int flag) {
    ALOGE("Hook住了dlopen");
    void *ret = orig_dlopen(filename, flag);
    return ret;
}

HOOK_DEF(void*, do_dlopen_V19, const char *filename, int flag, const void *extinfo) {
    ALOGE("Hook住了do_dlopen_V19");
    void *ret = orig_do_dlopen_V19(filename, flag, extinfo);
    return ret;
}

HOOK_DEF(void*, do_dlopen_V24, const char *name, int flags, const void *extinfo,
         void *caller_addr) {
    ALOGE("Hook住了do_dlopen_V24");
    void *ret = orig_do_dlopen_V24(name, flags, extinfo, caller_addr);
    return ret;
}

int findSymbol(const char *name, const char *libn,
               unsigned long *addr) {
    return find_name(getpid(), name, libn, addr);
}

void hook_dlopen(int api_level) {
    ALOGE("开始Hook dlopen");
    void *symbol = NULL;
    if (api_level > 23) {
        if (findSymbol("__dl__Z9do_dlopenPKciPK17android_dlextinfoPv", "linker",
                       (unsigned long *) &symbol) == 0) {
            ZzHookReplace(symbol, (void *) new_do_dlopen_V24,
                          (void **) &orig_do_dlopen_V24);
        }
    } else if (api_level >= 19) {
        if (findSymbol("__dl__Z9do_dlopenPKciPK17android_dlextinfo", "linker",
                       (unsigned long *) &symbol) == 0) {
            ZzHookReplace(symbol, (void *) new_do_dlopen_V19,
                          (void **) &orig_do_dlopen_V19);
        }
    } else {
        if (findSymbol("__dl_dlopen", "linker",
                       (unsigned long *) &symbol) == 0) {
            ZzHookReplace(symbol, (void *) new_dlopen, (void **) &orig_dlopen);
        }
    }
}


void IOUniformer::startUniformer() {
    ALOGE("调用了Native的startUniformer()方法");
    void *handle = dlopen("libc.so", RTLD_NOW);
    if (handle) {
        ALOGE("关闭libc.so的句柄");
        dlclose(handle);
    }
    hook_dlopen(24);
}