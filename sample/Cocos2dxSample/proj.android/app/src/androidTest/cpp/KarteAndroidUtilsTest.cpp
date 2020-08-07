//
// Created by akihiro.aida on 2019-06-27.
//

#include "jni.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "platform/android/jni/JniHelper.h"
#include "KarteAndroidUtils.h"

extern "C" JNIEXPORT jobject JNICALL
Java_org_cocos2dx_cpp_NativeTestBridge_stringToJSONObject(
        JNIEnv *env, jobject instance, jstring str_) {
    if (nullptr == str_)
        return KarteAndroidUtils::stringToJSONObject(nullptr);
    const char *str = env->GetStringUTFChars(str_, 0);
    jobject jJson = KarteAndroidUtils::stringToJSONObject(str);
    env->ReleaseStringUTFChars(str_, str);
    return jJson;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_cocos2dx_cpp_NativeTestBridge_JSONObjectToString(
        JNIEnv *env, jobject instance, jobject json) {
    return KarteAndroidUtils::JSONObjectToString(json);
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_cocos2dx_cpp_NativeTestBridge_JSONArrayToString(
        JNIEnv *env, jobject instance, jobject json) {
    return KarteAndroidUtils::JSONArrayToString(json);
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_cocos2dx_cpp_NativeTestBridge_copyString(
        JNIEnv *env, jobject instance, jstring str) {
    return env->NewStringUTF(KarteAndroidUtils::jStringToCString(str));
}