//
//  HFViewController.m
//  HFUtils
//
//  Created by liuhongfei on 09/06/2024.
//  Copyright (c) 2024 liuhongfei. All rights reserved.
//

#import "HFViewController.h"
#import <HFUtils/HFUtils.h>

@interface HFViewController ()

@end

@implementation HFViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"HFUtils";
    self.view.backgroundColor = UIColor.whiteColor;
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        dispatch_async(dispatch_get_main_queue(), ^{
//            [HFProgressHUD showActivityMessageInWindow:nil];
//            [HFProgressHUD showActivityMessageInView:nil];
//            [HFProgressHUD showTipMessageInWindow:@"在window"];
//            [HFProgressHUD showTipMessageInView:@"在View"];
//            [HFProgressHUD showErrorMessage:@"显示错误"];
//            [HFProgressHUD showWarnMessage:@"显示警告"];
//            [HFProgressHUD showInfoMessage:@"显示信息"];
//            [HFProgressHUD showSuccessMessage:@"加载成功"];
            
            HFAlertView *alert = [[HFAlertView alloc] initWithNewWindow];
            [alert setHorizontalButtons:YES];
            [alert showSuccess:@"11111" subTitle:@"22222" closeButtonTitle:@"确定" duration:0.0f];

            [self performSelector:@selector(dismiss) withObject:nil afterDelay:2];
        });
    });
}

- (void)dismiss {
    dispatch_async(dispatch_get_main_queue(), ^{
//        [HFProgressHUD hideHUD];
    });
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
