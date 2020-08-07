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
#include "KarteUserSyncCpp.h"
#include "KarteAndroidUtils.h"
#include "KarteUtilCpp.h"

#include <jni.h>
#include <cocos/platform/android/jni/JniHelper.h>

const char* userSyncClassName = "io/karte/android/core/usersync/UserSync";

const char* KarteUserSyncCpp::getUrlString() {
    return this->urlString;
}

KarteUserSyncCpp::KarteUserSyncCpp(const char* urlString) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo appendUserSyncQueryParameter;
    if (cocos2d::JniHelper::getStaticMethodInfo(appendUserSyncQueryParameter, userSyncClassName, "appendUserSyncQueryParameter", "(Ljava/lang/String;)Ljava/lang/String;")) {
        jstring jUrlString = env->NewStringUTF(urlString);
        jstring jString = (jstring) env->CallStaticObjectMethod(appendUserSyncQueryParameter.classID, appendUserSyncQueryParameter.methodID, jUrlString);

        this->urlString = KarteAndroidUtils::jStringToCString(jString);

        env->DeleteLocalRef(jString);
        env->DeleteLocalRef(jUrlString);
    }
}

KarteUserSyncCpp& KarteUserSyncCpp::operator=(const KarteUserSyncCpp &o) {
    if (this != &o) {
        urlString = KarteUtilCpp::copyString(o.urlString);
    }
    return *this;
}

KarteUserSyncCpp::KarteUserSyncCpp(const KarteUserSyncCpp &o) {
    this->urlString = KarteUtilCpp::copyString(o.urlString);
}

KarteUserSyncCpp::~KarteUserSyncCpp() {
    delete [] urlString;
}