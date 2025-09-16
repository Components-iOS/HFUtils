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
    // iOS 13+
    if (@available(iOS 13.0, *)) {
        for (UIWindowScene *windowScene in [UIApplication sharedApplication].connectedScenes) {
            if (windowScene.activationState == UISceneActivationStateForegroundActive) {
                for (UIWindow *window in windowScene.windows) {
                    if (window.isKeyWindow) {
                        return window;
                    }
                }
            }
        }
        
        for (UIWindowScene *windowScene in [UIApplication sharedApplication].connectedScenes) {
            if (windowScene.activationState == UISceneActivationStateForegroundActive) {
                for (UIWindow *window in windowScene.windows) {
                    if (window.rootViewController != nil) {
                        return window;
                    }
                }
            }
        }
    }
    
    // iOS 12
    if ([UIApplication sharedApplication].keyWindow) {
        return [UIApplication sharedApplication].keyWindow;
    }
    
    return [UIApplication sharedApplication].windows.firstObject;
}

+ (UIWindowScene *)currentWindowScene API_AVAILABLE(ios(13.0)) {
    if (@available(iOS 13.0, *)) {
        for (UIWindowScene *windowScene in [UIApplication sharedApplication].connectedScenes) {
            if (windowScene.activationState == UISceneActivationStateForegroundActive) {
                return windowScene;
            }
        }
        
        for (UIScene *scene in [UIApplication sharedApplication].connectedScenes) {
            if ([scene isKindOfClass:[UIWindowScene class]]) {
                return (UIWindowScene *)scene;
            }
        }
    }
    return nil;
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
