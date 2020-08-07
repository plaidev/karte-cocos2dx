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
#ifndef KarteVariableCpp_h
#define KarteVariableCpp_h

class KarteVariableCpp {
private:
    const char* key;
    const char* campaignId;
    const char* shortenId;
    bool isDefined;
    const char* string;
    
public:
    void setKey(const char* key);
    void setCampaignId(const char* campaignId);
    void setShortenId(const char* shortenId);
    void setIsDefined(const bool isDefined);
    void setString(const char* string);

    const char * getKey() const;
    const char* getCampaignId();
    const char* getShortenId();
    bool getIsDefined();
    
    const char* getString(const char* defaultValue);
    bool getBool(const bool defaultValue);
    long long getInteger(const long defaultValue);
    double getDouble(const double defaultValue);
    
    KarteVariableCpp():
            key(nullptr), campaignId(nullptr), shortenId(nullptr), isDefined(), string(nullptr) {};
    KarteVariableCpp(const KarteVariableCpp &o);
    KarteVariableCpp& operator=(const KarteVariableCpp &o);
    ~KarteVariableCpp();
};

#endif /* KarteVariableCpp_h */
#endif
