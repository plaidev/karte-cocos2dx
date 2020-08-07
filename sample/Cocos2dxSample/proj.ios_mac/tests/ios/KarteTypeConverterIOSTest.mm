//
//  KarteTypeConverterIOSTest.mm
//  Cocos2dxSample-mobileTests
//
//  Created by Koichi Tanaka on 2019/05/21.
//

#import <XCTest/XCTest.h>
#include "KarteIOSUtils.h"
#include "KarteUtilCpp.h"

@interface KarteTypeConverterIOSTest : XCTestCase

@end

@implementation KarteTypeConverterIOSTest

- (void)setUp {
    [super setUp];
}

- (void)tearDown {
    [super tearDown];
}

- (void)testNSStringWithCString {
    [XCTContext runActivityNamed:@"CのASCII文字列がNSStringに変換できること" block:^(id<XCTActivity>  _Nonnull activity) {
        const char* cstr = "abc";
        XCTAssert([KarteIOSUtils::nsstringWithCString(cstr) isEqualToString:@"abc"]);
    }];
    
    [XCTContext runActivityNamed:@"Cの空文字列がNSStringに変換できること" block:^(id<XCTActivity>  _Nonnull activity) {
        const char* cstr = "";
        XCTAssert([KarteIOSUtils::nsstringWithCString(cstr) isEqualToString:@""]);
    }];
    
    [XCTContext runActivityNamed:@"NULLが渡された時にnilが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
        const char* cstr = NULL;
        XCTAssert(KarteIOSUtils::nsstringWithCString(cstr) == nil);
    }];
    
    [XCTContext runActivityNamed:@"マルチバイト文字列が渡された時にNSStringに変換できること" block:^(id<XCTActivity>  _Nonnull activity) {
        const char* cstr = "家族の絵文字👪";
        XCTAssert([KarteIOSUtils::nsstringWithCString(cstr) isEqualToString:@"家族の絵文字👪"]);
    }];
    
    [XCTContext runActivityNamed:@"NULL文字が複数出現する文字列が渡されてもNSStringに変換できること" block:^(id<XCTActivity>  _Nonnull activity) {
        // Multiple Null-terminated string tests
        char cstr[4] = "abc"; //a,b,c,\0
        cstr[1] = '\0'; //a,\0,c,\0
        XCTAssert([KarteIOSUtils::nsstringWithCString(cstr) isEqualToString:@"a"]);
    }];
}

- (void)testCstringWithNSString {
    [XCTContext runActivityNamed:@"NSStringの文字列が渡された時にNULL終端されたC文字列が返されること" block:^(id<XCTActivity>  _Nonnull activity) {
        NSString* nsstr = @"abc";
        const char* cstr = KarteIOSUtils::cstringWithNSString(nsstr);
        XCTAssert(strcmp(cstr, "abc") == 0,  @"%s is not equal %s", cstr, "abc");
        XCTAssert(cstr[strlen(cstr)] == '\0',  @"%s is not terminated with null string", cstr);
    }];
    
    [XCTContext runActivityNamed:@"空文字が渡された時は空文字が返されること" block:^(id<XCTActivity>  _Nonnull activity) {
        NSString* nsstr = @"";
        const char* cstr = KarteIOSUtils::cstringWithNSString(nsstr);
        XCTAssert(strcmp(cstr, "") == 0,  @"%s is not equal %s", cstr, "");
    }];
    
    [XCTContext runActivityNamed:@"マルチバイト文字列が渡された時に同様のC文字列が返されること" block:^(id<XCTActivity>  _Nonnull activity) {
        NSString* nsstr = @"家族の絵文字👪";
        const char* cstr = KarteIOSUtils::cstringWithNSString(nsstr);
        XCTAssert(strcmp(cstr, "家族の絵文字👪") == 0,  @"%s is not equal %s", cstr, "家族の絵文字👪");
    }];
    
    [XCTContext runActivityNamed:@"nilが渡された時はnullptrが返されること" block:^(id<XCTActivity>  _Nonnull activity) {
        NSString* nsstr = nil;
        const char* cstr = KarteIOSUtils::cstringWithNSString(nsstr);
        XCTAssert(cstr == nullptr,  @"%s is not nullptr", cstr);
    }];
    
    [XCTContext runActivityNamed:@"NSNullが渡された時はnullptrが返されること" block:^(id<XCTActivity>  _Nonnull activity) {
        NSString* nsstr = (NSString *)[NSNull null];;
        const char* cstr = KarteIOSUtils::cstringWithNSString(nsstr);
        XCTAssert(cstr == nullptr,  @"%s is not nullptr", cstr);
    }];
    
    [XCTContext runActivityNamed:@"NSNumberが渡された時は空文字が返されること" block:^(id<XCTActivity>  _Nonnull activity) {
        NSString* nsstr = (NSString *)@1;
        const char* cstr = KarteIOSUtils::cstringWithNSString(nsstr);
        XCTAssert(cstr == nullptr,  @"%s is not nullptr", cstr);
    }];
}

- (void)testNSDictionaryWithCStringJson {
    [XCTContext runActivityNamed:@"有効なCのjson文字列からNSDictionaryへの変換" block:^(id<XCTActivity>  _Nonnull activity) {
        [XCTContext runActivityNamed:@"nullを含む" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = R"({"string": "abc", "number": 123, "double": 123.45, "isNull": null })";
            NSDictionary* dict = KarteIOSUtils::nsdictionaryWithCStringJson(json);
            
            XCTAssertEqualObjects(dict[@"string"], @"abc", @"%@ is not equal %@", dict[@"string"], @"abc");
            XCTAssertEqualObjects(dict[@"number"], @123, @"%@ is not equal %@", dict[@"number"], @123);
            XCTAssertEqualObjects(dict[@"double"], @123.45, @"%@ is not equal %@", dict[@"double"], @123.45);
            XCTAssertEqual(dict[@"isNull"], [NSNull null], @"%@ is not equal %@", dict[@"isNull"], [NSNull null]);
            XCTAssertNil(dict[@"unknown-key"], @"%@ key should return nil", @"unknown-key");
        }];
        
        [XCTContext runActivityNamed:@"nullを含まない" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = R"({"string": "abc", "number": 123, "double": 123.45 })";
            NSDictionary* dict = KarteIOSUtils::nsdictionaryWithCStringJson(json);
            
            XCTAssertEqualObjects(dict[@"string"], @"abc", @"%@ is not equal %@", dict[@"string"], @"abc");
            XCTAssertEqualObjects(dict[@"number"], @123, @"%@ is not equal %@", dict[@"number"], @123);
            XCTAssertEqualObjects(dict[@"double"], @123.45, @"%@ is not equal %@", dict[@"double"], @123.45);
            XCTAssertNil(dict[@"unknown-key"], @"%@ key should return nil", @"unknown-key");
        }];
        
        [XCTContext runActivityNamed:@"空のjson{}" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = "{}";
            NSDictionary* dict = KarteIOSUtils::nsdictionaryWithCStringJson(json);
            
            XCTAssertNotNil(dict, @"dict should not be nil");
        }];
    }];
    
    [XCTContext runActivityNamed:@"無効なCのjson文字列からNSDictionaryへの変換" block:^(id<XCTActivity>  _Nonnull activity) {
        [XCTContext runActivityNamed:@"文字列でないkey" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = "{ string: \"abc\" }";
            NSDictionary* dict = KarteIOSUtils::nsdictionaryWithCStringJson(json);
            XCTAssertNil(dict, @"invalid json string should return nil");
        }];
        
        [XCTContext runActivityNamed:@"空のjson[]" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = "[]";
            NSDictionary* dict = KarteIOSUtils::nsdictionaryWithCStringJson(json);
            
            XCTAssertNil(dict, @"dict should be nil");
        }];
        
        [XCTContext runActivityNamed:@"Cのjson文字列がnullptrの時にnilが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = NULL;
            NSDictionary* dict = KarteIOSUtils::nsdictionaryWithCStringJson(json);
            XCTAssertNil(dict, @"invalid json string should return nil");
        }];
        
        [XCTContext runActivityNamed:@"Cのjson文字列が空文字の時にnilが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = "";
            NSDictionary* dict = KarteIOSUtils::nsdictionaryWithCStringJson(json);
            XCTAssertNil(dict, @"invalid json string should return nil");
        }];
    }];
}

- (void)testNSArrayWithCStringJson {
    [XCTContext runActivityNamed:@"有効なCのjson文字列からNSArrayへの変換" block:^(id<XCTActivity>  _Nonnull activity) {
        [XCTContext runActivityNamed:@"nullを含む" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = R"(["abc", 123, 123.45, null ])";
            NSArray* array = KarteIOSUtils::nsarrayWithCStringJson(json);
            
            XCTAssert([array count] == 4);
            XCTAssertEqualObjects(array[0], @"abc", @"%@ is not equal %@", array[0], @"abc");
            XCTAssertEqualObjects(array[1], @123, @"%@ is not equal %@", array[1], @123);
            XCTAssertEqualObjects(array[2], @123.45, @"%@ is not equal %@", array[2], @123.45);
            XCTAssertEqual(array[3], [NSNull null], @"%@ is not equal %@", array[3], [NSNull null]);
        }];
        
        [XCTContext runActivityNamed:@"nullを含まない" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = R"(["abc", 123, 123.45])";
            NSArray* array = KarteIOSUtils::nsarrayWithCStringJson(json);
            
            XCTAssertEqualObjects(array[0], @"abc", @"%@ is not equal %@", array[0], @"abc");
            XCTAssertEqualObjects(array[1], @123, @"%@ is not equal %@", array[1], @123);
            XCTAssertEqualObjects(array[2], @123.45, @"%@ is not equal %@", array[2], @123.45);
        }];
        
        [XCTContext runActivityNamed:@"空のjson[]" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = "[]";
            NSArray* array = KarteIOSUtils::nsarrayWithCStringJson(json);
            
            XCTAssertNotNil(array, @"array should not be nil");
        }];
    }];
    
    [XCTContext runActivityNamed:@"無効なCのjson文字列からNSArrayへの変換" block:^(id<XCTActivity>  _Nonnull activity) {
        [XCTContext runActivityNamed:@"Cのjson文字列がnullptrの時にnilが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = NULL;
            NSArray* array = KarteIOSUtils::nsarrayWithCStringJson(json);
            XCTAssertNil(array, @"invalid json string should return nil");
        }];
        
        [XCTContext runActivityNamed:@"Cのjson文字列が空文字の時にnilが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* json = "";
            NSArray* array = KarteIOSUtils::nsarrayWithCStringJson(json);
            XCTAssertNil(array, @"invalid json string should return nil");
        }];
    }];
}

- (void)testCstringJsonWithNSDictionary {
    [XCTContext runActivityNamed:@"NSDictionaryからC文字列JSONへの変換成功時" block:^(id<XCTActivity>  _Nonnull activity) {
        NSDictionary* dict1 = @{@"string":@"abc", @"number":@123, @"double":@123.45, @"isNull":[NSNull null]};
        const char* expected = R"({"string":"abc","number":123,"double":123.45,"isNull":null})";
        const char* actual = KarteIOSUtils::cstringJsonWithNSDictionary(dict1);

        XCTAssert(strcmp(expected, actual) == 0,  @"%s is not %s", actual, expected);
    }];
    
    [XCTContext runActivityNamed:@"NSDictionaryからC文字列JSONへの変換成功時" block:^(id<XCTActivity>  _Nonnull activity) {
        NSDictionary* dict1 = @{@"hoge":@"fuga"};
        const char* expected = R"({"hoge":"fuga"})";
        const char* actual = KarteIOSUtils::cstringJsonWithNSDictionary(dict1);
        
        XCTAssert(strcmp(expected, actual) == 0,  @"%s is not %s", actual, expected);
    }];
    
    [XCTContext runActivityNamed:@"NSDictionaryからC文字列JSONへの変換失敗時にnullptrが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
        [XCTContext runActivityNamed:@"キーが数値" block:^(id<XCTActivity>  _Nonnull activity) {
            NSDictionary* param = @{@1:@"abc", @"number":@123, @"double":@123.45, @"isNull":[NSNull null]};
            const char* expected = nullptr;
            const char* actual = KarteIOSUtils::cstringJsonWithNSDictionary(param);
            
            XCTAssert(expected == actual,  @"%s is not %s", actual, expected);
        }];
        
        [XCTContext runActivityNamed:@"引数がnil" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* expected = nullptr;
            const char* actual = KarteIOSUtils::cstringJsonWithNSDictionary(nil);
            
            XCTAssert(expected == actual,  @"%s is not %s", actual, expected);
        }];
        
        [XCTContext runActivityNamed:@"引数がNSNull" block:^(id<XCTActivity>  _Nonnull activity) {
            NSDictionary *param = (NSDictionary *)[NSNull null];
            const char* expected = nullptr;
            const char* actual = KarteIOSUtils::cstringJsonWithNSDictionary(param);
            
            XCTAssert(expected == actual,  @"%s is not %s", actual, expected);
        }];
        
        [XCTContext runActivityNamed:@"引数がNSNumber" block:^(id<XCTActivity>  _Nonnull activity) {
            NSDictionary *param = (NSDictionary *)(@1);
            const char* expected = nullptr;
            const char* actual = KarteIOSUtils::cstringJsonWithNSDictionary(param);
            
            XCTAssert(expected == actual,  @"%s is not %s", actual, expected);
        }];
    }];
}

- (void)testCstringJsonWithNSArray {
    [XCTContext runActivityNamed:@"NSArrayからC文字列JSONへの変換成功時" block:^(id<XCTActivity>  _Nonnull activity) {
        NSArray* param = @[@"string",@"abc",@"number"];
        const char* expected = R"(["string","abc","number"])";
        const char* actual = KarteIOSUtils::cstringJsonWithNSArray(param);
        
        XCTAssert(strcmp(expected, actual) == 0,  @"%s is not %s", actual, expected);
    }];
    [XCTContext runActivityNamed:@"NSArrayからC文字列JSONへの変換成功時" block:^(id<XCTActivity>  _Nonnull activity) {
        NSArray* param = @[@{@"string":@"abc", @"number":@123, @"double":@123.45, @"isNull":[NSNull null]}];
        const char* expected = R"([{"string":"abc","number":123,"double":123.45,"isNull":null}])";
        const char* actual = KarteIOSUtils::cstringJsonWithNSArray(param);
        
        XCTAssert(strcmp(expected, actual) == 0,  @"%s is not %s", actual, expected);
    }];
    
    [XCTContext runActivityNamed:@"NSArrayからC文字列JSONへの変換失敗時にnullptrが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
        [XCTContext runActivityNamed:@"引数がnil" block:^(id<XCTActivity>  _Nonnull activity) {
            const char* expected = nullptr;
            const char* actual = KarteIOSUtils::cstringJsonWithNSArray(nil);
            
            XCTAssert(expected == actual,  @"%s is not %s", actual, expected);
        }];
        
        [XCTContext runActivityNamed:@"引数がNSNull" block:^(id<XCTActivity>  _Nonnull activity) {
            NSArray *param = (NSArray *)[NSNull null];
            const char* expected = nullptr;
            const char* actual = KarteIOSUtils::cstringJsonWithNSArray(param);
            
            XCTAssert(expected == actual,  @"%s is not nullptr", actual);
        }];
        
        [XCTContext runActivityNamed:@"引数がNSNumber" block:^(id<XCTActivity>  _Nonnull activity) {
            NSArray *param = (NSArray *)(@1);
            const char* expected = nullptr;
            const char* actual = KarteIOSUtils::cstringJsonWithNSArray(param);
            
            XCTAssert(expected == actual,  @"%s is not %s", actual, expected);
        }];
    }];
}

- (void)testCopyString {
    [XCTContext runActivityNamed:@"CのASCII文字列がコピーできること" block:^(id<XCTActivity>  _Nonnull activity) {
        const char* expected = "abc";
        const char* actual = KarteUtilCpp::copyString(expected);
        XCTAssert(strcmp(expected, actual) == 0,  @"%s is not %s", actual, expected);
    }];
    
    [XCTContext runActivityNamed:@"nullpointerを渡すとnullpointerが返ること" block:^(id<XCTActivity>  _Nonnull activity) {
        const char* expected = nullptr;
        const char* actual = KarteUtilCpp::copyString(expected);
        XCTAssert(actual == nullptr,  @"%s is not %s", actual, expected);
    }];
    
    [XCTContext runActivityNamed:@"マルチバイト文字列が渡された時に正しくコピーできること" block:^(id<XCTActivity>  _Nonnull activity) {
        const char* expected = "家族の絵文字👪";
        const char* actual = KarteUtilCpp::copyString(expected);
        XCTAssert(strcmp(expected, actual) == 0,  @"%s is not %s", actual, expected);
    }];
}

@end
