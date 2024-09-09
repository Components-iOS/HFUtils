//
//  HFSwitchView.h
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#if defined(__has_feature) && __has_feature(modules)
@import UIKit;
#else
#import <UIKit/UIKit.h>
#endif

@interface HFSwitchView : UIView

@property (strong, nonatomic) UIColor *tintColor UI_APPEARANCE_SELECTOR;
@property (strong, nonatomic) UIColor *labelColor UI_APPEARANCE_SELECTOR;
@property (strong, nonatomic) UIFont *labelFont UI_APPEARANCE_SELECTOR;
@property (strong, nonatomic) NSString *labelText UI_APPEARANCE_SELECTOR;
@property (nonatomic, getter=isSelected) BOOL selected;

@end
