//
//  HFUUIDHelper.m
//  HFUtils
//
//  Created by liuhongfei on 2026/4/8.
//

#import "HFUUIDHelper.h"
#import <Security/Security.h>

// KeyChain中存储UUID的服务名和账户名
static NSString * const kKeychainServiceName = @"cn.HFUtils.HFUUIDHelper";
static NSString * const kKeychainAccountName = @"HFUUIDHelper_DeviceUUID";
static NSString * const kUserDefaultsIdentifierKey = @"HFUUIDHelper_DeviceUUID";

@implementation HFUUIDHelper

#pragma mark - Public Methods

+ (NSString *)getDeviceIdentifierFromKeychain {
    NSString *identifier = [self getUUIDFromKeychain];
    if (identifier.length > 0) {
        [self deleteUUIDFromUserDefaults];
        return identifier;
    }
    NSString *newIdentifier = [self generateUUID];
    [self saveUUIDToKeychain:newIdentifier];
    [self deleteUUIDFromUserDefaults];
    return newIdentifier;
}

+ (NSString *)getDeviceIdentifierFromUserDefaults {
    NSString *identifier = [self getUUIDFromUserDefaults];
    if (identifier.length > 0) {
        [self deleteUUIDFromKeychain];
        return identifier;
    }
    NSString *newIdentifier = [self generateUUID];
    [self saveUUIDToUserDefaults:newIdentifier];
    [self deleteUUIDFromKeychain];
    return newIdentifier;
}

+ (NSString *)resetDeviceIdentifierInKeychain {
    [self deleteUUIDFromKeychain];
    NSString *newIdentifier = [self generateUUID];
    [self saveUUIDToKeychain:newIdentifier];
    [self deleteUUIDFromUserDefaults];
    return newIdentifier;
}

+ (NSString *)resetDeviceIdentifierInUserDefaults {
    [self deleteUUIDFromUserDefaults];
    NSString *newIdentifier = [self generateUUID];
    [self saveUUIDToUserDefaults:newIdentifier];
    [self deleteUUIDFromKeychain];
    return newIdentifier;
}

#pragma mark - Private Methods

// 生成UUID
+ (NSString *)generateUUID {
    NSString *uuid = [NSUUID UUID].UUIDString;
    long long ts = (long long)([[NSDate date] timeIntervalSince1970]);
    int rand3 = (int)arc4random_uniform(1000);
    return [NSString stringWithFormat:@"%@-%lld%03d", uuid, ts, rand3];
}

// 从KeyChain中获取UUID
+ (NSString *)getUUIDFromKeychain {
    NSMutableDictionary *keychainQuery = [self getKeychainQuery];
    
    // 设置查询参数
    [keychainQuery setObject:(__bridge id)kSecMatchLimitOne forKey:(__bridge id)kSecMatchLimit];
    [keychainQuery setObject:(__bridge id)kCFBooleanTrue forKey:(__bridge id)kSecReturnData];
    
    CFDataRef keyData = NULL;
    OSStatus status = SecItemCopyMatching((__bridge CFDictionaryRef)keychainQuery, (CFTypeRef *)&keyData);
    
    if (status == errSecSuccess) {
        @try {
            NSData *data = (__bridge_transfer NSData *)keyData;
            NSString *text = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            if (text.length > 0) {
                NSRange lastDash = [text rangeOfString:@"-" options:NSBackwardsSearch];
                if (lastDash.location != NSNotFound && lastDash.location + 1 < text.length) {
                    NSString *uuidPart = [text substringToIndex:lastDash.location];
                    NSString *tsPart = [text substringFromIndex:lastDash.location + 1];
                    if ([[NSUUID alloc] initWithUUIDString:uuidPart] != nil) {
                        NSCharacterSet *nonDigits = [[NSCharacterSet decimalDigitCharacterSet] invertedSet];
                        if (tsPart.length > 0 && [tsPart rangeOfCharacterFromSet:nonDigits].location == NSNotFound) {
                            return text;
                        }
                    }
                }
                if ([[NSUUID alloc] initWithUUIDString:text] != nil || [text hasPrefix:@"{"]) {
                    [self deleteUUIDFromKeychain];
                }
                return nil;
            }
            [self deleteUUIDFromKeychain];
            return nil;
        } @catch (NSException *exception) {
            NSLog(@"获取UUID异常: %@", exception);
            return nil;
        }
    }
    
    return nil;
}

// 保存UUID到KeyChain
+ (void)saveUUIDToKeychain:(NSString *)uuid {
    NSMutableDictionary *keychainQuery = [self getKeychainQuery];
    
    // 先尝试删除已有的记录
    SecItemDelete((__bridge CFDictionaryRef)keychainQuery);
    
    // 设置要保存的数据
    NSData *data = [uuid dataUsingEncoding:NSUTF8StringEncoding];
    [keychainQuery setObject:data forKey:(__bridge id)kSecValueData];
    [keychainQuery setObject:(__bridge id)kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly forKey:(__bridge id)kSecAttrAccessible];
    
    // 添加到KeyChain
    OSStatus status = SecItemAdd((__bridge CFDictionaryRef)keychainQuery, NULL);
    if (status != errSecSuccess) {
        NSLog(@"保存UUID到KeyChain失败: %d", (int)status);
    }
}

// 从KeyChain中删除UUID
+ (void)deleteUUIDFromKeychain {
    NSMutableDictionary *keychainQuery = [self getKeychainQuery];
    SecItemDelete((__bridge CFDictionaryRef)keychainQuery);
}

// 获取KeyChain查询字典
+ (NSMutableDictionary *)getKeychainQuery {
    return [@{
        (__bridge id)kSecClass: (__bridge id)kSecClassGenericPassword,
        (__bridge id)kSecAttrService: kKeychainServiceName,
        (__bridge id)kSecAttrAccount: kKeychainAccountName
    } mutableCopy];
}

// NSUserDefaults
+ (NSString *)getUUIDFromUserDefaults {
    NSString *text = [[NSUserDefaults standardUserDefaults] stringForKey:kUserDefaultsIdentifierKey];
    if (text.length > 0) {
        NSRange lastDash = [text rangeOfString:@"-" options:NSBackwardsSearch];
        if (lastDash.location != NSNotFound && lastDash.location + 1 < text.length) {
            NSString *uuidPart = [text substringToIndex:lastDash.location];
            NSString *tsPart = [text substringFromIndex:lastDash.location + 1];
            if ([[NSUUID alloc] initWithUUIDString:uuidPart] != nil) {
                NSCharacterSet *nonDigits = [[NSCharacterSet decimalDigitCharacterSet] invertedSet];
                if (tsPart.length > 0 && [tsPart rangeOfCharacterFromSet:nonDigits].location == NSNotFound) {
                    return text;
                }
            }
        }
        [self deleteUUIDFromUserDefaults];
        return nil;
    }
    return nil;
}

+ (void)saveUUIDToUserDefaults:(NSString *)uuid {
    [[NSUserDefaults standardUserDefaults] setObject:uuid forKey:kUserDefaultsIdentifierKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+ (void)deleteUUIDFromUserDefaults {
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:kUserDefaultsIdentifierKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

@end
