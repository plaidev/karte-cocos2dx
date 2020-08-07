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
#include "KarteCocosCompat.h"
#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"

#include <pthread.h>

#define  LOG_TAG    "Karte.CocosCompat"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static pthread_key_t g_key = 0;
jobject KarteCocosCompat::_context = nullptr;

#if COCOS2D_VERSION >= 0x00030000
#define COCOS2D_V3 1
#endif

#if COCOS2D_VERSION >= 0x00031200
#define COCOS2D_V3_12 1
#endif


void _detachCurrentThreadForCompat(void* env) {
    cocos2d::JniHelper::getJavaVM()->DetachCurrentThread();
}

static JNIEnv* cacheEnv(JavaVM* jvm) {
    JNIEnv* _env = nullptr;
    // get jni environment
    jint ret = jvm->GetEnv((void**)&_env, JNI_VERSION_1_4);

    switch (ret) {
        case JNI_OK :
            // Success!
            pthread_setspecific(g_key, _env);
            return _env;

        case JNI_EDETACHED :
            // Thread not attached
            if (jvm->AttachCurrentThread(&_env, nullptr) < 0)
            {
                LOGE("Failed to get the environment using AttachCurrentThread()");

                return nullptr;
            } else {
                // Success : Attached and obtained JNIEnv!
                pthread_setspecific(g_key, _env);
                return _env;
            }

        case JNI_EVERSION :
            // Cannot recover from this error
            LOGE("JNI interface version 1.4 not supported");
        default :
            LOGE("Failed to get the environment using GetEnv()");
            return nullptr;
    }
}

static JNIEnv* getEnv_(JavaVM* jvm) {
    auto* _env = (JNIEnv *)pthread_getspecific(g_key);
    if (_env == nullptr)
        _env = cacheEnv(jvm);
    return _env;
}

JNIEnv* KarteCocosCompat::getEnv() {
#ifdef COCOS2D_V3
    return cocos2d::JniHelper::getEnv();
#else
    JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
    if (g_key == 0)
        pthread_key_create(&g_key, _detachCurrentThreadForCompat);
    return getEnv_(jvm);
#endif
}

jobject KarteCocosCompat::getContext() {
#ifdef COCOS2D_V3_12
    return cocos2d::JniHelper::getActivity();
#else
    if (nullptr == _context) {
        JNIEnv* env = getEnv();
        const char* className = "org/cocos2dx/lib/Cocos2dxHelper";
        jclass helper = env->FindClass(className);
        if (nullptr == helper) {
            LOGE("Failed to find class %s", className);
            return nullptr;
        }
#ifdef COCOS2D_V3
        const char* fieldName = "sActivity";
        jfieldID fieldId = env->GetStaticFieldID(helper, fieldName, "Landroid/app/Activity;");
#else
        const char* fieldName = "sContext";
        jfieldID fieldId = env->GetStaticFieldID(helper, fieldName, "Landroid/content/Context;");
#endif;
        if (nullptr == fieldId) {
            LOGE("Failed to find static method id of %s", fieldName);
            env->ExceptionClear();
            return nullptr;
        }
        jobject context = env->GetStaticObjectField(helper, fieldId);
        _context = env->NewGlobalRef(context);
    }
    return _context;
#endif
}