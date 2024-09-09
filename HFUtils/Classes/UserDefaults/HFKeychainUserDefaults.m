//
//  HFKeychainUserDefaults.m
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import "HFKeychainUserDefaults.h"

#define HD_KEY_CHAIN_USER_MANAGER @"HD_KEY_CHAIN_USER_MANAGER"

@implementation HFKeychainUserDefaults

static HFKeychainUserDefaults *userDefaults = nil;

+ (instancetype)standardUserDefaults {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (userDefaults == nil) {
            userDefaults = [[HFKeychainUserDefaults alloc] initKeychainObjectWithIdentifier:HD_KEY_CHAIN_USER_MANAGER];
        }
    });
    return userDefaults;
}

#pragma mark - 赋值方法,可根据实际情况自行修改
- (void)setValue:(id)value forUndefinedKey:(NSString *)key {
    
}

- (void)setValue:(id)value forKey:(NSString *)key {
    [super setValue:value forKey:key];
}

@end
