//
//  HFPullMenuModel.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, HFPullMenuStyle) {
    HFPullMenuDarkStyle = 0,  // 类微信、黑底白字
    HFPullMenuLightStyle      // 类支付宝、白底黑字
};

@interface HFPullMenuModel : NSObject

/// 文字
@property (nonatomic, copy) NSString *title;

/// 图片
@property (nonatomic, copy) NSString *imageName;

@end

NS_ASSUME_NONNULL_END
