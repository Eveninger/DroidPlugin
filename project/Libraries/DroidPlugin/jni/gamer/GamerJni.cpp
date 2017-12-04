//
// Created by 夜游 on 2017/12/4.
//

#include "GamerJni.h"

alias_ref<jclass> nativeEngineClass;

jstring fuck(alias_ref<jclass> jclazz) {
    JNIEnv *env = Environment::current();
    return env->NewStringUTF("Hello from JNI !  Compiled with ABI ");
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    return initialize(vm, [] {
        nativeEngineClass = findClassStatic("com/morgoo/droidplugin/PluginHelper");
        nativeEngineClass->registerNatives({makeNativeMethod("stringFromJNI", fuck)});
    });
}