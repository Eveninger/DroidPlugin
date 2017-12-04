//
// Created by 夜游 on 2017/12/4.
//

#ifndef DROIDPLUGIN_GAMERJNI_H
#define DROIDPLUGIN_GAMERJNI_H

#include <fb/fbjni.h>

using namespace facebook::jni;

extern alias_ref<jclass> nativeEngineClass;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved);
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved);

#endif //DROIDPLUGIN_GAMERJNI_H
