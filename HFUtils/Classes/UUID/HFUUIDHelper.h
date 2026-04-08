//
//  HFUUIDHelper.h
//  HFUtils
//
//  Created by liuhongfei on 2026/4/8.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HFUUIDHelper : NSObject

/**
 * 获取设备唯一标识符
 * 该方法会生成一个UUID并将其存储
 * 即使应用被卸载后重新安装，该标识符仍然保持不变
 * @return 设备唯一标识符字符串
 */
+ (NSString *)getDeviceIdentifierFromKeychain;
+ (NSString *)getDeviceIdentifierFromUserDefaults;

/**
 * 重置设备标识符
 * 该方法会删除存储的UUID并生成一个新的
 * @return 新生成的设备唯一标识符字符串
 */
+ (NSString *)resetDeviceIdentifierInKeychain;
+ (NSString *)resetDeviceIdentifierInUserDefaults;

@end

NS_ASSUME_NONNULL_END
