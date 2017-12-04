//
// Created by 夜游 on 2017/12/4.
//

#include "GamerJni.h"
#include "IOUniformer.h"

alias_ref<jclass> nativeEngineClass;

jstring fuck(alias_ref<jclass> jclazz) {
    JNIEnv *env = Environment::current();
    return env->NewStringUTF("Hello from JNI !  Compiled with ABI ");
}

void startUniformer(alias_ref<jclass> jclazz) {
    IOUniformer::startUniformer();
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    return initialize(vm, [] {
        nativeEngineClass = findClassStatic("com/morgoo/droidplugin/PluginHelper");
        nativeEngineClass->registerNatives({makeNativeMethod("stringFromJNI", fuck)});
        nativeEngineClass->registerNatives({makeNativeMethod("startUniformer", startUniformer)});
    });
}