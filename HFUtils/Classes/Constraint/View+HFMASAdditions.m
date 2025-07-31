//
//  UIView+HFMASAdditions.m
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "View+HFMASAdditions.h"
#import <objc/runtime.h>

@implementation HFMAS_VIEW (HFMASAdditions)

- (NSArray *)mas_makeConstraints:(void(^)(HFMASConstraintMaker *))__attribute__((noescape))block {
    self.translatesAutoresizingMaskIntoConstraints = NO;
    HFMASConstraintMaker *constraintMaker = [[HFMASConstraintMaker alloc] initWithView:self];
    block(constraintMaker);
    return [constraintMaker install];
}

- (NSArray *)mas_updateConstraints:(void(^)(HFMASConstraintMaker *))__attribute__((noescape))block {
    self.translatesAutoresizingMaskIntoConstraints = NO;
    HFMASConstraintMaker *constraintMaker = [[HFMASConstraintMaker alloc] initWithView:self];
    constraintMaker.updateExisting = YES;
    block(constraintMaker);
    return [constraintMaker install];
}

- (NSArray *)mas_remakeConstraints:(void(^)(HFMASConstraintMaker *make))__attribute__((noescape))block {
    self.translatesAutoresizingMaskIntoConstraints = NO;
    HFMASConstraintMaker *constraintMaker = [[HFMASConstraintMaker alloc] initWithView:self];
    constraintMaker.removeExisting = YES;
    block(constraintMaker);
    return [constraintMaker install];
}

#pragma mark - NSLayoutAttribute properties

- (HFMASViewAttribute *)mas_left {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeLeft];
}

- (HFMASViewAttribute *)mas_top {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeTop];
}

- (HFMASViewAttribute *)mas_right {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeRight];
}

- (HFMASViewAttribute *)mas_bottom {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeBottom];
}

- (HFMASViewAttribute *)mas_leading {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeLeading];
}

- (HFMASViewAttribute *)mas_trailing {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeTrailing];
}

- (HFMASViewAttribute *)mas_width {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeWidth];
}

- (HFMASViewAttribute *)mas_height {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeHeight];
}

- (HFMASViewAttribute *)mas_centerX {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeCenterX];
}

- (HFMASViewAttribute *)mas_centerY {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeCenterY];
}

- (HFMASViewAttribute *)mas_baseline {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeBaseline];
}

- (HFMASViewAttribute *(^)(NSLayoutAttribute))mas_attribute
{
    return ^(NSLayoutAttribute attr) {
        return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:attr];
    };
}

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000) || (__MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)

- (HFMASViewAttribute *)mas_firstBaseline {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeFirstBaseline];
}
- (HFMASViewAttribute *)mas_lastBaseline {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeLastBaseline];
}

#endif

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000)

- (HFMASViewAttribute *)mas_leftMargin {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeLeftMargin];
}

- (HFMASViewAttribute *)mas_rightMargin {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeRightMargin];
}

- (HFMASViewAttribute *)mas_topMargin {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeTopMargin];
}

- (HFMASViewAttribute *)mas_bottomMargin {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeBottomMargin];
}

- (HFMASViewAttribute *)mas_leadingMargin {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeLeadingMargin];
}

- (HFMASViewAttribute *)mas_trailingMargin {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeTrailingMargin];
}

- (HFMASViewAttribute *)mas_centerXWithinMargins {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeCenterXWithinMargins];
}

- (HFMASViewAttribute *)mas_centerYWithinMargins {
    return [[HFMASViewAttribute alloc] initWithView:self layoutAttribute:NSLayoutAttributeCenterYWithinMargins];
}

#endif

#if (__IPHONE_OS_VERSION_MAX_ALLOWED >= 110000) || (__TV_OS_VERSION_MAX_ALLOWED >= 110000)

- (HFMASViewAttribute *)mas_safeAreaLayoutGuide {
    return [[HFMASViewAttribute alloc] initWithView:self item:self.safeAreaLayoutGuide layoutAttribute:NSLayoutAttributeBottom];
}
- (HFMASViewAttribute *)mas_safeAreaLayoutGuideTop {
    return [[HFMASViewAttribute alloc] initWithView:self item:self.safeAreaLayoutGuide layoutAttribute:NSLayoutAttributeTop];
}
- (HFMASViewAttribute *)mas_safeAreaLayoutGuideBottom {
    return [[HFMASViewAttribute alloc] initWithView:self item:self.safeAreaLayoutGuide layoutAttribute:NSLayoutAttributeBottom];
}
- (HFMASViewAttribute *)mas_safeAreaLayoutGuideLeft {
    return [[HFMASViewAttribute alloc] initWithView:self item:self.safeAreaLayoutGuide layoutAttribute:NSLayoutAttributeLeft];
}
- (HFMASViewAttribute *)mas_safeAreaLayoutGuideRight {
    return [[HFMASViewAttribute alloc] initWithView:self item:self.safeAreaLayoutGuide layoutAttribute:NSLayoutAttributeRight];
}

#endif

#pragma mark - associated properties

- (id)mas_key {
    return objc_getAssociatedObject(self, @selector(mas_key));
}

- (void)setMas_key:(id)key {
    objc_setAssociatedObject(self, @selector(mas_key), key, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

#pragma mark - heirachy

- (instancetype)mas_closestCommonSuperview:(HFMAS_VIEW *)view {
    HFMAS_VIEW *closestCommonSuperview = nil;

    HFMAS_VIEW *secondViewSuperview = view;
    while (!closestCommonSuperview && secondViewSuperview) {
        HFMAS_VIEW *firstViewSuperview = self;
        while (!closestCommonSuperview && firstViewSuperview) {
            if (secondViewSuperview == firstViewSuperview) {
                closestCommonSuperview = secondViewSuperview;
            }
            firstViewSuperview = firstViewSuperview.superview;
        }
        secondViewSuperview = secondViewSuperview.superview;
    }
    return closestCommonSuperview;
}

@end
