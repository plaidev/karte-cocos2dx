//
//  KarteAppCpp.mm
//  Cocos2dxSample-mobile
//
//  Created by koichi tanaka on 2020/07/15.
//

#include "KarteAppCpp.h"
#include "KarteIOSUtils.h"
#include "KarteUtilCpp.h"

#import <KarteCore/KarteCore-Swift.h>

KarteAppCpp::KarteAppCpp() {
    NSString *visitorId = KRTApp.visitorId;
    this->visitorId = KarteIOSUtils::cstringWithNSString(visitorId);
}

KarteAppCpp& KarteAppCpp::operator=(const KarteAppCpp &o) {
    if (this != &o) {
        visitorId = KarteUtilCpp::copyString(o.visitorId);
    }
    return *this;
}

KarteAppCpp::KarteAppCpp(const KarteAppCpp &o) {
    this->visitorId = KarteUtilCpp::copyString(o.visitorId);
}

KarteAppCpp::~KarteAppCpp() {
    delete [] visitorId;
}

const char* KarteAppCpp::getVisitorId() {
    NSString *visitorId = KRTApp.visitorId;
    this->visitorId = KarteIOSUtils::cstringWithNSString(visitorId);
    return this->visitorId;
}

bool KarteAppCpp::isOptOut() {
    return KRTApp.isOptOut;
}

void KarteAppCpp::optIn() {
    [KRTApp optIn];
}

void KarteAppCpp::optOut() {
    [KRTApp optOut];
}

void KarteAppCpp::renewVisitorId() {
    [KRTApp renewVisitorId];
}
