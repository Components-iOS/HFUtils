//
//  HFUserObject.m
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import "HFUserObject.h"
#import <objc/runtime.h>

@interface HFUserObject ()

// 是否为存储在Keychain中的对象
@property (nonatomic, assign) BOOL isKeychainObject;

@end

@implementation HFUserObject

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (instancetype)initWithIdentifier:(NSString *)identifier {
    NSData *userInfoData = [[NSUserDefaults standardUserDefaults] objectForKey:identifier];
    if (userInfoData == nil) {
        if (self = [super init]) {
            _identifier = identifier;
        }
    } else {
        @try {
            self = [NSKeyedUnarchiver unarchiveObjectWithData:userInfoData];
            _identifier = identifier;
        } @catch (NSException *exception) {
            if ([exception.name isEqualToString:@"NSInvalidArgumentException"]) {
                NSLog(@"未遵循NSCoding协议错误,请查看下面的错误日志中的类名👇👇👇");
                @throw exception;
            } else {
                NSLog(@"其他错误,请查看下面的错误日志👇👇👇");
                @throw exception;
            }
        }
    }
    _isKeychainObject = NO;
    return self;
}

- (instancetype)initKeychainObjectWithIdentifier:(NSString *)identifier {
    NSData *userInfoData = [HFUserObject getKeyChainData:identifier];
    if (userInfoData == nil) {
        if (self = [super init]) {
            _identifier = identifier;
        }
    } else {
        @try {
            self = [NSKeyedUnarchiver unarchiveObjectWithData:userInfoData];
            _identifier = identifier;
        } @catch (NSException *exception) {
            if ([exception.name isEqualToString:@"NSInvalidArgumentException"]) {
                NSLog(@"未遵循NSCoding协议错误,请查看下面的错误日志中的类名👇👇👇");
                @throw exception;
            } else {
                NSLog(@"其他错误,请查看下面的错误日志👇👇👇");
                @throw exception;
            }
        }
    }
    _isKeychainObject = YES;
    return self;
}

#pragma mark - Keychain封装方法
+ (NSMutableDictionary *)getKeyChainQuery:(NSString *)identifier {
    return [NSMutableDictionary dictionaryWithObjectsAndKeys:
            (__bridge_transfer id)kSecClassGenericPassword,(__bridge_transfer id)kSecClass,
            identifier, (__bridge_transfer id)kSecAttrService,
            identifier, (__bridge_transfer id)kSecAttrAccount,
            (__bridge_transfer id)kSecAttrAccessibleAfterFirstUnlock,(__bridge_transfer id)kSecAttrAccessible,
            nil];
}

+ (NSData *)getKeyChainData:(NSString *)identifier {
    NSData *resultData = nil;
    NSMutableDictionary *keychainQuery = [self getKeyChainQuery:identifier];
    [keychainQuery setObject:(id)kCFBooleanTrue forKey:(__bridge_transfer id)kSecReturnData];
    [keychainQuery setObject:(__bridge_transfer id)kSecMatchLimitOne forKey:(__bridge_transfer id)kSecMatchLimit];
    CFDataRef keyData = NULL;
    if (SecItemCopyMatching((__bridge_retained CFDictionaryRef)keychainQuery, (CFTypeRef *)&keyData) == noErr) {
        @try {
            resultData = (__bridge_transfer NSData *)keyData;
        } @catch (NSException *e) {
            NSLog(@"Unarchive of %@ failed: %@", identifier, e);
        }
    }
    return resultData;
}

+ (void)saveUserDataKey:(NSString *)identifier dataValue:(id)valueData {
    // Get search dictionary
    NSMutableDictionary *keychainQuery = [self getKeyChainQuery:identifier];
    // Delete old item before add new item
    SecItemDelete((__bridge_retained CFDictionaryRef)keychainQuery);
    // Add new object to search dictionary(Attention:the data format)
    [keychainQuery setObject:[NSKeyedArchiver archivedDataWithRootObject:valueData] forKey:(__bridge_transfer id)kSecValueData];
    // Add item to keychain with the search dictionary
    SecItemAdd((__bridge_retained CFDictionaryRef)keychainQuery, NULL);
}

#pragma mark - 保存数据和删除数据
- (void)saveAllPropertyAction {
    if (_isKeychainObject) {
        // 数据保存到Keychain中
        [HFUserObject saveUserDataKey:_identifier dataValue:self];
    } else {
        // 数据保存到NSUserDefaults
        NSData *allPropertyData = [NSKeyedArchiver archivedDataWithRootObject:self];
        [[NSUserDefaults standardUserDefaults] setObject:allPropertyData forKey:_identifier];
    }
}

- (void)deleteAllPropertyAction {
    unsigned int propertyCount = 0;
    objc_property_t *propertyList = class_copyPropertyList([self class], &propertyCount);
    for (int i = 0; i < propertyCount; i++) {
        objc_property_t *thisProperty = &propertyList[i];
        const char *name = property_getName(*thisProperty);
        NSString *propertyName = [NSString stringWithFormat:@"%s",name];
        [self setValue:nil forKey:propertyName];
    }
    free(propertyList);
    
    if (_isKeychainObject) {
        NSMutableDictionary *keychainQuery = [HFUserObject getKeyChainQuery:_identifier];
        SecItemDelete((__bridge_retained CFDictionaryRef)keychainQuery);
    } else {
        [[NSUserDefaults standardUserDefaults] removeObjectForKey:_identifier];
    }
}

#pragma mark - 弃用init方法
- (instancetype)init {
    if (self = [super init]) {
        NSString *exceptionContent = [NSString stringWithFormat:@"%@ 类中已经把init初始化弃用了,请用'- (instancetype)initWithIdentifier:(NSString *)identifier'来进行初始化操作 ",NSStringFromClass([self class])];
        @throw [NSException exceptionWithName:@"method is deprecated" reason:exceptionContent userInfo:nil];
    }
    return self;
}


@end

#pragma clang diagnostic pop
