//
//  UIView+HFMASShorthandAdditions.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "View+HFMASAdditions.h"

#ifdef MAS_SHORTHAND

/**
 *	Shorthand view additions without the 'mas_' prefixes,
 *  only enabled if MAS_SHORTHAND is defined
 */
@interface HFMAS_VIEW (HFMASShorthandAdditions)

@property (nonatomic, strong, readonly) HFMASViewAttribute *left;
@property (nonatomic, strong, readonly) HFMASViewAttribute *top;
@property (nonatomic, strong, readonly) HFMASViewAttribute *right;
@property (nonatomic, strong, readonly) HFMASViewAttribute *bottom;
@property (nonatomic, strong, readonly) HFMASViewAttribute *leading;
@property (nonatomic, strong, readonly) HFMASViewAttribute *trailing;
@property (nonatomic, strong, readonly) HFMASViewAttribute *width;
@property (nonatomic, strong, readonly) HFMASViewAttribute *height;
@property (nonatomic, strong, readonly) HFMASViewAttribute *centerX;
@property (nonatomic, strong, readonly) HFMASViewAttribute *centerY;
@property (nonatomic, strong, readonly) HFMASViewAttribute *baseline;
@property (nonatomic, strong, readonly) HFMASViewAttribute *(^attribute)(NSLayoutAttribute attr);

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000) || (__MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)

@property (nonatomic, strong, readonly) HFMASViewAttribute *firstBaseline;
@property (nonatomic, strong, readonly) HFMASViewAttribute *lastBaseline;

#endif

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000)

@property (nonatomic, strong, readonly) HFMASViewAttribute *leftMargin;
@property (nonatomic, strong, readonly) HFMASViewAttribute *rightMargin;
@property (nonatomic, strong, readonly) HFMASViewAttribute *topMargin;
@property (nonatomic, strong, readonly) HFMASViewAttribute *bottomMargin;
@property (nonatomic, strong, readonly) HFMASViewAttribute *leadingMargin;
@property (nonatomic, strong, readonly) HFMASViewAttribute *trailingMargin;
@property (nonatomic, strong, readonly) HFMASViewAttribute *centerXWithinMargins;
@property (nonatomic, strong, readonly) HFMASViewAttribute *centerYWithinMargins;

#endif

#if (__IPHONE_OS_VERSION_MAX_ALLOWED >= 110000) || (__TV_OS_VERSION_MAX_ALLOWED >= 110000)

@property (nonatomic, strong, readonly) HFMASViewAttribute *safeAreaLayoutGuideTop API_AVAILABLE(ios(11.0),tvos(11.0));
@property (nonatomic, strong, readonly) HFMASViewAttribute *safeAreaLayoutGuideBottom API_AVAILABLE(ios(11.0),tvos(11.0));
@property (nonatomic, strong, readonly) HFMASViewAttribute *safeAreaLayoutGuideLeft API_AVAILABLE(ios(11.0),tvos(11.0));
@property (nonatomic, strong, readonly) HFMASViewAttribute *safeAreaLayoutGuideRight API_AVAILABLE(ios(11.0),tvos(11.0));

#endif

- (NSArray *)makeConstraints:(void(^)(HFMASConstraintMaker *make))block;
- (NSArray *)updateConstraints:(void(^)(HFMASConstraintMaker *make))block;
- (NSArray *)remakeConstraints:(void(^)(HFMASConstraintMaker *make))block;

@end

#define MAS_ATTR_FORWARD(attr)  \
- (HFMASViewAttribute *)attr {    \
    return [self mas_##attr];   \
}

@implementation HFMAS_VIEW (HFMASShorthandAdditions)

MAS_ATTR_FORWARD(top);
MAS_ATTR_FORWARD(left);
MAS_ATTR_FORWARD(bottom);
MAS_ATTR_FORWARD(right);
MAS_ATTR_FORWARD(leading);
MAS_ATTR_FORWARD(trailing);
MAS_ATTR_FORWARD(width);
MAS_ATTR_FORWARD(height);
MAS_ATTR_FORWARD(centerX);
MAS_ATTR_FORWARD(centerY);
MAS_ATTR_FORWARD(baseline);

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000) || (__MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)

MAS_ATTR_FORWARD(firstBaseline);
MAS_ATTR_FORWARD(lastBaseline);

#endif

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000)

MAS_ATTR_FORWARD(leftMargin);
MAS_ATTR_FORWARD(rightMargin);
MAS_ATTR_FORWARD(topMargin);
MAS_ATTR_FORWARD(bottomMargin);
MAS_ATTR_FORWARD(leadingMargin);
MAS_ATTR_FORWARD(trailingMargin);
MAS_ATTR_FORWARD(centerXWithinMargins);
MAS_ATTR_FORWARD(centerYWithinMargins);

#endif

#if (__IPHONE_OS_VERSION_MAX_ALLOWED >= 110000) || (__TV_OS_VERSION_MAX_ALLOWED >= 110000)

MAS_ATTR_FORWARD(safeAreaLayoutGuideTop);
MAS_ATTR_FORWARD(safeAreaLayoutGuideBottom);
MAS_ATTR_FORWARD(safeAreaLayoutGuideLeft);
MAS_ATTR_FORWARD(safeAreaLayoutGuideRight);

#endif

- (HFMASViewAttribute *(^)(NSLayoutAttribute))attribute {
    return [self mas_attribute];
}

- (NSArray *)makeConstraints:(void(NS_NOESCAPE ^)(HFMASConstraintMaker *))block {
    return [self mas_makeConstraints:block];
}

- (NSArray *)updateConstraints:(void(NS_NOESCAPE ^)(HFMASConstraintMaker *))block {
    return [self mas_updateConstraints:block];
}

- (NSArray *)remakeConstraints:(void(NS_NOESCAPE ^)(HFMASConstraintMaker *))block {
    return [self mas_remakeConstraints:block];
}

@end

#endif
