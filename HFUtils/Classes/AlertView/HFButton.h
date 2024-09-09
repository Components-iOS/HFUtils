//
//  HFButton.h
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#if defined(__has_feature) && __has_feature(modules)
@import UIKit;
#else
#import <UIKit/UIKit.h>
#endif

@class HFTimerDisplay;

@interface HFButton : UIButton

typedef void (^HFActionBlock)(void);
typedef BOOL (^HFValidationBlock)(void);
typedef NSDictionary* (^CompleteButtonFormatBlock)(void);
typedef NSDictionary* (^ButtonFormatBlock)(void);

// Action Types
typedef NS_ENUM(NSInteger, HFActionType)
{
    HFNone,
    HFSelector,
    HFBlock
};

/** Set button action type.
 *
 * Holds the button action type.
 */
@property HFActionType actionType;

/** Set action button block.
 *
 * TODO
 */
@property (copy, nonatomic) HFActionBlock actionBlock;

/** Set Validation button block.
 *
 * Set one kind of validation and keeps the alert visible until the validation is successful
 */
@property (copy, nonatomic) HFValidationBlock validationBlock;

/** Set Complete button format block.
 *
 * Holds the complete button format block.
 * Support keys : backgroundColor, borderWidth, borderColor, textColor
 */
@property (copy, nonatomic) CompleteButtonFormatBlock completeButtonFormatBlock;

/** Set button format block.
 *
 * Holds the button format block.
 * Support keys : backgroundColor, borderWidth, borderColor, textColor
 */
@property (copy, nonatomic) ButtonFormatBlock buttonFormatBlock;

/** Set HFButton color.
 *
 * Set HFButton color.
 */
@property (strong, nonatomic) UIColor *defaultBackgroundColor UI_APPEARANCE_SELECTOR;

/** Set Target object.
 *
 * Target is an object that holds the information necessary to send a message to another object when an event occurs.
 */
@property id target;

/** Set selector id.
 *
 * A selector is the name used to select a method to execute for an object,
 * or the unique identifier that replaces the name when the source code is compiled.
 */
@property SEL selector;

/** Parse button configuration
 *
 * Parse ButtonFormatBlock and CompleteButtonFormatBlock setting custom configuration.
 * Set keys : backgroundColor, borderWidth, borderColor, textColor
 */
- (void)parseConfig:(NSDictionary *)buttonConfig;

/** Set button timer.
 *
 * Holds the button timer, if present.
 */
@property (strong, nonatomic) HFTimerDisplay *timer;

/** Init method
 *
 */
- (instancetype)initWithWindowWidth:(CGFloat)windowWidth;

/** Adjust width of the button according to the width of the alert and
 * the number of buttons. Only used when buttons are horizontally aligned.
 *
 * @param windowWidth The width of the alert.
 * @param numberOfButtons The number of buttons in the alert.
 */
- (void)adjustWidthWithWindowWidth:(CGFloat)windowWidth numberOfButtons:(NSUInteger)numberOfButtons;

@end
