//
//  UIViewController+HFMASAdditions.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFMASUtilities.h"
#import "HFMASConstraintMaker.h"
#import "HFMASViewAttribute.h"

#ifdef HFMAS_VIEW_CONTROLLER

@interface HFMAS_VIEW_CONTROLLER (HFMASAdditions)

/**
 *	following properties return a new HFMASViewAttribute with appropriate UILayoutGuide and NSLayoutAttribute
 */
@property (nonatomic, strong, readonly) HFMASViewAttribute *mas_topLayoutGuide;
@property (nonatomic, strong, readonly) HFMASViewAttribute *mas_bottomLayoutGuide;
@property (nonatomic, strong, readonly) HFMASViewAttribute *mas_topLayoutGuideTop;
@property (nonatomic, strong, readonly) HFMASViewAttribute *mas_topLayoutGuideBottom;
@property (nonatomic, strong, readonly) HFMASViewAttribute *mas_bottomLayoutGuideTop;
@property (nonatomic, strong, readonly) HFMASViewAttribute *mas_bottomLayoutGuideBottom;


@end

#endif
