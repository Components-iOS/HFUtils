//
//  HFCurrentVC.m
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#import "HFWindowVCHelper.h"

@implementation HFWindowVCHelper

+ (UIWindow *)currentWindow {
    UIWindow *currentWindow = nil;

    if (@available(iOS 13.0, *)) {
        for (UIWindowScene *windowScene in [UIApplication sharedApplication].connectedScenes) {
            if ([windowScene isKindOfClass:[UIWindowScene class]]) {
                UIWindowScene *scene = (UIWindowScene *)windowScene;
                for (UIWindow *window in scene.windows) {
                    if (window.isKeyWindow) {
                        currentWindow = window;
                        break;
                    }
                }
                if (currentWindow) break;
            }
        }
    } else {
        currentWindow = [UIApplication sharedApplication].keyWindow;
    }

    return currentWindow;
}

+ (UIViewController *)currentVC {
    UIWindow *window = [self currentWindow];
    
    if (window) {
        UIViewController *rootViewController = window.rootViewController;
        while (rootViewController.presentedViewController) {
            rootViewController = rootViewController.presentedViewController;
        }
        return rootViewController;
    }
    
    return nil;
}

@end
