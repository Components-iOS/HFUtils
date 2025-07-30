//
//  HFPullMenuCell.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import <UIKit/UIKit.h>
#import "HFPullMenuConfig.h"
#import "HFPullMenuModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface HFPullMenuCell : UITableViewCell

/// 相关配置
@property (nonatomic, strong) HFPullMenuConfig *pullMenuConfig;
/// Menu样式
@property (nonatomic, assign) HFPullMenuStyle pullMenuStyle;
/// Model
@property (nonatomic, strong) HFPullMenuModel *pullMenuModel;
/// 线条颜色
@property (nonatomic, strong) UIColor *lineColor;
/// 最后一栏cell
@property (nonatomic, assign) BOOL isFinalCell;

@end

NS_ASSUME_NONNULL_END
