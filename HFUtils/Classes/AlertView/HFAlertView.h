//
//  HFAlertView.h
//  HFUtils
//
//  Created by liuhongfei on 2024/9/6.
//  Copyright © 2024 liuhongfei. All rights reserved.
//
//  Base on SCLAlertView

#if defined(__has_feature) && __has_feature(modules)
@import UIKit;
#else
#import <UIKit/UIKit.h>
#endif
#import "HFButton.h"
#import "HFTextView.h"
#import "HFSwitchView.h"

typedef NSAttributedString* (^HFAttributedFormatBlock)(NSString *value);
typedef void (^HFDismissBlock)(void);
typedef void (^HFDismissAnimationCompletionBlock)(void);
typedef void (^HFShowAnimationCompletionBlock)(void);
typedef void (^HFForceHideBlock)(void);

@interface HFAlertView : UIViewController 

/** Alert Styles
 *
 * Set HFAlertView Style
 */
typedef NS_ENUM(NSInteger, HFAlertViewStyle)
{
    HFAlertViewStyleSuccess,
    HFAlertViewStyleError,
    HFAlertViewStyleNotice,
    HFAlertViewStyleWarning,
    HFAlertViewStyleInfo,
    HFAlertViewStyleEdit,
    HFAlertViewStyleWaiting,
    HFAlertViewStyleQuestion,
    HFAlertViewStyleCustom
};

/** Alert hide animation styles
 *
 * Set HFAlertView hide animation type.
 */
typedef NS_ENUM(NSInteger, HFAlertViewHideAnimation)
{
    HFAlertViewHideAnimationFadeOut,
    HFAlertViewHideAnimationSlideOutToBottom,
    HFAlertViewHideAnimationSlideOutToTop,
    HFAlertViewHideAnimationSlideOutToLeft,
    HFAlertViewHideAnimationSlideOutToRight,
    HFAlertViewHideAnimationSlideOutToCenter,
    HFAlertViewHideAnimationSlideOutFromCenter,
    HFAlertViewHideAnimationSimplyDisappear
};

/** Alert show animation styles
 *
 * Set HFAlertView show animation type.
 */
typedef NS_ENUM(NSInteger, HFAlertViewShowAnimation)
{
    HFAlertViewShowAnimationFadeIn,
    HFAlertViewShowAnimationSlideInFromBottom,
    HFAlertViewShowAnimationSlideInFromTop,
    HFAlertViewShowAnimationSlideInFromLeft,
    HFAlertViewShowAnimationSlideInFromRight,
    HFAlertViewShowAnimationSlideInFromCenter,
    HFAlertViewShowAnimationSlideInToCenter,
    HFAlertViewShowAnimationSimplyAppear
};

/** Alert background styles
 *
 * Set HFAlertView background type.
 */
typedef NS_ENUM(NSInteger, HFAlertViewBackground)
{
    HFAlertViewBackgroundShadow,
    HFAlertViewBackgroundBlur,
    HFAlertViewBackgroundTransparent
};

/** Content view corner radius
 *
 * A float value that replaces the standard content viuew corner radius.
 */
@property CGFloat cornerRadius;

/** Tint top circle
 *
 * A boolean value that determines whether to tint the HFAlertView top circle.
 * (Default: YES)
 */
@property (assign, nonatomic) BOOL tintTopCircle;

/** Use larger icon
 *
 * A boolean value that determines whether to make the HFAlertView top circle icon larger.
 * (Default: NO)
 */
@property (assign, nonatomic) BOOL useLargerIcon;
    
/** Title Label
 *
 * The text displayed as title.
 */
@property (strong, nonatomic) UILabel *labelTitle;

/** Text view with the body message
 *
 * Holds the textview.
 */
@property (strong, nonatomic) UITextView *viewText;

/** Activity Indicator
 *
 * Holds the activityIndicator.
 */
@property (strong, nonatomic) UIActivityIndicatorView *activityIndicatorView;

/** Dismiss on tap outside
 *
 * A boolean value that determines whether to dismiss when tapping outside the HFAlertView.
 * (Default: NO)
 */
@property (assign, nonatomic) BOOL shouldDismissOnTapOutside;

/** Sound URL
 *
 * Holds the sound NSURL path.
 */
@property (strong, nonatomic) NSURL *soundURL;

/** Set text attributed format block
 *
 * Holds the attributed string.
 */
@property (copy, nonatomic) HFAttributedFormatBlock attributedFormatBlock;

/** Set Complete button format block.
 *
 * Holds the button format block.
 * Support keys : backgroundColor, borderWidth, borderColor, textColor
 */
@property (copy, nonatomic) CompleteButtonFormatBlock completeButtonFormatBlock;

/** Set button format block.
 *
 * Holds the button format block.
 * Support keys : backgroundColor, borderWidth, borderColor, textColor
 */
@property (copy, nonatomic) ButtonFormatBlock buttonFormatBlock;

/** Set force hide block.
 *
 * When set force hideview method invocation.
 */
@property (copy, nonatomic) HFForceHideBlock forceHideBlock;

/** Hide animation type
 *
 * Holds the hide animation type.
 * (Default: FadeOut)
 */
@property (nonatomic) HFAlertViewHideAnimation hideAnimationType;

/** Show animation type
 *
 * Holds the show animation type.
 * (Default: SlideInFromTop)
 */
@property (nonatomic) HFAlertViewShowAnimation showAnimationType;

/** Set HFAlertView background type.
 *
 * HFAlertView background type.
 * (Default: Shadow)
 */
@property (nonatomic) HFAlertViewBackground backgroundType;

/** Set custom color to HFAlertView.
 *
 * HFAlertView custom color.
 * (Buttons, top circle and borders)
 */
@property (strong, nonatomic) UIColor *customViewColor;

/** Set custom color to HFAlertView background.
 *
 * HFAlertView background custom color.
 */
@property (strong, nonatomic) UIColor *backgroundViewColor;

/** Set custom tint color for icon image.
 *
 * HFAlertView icon tint color
 */
@property (strong, nonatomic) UIColor *iconTintColor;

/** Set custom circle icon height.
 *
 * Circle icon height
 */
@property (nonatomic) CGFloat circleIconHeight;

/** Set HFAlertView extension bounds.
 *
 * Set new bounds (EXTENSION ONLY)
 */
@property (nonatomic) CGRect extensionBounds;

/** Set status bar hidden.
 *
 * Status bar hidden
 */
@property (nonatomic) BOOL statusBarHidden;

/** Set status bar style.
 *
 * Status bar style
 */
@property (nonatomic) UIStatusBarStyle statusBarStyle;

/** Set horizontal alignment for buttons
 *
 * Horizontal aligment instead of vertically if YES
 */
@property (nonatomic) BOOL horizontalButtons;

/** Initialize HFAlertView using specific width.
 *
 * Init instance
 */
- (instancetype)initWithWidth:(CGFloat)width;

/** Initialize HFAlertView using a new window.
 *
 * Init with new window
 */
- (instancetype)initWithNewWindow;

/** Initialize HFAlertView using a new window.
 *
 * Init with new window with custom width
 */
- (instancetype)initWithNewWindowWidth:(CGFloat)windowWidth;

/** Warns that alerts is gone
 *
 * Warns that alerts is gone using block
 */
- (void)alertIsDismissed:(HFDismissBlock)dismissBlock;

/** Warns that alerts dismiss animation is completed
 *
 * Warns that alerts dismiss animation is completed
 */
- (void)alertDismissAnimationIsCompleted:(HFDismissAnimationCompletionBlock)dismissAnimationCompletionBlock;

/** Warns that alerts show animation is completed
 *
 * Warns that alerts show animation is completed
 */
- (void)alertShowAnimationIsCompleted:(HFShowAnimationCompletionBlock)showAnimationCompletionBlock;

/** Hide HFAlertView
 *
 * Hide HFAlertView using animation and removing from super view.
 */

- (void)hideView;

/** HFAlertView visibility
 *
 * Returns if the alert is visible or not.
 */
- (BOOL)isVisible;

/** Remove Top Circle
 *
 * Remove top circle from HFAlertView.
 */
- (void)removeTopCircle;

/** Add a custom UIView
 *
 * @param customView UIView object to be added above the first HFButton.
 */
- (UIView *)addCustomView:(UIView *)customView;

/** Add Text Field
 *
 * @param title The text displayed on the textfield.
 */
- (HFTextView *)addTextField:(NSString *)title setDefaultText:(NSString *)defaultText;

/** Add a custom Text Field
 *
 * @param textField The custom textfield provided by the programmer.
 */
- (void)addCustomTextField:(UITextField *)textField;

/** Add a switch view
 *
 * @param label The label displayed for the switch.
 */
- (HFSwitchView *)addSwitchViewWithLabel:(NSString *)label;

/** Add Timer Display
 *
 * @param buttonIndex The index of the button to add the timer display to.
 * @param reverse Convert timer to countdown.
 */
- (void)addTimerToButtonIndex:(NSInteger)buttonIndex reverse:(BOOL)reverse;

/** Set Title font family and size
 *
 * @param titleFontFamily The family name used to displayed the title.
 * @param size Font size.
 */
- (void)setTitleFontFamily:(NSString *)titleFontFamily withSize:(CGFloat)size;

/** Set Text field font family and size
 *
 * @param bodyTextFontFamily The family name used to displayed the text field.
 * @param size Font size.
 */
- (void)setBodyTextFontFamily:(NSString *)bodyTextFontFamily withSize:(CGFloat)size;

/** Set Buttons font family and size
 *
 * @param buttonsFontFamily The family name used to displayed the buttons.
 * @param size Font size.
 */
- (void)setButtonsTextFontFamily:(NSString *)buttonsFontFamily withSize:(CGFloat)size;

/** Add a Button with a title and a block to handle when the button is pressed.
 *
 * @param title The text displayed on the button.
 * @param action A block of code to be executed when the button is pressed.
 */
- (HFButton *)addButton:(NSString *)title actionBlock:(HFActionBlock)action;

/** Add a Button with a title, a block to handle validation, and a block to handle when the button is pressed and validation succeeds.
 *
 * @param title The text displayed on the button.
 * @param validationBlock A block of code that will allow you to validate fields or do any other logic you may want to do to determine if the alert should be dismissed or not. Inside of this block, return a BOOL indicating whether or not the action block should be called and the alert dismissed.
 * @param action A block of code to be executed when the button is pressed and validation passes.
 */
- (HFButton *)addButton:(NSString *)title validationBlock:(HFValidationBlock)validationBlock actionBlock:(HFActionBlock)action;

/** Add a Button with a title, a target and a selector to handle when the button is pressed.
 *
 * @param title The text displayed on the button.
 * @param target Add target for particular event.
 * @param selector A method to be executed when the button is pressed.
 */
- (HFButton *)addButton:(NSString *)title target:(id)target selector:(SEL)selector;

/** Show Success HFAlertView
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showSuccess:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showSuccess:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Error HFAlertView
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showError:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showError:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Notice HFAlertView
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showNotice:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showNotice:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Warning HFAlertView
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showWarning:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showWarning:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Info HFAlertView
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showInfo:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showInfo:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Edit HFAlertView
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showEdit:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showEdit:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Title HFAlertView using a predefined type
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param style One of predefined HFAlertView styles.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showTitle:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle style:(HFAlertViewStyle)style closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showTitle:(NSString *)title subTitle:(NSString *)subTitle style:(HFAlertViewStyle)style closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Shows a custom HFAlertView without using a predefined type, allowing for a custom image and color to be specified.
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param image A UIImage object to be used as the icon for the alert view.
 * @param color A UIColor object to be used to tint the background of the icon circle and the buttons.
 * @param title The title text of the alert view.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showCustom:(UIViewController *)vc image:(UIImage *)image color:(UIColor *)color title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showCustom:(UIImage *)image color:(UIColor *)color title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Waiting HFAlertView with UIActityIndicator.
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showWaiting:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showWaiting:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

/** Show Question HFAlertView
 *
 * @param vc The view controller the alert view will be displayed in.
 * @param title The text displayed on the button.
 * @param subTitle The subtitle text of the alert view.
 * @param closeButtonTitle The text for the close button.
 * @param duration The amount of time the alert will remain on screen until it is automatically dismissed. If automatic dismissal is not desired, set to 0.
 */
- (void)showQuestion:(UIViewController *)vc title:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;
- (void)showQuestion:(NSString *)title subTitle:(NSString *)subTitle closeButtonTitle:(NSString *)closeButtonTitle duration:(NSTimeInterval)duration;

@end

@protocol HFItemsBuilder__Protocol__Fluent <NSObject>
- (void)setupFluent;
@end

@interface HFAlertViewBuilder__WithFluent: NSObject <HFItemsBuilder__Protocol__Fluent> @end

@interface HFAlertViewShowBuilder : HFAlertViewBuilder__WithFluent

@property(weak, nonatomic, readonly) UIViewController *parameterViewController;
@property(copy, nonatomic, readonly) UIImage *parameterImage;
@property(copy, nonatomic, readonly) UIColor *parameterColor;
@property(copy, nonatomic, readonly) NSString *parameterTitle;
@property(copy, nonatomic, readonly) NSString *parameterSubTitle;
@property(copy, nonatomic, readonly) NSString *parameterCompleteText;
@property(copy, nonatomic, readonly) NSString *parameterCloseButtonTitle;
@property(assign, nonatomic, readonly) HFAlertViewStyle parameterStyle;
@property(assign, nonatomic, readonly) NSTimeInterval parameterDuration;

#pragma mark - Setters
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^viewController)(UIViewController *viewController);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^image)(UIImage *image);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^color)(UIColor *color);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^title)(NSString *title);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^subTitle)(NSString *subTitle);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^completeText)(NSString *completeText);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^style)(HFAlertViewStyle style);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^closeButtonTitle)(NSString *closeButtonTitle);
@property(copy, nonatomic, readonly) HFAlertViewShowBuilder *(^duration)(NSTimeInterval duration);

- (void)showAlertView:(HFAlertView *)alertView;
- (void)showAlertView:(HFAlertView *)alertView onViewController:(UIViewController *)controller;
@property(copy, nonatomic, readonly) void (^show)(HFAlertView *view, UIViewController *controller);
@end

@interface HFALertViewTextFieldBuilder : HFAlertViewBuilder__WithFluent

#pragma mark - Available later after adding
@property(weak, nonatomic, readonly) HFTextView *textField;

#pragma mark - Setters
@property(copy, nonatomic, readonly) HFALertViewTextFieldBuilder *(^title) (NSString *title);

@end

@interface HFALertViewButtonBuilder : HFAlertViewBuilder__WithFluent

#pragma mark - Available later after adding
@property(weak, nonatomic, readonly) HFButton *button;

#pragma mark - Setters
@property(copy, nonatomic, readonly) HFALertViewButtonBuilder *(^title) (NSString *title);
@property(copy, nonatomic, readonly) HFALertViewButtonBuilder *(^target) (id target);
@property(copy, nonatomic, readonly) HFALertViewButtonBuilder *(^selector) (SEL selector);
@property(copy, nonatomic, readonly) HFALertViewButtonBuilder *(^actionBlock) (void(^actionBlock)(void));
@property(copy, nonatomic, readonly) HFALertViewButtonBuilder *(^validationBlock) (BOOL(^validationBlock)(void));

@end

@interface HFAlertViewBuilder : HFAlertViewBuilder__WithFluent

#pragma mark - Parameters
@property (strong, nonatomic, readonly) HFAlertView *alertView;

#pragma mark - Init
- (instancetype)init;
- (instancetype)initWithNewWindow;
- (instancetype)initWithNewWindowWidth:(CGFloat)width;

#pragma mark - Properties
@property(copy, nonatomic) HFAlertViewBuilder *(^cornerRadius) (CGFloat cornerRadius);
@property(copy, nonatomic) HFAlertViewBuilder *(^tintTopCircle) (BOOL tintTopCircle);
@property(copy, nonatomic) HFAlertViewBuilder *(^useLargerIcon) (BOOL useLargerIcon);
@property(copy, nonatomic) HFAlertViewBuilder *(^labelTitle) (UILabel *labelTitle);
@property(copy, nonatomic) HFAlertViewBuilder *(^viewText) (UITextView *viewText);
@property(copy, nonatomic) HFAlertViewBuilder *(^activityIndicatorView) (UIActivityIndicatorView *activityIndicatorView);
@property(copy, nonatomic) HFAlertViewBuilder *(^shouldDismissOnTapOutside) (BOOL shouldDismissOnTapOutside);
@property(copy, nonatomic) HFAlertViewBuilder *(^soundURL) (NSURL *soundURL);
@property(copy, nonatomic) HFAlertViewBuilder *(^attributedFormatBlock) (HFAttributedFormatBlock attributedFormatBlock);
@property(copy, nonatomic) HFAlertViewBuilder *(^completeButtonFormatBlock) (CompleteButtonFormatBlock completeButtonFormatBlock);
@property(copy, nonatomic) HFAlertViewBuilder *(^buttonFormatBlock) (ButtonFormatBlock buttonFormatBlock);
@property(copy, nonatomic) HFAlertViewBuilder *(^forceHideBlock) (HFForceHideBlock forceHideBlock);
@property(copy, nonatomic) HFAlertViewBuilder *(^hideAnimationType) (HFAlertViewHideAnimation hideAnimationType);
@property(copy, nonatomic) HFAlertViewBuilder *(^showAnimationType) (HFAlertViewShowAnimation showAnimationType);
@property(copy, nonatomic) HFAlertViewBuilder *(^backgroundType) (HFAlertViewBackground backgroundType);
@property(copy, nonatomic) HFAlertViewBuilder *(^customViewColor) (UIColor *customViewColor);
@property(copy, nonatomic) HFAlertViewBuilder *(^backgroundViewColor) (UIColor *backgroundViewColor);
@property(copy, nonatomic) HFAlertViewBuilder *(^iconTintColor) (UIColor *iconTintColor);
@property(copy, nonatomic) HFAlertViewBuilder *(^circleIconHeight) (CGFloat circleIconHeight);
@property(copy, nonatomic) HFAlertViewBuilder *(^extensionBounds) (CGRect extensionBounds);
@property(copy, nonatomic) HFAlertViewBuilder *(^statusBarHidden) (BOOL statusBarHidden);
@property(copy, nonatomic) HFAlertViewBuilder *(^statusBarStyle) (UIStatusBarStyle statusBarStyle);

#pragma mark - Custom Setters
@property(copy, nonatomic) HFAlertViewBuilder *(^alertIsDismissed) (HFDismissBlock dismissBlock);
@property(copy, nonatomic) HFAlertViewBuilder *(^alertDismissAnimationIsCompleted) (HFDismissAnimationCompletionBlock dismissAnimationCompletionBlock);
@property(copy, nonatomic) HFAlertViewBuilder *(^alertShowAnimationIsCompleted) (HFShowAnimationCompletionBlock showAnimationCompletionBlock);
@property(copy, nonatomic) HFAlertViewBuilder *(^removeTopCircle)(void);
@property(copy, nonatomic) HFAlertViewBuilder *(^addCustomView)(UIView *view);
@property(copy, nonatomic) HFAlertViewBuilder *(^addTextField)(NSString *title, NSString *defaultText);
@property(copy, nonatomic) HFAlertViewBuilder *(^addCustomTextField)(UITextField *textField);
@property(copy, nonatomic) HFAlertViewBuilder *(^addSwitchViewWithLabelTitle)(NSString *title);
@property(copy, nonatomic) HFAlertViewBuilder *(^addTimerToButtonIndex)(NSInteger buttonIndex, BOOL reverse);
@property(copy, nonatomic) HFAlertViewBuilder *(^setTitleFontFamily)(NSString *titleFontFamily, CGFloat size);
@property(copy, nonatomic) HFAlertViewBuilder *(^setBodyTextFontFamily)(NSString *bodyTextFontFamily, CGFloat size);
@property(copy, nonatomic) HFAlertViewBuilder *(^setButtonsTextFontFamily)(NSString *buttonsFontFamily, CGFloat size);
@property(copy, nonatomic) HFAlertViewBuilder *(^addButtonWithActionBlock)(NSString *title, HFActionBlock action);
@property(copy, nonatomic) HFAlertViewBuilder *(^addButtonWithValidationBlock)(NSString *title, HFValidationBlock validationBlock, HFActionBlock action);
@property(copy, nonatomic) HFAlertViewBuilder *(^addButtonWithTarget)(NSString *title, id target, SEL selector);

#pragma mark - Builders
@property(copy, nonatomic) HFAlertViewBuilder *(^addButtonWithBuilder)(HFALertViewButtonBuilder *builder);
@property(copy, nonatomic) HFAlertViewBuilder *(^addTextFieldWithBuilder)(HFALertViewTextFieldBuilder *builder);

@end
