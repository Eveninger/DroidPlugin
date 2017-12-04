//
// Created by 夜游 on 2017/12/4.
//

#ifndef DROIDPLUGIN_IOUNIFORMER_H
#define DROIDPLUGIN_IOUNIFORMER_H

#define HOOK_SYMBOL(handle, func) hook_function(handle, #func, (void*) new_##func, (void**) &orig_##func)
#define HOOK_DEF(ret, func, ...) ret (*orig_##func)(__VA_ARGS__); ret new_##func(__VA_ARGS__)

namespace IOUniformer {
    void startUniformer();
}

#endif //DROIDPLUGIN_IOUNIFORMER_H
