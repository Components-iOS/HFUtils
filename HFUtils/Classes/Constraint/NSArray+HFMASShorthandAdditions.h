//
//  NSArray+HFMASShorthandAdditions.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "NSArray+HFMASAdditions.h"

#ifdef MAS_SHORTHAND

/**
 *	Shorthand array additions without the 'mas_' prefixes,
 *  only enabled if MAS_SHORTHAND is defined
 */
@interface NSArray (HFMASShorthandAdditions)

- (NSArray *)makeConstraints:(void(^)(HFMASConstraintMaker *make))block;
- (NSArray *)updateConstraints:(void(^)(HFMASConstraintMaker *make))block;
- (NSArray *)remakeConstraints:(void(^)(HFMASConstraintMaker *make))block;

@end

@implementation NSArray (HFMASShorthandAdditions)

- (NSArray *)makeConstraints:(void(^)(HFMASConstraintMaker *))block {
    return [self mas_makeConstraints:block];
}

- (NSArray *)updateConstraints:(void(^)(HFMASConstraintMaker *))block {
    return [self mas_updateConstraints:block];
}

- (NSArray *)remakeConstraints:(void(^)(HFMASConstraintMaker *))block {
    return [self mas_remakeConstraints:block];
}

@end

#endif
