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
#include "KarteVariablesCpp.h"

#include "platform/android/jni/JniHelper.h"
#include "KarteAndroidUtils.h"
#include "KarteVariableCpp.h"
#include "KarteUtilCpp.h"

#include <jni.h>

jstring stringField(JNIEnv *env, jclass variable_class, jobject variable, const char* fieldName) {
    jfieldID fieldId = env->GetFieldID(variable_class, fieldName, "Ljava/lang/String;");
    if (fieldId == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "Karte.Variables", "Field Id not found: %s", fieldName);
        return nullptr;
    }
    return (jstring) env->GetObjectField(variable, fieldId);
}

jboolean booleanField(JNIEnv *env, jclass variable_class, jobject variable, const char* fieldName) {
    jfieldID fieldId = env->GetFieldID(variable_class, fieldName, "Z");
    if (fieldId == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "Karte.Variables", "Field Id not found: %s", fieldName);
        return false;
    }
    return env->GetBooleanField(variable, fieldId);
}


jobject makeCallback(std::function<void(bool)>* completion) {
    auto wrapper = new CallbackWrapper<void, bool>(*completion);
    JNIEnv* env = KarteAndroidUtils::getEnv();
    cocos2d::JniMethodInfo constructor;
    if (cocos2d::JniHelper::getMethodInfo(constructor, "io/karte/android/cocos2dx/FetchVariablesCompletionHandler", "<init>", "([B)V")) {
        void *buffer = wrapper;
        jbyteArray pointer = env->NewByteArray(sizeof(void*));
        env->SetByteArrayRegion(pointer, 0, sizeof(void*), (jbyte*)&buffer);
        jobject callback = env->NewObject(constructor.classID, constructor.methodID, pointer);
        env->DeleteLocalRef(pointer);
        return callback;
    }
    return nullptr;
}

void KarteVariablesCpp::fetchWithCompletion(std::function<void(bool)> completion) {
    JNIEnv* env = KarteAndroidUtils::getEnv();
    jclass jVariablesClass = KarteAndroidUtils::getVariablesClass();
    if (nullptr == jVariablesClass)
        return;
    jobject callback = makeCallback(&completion);
    if (nullptr == callback) {
        env->DeleteLocalRef(jVariablesClass);
        return;
    }

    cocos2d::JniMethodInfo fetch;
    if (cocos2d::JniHelper::getStaticMethodInfo(fetch, KarteAndroidUtils::variablesClassName, "fetch", "(Lio/karte/android/variables/FetchCompletion;)V")) {
        env->CallStaticVoidMethod(jVariablesClass, fetch.methodID, callback);
    }
    env->DeleteLocalRef(jVariablesClass);
    env->DeleteLocalRef(callback);
}

KarteVariableCpp KarteVariablesCpp::variableForKey(const char* key) {
    KarteVariableCpp variable = KarteVariableCpp();
    variable.setKey(KarteUtilCpp::copyString(key));

    JNIEnv* env = KarteAndroidUtils::getEnv();
    jclass jVariableClass = env->FindClass(KarteAndroidUtils::variableClassName);
    if (jVariableClass == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "Karte.Variables", "Class not found: %s", KarteAndroidUtils::variableClassName);
        return variable;
    }

    jobject jVariable = KarteAndroidUtils::getVariable(variable.getKey());
    if (jVariable == nullptr) {
        env->DeleteLocalRef(jVariableClass);
        return variable;
    }

    auto jCampaignId = stringField(env, jVariableClass, jVariable, "campaignId");
    if (jCampaignId == nullptr) {
        env->DeleteLocalRef(jVariableClass);
        env->DeleteLocalRef(jVariable);
        return variable;
    }
    variable.setCampaignId(KarteAndroidUtils::jStringToCString(jCampaignId));
    env->DeleteLocalRef(jCampaignId);

    auto jShortenId = stringField(env, jVariableClass, jVariable, "shortenId");
    if (jShortenId == nullptr) {
        env->DeleteLocalRef(jVariableClass);
        env->DeleteLocalRef(jVariable);
        env->DeleteLocalRef(jCampaignId);
        return variable;
    }
    variable.setShortenId(KarteAndroidUtils::jStringToCString(jShortenId));
    env->DeleteLocalRef(jShortenId);

    auto jIsDefined = booleanField(env, jVariableClass, jVariable, "isDefined");
    variable.setIsDefined(bool(jIsDefined));

    env->DeleteLocalRef(jVariableClass);
    env->DeleteLocalRef(jVariable);
    return variable;
}

void trackWithVariables(const std::vector<KarteVariableCpp>& variables, const char* valuesJson, const char* methodName) {
    JNIEnv* env = KarteAndroidUtils::getEnv();

    jclass jVariablesClass = env->FindClass(KarteAndroidUtils::variablesClassName);
    if (jVariablesClass == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "Karte.Variables", "Class not found: %s", KarteAndroidUtils::variablesClassName);
        return;
    }

    jobject jVariableList = nullptr;
    cocos2d::JniMethodInfo constructor;
    if (cocos2d::JniHelper::getMethodInfo(constructor, "java/util/ArrayList", "<init>", "()V")) {
        jVariableList = env->NewObject(constructor.classID, constructor.methodID);
        cocos2d::JniMethodInfo add;
        if (cocos2d::JniHelper::getMethodInfo(add, "java/util/ArrayList", "add", "(Ljava/lang/Object;)Z")) {
            for (const auto &var : variables) {
                jobject jVar = KarteAndroidUtils::getVariable(var.getKey());
                env->CallBooleanMethod(jVariableList, add.methodID, jVar);
                env->DeleteLocalRef(jVar);
            }
        }
    }
    if (nullptr == jVariableList) {
        env->DeleteLocalRef(jVariablesClass);
        return;
    }

    jobject jJsonObject = KarteAndroidUtils::stringToJSONObject(valuesJson);
    if (nullptr == jJsonObject) {
        env->DeleteLocalRef(jVariablesClass);
        env->DeleteLocalRef(jVariableList);
        return;
    }

    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, KarteAndroidUtils::variablesClassName, methodName, "(Ljava/util/List;Lorg/json/JSONObject;)V")) {
        env->CallStaticVoidMethod(jVariablesClass, methodInfo.methodID, jVariableList, jJsonObject);
    }

    env->DeleteLocalRef(jVariablesClass);
    env->DeleteLocalRef(jVariableList);
    env->DeleteLocalRef(jJsonObject);
}

void KarteVariablesCpp::trackOpenWithVariables(const std::vector<KarteVariableCpp>& variables, const char* valuesJson) {
    trackWithVariables(variables, valuesJson, "trackOpen");
}

void KarteVariablesCpp::trackClickWithVariables(const std::vector<KarteVariableCpp>& variables, const char* valuesJson) {
    trackWithVariables(variables, valuesJson, "trackClick");
}

extern "C" JNIEXPORT void JNICALL
Java_io_karte_android_cocos2dx_FetchVariablesCompletionHandler_onCompletedNative(
        JNIEnv *env, jobject instance, jboolean jIsSuccess, jbyteArray jCallback) {
    void *pointer;
    env->GetByteArrayRegion(jCallback, 0, sizeof(pointer), (jbyte *) &pointer);
    auto wrapper = static_cast<CallbackWrapper<void, bool> *>(pointer);
    wrapper->callback((bool) jIsSuccess);
    delete wrapper;
}
