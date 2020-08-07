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
#include "KarteIOSUtils.h"

#import <KarteCore/KarteCore-Swift.h>

void KarteTrackerCpp::track(const char* eventName,  const char* valuesJson) {
    NSString *nsEventName = KarteIOSUtils::nsstringWithCString(eventName);
    NSDictionary *values = KarteIOSUtils::nsdictionaryWithCStringJson(valuesJson);
    [KRTTracker track:nsEventName values:values];
}

void KarteTrackerCpp::identify(const char* valuesJson) {
    NSDictionary *dictionaryValues = KarteIOSUtils::nsdictionaryWithCStringJson(valuesJson);
    [KRTTracker identify:dictionaryValues];
}

void KarteTrackerCpp::view(const char* viewName, const char* title, const char* valuesJson) {
    NSString *nsViewName = KarteIOSUtils::nsstringWithCString(viewName) ?: @"";
    NSString *nsViewTitle = KarteIOSUtils::nsstringWithCString(title) ?: @"";
    NSDictionary *values = KarteIOSUtils::nsdictionaryWithCStringJson(valuesJson);
    [KRTTracker view:nsViewName title:nsViewTitle values:values];
}
