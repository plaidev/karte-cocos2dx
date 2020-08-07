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
#ifndef PROJ_ANDROID_KARTEANDROIDUTILS_H
#define PROJ_ANDROID_KARTEANDROIDUTILS_H

#include <jni.h>
#include <functional>


class KarteAndroidUtils {
public:
    static const char* appClassName;
    static const char* variableClassName;
    static const char* variablesClassName;

    static jclass getVariablesClass();
    static jobject getVariable(const char* key);

    static jobject stringToJSONObject(const char* jsonString);
    static jstring JSONObjectToString(jobject jJsonObject);
    static jstring JSONArrayToString(jobject jJsonArray);
    static const char* jStringToCString(jstring jString);

    static JNIEnv* getEnv();
    static jobject getContext();
};

template <typename Rtn, typename... Args>
class CallbackWrapper {
private:
    std::function<Rtn(Args...)> _func;
public:
    CallbackWrapper(std::function<Rtn(Args...)> func) : _func(func) {}
    ~CallbackWrapper() = default;
    Rtn callback(Args... args) { return _func(args...); }
};

#endif //PROJ_ANDROID_KARTEANDROIDUTILS_H
