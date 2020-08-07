//
//  Copyright 2020 PLAID, Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
#include "KarteAndroidUtils.h"
#include "platform/android/jni/JniHelper.h"
#include "KarteCocosCompat.h"

#include <android/log.h>
#include <jni.h>

const char* KarteAndroidUtils::appClassName = "io/karte/android/KarteApp";
const char* KarteAndroidUtils::variableClassName = "io/karte/android/variables/Variable";
const char* KarteAndroidUtils::variablesClassName = "io/karte/android/variables/Variables";

jclass KarteAndroidUtils::getVariablesClass() {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jclass variables_class = env->FindClass(KarteAndroidUtils::variablesClassName);
    if (variables_class == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "Karte.AndroidUtils", "Class not found: %s", KarteAndroidUtils::variablesClassName);
        return nullptr;
    }
    return variables_class;
}

jobject KarteAndroidUtils::getVariable(const char* key) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jclass variables_class = KarteAndroidUtils::getVariablesClass();
    cocos2d::JniMethodInfo get;
    if (cocos2d::JniHelper::getStaticMethodInfo(get, variablesClassName, "get", "(Ljava/lang/String;)Lio/karte/android/variables/Variable;")) {
        jstring jKey = env->NewStringUTF(key);
        jobject jVariable = env->CallStaticObjectMethod(variables_class, get.methodID, jKey);
        env->DeleteLocalRef(variables_class);
        env->DeleteLocalRef(jKey);
        return jVariable;
    }
    env->DeleteLocalRef(variables_class);
    return nullptr;
}

jobject KarteAndroidUtils::stringToJSONObject(const char* jsonString) {
    if (nullptr == jsonString) {
        cocos2d::JniMethodInfo constructor;
        if (cocos2d::JniHelper::getMethodInfo(constructor, "org/json/JSONObject", "<init>", "()V"))
        {
            return constructor.env->NewObject(constructor.classID, constructor.methodID);;
        }
    }

    cocos2d::JniMethodInfo constructor;
    if (cocos2d::JniHelper::getMethodInfo(constructor, "org/json/JSONObject", "<init>", "(Ljava/lang/String;)V"))
    {
        jstring jStr = constructor.env->NewStringUTF(jsonString);
        jobject jsonObject = constructor.env->NewObject(constructor.classID, constructor.methodID, jStr);
        constructor.env->DeleteLocalRef(jStr);
        if (constructor.env->ExceptionCheck()){
            __android_log_print(ANDROID_LOG_ERROR, "Karte.AndroidUtils", "JSON parse error: %s", jsonString);
            constructor.env->ExceptionClear();
            constructor.env->DeleteLocalRef(jsonObject);
            return nullptr;
        }
        return jsonObject;
    }
    return nullptr;
}

jstring KarteAndroidUtils::JSONObjectToString(jobject jJsonObject) {
    if (nullptr == jJsonObject)
        return nullptr;

    cocos2d::JniMethodInfo toString;
    if (cocos2d::JniHelper::getMethodInfo(toString, "org/json/JSONObject", "toString", "()Ljava/lang/String;"))
    {
        return (jstring)toString.env->CallObjectMethod(jJsonObject, toString.methodID);
    }
    return nullptr;
}

jstring KarteAndroidUtils::JSONArrayToString(jobject jJsonArray) {
    if (nullptr == jJsonArray)
        return nullptr;

    cocos2d::JniMethodInfo toString;
    if (cocos2d::JniHelper::getMethodInfo(toString, "org/json/JSONArray", "toString", "()Ljava/lang/String;"))
    {
        return (jstring)toString.env->CallObjectMethod(jJsonArray, toString.methodID);
    }
    return nullptr;
}

const char* KarteAndroidUtils::jStringToCString(jstring jString) {
    if (nullptr == jString)
        return nullptr;

    JNIEnv* env = KarteAndroidUtils::getEnv();
    const char* cString = env->GetStringUTFChars(jString, nullptr);
    char* string = new char[strlen(cString) + 1];
    strcpy(string, cString);
    env->ReleaseStringUTFChars(jString, cString);
    return string;
}

JNIEnv* KarteAndroidUtils::getEnv() {
    return KarteCocosCompat::getEnv();
}

jobject KarteAndroidUtils::getContext() {
    return KarteCocosCompat::getContext();
}