//
//  HFLoadStateProperty.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import <Foundation/Foundation.h>
#import "UIView+LoadState.h"

typedef void (^NetworkReloadBlock) (void);
typedef void (^NoDataActionBlock) (void);

@interface HFLoadStateProperty : NSObject

/// 网络加载失败视图，指定的点击重新加载执行的block
@property (nonatomic, copy) NoDataActionBlock noDataActionBlock;

///  加载区域insets
// 默认为0，居中,小于0向上偏移，大于0向下
@property (nonatomic, assign) CGFloat contentVerticalOffset;
// 默认为0，图片下方
@property (nonatomic, assign) CGFloat labelOffset;
@property (nonatomic, assign) UIEdgeInsets loadingAreaInsets;
// 忽略导航高度，默认NO
@property (nonatomic, assign) BOOL ignoreNavBar;

@property (nonatomic, assign) CGFloat indicatorOffsetX;
@property (nonatomic, assign) CGFloat indicatorOffsetY;
// 加载的背景alpha，默认0.7
@property (nonatomic, assign) CGFloat indicatorAlpha;

- (void)setImage:(UIImage *)image forLoadState:(HFViewState)loadState;
- (UIImage *)imageForState:(HFViewState)loadState;

- (NSString *)textForState:(HFViewState)loadState;
- (void)setText:(NSString *)text forLoadState:(HFViewState)loadState;
- (NSString *)detailForState:(HFViewState)loadState;
- (void)setDetail:(NSString *)text forLoadState:(HFViewState)loadState;

/**
 * 设置自定义视图
 */
- (void)setCustomerView:(UIView *)view forLoadState:(HFViewState)loadState;

/**
 * 获取设置的自定义视图，由UIView (State) 调用
 */
- (UIView *)customerViewForLoadState:(HFViewState)loadState;

+ (void)setImageNoData:(UIImage *)noData
                 error:(UIImage *)error
               network:(UIImage *)networkfail;

+ (void)setTitleNoData:(NSString *)noData
                 error:(NSString *)error
               network:(NSString *)networkfail;

+ (instancetype)defaultProperties;

@end
