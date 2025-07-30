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

@property (nonatomic, strong) UIButton *moreBtn;

@end

@implementation HFViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"HFUtils";
    self.view.backgroundColor = UIColor.whiteColor;
    
    [self testPullMenuView];
}

- (void)testPullMenuView {
    self.moreBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    self.moreBtn.frame = CGRectMake(200, 200, 80, 80);
    self.moreBtn.contentEdgeInsets = UIEdgeInsetsMake(10, 10, 10, 10);
    self.moreBtn.backgroundColor = UIColor.orangeColor;
    [self.moreBtn addTarget:self action:@selector(testMoreBtnDidClick) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.moreBtn];
}

- (void)testMoreBtnDidClick {
    NSArray *titleArray = @[@"开始推流", @"修改会议", @"会中邀请", @"呼叫状态", @"直播间观众", @"直播间评论", @"自动提升嘉宾", @"手动提升嘉宾"];

    HFPullMenuView *menuView = [HFPullMenuView pullMenuAnchorView:self.moreBtn titleArray:titleArray currentWindow:nil];
    menuView.pullMenuStyle = HFPullMenuDarkStyle;
    menuView.menuCellHeight = 40;
    
    menuView.selected_callback = ^(NSInteger index) {
        NSString *moreMenuStr = titleArray[index];
        NSLog(@"%@",moreMenuStr);
    };
}

- (void)testProgressHUD {
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

            [self performSelector:@selector(testDismissProgressHUD) withObject:nil afterDelay:2];
        });
    });
}

- (void)testDismissProgressHUD {
    dispatch_async(dispatch_get_main_queue(), ^{
        [HFProgressHUD hideHUD];
    });
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
