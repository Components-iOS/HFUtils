//
//  HFMASViewConstraint.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFMASViewAttribute.h"
#import "HFMASConstraint.h"
#import "HFMASLayoutConstraint.h"
#import "HFMASUtilities.h"

/**
 *  A single constraint.
 *  Contains the attributes neccessary for creating a NSLayoutConstraint and adding it to the appropriate view
 */
@interface HFMASViewConstraint : HFMASConstraint <NSCopying>

/**
 *	First item/view and first attribute of the NSLayoutConstraint
 */
@property (nonatomic, strong, readonly) HFMASViewAttribute *firstViewAttribute;

/**
 *	Second item/view and second attribute of the NSLayoutConstraint
 */
@property (nonatomic, strong, readonly) HFMASViewAttribute *secondViewAttribute;

/**
 *	initialises the HFMASViewConstraint with the first part of the equation
 *
 *	@param	firstViewAttribute	view.mas_left, view.mas_width etc.
 *
 *	@return	a new view constraint
 */
- (id)initWithFirstViewAttribute:(HFMASViewAttribute *)firstViewAttribute;

/**
 *  Returns all HFMASViewConstraints installed with this view as a first item.
 *
 *  @param  view  A view to retrieve constraints for.
 *
 *  @return An array of HFMASViewConstraints.
 */
+ (NSArray *)installedConstraintsForView:(HFMAS_VIEW *)view;

@end
