//
//  HFPullMenuConfig.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#define HFMenuContentMargin       15          // 默认文本图片边距
#define HFMenuImageWidth          30          // 默认图片最小尺寸
#define HFMenuBorderMinMargin     10          // 默认下拉框边界围栏
#define HFMenuTitleFontSize       15          // 默认文本字体大小

@interface HFPullMenuConfig : NSObject

/// 文本图片边距
@property (nonatomic, assign) CGFloat menuContentMargin;
/// 图片最小尺寸
@property (nonatomic, assign) CGFloat menuImageWidth;
/// 下拉框边界围栏
@property (nonatomic, assign) CGFloat menuBorderMinMargin;
/// 文本字体大小
@property (nonatomic, assign) CGFloat menuTitleFontSize;

@end

NS_ASSUME_NONNULL_END
