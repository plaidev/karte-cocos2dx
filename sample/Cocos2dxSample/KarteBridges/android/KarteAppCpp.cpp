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
#include "KarteAppCpp.h"
#include "KarteAndroidUtils.h"
#include "platform/android/jni/JniHelper.h"
#include "KarteUtilCpp.h"

#include <jni.h>

const char* getString(const char* methodName) {
    const char* string = nullptr;
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, KarteAndroidUtils::appClassName, methodName, "()Ljava/lang/String;")) {
        auto jString = (jstring) env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        string = KarteAndroidUtils::jStringToCString(jString);
        env->DeleteLocalRef(jString);
    }
    return string;
}

bool getBool(const char* methodName) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo methodInfo;
    bool boolValue = false;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, KarteAndroidUtils::appClassName, methodName, "()Z")) {
        boolValue = env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
    }
    return boolValue;
}

void callStaticVoidMethod(const char* methodName) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, KarteAndroidUtils::appClassName, methodName, "()V"))
    {
        env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        if (env->ExceptionCheck()) {
            __android_log_print(ANDROID_LOG_ERROR, "Karte.KarteApp", "Field to call method: %s", methodName);
            env->ExceptionClear();
        }
    }
}

KarteAppCpp::KarteAppCpp() {
    visitorId = getString("getVisitorId");
}

KarteAppCpp& KarteAppCpp::operator=(const KarteAppCpp &o) {
    if (this != &o) {
        visitorId = KarteUtilCpp::copyString((char *)o.visitorId);
    }
    return *this;
}

KarteAppCpp::KarteAppCpp(const KarteAppCpp &o) {
    this->visitorId = KarteUtilCpp::copyString((char *)o.visitorId);
}

KarteAppCpp::~KarteAppCpp() {
    delete [] visitorId;
}

const char* KarteAppCpp::getVisitorId() {
    this->visitorId = getString("getVisitorId");
    return visitorId;
}

bool KarteAppCpp::isOptOut() {
    return getBool("isOptOut");
}

void KarteAppCpp::optOut() {
    callStaticVoidMethod("optOut");
}

void KarteAppCpp::optIn() {
    callStaticVoidMethod("optIn");
}

void KarteAppCpp::renewVisitorId() {
    callStaticVoidMethod("renewVisitorId");
}