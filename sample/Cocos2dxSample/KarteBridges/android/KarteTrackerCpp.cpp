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
#include "KarteTrackerCpp.h"
#include "KarteAndroidUtils.h"
#include "platform/android/jni/JniHelper.h"
#include "KarteUtilCpp.h"

#include <jni.h>

const char* trackerClassName = "io/karte/android/tracking/Tracker";

void KarteTrackerCpp::track(const char* eventName,  const char* valuesJson) {
    jobject jJsonObject = KarteAndroidUtils::stringToJSONObject(valuesJson);
    if (nullptr == jJsonObject) {
        return;
    }

    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo track;
    if (cocos2d::JniHelper::getStaticMethodInfo(track, trackerClassName, "track", "(Ljava/lang/String;Lorg/json/JSONObject;)V"))
    {
        jstring jEventName = env->NewStringUTF(eventName);
        env->CallStaticVoidMethod(track.classID, track.methodID, jEventName, jJsonObject);
        env->DeleteLocalRef(jEventName);
    }
    env->DeleteLocalRef(jJsonObject);
}

void KarteTrackerCpp::identify(const char* valuesJson) {
    jobject jJsonObject = KarteAndroidUtils::stringToJSONObject(valuesJson);
    if (nullptr == jJsonObject) {
        return;
    }

    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo identify;
    if (cocos2d::JniHelper::getStaticMethodInfo(identify, trackerClassName, "identify", "(Lorg/json/JSONObject;)V"))
    {
        env->CallStaticVoidMethod(identify.classID, identify.methodID, jJsonObject);
    }
    env->DeleteLocalRef(jJsonObject);
}

void KarteTrackerCpp::view(const char* viewName, const char* title, const char* valuesJson) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jobject jJsonObject = KarteAndroidUtils::stringToJSONObject(valuesJson);
    if (nullptr == jJsonObject) {
        return;
    }

    cocos2d::JniMethodInfo view;
    if (cocos2d::JniHelper::getStaticMethodInfo(view, trackerClassName, "view", "(Ljava/lang/String;Ljava/lang/String;Lorg/json/JSONObject;)V")) {

        jstring jViewName = env->NewStringUTF(viewName);
        jstring jTitle = env->NewStringUTF(title);
        env->CallStaticVoidMethod(view.classID, view.methodID, jViewName, jTitle, jJsonObject);

        env->DeleteLocalRef(jViewName);
        env->DeleteLocalRef(jTitle);
    }
    env->DeleteLocalRef(jJsonObject);
}