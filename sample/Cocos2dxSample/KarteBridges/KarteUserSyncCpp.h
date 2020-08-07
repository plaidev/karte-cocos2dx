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
#ifdef __cplusplus
#ifndef KarteUserSyncCpp_h
#define KarteUserSyncCpp_h

class KarteUserSyncCpp {
private:
    const char* urlString;
public:
    KarteUserSyncCpp(const char* urlString);
    KarteUserSyncCpp& operator=(const KarteUserSyncCpp &o);
    KarteUserSyncCpp(const KarteUserSyncCpp &o);
    ~KarteUserSyncCpp();
    
    const char* getUrlString();
};

#endif /* KarteUserSyncCpp_h */
#endif
