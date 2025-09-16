//
//  HFCurrentVC.h
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HFWindowVCHelper : NSObject

+ (UIWindow *)currentWindow;

+ (UIWindowScene *)currentWindowScene API_AVAILABLE(ios(13.0));

+ (UIViewController *)currentVC;

@end

NS_ASSUME_NONNULL_END
