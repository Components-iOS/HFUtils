//
//  HFSwipeTableCell.h
//  HFUtils_Example
//
//  Created by bizconf on 2025/3/1.
//  Copyright © 2025 liuhongfei. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HFSwipeButton.h"

/** Transition types */
typedef NS_ENUM(NSInteger, HFSwipeTransition) {
    HFSwipeTransitionBorder = 0,
    HFSwipeTransitionStatic,
    HFSwipeTransitionDrag,
    HFSwipeTransitionClipCenter,
    HFSwipeTransitionRotate3D
};

/** Compatibility with older versions */
#define HFSwipeTransition3D HFSwipeTransitionRotate3D
#define HFSwipeStateSwippingLeftToRight HFSwipeStateSwipingLeftToRight
#define HFSwipeStateSwippingRightToLeft HFSwipeStateSwipingRightToLeft

/** Swipe directions */
typedef NS_ENUM(NSInteger, HFSwipeDirection) {
    HFSwipeDirectionLeftToRight = 0,
    HFSwipeDirectionRightToLeft
};

/** Swipe state */
typedef NS_ENUM(NSInteger, HFSwipeState) {
    HFSwipeStateNone = 0,
    HFSwipeStateSwipingLeftToRight,
    HFSwipeStateSwipingRightToLeft,
    HFSwipeStateExpandingLeftToRight,
    HFSwipeStateExpandingRightToLeft,
};

/** Swipe Expansion Layout */
typedef NS_ENUM(NSInteger, HFSwipeExpansionLayout) {
    HFSwipeExpansionLayoutBorder = 0,
    HFSwipeExpansionLayoutCenter,
    HFSwipeExpansionLayoutNone
};

/** Swipe Easing Function */
typedef NS_ENUM(NSInteger, HFSwipeEasingFunction) {
    HFSwipeEasingFunctionLinear = 0,
    HFSwipeEasingFunctionQuadIn,
    HFSwipeEasingFunctionQuadOut,
    HFSwipeEasingFunctionQuadInOut,
    HFSwipeEasingFunctionCubicIn,
    HFSwipeEasingFunctionCubicOut,
    HFSwipeEasingFunctionCubicInOut,
    HFSwipeEasingFunctionBounceIn,
    HFSwipeEasingFunctionBounceOut,
    HFSwipeEasingFunctionBounceInOut
};

/**
 * Swipe animation settings
 **/
@interface HFSwipeAnimation : NSObject

/** Animation duration in seconds. Default value 0.3 */
@property (nonatomic, assign) CGFloat duration;
/** Animation easing function. Default value EaseOutBounce */
@property (nonatomic, assign) HFSwipeEasingFunction easingFunction;
/** Override this method to implement custom easing functions */
- (CGFloat)value:(CGFloat)elapsed duration:(CGFloat)duration from:(CGFloat)from to:(CGFloat)to;

@end

/**
 * Swipe settings
 **/
@interface HFSwipeSettings : NSObject

/** Transition used while swiping buttons */
@property (nonatomic, assign) HFSwipeTransition transition;
/** Size proportional threshold to hide/keep the buttons when the user ends swiping. Default value 0.5 */
@property (nonatomic, assign) CGFloat threshold;
/**
 * Optional offset to change the swipe buttons position. Relative to the cell border position. Default value: 0
 * For example it can be used to avoid cropped buttons when sectionIndexTitlesForTableView is used in the UITableView
 */
@property (nonatomic, assign) CGFloat offset;
/** Top margin of the buttons relative to the contentView */
@property (nonatomic, assign) CGFloat topMargin;
/** Bottom margin of the buttons relative to the contentView */
@property (nonatomic, assign) CGFloat bottomMargin;
/** Distance between the buttons. Default value : 0 */
@property (nonatomic, assign) CGFloat buttonsDistance;
/** If true, expands the last button length by safeAreaInsets. Useful for devices with a notch (e.g. iPhone X) */
@property (nonatomic, assign) BOOL expandLastButtonBySafeAreaInsets;

/** Animation settings when the swipe buttons are shown */
@property (nonatomic, strong, nonnull) HFSwipeAnimation *showAnimation;
/** Animation settings when the swipe buttons are hided */
@property (nonatomic, strong, nonnull) HFSwipeAnimation *hideAnimation;
/** Animation settings when the cell is stretched from the swipe buttons */
@property (nonatomic, strong, nonnull) HFSwipeAnimation *stretchAnimation;

/** Property to read or change swipe animation durations. Default value 0.3 */
@property (nonatomic, assign) CGFloat animationDuration DEPRECATED_ATTRIBUTE;

/**
 * If true the buttons are kept swiped when the threshold is reached and the user ends the gesture
 * If false, the buttons are always hidden when the user ends the swipe gesture
 */
@property (nonatomic, assign) BOOL keepButtonsSwiped;

/** If true the table cell is not swiped, just the buttons **/
@property (nonatomic, assign) BOOL onlySwipeButtons;

/** If NO the swipe bounces will be disabled, the swipe motion will stop right after the button */
@property (nonatomic, assign) BOOL enableSwipeBounces;

/**
 * Coefficient applied to cell movement in bounce zone. Set to value between 0.0 and 1.0
 * to make the cell 'resist' swiping after buttons are revealed. Default is 1.0
 */
@property (nonatomic, assign) CGFloat swipeBounceRate;

// default is NO. Controls whether buttons with different width are allowed. Buttons are resized to have the same size by default.
@property (nonatomic) BOOL allowsButtonsWithDifferentWidth;

@end

/**
 * Expansion settings to make expandable buttons
 * Swipe button are not expandable by default
 **/
@interface HFSwipeExpansionSettings : NSObject

/** index of the expandable button (in the left or right buttons arrays) */
@property (nonatomic, assign) NSInteger buttonIndex;
/** if true the button fills the cell on trigger, else it bounces back to its initial position */
@property (nonatomic, assign) BOOL fillOnTrigger;
/** Size proportional threshold to trigger the expansion button. Default value 1.5 */
@property (nonatomic, assign) CGFloat threshold;
/** Optional expansion color. Expanded button's background color is used by default **/
@property (nonatomic, strong, nullable) UIColor * expansionColor;
/** Defines the layout of the expanded button **/
@property (nonatomic, assign) HFSwipeExpansionLayout expansionLayout;
/** Animation settings when the expansion is triggered **/
@property (nonatomic, strong, nonnull) HFSwipeAnimation *triggerAnimation;

/**
 * Property to read or change expansion animation durations. Default value 0.2
 * The target animation is the change of a button from normal state to expanded state
 */
@property (nonatomic, assign) CGFloat animationDuration;

@end

/** helper forward declaration */
@class HFSwipeTableCell;

/**
 * Optional delegate to configure swipe buttons or to receive triggered actions.
 * Buttons can be configured inline when the cell is created instead of using this delegate,
 * but using the delegate improves memory usage because buttons are only created in demand
 */
@protocol HFSwipeTableCellDelegate <NSObject>

@optional

/**
 * Delegate method to enable/disable swipe gestures
 * @return YES if swipe is allowed
 */
- (BOOL)swipeTableCell:(nonnull HFSwipeTableCell *)cell canSwipe:(HFSwipeDirection)direction fromPoint:(CGPoint)point;
- (BOOL)swipeTableCell:(nonnull HFSwipeTableCell *)cell canSwipe:(HFSwipeDirection)direction DEPRECATED_ATTRIBUTE; //backwards compatibility

/**
 * Delegate method invoked when the current swipe state changes
 * @param state the current Swipe State
 * @param gestureIsActive YES if the user swipe gesture is active. No if the uses has already ended the gesture
 */
- (void)swipeTableCell:(nonnull HFSwipeTableCell *)cell didChangeSwipeState:(HFSwipeState)state gestureIsActive:(BOOL)gestureIsActive;

/**
 * Called when the user clicks a swipe button or when a expandable button is automatically triggered
 * @return YES to autohide the current swipe buttons
 */
- (BOOL)swipeTableCell:(nonnull HFSwipeTableCell *)cell tappedButtonAtIndex:(NSInteger)index direction:(HFSwipeDirection)direction fromExpansion:(BOOL)fromExpansion;

/**
 * Delegate method to setup the swipe buttons and swipe/expansion settings
 * Buttons can be any kind of UIView but it's recommended to use the convenience HFSwipeButton class
 * Setting up buttons with this delegate instead of using cell properties improves memory usage because buttons are only created in demand
 * @param cell the UITableViewCell to configure. You can get the indexPath using [tableView indexPathForCell:cell]
 * @param direction The swipe direction (left to right or right to left)
 * @param swipeSettings instance to configure the swipe transition and setting (optional)
 * @param expansionSettings instance to configure button expansions (optional)
 * @return Buttons array
 */
- (nullable NSArray <UIView *>*)swipeTableCell:(nonnull HFSwipeTableCell *)cell swipeButtonsForDirection:(HFSwipeDirection)direction swipeSettings:(nonnull HFSwipeSettings *)swipeSettings expansionSettings:(nonnull HFSwipeExpansionSettings *)expansionSettings;

/**
 * Called when the user taps on a swiped cell
 * @return YES to autohide the current swipe buttons
 */
- (BOOL)swipeTableCell:(nonnull HFSwipeTableCell *)cell shouldHideSwipeOnTap:(CGPoint)point;

/**
 * Called when the cell will begin swiping
 * Useful to make cell changes that only are shown after the cell is swiped open
 */
- (void)swipeTableCellWillBeginSwiping:(nonnull HFSwipeTableCell *)cell;

/**
 * Called when the cell will end swiping
 */
- (void)swipeTableCellWillEndSwiping:(nonnull HFSwipeTableCell *)cell;

@end

/**
 * Swipe Cell class
 * To implement swipe cells you have to override from this class
 * You can create the cells programmatically, using xibs or storyboards
 */
@interface HFSwipeTableCell : UITableViewCell

/** optional delegate (not retained) */
@property (nonatomic, weak, nullable) id <HFSwipeTableCellDelegate>delegate;

/** optional to use contentView alternative. Use this property instead of contentView to support animated views while swiping */
@property (nonatomic, strong, readonly, nonnull) UIView *swipeContentView;

/**
 * Left and right swipe buttons and its settings.
 * Buttons can be any kind of UIView but it's recommended to use the convenience HFSwipeButton class
 */
@property (nonatomic, copy, nonnull) NSArray <UIView *>* leftButtons;
@property (nonatomic, copy, nonnull) NSArray <UIView *>* rightButtons;
@property (nonatomic, strong, nonnull) HFSwipeSettings *leftSwipeSettings;
@property (nonatomic, strong, nonnull) HFSwipeSettings *rightSwipeSettings;

/** Optional settings to allow expandable buttons */
@property (nonatomic, strong, nonnull) HFSwipeExpansionSettings *leftExpansion;
@property (nonatomic, strong, nonnull) HFSwipeExpansionSettings *rightExpansion;

/** Readonly property to fetch the current swipe state */
@property (nonatomic, readonly) HFSwipeState swipeState;
/** Readonly property to check if the user swipe gesture is currently active */
@property (nonatomic, readonly) BOOL isSwipeGestureActive;

// default is NO. Controls whether multiple cells can be swiped simultaneously
@property (nonatomic) BOOL allowsMultipleSwipe;
// default is NO. Controls whether buttons with different width are allowed. Buttons are resized to have the same size by default.
@property (nonatomic) BOOL allowsButtonsWithDifferentWidth DEPRECATED_MSG_ATTRIBUTE("Use HFSwipeSettings.allowsButtonsWithDifferentWidth instead");
// default is YES. Controls whether swipe gesture is allowed when the touch starts into the swiped buttons
@property (nonatomic) BOOL allowsSwipeWhenTappingButtons;
// default is YES. Controls whether swipe gesture is allowed in opposite directions. NO value disables swiping in opposite direction once started in one direction
@property (nonatomic) BOOL allowsOppositeSwipe;
// default is NO. Controls whether the cell selection/highlight status is preserved when expansion occurs
@property (nonatomic) BOOL preservesSelectionStatus;
/*
 default is NO. Controls whether dismissing a swiped cell when tapping outside of the cell generates a real touch event on the other cell.
 Default behaviour is the same as the Mail app on iOS. Enable it if you want to allow to start a new swipe while a cell is already in swiped in a single step.
 */
@property (nonatomic) BOOL touchOnDismissSwipe;

/** Optional background color for swipe overlay. If not set, its inferred automatically from the cell contentView */
@property (nonatomic, strong, nullable) UIColor *swipeBackgroundColor;
/** Property to read or change the current swipe offset programmatically */
@property (nonatomic, assign) CGFloat swipeOffset;

/** Utility methods to show or hide swipe buttons programmatically */
- (void)hideSwipeAnimated:(BOOL)animated;
- (void)hideSwipeAnimated:(BOOL)animated completion:(nullable void(^)(BOOL finished))completion;
- (void)showSwipe:(HFSwipeDirection)direction animated:(BOOL)animated;
- (void)showSwipe:(HFSwipeDirection)direction animated:(BOOL)animated completion:(nullable void(^)(BOOL finished))completion;
- (void)setSwipeOffset:(CGFloat)offset animated:(BOOL)animated completion:(nullable void(^)(BOOL finished))completion;
- (void)setSwipeOffset:(CGFloat)offset animation:(nullable HFSwipeAnimation *)animation completion:(nullable void(^)(BOOL finished))completion;
- (void)expandSwipe:(HFSwipeDirection)direction animated:(BOOL)animated;

/** Refresh method to be used when you want to update the cell contents while the user is swiping */
- (void)refreshContentView;

/**
 * Refresh method to be used when you want to dynamically change the left or right buttons (add or remove)
 * If you only want to change the title or the backgroundColor of a button you can change it's properties (get the button instance from leftButtons or rightButtons arrays)
 * @param usingDelegate if YES new buttons will be fetched using the HFSwipeTableCellDelegate. Otherwise new buttons will be fetched from leftButtons/rightButtons properties.
 */
- (void)refreshButtons:(BOOL)usingDelegate;

@end

