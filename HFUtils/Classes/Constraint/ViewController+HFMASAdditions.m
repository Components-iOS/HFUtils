//
//  UIViewController+HFMASAdditions.m
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "ViewController+HFMASAdditions.h"

#ifdef HFMAS_VIEW_CONTROLLER

@implementation HFMAS_VIEW_CONTROLLER (HFMASAdditions)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (HFMASViewAttribute *)mas_topLayoutGuide {
    return [[HFMASViewAttribute alloc] initWithView:self.view item:self.topLayoutGuide layoutAttribute:NSLayoutAttributeBottom];
}
- (HFMASViewAttribute *)mas_topLayoutGuideTop {
    return [[HFMASViewAttribute alloc] initWithView:self.view item:self.topLayoutGuide layoutAttribute:NSLayoutAttributeTop];
}
- (HFMASViewAttribute *)mas_topLayoutGuideBottom {
    return [[HFMASViewAttribute alloc] initWithView:self.view item:self.topLayoutGuide layoutAttribute:NSLayoutAttributeBottom];
}

- (HFMASViewAttribute *)mas_bottomLayoutGuide {
    return [[HFMASViewAttribute alloc] initWithView:self.view item:self.bottomLayoutGuide layoutAttribute:NSLayoutAttributeTop];
}
- (HFMASViewAttribute *)mas_bottomLayoutGuideTop {
    return [[HFMASViewAttribute alloc] initWithView:self.view item:self.bottomLayoutGuide layoutAttribute:NSLayoutAttributeTop];
}
- (HFMASViewAttribute *)mas_bottomLayoutGuideBottom {
    return [[HFMASViewAttribute alloc] initWithView:self.view item:self.bottomLayoutGuide layoutAttribute:NSLayoutAttributeBottom];
}

#pragma clang diagnostic pop

@end

#endif
