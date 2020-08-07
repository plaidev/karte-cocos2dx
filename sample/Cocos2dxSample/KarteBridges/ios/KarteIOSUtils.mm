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
#include "KarteIOSUtils.h"

const char* KarteIOSUtils::cstringWithNSString(NSString* nsstring) {
    if (![nsstring isKindOfClass:[NSString class]]) {
        return nullptr;
    }
    return strdup([nsstring UTF8String]);
}

const char* KarteIOSUtils::cstringJsonWithNSArray(NSArray *array) {
    if (![array isKindOfClass:[NSArray class]]) {
        return nullptr;
    }
    return cstringJsonWithContainer(array);
}

const char* KarteIOSUtils::cstringJsonWithNSDictionary(NSDictionary *dictionary) {
    if (![dictionary isKindOfClass:[NSDictionary class]]) {
        return nullptr;
    }
    return cstringJsonWithContainer(dictionary);
}

NSString* KarteIOSUtils::nsstringWithCString(const char* cstring) {
    if (!cstring) {
        return nil;
    }
    return [NSString stringWithUTF8String:cstring];
}

NSArray* KarteIOSUtils::nsarrayWithCStringJson(const char* cstring) {
    if (!cstring) {
        return nil;
    }
    NSString* json = nsstringWithCString(cstring);
    NSData* data = [json dataUsingEncoding:NSUTF8StringEncoding];
    if (!data) {
        return nil;
    }
    
    NSError *error = nil;
    id jsonObject = [NSJSONSerialization JSONObjectWithData:data
                                                    options:kNilOptions
                                                      error:&error];
    if (error || ![jsonObject isKindOfClass:[NSArray class]]) {
        return nil;
    }
    return jsonObject;
}

NSDictionary* KarteIOSUtils::nsdictionaryWithCStringJson(const char* cstring) {
    if (!cstring) {
        return nil;
    }
    NSString* json = nsstringWithCString(cstring);
    NSData* data = [json dataUsingEncoding:NSUTF8StringEncoding];
    if (!data) {
        return nil;
    }
    
    NSError *error = nil;
    id jsonObject = [NSJSONSerialization JSONObjectWithData:data
                                                    options:kNilOptions
                                                      error:&error];
    if (error || ![jsonObject isKindOfClass:[NSDictionary class]]) {
        return nil;
    }
    return jsonObject;
}


const char* KarteIOSUtils::cstringJsonWithContainer(id container) {
    if (![NSJSONSerialization isValidJSONObject:container]) {
        return nullptr;
    }
    
    NSError *error = nil;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:container
                                                       options:kNilOptions
                                                         error:&error];
    if (!jsonData || error) {
        return nullptr;
    }
    NSString *nsStringJson = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    const char* cStringJson = cstringWithNSString(nsStringJson);
    
    return cStringJson;
}

