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
#include "KarteIOSUtils.h"
#include "KarteUtilCpp.h"

#import <KarteCore/KarteCore-Swift.h>

KarteUserSyncCpp::KarteUserSyncCpp(const char* urlString) {
    NSString *nsurlString = KarteIOSUtils::nsstringWithCString(urlString);
    NSURL *nsurl = [NSURL URLWithString:nsurlString];
    NSURL *nssyncURL = [KRTUserSync appendingQueryParameterWithURL:nsurl];
    this->urlString = KarteIOSUtils::cstringWithNSString(nssyncURL.absoluteString);
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

const char* KarteUserSyncCpp::getUrlString() {
    return this->urlString;
}
