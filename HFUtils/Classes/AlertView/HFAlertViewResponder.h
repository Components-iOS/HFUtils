//
//  HFAlertViewResponder.h
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#if defined(__has_feature) && __has_feature(modules)
@import Foundation;
#else
#import <Foundation/Foundation.h>
#endif
#import "HFAlertView.h"

@interface HFAlertViewResponder : NSObject

/** TODO
 *
 * TODO
 */
- (instancetype)init:(HFAlertView *)alertview;

/** TODO
 *
 * TODO
 */
- (void)close;

@end
