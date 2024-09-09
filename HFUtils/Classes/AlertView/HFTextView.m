//
//  HFSwitchView.m
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#import "HFTextView.h"

#define MIN_HEIGHT 30.0f

@implementation HFTextView

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        [self setup];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if(self)
    {
        [self setup];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self setup];
    }
    return self;
}

- (void)setup
{
    self.frame = CGRectMake(0.0f, 0.0f, 0.0f, MIN_HEIGHT);
    self.returnKeyType = UIReturnKeyDone;
    self.borderStyle = UITextBorderStyleRoundedRect;
    self.autocapitalizationType = UITextAutocapitalizationTypeSentences;
    self.clearButtonMode = UITextFieldViewModeWhileEditing;
    self.layer.masksToBounds = YES;
    self.layer.borderWidth = 1.0f;
}

@end
