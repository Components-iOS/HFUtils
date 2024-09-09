//
//  HFProgressHUD+Utils.m
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#import "HFProgressHUD+Utils.h"
#import "HFWindowVCHelper.h"

@implementation HFProgressHUD (Utils)

#pragma mark - show tips
+ (void)showTipMessageInWindow:(NSString *)message {
    [self showTipMessage:message isWindow:true timer:2];
}

+ (void)showTipMessageInView:(NSString *)message {
    [self showTipMessage:message isWindow:false timer:2];
}

+ (void)showTipMessageInWindow:(NSString *)message timer:(int)aTimer {
    [self showTipMessage:message isWindow:true timer:aTimer];
}

+ (void)showTipMessageInView:(NSString *)message timer:(int)aTimer {
    [self showTipMessage:message isWindow:false timer:aTimer];
}

+ (void)showTipMessage:(NSString *)message isWindow:(BOOL)isWindow timer:(int)aTimer {
    HFProgressHUD *hud = [self createMBProgressHUDviewWithMessage:message isWindiw:isWindow];
    hud.mode = HFProgressHUDModeText;
    [hud hideAnimated:YES afterDelay:aTimer];
}

#pragma mark - show activity
+ (void)showActivityMessageInWindow:(NSString *)message {
    [self showActivityMessage:message isWindow:true timer:0];
}

+ (void)showActivityMessageInView:(NSString *)message {
    [self showActivityMessage:message isWindow:false timer:0];
}

+ (void)showActivityMessageInWindow:(NSString *)message timer:(int)aTimer {
    [self showActivityMessage:message isWindow:true timer:aTimer];
}

+ (void)showActivityMessageInView:(NSString *)message timer:(int)aTimer {
    [self showActivityMessage:message isWindow:false timer:aTimer];
}

+ (void)showActivityMessage:(NSString *)message isWindow:(BOOL)isWindow timer:(int)aTimer {
    HFProgressHUD *hud = [self createMBProgressHUDviewWithMessage:message isWindiw:isWindow];
    hud.mode = HFProgressHUDModeIndeterminate;
    
    if (aTimer > 0) {
        [hud hideAnimated:YES afterDelay:aTimer];
    }
}

#pragma mark - show image
+ (void)showSuccessMessage:(NSString *)message {
    NSString *name = @"utils_hud_success@2x";
    [self showCustomIconInWindow:name message:message];
}

+ (void)showErrorMessage:(NSString *)message {
    NSString *name = @"utils_hud_error@2x";
    [self showCustomIconInWindow:name message:message];
}

+ (void)showInfoMessage:(NSString *)message {
    NSString *name = @"utils_hud_info@2x";
    [self showCustomIconInWindow:name message:message];
}

+ (void)showWarnMessage:(NSString *)message {
    NSString *name = @"utils_hud_warn@2x";
    [self showCustomIconInWindow:name message:message];
}

+ (void)showCustomIconInWindow:(NSString *)iconName message:(NSString *)message {
    [self showCustomIcon:iconName message:message isWindow:true];
}

+ (void)showCustomIconInView:(NSString *)iconName message:(NSString *)message {
    [self showCustomIcon:iconName message:message isWindow:false];
}

+ (void)showCustomIcon:(NSString *)iconName message:(NSString *)message isWindow:(BOOL)isWindow {
    HFProgressHUD *hud = [self createMBProgressHUDviewWithMessage:message isWindiw:isWindow];
    hud.customView = [[UIImageView alloc] initWithImage:[self loadBundleImage:iconName]];
    hud.mode = HFProgressHUDModeCustomView;
    [hud hideAnimated:YES afterDelay:2];
}

#pragma mark - hidden hud
+ (void)hideHUD {
    UIView *winView = (UIView *)[HFWindowVCHelper currentWindow];
    [self hideHUDForView:winView animated:YES];
    [self hideHUDForView:[HFWindowVCHelper currentVC].view animated:YES];
    
    // 隐藏并移除当前视图上的所有 HUDs
    for (UIView *subview in winView.subviews) {
        if ([subview isKindOfClass:[HFProgressHUD class]]) {
            HFProgressHUD *hud = (HFProgressHUD *)subview;
            [hud hideAnimated:YES];
        }
    }
    
    for (UIView *subview in [HFWindowVCHelper currentVC].view.subviews) {
        if ([subview isKindOfClass:[HFProgressHUD class]]) {
            HFProgressHUD *hud = (HFProgressHUD *)subview;
            [hud hideAnimated:YES];
        }
    }
}

#pragma mark - private methods
+ (HFProgressHUD *)createMBProgressHUDviewWithMessage:(NSString *)message isWindiw:(BOOL)isWindow {
    UIView *view = isWindow ? (UIView *)[HFWindowVCHelper currentWindow] : [HFWindowVCHelper currentVC].view;
    HFProgressHUD *hud = [HFProgressHUD showHUDAddedTo:view animated:YES];
    // 更深的黑色背景
    hud.label.text = message ? message : @"加载中...";
    hud.label.font = [UIFont systemFontOfSize:15.f];
    hud.contentColor = [UIColor whiteColor];
    hud.removeFromSuperViewOnHide = YES;
    hud.bezelView.style = HFProgressHUDBackgroundStyleSolidColor;
    hud.bezelView.backgroundColor = [UIColor colorWithWhite:0 alpha:0.7];
    hud.backgroundView.style = HFProgressHUDBackgroundStyleSolidColor;
    hud.backgroundView.backgroundColor = [UIColor colorWithWhite:0.0 alpha:1.0];
    hud.backgroundView.color = [UIColor clearColor];
    return hud;
}

+ (UIImage *)loadBundleImage:(NSString *)imageName {
    NSBundle *currentBundle = [NSBundle bundleForClass:[self class]];
    NSString *imagePath = [currentBundle pathForResource:[NSString stringWithFormat:@"%@.png",imageName] ofType:nil inDirectory:@"HFUtils.bundle/HFUtils.bundle"];
    return [UIImage imageWithContentsOfFile:imagePath];
}

@end
