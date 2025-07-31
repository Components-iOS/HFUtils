//
//  NSArray+HFMASAdditions.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFMASUtilities.h"
#import "HFMASConstraintMaker.h"
#import "HFMASViewAttribute.h"

typedef NS_ENUM(NSUInteger, MASAxisType) {
    MASAxisTypeHorizontal,
    MASAxisTypeVertical
};

@interface NSArray (HFMASAdditions)

/**
 *  Creates a HFMASConstraintMaker with each view in the callee.
 *  Any constraints defined are added to the view or the appropriate superview once the block has finished executing on each view
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to each view.
 *
 *  @return Array of created HFMASConstraints
 */
- (NSArray *)mas_makeConstraints:(void (NS_NOESCAPE ^)(HFMASConstraintMaker *make))block;

/**
 *  Creates a HFMASConstraintMaker with each view in the callee.
 *  Any constraints defined are added to each view or the appropriate superview once the block has finished executing on each view.
 *  If an existing constraint exists then it will be updated instead.
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to each view.
 *
 *  @return Array of created/updated HFMASConstraints
 */
- (NSArray *)mas_updateConstraints:(void (NS_NOESCAPE ^)(HFMASConstraintMaker *make))block;

/**
 *  Creates a HFMASConstraintMaker with each view in the callee.
 *  Any constraints defined are added to each view or the appropriate superview once the block has finished executing on each view.
 *  All constraints previously installed for the views will be removed.
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to each view.
 *
 *  @return Array of created/updated HFMASConstraints
 */
- (NSArray *)mas_remakeConstraints:(void (NS_NOESCAPE ^)(HFMASConstraintMaker *make))block;

/**
 *  distribute with fixed spacing
 *
 *  @param axisType     which axis to distribute items along
 *  @param fixedSpacing the spacing between each item
 *  @param leadSpacing  the spacing before the first item and the container
 *  @param tailSpacing  the spacing after the last item and the container
 */
- (void)mas_distributeViewsAlongAxis:(MASAxisType)axisType withFixedSpacing:(CGFloat)fixedSpacing leadSpacing:(CGFloat)leadSpacing tailSpacing:(CGFloat)tailSpacing;

/**
 *  distribute with fixed item size
 *
 *  @param axisType        which axis to distribute items along
 *  @param fixedItemLength the fixed length of each item
 *  @param leadSpacing     the spacing before the first item and the container
 *  @param tailSpacing     the spacing after the last item and the container
 */
- (void)mas_distributeViewsAlongAxis:(MASAxisType)axisType withFixedItemLength:(CGFloat)fixedItemLength leadSpacing:(CGFloat)leadSpacing tailSpacing:(CGFloat)tailSpacing;

@end
