//
//  HFCodingObject.h
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import <Foundation/Foundation.h>

/// HFCodingObject 是利用runtime创建的归档对象,可自定义添加属性
/// ❗️❗️❗️❗️❗️属性必须遵循NSCoding协议❗️❗️❗️❗️❗️
@interface HFCodingObject : NSObject<NSCoding>

/// 不需要归档的属性名称集合
@property (nonatomic, copy) NSArray <NSString *> *unEncodePropertys;

/// 是否需要管理提示Log打印,默认为NO
@property (nonatomic, assign) BOOL closeAlertLog;

@end
