//
//  HFMASCompositeConstraint.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFMASConstraint.h"
#import "HFMASUtilities.h"

/**
 *	A group of HFMASConstraint objects
 */
@interface HFMASCompositeConstraint : HFMASConstraint

/**
 *	Creates a composite with a predefined array of children
 *
 *	@param	children	child HFMASConstraints
 *
 *	@return	a composite constraint
 */
- (id)initWithChildren:(NSArray *)children;

@end
