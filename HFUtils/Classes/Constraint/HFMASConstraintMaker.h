//
//  HFMASConstraintMaker.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFMASConstraint.h"
#import "HFMASUtilities.h"

typedef NS_OPTIONS(NSInteger, MASAttribute) {
    MASAttributeLeft = 1 << NSLayoutAttributeLeft,
    MASAttributeRight = 1 << NSLayoutAttributeRight,
    MASAttributeTop = 1 << NSLayoutAttributeTop,
    MASAttributeBottom = 1 << NSLayoutAttributeBottom,
    MASAttributeLeading = 1 << NSLayoutAttributeLeading,
    MASAttributeTrailing = 1 << NSLayoutAttributeTrailing,
    MASAttributeWidth = 1 << NSLayoutAttributeWidth,
    MASAttributeHeight = 1 << NSLayoutAttributeHeight,
    MASAttributeCenterX = 1 << NSLayoutAttributeCenterX,
    MASAttributeCenterY = 1 << NSLayoutAttributeCenterY,
    MASAttributeBaseline = 1 << NSLayoutAttributeBaseline,
    
#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000) || (__MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)
    
    MASAttributeFirstBaseline = 1 << NSLayoutAttributeFirstBaseline,
    MASAttributeLastBaseline = 1 << NSLayoutAttributeLastBaseline,
    
#endif
    
#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000)
    
    MASAttributeLeftMargin = 1 << NSLayoutAttributeLeftMargin,
    MASAttributeRightMargin = 1 << NSLayoutAttributeRightMargin,
    MASAttributeTopMargin = 1 << NSLayoutAttributeTopMargin,
    MASAttributeBottomMargin = 1 << NSLayoutAttributeBottomMargin,
    MASAttributeLeadingMargin = 1 << NSLayoutAttributeLeadingMargin,
    MASAttributeTrailingMargin = 1 << NSLayoutAttributeTrailingMargin,
    MASAttributeCenterXWithinMargins = 1 << NSLayoutAttributeCenterXWithinMargins,
    MASAttributeCenterYWithinMargins = 1 << NSLayoutAttributeCenterYWithinMargins,

#endif
    
};

/**
 *  Provides factory methods for creating HFMASConstraints.
 *  Constraints are collected until they are ready to be installed
 *
 */
@interface HFMASConstraintMaker : NSObject

/**
 *	The following properties return a new HFMASViewConstraint
 *  with the first item set to the makers associated view and the appropriate HFMASViewAttribute
 */
@property (nonatomic, strong, readonly) HFMASConstraint *left;
@property (nonatomic, strong, readonly) HFMASConstraint *top;
@property (nonatomic, strong, readonly) HFMASConstraint *right;
@property (nonatomic, strong, readonly) HFMASConstraint *bottom;
@property (nonatomic, strong, readonly) HFMASConstraint *leading;
@property (nonatomic, strong, readonly) HFMASConstraint *trailing;
@property (nonatomic, strong, readonly) HFMASConstraint *width;
@property (nonatomic, strong, readonly) HFMASConstraint *height;
@property (nonatomic, strong, readonly) HFMASConstraint *centerX;
@property (nonatomic, strong, readonly) HFMASConstraint *centerY;
@property (nonatomic, strong, readonly) HFMASConstraint *baseline;

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000) || (__MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)

@property (nonatomic, strong, readonly) HFMASConstraint *firstBaseline;
@property (nonatomic, strong, readonly) HFMASConstraint *lastBaseline;

#endif

#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (__TV_OS_VERSION_MIN_REQUIRED >= 9000)

@property (nonatomic, strong, readonly) HFMASConstraint *leftMargin;
@property (nonatomic, strong, readonly) HFMASConstraint *rightMargin;
@property (nonatomic, strong, readonly) HFMASConstraint *topMargin;
@property (nonatomic, strong, readonly) HFMASConstraint *bottomMargin;
@property (nonatomic, strong, readonly) HFMASConstraint *leadingMargin;
@property (nonatomic, strong, readonly) HFMASConstraint *trailingMargin;
@property (nonatomic, strong, readonly) HFMASConstraint *centerXWithinMargins;
@property (nonatomic, strong, readonly) HFMASConstraint *centerYWithinMargins;

#endif

/**
 *  Returns a block which creates a new HFMASCompositeConstraint with the first item set
 *  to the makers associated view and children corresponding to the set bits in the
 *  MASAttribute parameter. Combine multiple attributes via binary-or.
 */
@property (nonatomic, strong, readonly) HFMASConstraint *(^attributes)(MASAttribute attrs);

/**
 *	Creates a HFMASCompositeConstraint with type HFMASCompositeConstraintTypeEdges
 *  which generates the appropriate HFMASViewConstraint children (top, left, bottom, right)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) HFMASConstraint *edges;

/**
 *	Creates a HFMASCompositeConstraint with type HFMASCompositeConstraintTypeSize
 *  which generates the appropriate HFMASViewConstraint children (width, height)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) HFMASConstraint *size;

/**
 *	Creates a HFMASCompositeConstraint with type HFMASCompositeConstraintTypeCenter
 *  which generates the appropriate HFMASViewConstraint children (centerX, centerY)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) HFMASConstraint *center;

/**
 *  Whether or not to check for an existing constraint instead of adding constraint
 */
@property (nonatomic, assign) BOOL updateExisting;

/**
 *  Whether or not to remove existing constraints prior to installing
 */
@property (nonatomic, assign) BOOL removeExisting;

/**
 *	initialises the maker with a default view
 *
 *	@param	view	any HFMASConstraint are created with this view as the first item
 *
 *	@return	a new HFMASConstraintMaker
 */
- (id)initWithView:(HFMAS_VIEW *)view;

/**
 *	Calls install method on any HFMASConstraints which have been created by this maker
 *
 *	@return	an array of all the installed HFMASConstraints
 */
- (NSArray *)install;

- (HFMASConstraint * (^)(dispatch_block_t))group;

@end
