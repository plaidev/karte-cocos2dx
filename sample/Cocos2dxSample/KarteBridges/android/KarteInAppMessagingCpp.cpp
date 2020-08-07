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
#include "KarteInAppMessagingCpp.h"
#include "KarteAndroidUtils.h"
#include "platform/android/jni/JniHelper.h"

#include <jni.h>

const char* iamClassName = "io/karte/android/inappmessaging/InAppMessaging";

void KarteInAppMessagingCpp::dismiss() {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo dismiss;
    if (cocos2d::JniHelper::getStaticMethodInfo(dismiss, iamClassName, "dismiss", "()V"))
    {
        env->CallStaticVoidMethod(dismiss.classID, dismiss.methodID);
    }
}

void KarteInAppMessagingCpp::suppress() {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo suppress;
    if (cocos2d::JniHelper::getStaticMethodInfo(suppress, iamClassName, "suppress", "()V"))
    {
        env->CallStaticVoidMethod(suppress.classID, suppress.methodID);
    }
}

void KarteInAppMessagingCpp::unsuppress() {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo unsuppress;
    if (cocos2d::JniHelper::getStaticMethodInfo(unsuppress, iamClassName, "unsuppress", "()V"))
    {
        env->CallStaticVoidMethod(unsuppress.classID, unsuppress.methodID);
    }
}

bool KarteInAppMessagingCpp::isPresenting() {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo isPresenting;
    if (cocos2d::JniHelper::getStaticMethodInfo(isPresenting, iamClassName, "isPresenting", "()Z"))
    {
        return env->CallStaticBooleanMethod(isPresenting.classID, isPresenting.methodID);
    }
    return false;
}