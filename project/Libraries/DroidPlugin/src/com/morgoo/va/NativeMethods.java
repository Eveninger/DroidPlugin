package com.morgoo.va;

import android.os.Build;

import java.lang.reflect.Method;

import dalvik.system.DexFile;

/**
 * @author Lody
 */
public class NativeMethods {

    public static int gCameraMethodType;
    public static Method gCameraNativeSetup;

    public static Method gOpenDexFileNative;

    public static Method gAudioRecordNativeCheckPermission;

    public static void init() {
        String methodName =
                Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT ? "openDexFileNative" : "openDexFile";
        for (Method method : DexFile.class.getDeclaredMethods()) {
            if (method.getName().equals(methodName)) {
                gOpenDexFileNative = method;
                break;
            }
        }
        if (gOpenDexFileNative == null) {
            throw new RuntimeException("Unable to find method : " + methodName);
        }
        gOpenDexFileNative.setAccessible(true);
    }

}
