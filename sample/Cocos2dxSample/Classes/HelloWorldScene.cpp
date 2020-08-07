/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "KarteCpp.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    
    CCLOG("visitorId is %s", KarteAppCpp().getVisitorId());
    if (KarteAppCpp::isOptOut()) {
        CCLOG("isOptOut is true");
    } else {
        CCLOG("isOptOut is false");
    }
        
//    CCLOG("appKey is %s", KarteTrackerCpp().getAppKey());
//    CCLOG("visitorId is %s", KarteTrackerCpp().getVisitorId());
    
    Size s = Director::getInstance()->getVisibleSize();
    float fontSize = 13.0;
    Menu* apiMenuLeft = Menu::create(
                                         MenuItemLabel::create(Label::createWithTTF("track", "fonts/Marker Felt.ttf", fontSize),
                                                               CC_CALLBACK_1(HelloWorld::track, this)),
                                         MenuItemLabel::create(Label::createWithTTF("view", "fonts/Marker Felt.ttf", fontSize),
                                                               CC_CALLBACK_1(HelloWorld::view, this)),
                                         MenuItemLabel::create(Label::createWithTTF("identity", "fonts/Marker Felt.ttf", fontSize),
                                                               CC_CALLBACK_1(HelloWorld::identity, this)),
                                         MenuItemLabel::create(Label::createWithTTF("fetchVariable", "fonts/Marker Felt.ttf", fontSize),
                                                               CC_CALLBACK_1(HelloWorld::fetchVariable, this)),
                                         MenuItemLabel::create(Label::createWithTTF("renewVisitorId", "fonts/Marker Felt.ttf", fontSize),
                                                               CC_CALLBACK_1(HelloWorld::renewVisitorId, this)),
                                         MenuItemLabel::create(Label::createWithTTF("optOut", "fonts/Marker Felt.ttf", fontSize),
                                                               CC_CALLBACK_1(HelloWorld::optOut, this)),
                                         MenuItemLabel::create(Label::createWithTTF("optIn", "fonts/Marker Felt.ttf", fontSize),
                                                               CC_CALLBACK_1(HelloWorld::optIn, this)),
                                         NULL);
    
    apiMenuLeft->setPosition(Vec2(s.width / 4, s.height*0.8f));
    apiMenuLeft->alignItemsVerticallyWithPadding(10);
    this->addChild(apiMenuLeft);
    
    Menu* apiMenuRight = Menu::create(
                                      MenuItemLabel::create(Label::createWithTTF("dismiss", "fonts/Marker Felt.ttf", fontSize),
                                                            CC_CALLBACK_1(HelloWorld::dismissInAppMessage, this)),
                                      MenuItemLabel::create(Label::createWithTTF("isPresenting", "fonts/Marker Felt.ttf", fontSize),
                                                            CC_CALLBACK_1(HelloWorld::isPresentingMessage, this)),
                                      MenuItemLabel::create(Label::createWithTTF("suppress", "fonts/Marker Felt.ttf", fontSize),
                                                            CC_CALLBACK_1(HelloWorld::suppressInAppMessage, this)),
                                      MenuItemLabel::create(Label::createWithTTF("unsuppress", "fonts/Marker Felt.ttf", fontSize),
                                                            CC_CALLBACK_1(HelloWorld::unsuppressInAppMessage, this)),
                                      MenuItemLabel::create(Label::createWithTTF("webUserSync", "fonts/Marker Felt.ttf", fontSize),
                                                            CC_CALLBACK_1(HelloWorld::webUserSync, this)),
                                      MenuItemLabel::create(Label::createWithTTF("push", "fonts/Marker Felt.ttf", fontSize),
                                                            CC_CALLBACK_1(HelloWorld::push, this)),
                                      MenuItemLabel::create(Label::createWithTTF("chat", "fonts/Marker Felt.ttf", fontSize),
                                                            CC_CALLBACK_1(HelloWorld::chat, this)),
                                     NULL);
    
    apiMenuRight->setPosition(Vec2(s.width * 0.85f, s.height*0.8f));
    apiMenuRight->alignItemsVerticallyWithPadding(10);

    this->addChild(apiMenuRight);
    
    return true;
}

void HelloWorld::track(Ref* pSender)
{
    auto values = R"({"stage_name": "1st_stage", "game_score": 200, "sample_ratio": 74.35, "bonus_item": null })";
    KarteTrackerCpp::track("game_clear", values);
}

void HelloWorld::view(Ref* pSender)
{
    auto values = R"({"stage_name": "1st_stage", "game_score": 200, "sample_ratio": 74.35, "bonus_item": null })";
    KarteTrackerCpp::view("cocosTopPage", "cocosTopPage", values);
}

void HelloWorld::identity(Ref* pSender)
{
    auto values = R"({"stage_name": "1st_stage", "game_score": 200, "sample_ratio": 74.35, "bonus_item": null })";
    KarteTrackerCpp::identify(values);
}

void HelloWorld::fetchVariable(Ref* pSender)
{
    KarteVariablesCpp::fetchWithCompletion([](bool isSuccess){
        if (isSuccess) {
            auto undefinedVar = KarteVariablesCpp::variableForKey("undefined_variable");
            CCLOG("undefinedVar campaignId is %s", undefinedVar.getCampaignId());
            CCLOG("undefinedVar shortenId is %s", undefinedVar.getShortenId());
            CCLOG("undefinedVar isDefined is %d", undefinedVar.getIsDefined());
            CCLOG("undefinedVar getKey is %s", undefinedVar.getKey());
            CCLOG("undefinedVar getString is %s", undefinedVar.getString("default"));
            CCLOG("undefinedVar getString with nullptr is %s", undefinedVar.getString(nullptr));
            CCLOG("undefinedVar getString with NULL is %s", undefinedVar.getString(NULL));
            CCLOG("undefinedVar getString with array json is %s", undefinedVar.getString(R"(["a","b"])"));
            CCLOG("undefinedVar getString with dictionary json is %s", undefinedVar.getString(R"({"a":"b"})"));
            CCLOG("undefinedVar getBool is %d", undefinedVar.getBool(false));
            CCLOG("undefinedVar getInteger is %lld", undefinedVar.getInteger(10));
            CCLOG("undefinedVar getDouble is %f", undefinedVar.getDouble(0.1));

            auto variable1 = KarteVariablesCpp::variableForKey("string_var1");
            CCLOG("variable1 campaignId is %s", variable1.getCampaignId());
            CCLOG("variable1 shortenId is %s", variable1.getShortenId());
            CCLOG("variable1 isDefined is %d", variable1.getIsDefined());
            auto string = variable1.getString("default value");
            CCLOG("variable string_var1 is %s", string);

            auto variable1IntegerValue = variable1.getInteger(100);
            CCLOG("variable string_var1 ref with integer is %lld", variable1IntegerValue);

            auto variable1DoubleValue = variable1.getDouble(0.1);
            CCLOG("variable string_var1 ref with double is %lf", variable1DoubleValue);

            auto variable2 = KarteVariablesCpp::variableForKey("json_var2");
            auto defaultDictionaryJson = R"({ "test-key":"test-value" })";
            auto dict = variable2.getString(defaultDictionaryJson);
            CCLOG("variable json_var2 is %s", dict);

            auto variable3 = KarteVariablesCpp::variableForKey("long_var2");
            auto integer = variable3.getInteger(99);
            CCLOG("variable long_var2 is %lld", integer);

            auto variable3DefaultDouble = KarteVariablesCpp::variableForKey("long_var2");
            auto variable3DefaultDoubleValue = variable3DefaultDouble.getDouble(0.1);
            CCLOG("variable long_var2 ref with double is %lf", variable3DefaultDoubleValue);

            auto variable3DefaultString = KarteVariablesCpp::variableForKey("long_var2");
            auto variable3DefaultStringValue = variable3DefaultString.getString("");
            CCLOG("variable long_var2 ref with string is %s", variable3DefaultStringValue);

            auto variable4 = KarteVariablesCpp::variableForKey("array_var5");
            auto defaultArrayJson = R"(["testArrayValue1","testArrayValue2"])";
            auto array = variable4.getString(defaultArrayJson);
            CCLOG("variable array_var5 is %s", array);

            auto variable5 = KarteVariablesCpp::variableForKey("double_var1");
            auto doubleValue = variable5.getDouble(0.1);
            CCLOG("variable double_var1 is %f", doubleValue);

            auto variable6 = KarteVariablesCpp::variableForKey("boolean_var3");
            auto boolValue = variable6.getBool(false);
            CCLOG("variable boolean_var3 is %d", boolValue);

            std::vector<KarteVariableCpp> variables{undefinedVar, variable1, variable2, variable3, variable4, variable5, variable6};
            KarteVariablesCpp::trackOpenWithVariables(variables, R"({"test-key":"test-value"})");
            KarteVariablesCpp::trackClickWithVariables(variables, R"({"test-key":"test-value"})");
        }
    });
}

void HelloWorld::renewVisitorId(Ref* pSender) {
    CCLOG("before renew visitorId is %s", KarteAppCpp().getVisitorId());
    KarteAppCpp::renewVisitorId();
    CCLOG("after renew visitorId is %s", KarteAppCpp().getVisitorId());
}

void HelloWorld::optOut(Ref* pSender) {
    KarteAppCpp::optOut();
}

void HelloWorld::optIn(Ref* pSender) {
    KarteAppCpp::optIn();
}

void HelloWorld::dismissInAppMessage(Ref* pSender) {
    KarteInAppMessagingCpp::dismiss();
}

void HelloWorld::isPresentingMessage(Ref* pSender) {
    if (KarteInAppMessagingCpp::isPresenting()) {
        CCLOG("isPresenting = true");
    } else {
        CCLOG("isPresenting = false");
    }
}

void HelloWorld::suppressInAppMessage(cocos2d::Ref *pSender) {
    KarteInAppMessagingCpp::suppress();
}

void HelloWorld::unsuppressInAppMessage(cocos2d::Ref *pSender) {
    KarteInAppMessagingCpp::unsuppress();
}

void HelloWorld::webUserSync(cocos2d::Ref *pSender) {
    const char* url = "https://example.com";
    CCLOG("User sync url is %s", KarteUserSyncCpp(url).getUrlString());
}

void HelloWorld::push(cocos2d::Ref *pSender) {
    auto values = R"({"stage_name": "1st_stage", "game_score": 200, "sample_ratio": 74.35, "bonus_item": null })";
    KarteTrackerCpp::view("push_text", "push_text", values);
}

void HelloWorld::chat(cocos2d::Ref *pSender) {
    KarteTrackerCpp::view("chat", "chat", nullptr);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
