//
//  HFAlertViewStyleKit.h
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#if defined(__has_feature) && __has_feature(modules)
@import Foundation;
@import UIKit;
#else
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif
#import "HFButton.h"

@interface HFAlertViewStyleKit : NSObject

// Images
/** TODO
 *
 * TODO
 */
+ (UIImage *)imageOfCheckmark;

/** TODO
 *
 * TODO
 */
+ (UIImage *)imageOfCross;

/** TODO
 *
 * TODO
 */
+ (UIImage *)imageOfNotice;

/** TODO
 *
 * TODO
 */
+ (UIImage *)imageOfWarning;

/** TODO
 *
 * TODO
 */
+ (UIImage *)imageOfInfo;

/** TODO
 *
 * TODO
 */
+ (UIImage *)imageOfEdit;

/** TODO
 *
 * TODO
 */
+ (UIImage *)imageOfQuestion;

/** TODO
 *
 * TODO
 */
+ (void)drawCheckmark;

/** TODO
 *
 * TODO
 */
+ (void)drawCross;

/** TODO
 *
 * TODO
 */
+ (void)drawNotice;

/** TODO
 *
 * TODO
 */
+ (void)drawWarning;

/** TODO
 *
 * TODO
 */
+ (void)drawInfo;

/** TODO
 *
 * TODO
 */
+ (void)drawEdit;

/** TODO
 *
 * TODO
 */
+ (void)drawQuestion;

@end
