//
//  HFMASConstraint+Private.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFMASConstraint.h"

@protocol HFMASConstraintDelegate;


@interface HFMASConstraint ()

/**
 *  Whether or not to check for an existing constraint instead of adding constraint
 */
@property (nonatomic, assign) BOOL updateExisting;

/**
 *	Usually HFMASConstraintMaker but could be a parent HFMASConstraint
 */
@property (nonatomic, weak) id<HFMASConstraintDelegate> delegate;

/**
 *  Based on a provided value type, is equal to calling:
 *  NSNumber - setOffset:
 *  NSValue with CGPoint - setPointOffset:
 *  NSValue with CGSize - setSizeOffset:
 *  NSValue with HFMASEdgeInsets - setInsets:
 */
- (void)setLayoutConstantWithValue:(NSValue *)value;

@end


@interface HFMASConstraint (Abstract)

/**
 *	Sets the constraint relation to given NSLayoutRelation
 *  returns a block which accepts one of the following:
 *    HFMASViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (HFMASConstraint * (^)(id, NSLayoutRelation))equalToWithRelation;

/**
 *	Override to set a custom chaining behaviour
 */
- (HFMASConstraint *)addConstraintWithLayoutAttribute:(NSLayoutAttribute)layoutAttribute;

@end


@protocol HFMASConstraintDelegate <NSObject>

/**
 *	Notifies the delegate when the constraint needs to be replaced with another constraint. For example
 *  A HFMASViewConstraint may turn into a HFMASCompositeConstraint when an array is passed to one of the equality blocks
 */
- (void)constraint:(HFMASConstraint *)constraint shouldBeReplacedWithConstraint:(HFMASConstraint *)replacementConstraint;

- (HFMASConstraint *)constraint:(HFMASConstraint *)constraint addConstraintWithLayoutAttribute:(NSLayoutAttribute)layoutAttribute;

@end
