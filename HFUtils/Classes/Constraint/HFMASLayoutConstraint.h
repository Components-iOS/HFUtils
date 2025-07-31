//
//  HFMASLayoutConstraint.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFMASUtilities.h"

/**
 *	When you are debugging or printing the constraints attached to a view this subclass
 *  makes it easier to identify which constraints have been created via Masonry
 */
@interface HFMASLayoutConstraint : NSLayoutConstraint

/**
 *	a key to associate with this constraint
 */
@property (nonatomic, strong) id mas_key;

@end
