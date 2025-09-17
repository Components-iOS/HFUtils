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

#pragma mark - 基本使用

/// 获取当前应用的主窗口（适配 SceneDelegate）
+ (UIWindow *)currentWindow;

/// 获取当前活跃的 WindowScene（iOS 13+）
+ (UIWindowScene *)currentWindowScene API_AVAILABLE(ios(13.0));

/// 获取当前最顶层的 ViewController
+ (UIViewController *)currentVC;

/// 获取状态栏高度（适配 SceneDelegate）
+ (CGFloat)statusBarHeight;

/// 获取安全区域 insets（适配 SceneDelegate）
+ (UIEdgeInsets)safeAreaInsets;

#pragma mark - 导航和视图控制器管理

/// 获取当前导航控制器
+ (UINavigationController * _Nullable)currentNavigationController;

/// 获取当前 TabBar 控制器
+ (UITabBarController * _Nullable)currentTabBarController;

/// 获取根视图控制器
+ (UIViewController * _Nullable)rootViewController;

/// 推送视图控制器到当前导航栈
/// @param viewController 要推送的视图控制器
/// @param animated 是否动画
+ (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated;

/// 弹出当前视图控制器
/// @param animated 是否动画
+ (void)popViewControllerAnimated:(BOOL)animated;

/// 模态展示视图控制器
/// @param viewController 要展示的视图控制器
/// @param animated 是否动画
/// @param completion 完成回调
+ (void)presentViewController:(UIViewController *)viewController
                     animated:(BOOL)animated
                   completion:(void (^ _Nullable)(void))completion;

#pragma mark - 弹窗和提示

/// 在当前窗口显示 Alert
/// @param title 标题
/// @param message 消息内容
/// @param cancelTitle 取消按钮标题
/// @param confirmTitle 确认按钮标题
/// @param cancelHandler 取消回调
/// @param confirmHandler 确认回调
+ (void)showAlertWithTitle:(NSString * _Nullable)title
                   message:(NSString * _Nullable)message
               cancelTitle:(NSString * _Nullable)cancelTitle
              confirmTitle:(NSString * _Nullable)confirmTitle
             cancelHandler:(void (^ _Nullable)(void))cancelHandler
            confirmHandler:(void (^ _Nullable)(void))confirmHandler;

/// 显示简单提示 Alert
/// @param title 标题
/// @param message 消息内容
+ (void)showSimpleAlertWithTitle:(NSString * _Nullable)title message:(NSString * _Nullable)message;

/// 显示 ActionSheet
/// @param title 标题
/// @param message 消息内容
/// @param actions 操作数组 @[@{@"title": @"标题", @"style": @(UIAlertActionStyleDefault), @"handler": block}]
/// @param cancelTitle 取消按钮标题
+ (void)showActionSheetWithTitle:(NSString * _Nullable)title
                         message:(NSString * _Nullable)message
                         actions:(NSArray<NSDictionary *> * _Nullable)actions
                     cancelTitle:(NSString * _Nullable)cancelTitle;

#pragma mark - 屏幕和设备信息

/// 获取屏幕宽度
+ (CGFloat)screenWidth;

/// 获取屏幕高度
+ (CGFloat)screenHeight;

/// 获取屏幕尺寸
+ (CGSize)screenSize;

/// 获取屏幕缩放比例
+ (CGFloat)screenScale;

/// 是否为横屏
+ (BOOL)isLandscape;

/// 是否为竖屏
+ (BOOL)isPortrait;

/// 是否为刘海屏/Face ID 设备
+ (BOOL)hasNotch;

/// 是否为 iPad
+ (BOOL)isIPad;

/// 是否为 iPhone
+ (BOOL)isIPhone;

#pragma mark - 键盘相关

/// 隐藏键盘
+ (void)dismissKeyboard;

/// 获取第一响应者视图
+ (UIView * _Nullable)firstResponder;

#pragma mark - 截图相关

/// 截取当前屏幕
+ (UIImage * _Nullable)captureScreen;

/// 截取指定视图
/// @param view 要截取的视图
+ (UIImage * _Nullable)captureView:(UIView *)view;

#pragma mark - 工具方法

/// 在主线程执行代码块
/// @param block 要执行的代码块
+ (void)executeOnMainThread:(void (^)(void))block;

/// 延迟执行代码块
/// @param delay 延迟时间（秒）
/// @param block 要执行的代码块
+ (void)executeAfterDelay:(NSTimeInterval)delay block:(void (^)(void))block;

/// 判断当前是否为主线程
+ (BOOL)isMainThread;

@end

NS_ASSUME_NONNULL_END
