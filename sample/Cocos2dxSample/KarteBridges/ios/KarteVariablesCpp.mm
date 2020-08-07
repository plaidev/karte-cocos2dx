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
#include "KarteIOSUtils.h"
#include "KarteUtilCpp.h"

#import <KarteCore//KarteCore-Swift.h>
#import <KarteVariables//KarteVariables-Swift.h>

void KarteVariablesCpp::fetchWithCompletion(std::function<void(bool)> completion) {
    [KRTVariables fetchWithCompletion:^(BOOL isSuccessful) {
        completion(isSuccessful);
    }];
}

KarteVariableCpp KarteVariablesCpp::variableForKey(const char* key) {
    NSString *nsKey = KarteIOSUtils::nsstringWithCString(key);
    KRTVariable *variable = [KRTVariables variableForKey:nsKey];

    auto variablecpp = KarteVariableCpp();
    variablecpp.setKey(KarteUtilCpp::copyString(key));
    variablecpp.setCampaignId(KarteIOSUtils::cstringWithNSString([variable campaignId]));
    variablecpp.setShortenId(KarteIOSUtils::cstringWithNSString([variable shortenId]));
    variablecpp.setIsDefined([variable isDefined]);
    variablecpp.setString(KarteIOSUtils::cstringWithNSString([variable string]));
    return variablecpp;
}

void KarteVariablesCpp::trackOpenWithVariables(const std::vector<KarteVariableCpp>& variables, const char* valuesJson) {
    NSMutableArray *mObjCVariableArray = [NSMutableArray array];
    for (auto itr = variables.begin(); itr != variables.end(); ++itr) {
        @autoreleasepool {
            auto cpp_variable = *itr;
            NSString *cId = KarteIOSUtils::nsstringWithCString(cpp_variable.getCampaignId());
            NSString *sId = KarteIOSUtils::nsstringWithCString(cpp_variable.getShortenId());
            
            KRTVariable *objcVariable = [[KRTVariable alloc] initWithName:@""];
            objcVariable.campaignId = cId;
            objcVariable.shortenId = sId;
            [mObjCVariableArray addObject:objcVariable];
        }
    }
    
    NSDictionary *values = KarteIOSUtils::nsdictionaryWithCStringJson(valuesJson);
    [KRTTracker trackOpenWithVariables:[mObjCVariableArray copy] values:values];
}

void KarteVariablesCpp::trackClickWithVariables(const std::vector<KarteVariableCpp>& variables, const char* valuesJson) {
    NSMutableArray *mObjCVariableArray = [NSMutableArray array];
    for (auto itr = variables.begin(); itr != variables.end(); ++itr) {
        @autoreleasepool {
            auto cpp_variable = *itr;
            NSString *cId = KarteIOSUtils::nsstringWithCString(cpp_variable.getCampaignId());
            NSString *sId = KarteIOSUtils::nsstringWithCString(cpp_variable.getShortenId());
            
            KRTVariable *objcVariable = [[KRTVariable alloc] initWithName:@""];
            objcVariable.campaignId = cId;
            objcVariable.shortenId = sId;
            [mObjCVariableArray addObject:objcVariable];
        }
    }
    
    NSDictionary *values = KarteIOSUtils::nsdictionaryWithCStringJson(valuesJson);
    [KRTTracker trackClickWithVariables:[mObjCVariableArray copy] values:values];
}
