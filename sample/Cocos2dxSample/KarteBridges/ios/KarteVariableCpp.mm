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
#include "KarteUtilCpp.h"
#include "KarteIOSUtils.h"

#import <KarteCore//KarteCore-Swift.h>
#import <KarteVariables//KarteVariables-Swift.h>

NSString *const KarteDefaultValueNull = @"krt_default_value_null";

void KarteVariableCpp::setKey(const char* key) {
    this->key = key;
}

void KarteVariableCpp::setCampaignId(const char* campaignId) {
    this->campaignId = campaignId;
}

void KarteVariableCpp::setShortenId(const char* shortenId) {
    this->shortenId = shortenId;
}

void KarteVariableCpp::setIsDefined(const bool isDefined) {
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
    auto k = KarteIOSUtils::nsstringWithCString(key);
    KRTVariable *variable = [KRTVariables variableForKey:k];
    NSString *nsStr = KarteIOSUtils::nsstringWithCString(defaultValue);
    if (!nsStr) {
        // Workaround for an issue where passing nil to a Swift nonnull argument from ObjC results in an empty character.
        nsStr = KarteDefaultValueNull;
    }
    NSString *str = [variable stringWithDefaultValue:nsStr];
    if ([str isEqualToString:KarteDefaultValueNull]) {
        return nullptr;
    }
    return this->string;
}

bool KarteVariableCpp::getBool(const bool defaultValue) {
    auto k = KarteIOSUtils::nsstringWithCString(key);
    KRTVariable *variable = [KRTVariables variableForKey:k];
    return [variable boolWithDefaultValue:defaultValue];
}

long long KarteVariableCpp::getInteger(const long defaultValue) {
    auto k = KarteIOSUtils::nsstringWithCString(key);
    KRTVariable *variable = [KRTVariables variableForKey:k];
    return [variable integerWithDefaultValue:defaultValue];
}

double KarteVariableCpp::getDouble(const double defaultValue) {
    auto k = KarteIOSUtils::nsstringWithCString(key);
    KRTVariable *variable = [KRTVariables variableForKey:k];
    return [variable doubleWithDefaultValue:defaultValue];
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
