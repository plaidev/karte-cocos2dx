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
#include "KarteVariableCpp.h"

#include "KarteAndroidUtils.h"
#include "KarteVariablesCpp.h"
#include "KarteUtilCpp.h"
#include "platform/android/jni/JniHelper.h"

static const char* const KRT_DEFAULT_VALUE_NULL = "krt_default_value_null";

void KarteVariableCpp::setKey(const char* key) {
    this->key = key;
}

void KarteVariableCpp::setCampaignId(const char* campaignId) {
    this->campaignId = campaignId;
}

void KarteVariableCpp::setShortenId(const char* shortenId) {
    this->shortenId = shortenId;
}

void KarteVariableCpp::setIsDefined(bool isDefined) {
    this->isDefined = isDefined;
}

void KarteVariableCpp::setString(const char* string) {
    this->string = string;
}

const char * KarteVariableCpp::getKey() const {
    return this->key;
}

const char* KarteVariableCpp::getCampaignId() {
    return this->campaignId;
}

const char* KarteVariableCpp::getShortenId() {
    return this->shortenId;
}

bool KarteVariableCpp::getIsDefined() {
    return this->isDefined;
}

const char* KarteVariableCpp::getString(const char* defaultValue) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jobject jVariable = KarteAndroidUtils::getVariable(key);
    if (nullptr == jVariable)
        return defaultValue;

    cocos2d::JniMethodInfo getString;
    if (cocos2d::JniHelper::getMethodInfo(getString, KarteAndroidUtils::variableClassName, "getString", "(Ljava/lang/String;)Ljava/lang/String;")) {
        jstring jDefaultString = env->NewStringUTF(defaultValue);
        if (defaultValue == nullptr) {
            jDefaultString = env->NewStringUTF(KRT_DEFAULT_VALUE_NULL);
        }
        jstring jString = (jstring) env->CallObjectMethod(jVariable, getString.methodID, jDefaultString);
        if (strcmp(KarteAndroidUtils::jStringToCString(jString), KRT_DEFAULT_VALUE_NULL) == 0) {
            env->DeleteLocalRef(jString);
            env->DeleteLocalRef(jDefaultString);
            env->DeleteLocalRef(jVariable);

            this->string = nullptr;
            return this->string;
        }

        this->string = KarteAndroidUtils::jStringToCString(jString);

        env->DeleteLocalRef(jString);
        env->DeleteLocalRef(jDefaultString);
        env->DeleteLocalRef(jVariable);
    }

    return this->string;
}

bool KarteVariableCpp::getBool(const bool defaultValue) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jobject jVariable = KarteAndroidUtils::getVariable(key);
    if (nullptr == jVariable)
        return defaultValue;

    bool value = defaultValue;
    cocos2d::JniMethodInfo getBoolean;
    if (cocos2d::JniHelper::getMethodInfo(getBoolean, KarteAndroidUtils::variableClassName, "getBoolean", "(Z)Z")) {
        value = env->CallBooleanMethod(jVariable, getBoolean.methodID, defaultValue);
    }
    env->DeleteLocalRef(jVariable);
    return value;
}

long long KarteVariableCpp::getInteger(const long defaultValue) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jobject jVariable = KarteAndroidUtils::getVariable(key);
    if (nullptr == jVariable)
        return defaultValue;

    long long value = defaultValue;
    cocos2d::JniMethodInfo getLong;
    if (cocos2d::JniHelper::getMethodInfo(getLong, KarteAndroidUtils::variableClassName, "getLong", "(J)J")) {
        value = (long long) env->CallLongMethod(jVariable, getLong.methodID, (jlong)defaultValue);
    }
    env->DeleteLocalRef(jVariable);
    return value;
}

double KarteVariableCpp::getDouble(const double defaultValue = 0.0) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jobject jVariable = KarteAndroidUtils::getVariable(key);
    if (nullptr == jVariable)
        return defaultValue;

    double value = defaultValue;
    cocos2d::JniMethodInfo getDouble;
    if (cocos2d::JniHelper::getMethodInfo(getDouble, KarteAndroidUtils::variableClassName, "getDouble", "(D)D")) {
        value = env->CallDoubleMethod(jVariable, getDouble.methodID, defaultValue);
    }
    env->DeleteLocalRef(jVariable);
    return value;
}

KarteVariableCpp::KarteVariableCpp(const KarteVariableCpp &o) {
    this->key = KarteUtilCpp::copyString(o.key);
    this->campaignId = KarteUtilCpp::copyString(o.campaignId);
    this->shortenId = KarteUtilCpp::copyString(o.shortenId);
    this->string = KarteUtilCpp::copyString(o.string);
}

KarteVariableCpp& KarteVariableCpp::operator=(const KarteVariableCpp &o) {
    if (this != &o) {
        this->key = KarteUtilCpp::copyString(o.key);
        this->campaignId = KarteUtilCpp::copyString(o.campaignId);
        this->shortenId = KarteUtilCpp::copyString(o.shortenId);
        this->string = KarteUtilCpp::copyString(o.string);
    }
    return *this;
}

KarteVariableCpp::~KarteVariableCpp() {
    delete [] key;
    delete [] campaignId;
    delete [] shortenId;
    delete [] string;
}
