//
//  HFPullMenuView.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import <UIKit/UIKit.h>
#import "HFPullMenuConfig.h"
#import "HFPullMenuModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface HFPullMenuView : UIView

/// 文字数组
@property (nonatomic, copy) NSArray *titleArray;
/// 图片数组
@property (nonatomic, copy) NSArray *imageArray;
/// 图文Model数组
@property (nonatomic, copy) NSArray <HFPullMenuModel *>*menuArray;

/// 配置
@property (nonatomic, strong) HFPullMenuConfig *pullMenuConfig;
/// Menu样式
@property (nonatomic, assign) HFPullMenuStyle pullMenuStyle;

/// 主样式color
@property (nonatomic, strong) UIColor *menuBgColor;
/// 蒙层背景Color
@property (nonatomic, strong) UIColor *coverBgColor;
/// 线条颜色
@property (nonatomic, strong) UIColor *lineColor;

/// cell高度
@property (nonatomic, assign) CGFloat menuCellHeight;
/// 最大高度限制，默认：5 * menuCellHeight
@property (nonatomic, assign) CGFloat menuMaxHeight;

/// 小三角高度，45°等腰三角形
@property (nonatomic, assign) CGFloat triangleHeight;
/// 调整使下拉优先 当向下偏转屏幕距离足够，优先向下偏转
@property (nonatomic, assign) BOOL adjustPullDown;

/// Click
@property (nonatomic, copy) void (^selected_callback) (NSInteger index);

/// 初始化方法（推荐）
/// - Parameters:
///   - anchorView: 下拉依赖视图
///   - menuArray: 图文Model数组
///   - titleArray: 文字数组
///   - imageArray: 图片数组
/// - Note: 箭头指向依赖视图
+ (instancetype)pullMenuAnchorView:(UIView *)anchorView;
+ (instancetype)pullMenuAnchorView:(UIView *)anchorView
                        titleArray:(nullable NSArray *)titleArray;
+ (instancetype)pullMenuAnchorView:(UIView *)anchorView
                        titleArray:(nullable NSArray *)titleArray
                        imageArray:(nullable NSArray *)imageArray;
+ (instancetype)pullMenuAnchorView:(UIView *)anchorView
                         menuArray:(nullable NSArray <HFPullMenuModel *>*)menuArray;

/// 初始化方法（推荐）
/// - Parameters:
///   - anchorPoint: 下拉依赖绝对坐标
///   - menuArray: 图文Model数组
///   - titleArray: 文字数组
///   - imageArray: 图片数组
/// - Note: 下拉依赖绝对坐标，箭头指向点
+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint;
+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint
                         titleArray:(nullable NSArray *)titleArray;
+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint
                         titleArray:(nullable NSArray *)titleArray
                         imageArray:(nullable NSArray *)imageArray;
+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint
                          menuArray:(nullable NSArray <HFPullMenuModel *>*)menuArray;

@end

NS_ASSUME_NONNULL_END
