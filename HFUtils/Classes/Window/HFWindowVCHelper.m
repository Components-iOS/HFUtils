//
//  HFCurrentVC.m
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#import "HFWindowVCHelper.h"

@implementation HFWindowVCHelper

#pragma mark - 基本使用

+ (UIWindow *)currentWindow {
    // 优先使用 iOS 13+ 的 Scene 方式获取 window
    if (@available(iOS 13.0, *)) {
        // 方式1：从活跃的 WindowScene 获取
        UIWindowScene *windowScene = [self currentWindowScene];
        if (windowScene) {
            // 从 WindowScene 的 windows 中查找 keyWindow
            for (UIWindow *window in windowScene.windows) {
                if (window.isKeyWindow) {
                    return window;
                }
            }
            // 如果没有 keyWindow，返回第一个可见窗口
            for (UIWindow *window in windowScene.windows) {
                if (!window.hidden) {
                    return window;
                }
            }
        }
        
        // 方式2：从所有连接的场景中查找
        for (UIScene *scene in [UIApplication sharedApplication].connectedScenes) {
            if ([scene isKindOfClass:[UIWindowScene class]]) {
                UIWindowScene *ws = (UIWindowScene *)scene;
                for (UIWindow *window in ws.windows) {
                    if (window.isKeyWindow) {
                        return window;
                    }
                }
            }
        }
        
        // 方式3：从 UIApplication 的 windows 获取（iOS 13-14）
        if ([UIApplication sharedApplication].windows.count > 0) {
            for (UIWindow *window in [UIApplication sharedApplication].windows) {
                if (window.isKeyWindow) {
                    return window;
                }
            }
            // 返回第一个不隐藏的窗口
            for (UIWindow *window in [UIApplication sharedApplication].windows) {
                if (!window.hidden) {
                    return window;
                }
            }
        }
    }
    
    // 兼容 iOS 12 及以下版本，使用传统方式
    if ([UIApplication sharedApplication].keyWindow) {
        return [UIApplication sharedApplication].keyWindow;
    }
    
    return [UIApplication sharedApplication].windows.firstObject;
}

+ (UIWindowScene *)currentWindowScene API_AVAILABLE(ios(13.0)) {
    if (@available(iOS 13.0, *)) {
        // 优先获取前台活跃的场景
        for (UIWindowScene *windowScene in [UIApplication sharedApplication].connectedScenes) {
            if ([windowScene isKindOfClass:[UIWindowScene class]] &&
                windowScene.activationState == UISceneActivationStateForegroundActive) {
                return windowScene;
            }
        }
        
        // 如果没有前台活跃的，获取第一个前台场景
        for (UIWindowScene *windowScene in [UIApplication sharedApplication].connectedScenes) {
            if ([windowScene isKindOfClass:[UIWindowScene class]] &&
                windowScene.activationState == UISceneActivationStateForegroundInactive) {
                return windowScene;
            }
        }
        
        // 最后获取任意一个 WindowScene
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
    
    if (!window) {
        return nil;
    }
    
    UIViewController *rootViewController = window.rootViewController;
    
    // 递归查找最顶层的 ViewController
    while (rootViewController) {
        if (rootViewController.presentedViewController) {
            rootViewController = rootViewController.presentedViewController;
        } else if ([rootViewController isKindOfClass:[UINavigationController class]]) {
            UINavigationController *nav = (UINavigationController *)rootViewController;
            rootViewController = nav.visibleViewController;
        } else if ([rootViewController isKindOfClass:[UITabBarController class]]) {
            UITabBarController *tab = (UITabBarController *)rootViewController;
            rootViewController = tab.selectedViewController;
        } else {
            break;
        }
    }
    
    return rootViewController;
}

+ (CGFloat)statusBarHeight {
    UIWindow *window = [self currentWindow];
    
    if (@available(iOS 13.0, *)) {
        UIWindowScene *windowScene = window.windowScene;
        if (windowScene && windowScene.statusBarManager) {
            return windowScene.statusBarManager.statusBarFrame.size.height;
        }
    }
    
    // 兜底方案：从安全区域获取
    if (window) {
        return window.safeAreaInsets.top;
    }
    
    // 最后的兜底方案：使用传统方式
    return [UIApplication sharedApplication].statusBarFrame.size.height;
}

+ (UIEdgeInsets)safeAreaInsets {
    UIWindow *window = [self currentWindow];
    
    if (window) {
        return window.safeAreaInsets;
    }
    
    // 兜底方案：返回零边距
    return UIEdgeInsetsZero;
}

#pragma mark - 导航和视图控制器管理

+ (UINavigationController *)currentNavigationController {
    UIViewController *currentVC = [self currentVC];
    
    if ([currentVC isKindOfClass:[UINavigationController class]]) {
        return (UINavigationController *)currentVC;
    }
    
    return currentVC.navigationController;
}

+ (UITabBarController *)currentTabBarController {
    UIViewController *rootVC = [self rootViewController];
    
    if ([rootVC isKindOfClass:[UITabBarController class]]) {
        return (UITabBarController *)rootVC;
    }
    
    UIViewController *currentVC = [self currentVC];
    return currentVC.tabBarController;
}

+ (UIViewController *)rootViewController {
    UIWindow *window = [self currentWindow];
    return window.rootViewController;
}

+ (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated {
    if (!viewController) {
        return;
    }
    
    UINavigationController *nav = [self currentNavigationController];
    if (nav) {
        [self executeOnMainThread:^{
            [nav pushViewController:viewController animated:animated];
        }];
    }
}

+ (void)popViewControllerAnimated:(BOOL)animated {
    UINavigationController *nav = [self currentNavigationController];
    if (nav && nav.viewControllers.count > 1) {
        [self executeOnMainThread:^{
            [nav popViewControllerAnimated:animated];
        }];
    }
}

+ (void)presentViewController:(UIViewController *)viewController
                     animated:(BOOL)animated
                   completion:(void (^)(void))completion {
    if (!viewController) {
        return;
    }
    
    UIViewController *currentVC = [self currentVC];
    if (currentVC) {
        [self executeOnMainThread:^{
            [currentVC presentViewController:viewController animated:animated completion:completion];
        }];
    }
}

#pragma mark - 弹窗和提示

+ (void)showAlertWithTitle:(NSString *)title
                   message:(NSString *)message
               cancelTitle:(NSString *)cancelTitle
              confirmTitle:(NSString *)confirmTitle
             cancelHandler:(void (^)(void))cancelHandler
            confirmHandler:(void (^)(void))confirmHandler {
    
    [self executeOnMainThread:^{
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:title
                                                                       message:message
                                                                preferredStyle:UIAlertControllerStyleAlert];
        
        if (cancelTitle.length > 0) {
            UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:cancelTitle
                                                                   style:UIAlertActionStyleCancel
                                                                 handler:^(UIAlertAction * _Nonnull action) {
                if (cancelHandler) {
                    cancelHandler();
                }
            }];
            [alert addAction:cancelAction];
        }
        
        if (confirmTitle.length > 0) {
            UIAlertAction *confirmAction = [UIAlertAction actionWithTitle:confirmTitle
                                                                    style:UIAlertActionStyleDefault
                                                                  handler:^(UIAlertAction * _Nonnull action) {
                if (confirmHandler) {
                    confirmHandler();
                }
            }];
            [alert addAction:confirmAction];
        }
        
        UIViewController *currentVC = [self currentVC];
        if (currentVC) {
            [currentVC presentViewController:alert animated:YES completion:nil];
        }
    }];
}

+ (void)showSimpleAlertWithTitle:(NSString *)title message:(NSString *)message {
    [self showAlertWithTitle:title
                     message:message
                 cancelTitle:nil
                confirmTitle:@"确定"
               cancelHandler:nil
              confirmHandler:nil];
}

+ (void)showActionSheetWithTitle:(NSString *)title
                         message:(NSString *)message
                         actions:(NSArray<NSDictionary *> *)actions
                     cancelTitle:(NSString *)cancelTitle {
    
    [self executeOnMainThread:^{
        UIAlertController *actionSheet = [UIAlertController alertControllerWithTitle:title
                                                                             message:message
                                                                      preferredStyle:UIAlertControllerStyleActionSheet];
        
        // 添加自定义操作
        for (NSDictionary *actionInfo in actions) {
            NSString *actionTitle = actionInfo[@"title"];
            NSNumber *styleNumber = actionInfo[@"style"] ?: @(UIAlertActionStyleDefault);
            UIAlertActionStyle style = (UIAlertActionStyle)[styleNumber integerValue];
            void (^handler)(void) = actionInfo[@"handler"];
            
            UIAlertAction *action = [UIAlertAction actionWithTitle:actionTitle
                                                             style:style
                                                           handler:^(UIAlertAction * _Nonnull action) {
                if (handler) {
                    handler();
                }
            }];
            [actionSheet addAction:action];
        }
        
        // 添加取消按钮
        if (cancelTitle.length > 0) {
            UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:cancelTitle
                                                                   style:UIAlertActionStyleCancel
                                                                 handler:nil];
            [actionSheet addAction:cancelAction];
        }
        
        UIViewController *currentVC = [self currentVC];
        if (currentVC) {
            // iPad 适配
            if ([self isIPad] && actionSheet.popoverPresentationController) {
                actionSheet.popoverPresentationController.sourceView = currentVC.view;
                actionSheet.popoverPresentationController.sourceRect = CGRectMake(currentVC.view.bounds.size.width/2,
                                                                                   currentVC.view.bounds.size.height/2,
                                                                                   1, 1);
            }
            
            [currentVC presentViewController:actionSheet animated:YES completion:nil];
        }
    }];
}

#pragma mark - 屏幕和设备信息

+ (CGFloat)screenWidth {
    return [UIScreen mainScreen].bounds.size.width;
}

+ (CGFloat)screenHeight {
    return [UIScreen mainScreen].bounds.size.height;
}

+ (CGSize)screenSize {
    return [UIScreen mainScreen].bounds.size;
}

+ (CGFloat)screenScale {
    return [UIScreen mainScreen].scale;
}

+ (BOOL)isLandscape {
    UIWindow *window = [self currentWindow];
    if (@available(iOS 13.0, *)) {
        return UIInterfaceOrientationIsLandscape(window.windowScene.interfaceOrientation);
    } else {
        return UIInterfaceOrientationIsLandscape([UIApplication sharedApplication].statusBarOrientation);
    }
}

+ (BOOL)isPortrait {
    return ![self isLandscape];
}

+ (BOOL)hasNotch {
    UIEdgeInsets safeAreaInsets = [self safeAreaInsets];
    return safeAreaInsets.bottom > 0;
}

+ (BOOL)isIPad {
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad;
}

+ (BOOL)isIPhone {
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
}

#pragma mark - 键盘相关

+ (void)dismissKeyboard {
    UIWindow *window = [self currentWindow];
    [window endEditing:YES];
}

+ (UIView *)firstResponder {
    UIWindow *window = [self currentWindow];
    return [self findFirstResponderInView:window];
}

+ (UIView *)findFirstResponderInView:(UIView *)view {
    if (view.isFirstResponder) {
        return view;
    }
    
    for (UIView *subView in view.subviews) {
        UIView *firstResponder = [self findFirstResponderInView:subView];
        if (firstResponder) {
            return firstResponder;
        }
    }
    
    return nil;
}

#pragma mark - 截图相关

+ (UIImage *)captureScreen {
    UIWindow *window = [self currentWindow];
    if (!window) {
        return nil;
    }
    
    return [self captureView:window];
}

+ (UIImage *)captureView:(UIView *)view {
    if (!view) {
        return nil;
    }
    
    UIGraphicsBeginImageContextWithOptions(view.bounds.size, NO, [self screenScale]);
    [view.layer renderInContext:UIGraphicsGetCurrentContext()];
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return image;
}

#pragma mark - 工具方法

+ (void)executeOnMainThread:(void (^)(void))block {
    if (!block) {
        return;
    }
    
    if ([self isMainThread]) {
        block();
    } else {
        dispatch_async(dispatch_get_main_queue(), block);
    }
}

+ (void)executeAfterDelay:(NSTimeInterval)delay block:(void (^)(void))block {
    if (!block) {
        return;
    }
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), dispatch_get_main_queue(), block);
}

+ (BOOL)isMainThread {
    return [NSThread isMainThread];
}

@end
