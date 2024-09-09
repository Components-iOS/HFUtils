//
//  HFUserDefaults.h
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import "HFUserObject.h"

@interface HFUserDefaults : HFUserObject

/// HFUserDefaults 是用户偏好设置存储单例对象.
+ (instancetype)standardUserDefaults;

// 请在下方添加你所需要保存的属性,注意要遵循NSCoding协议,或者继承于SDCodingObject类 ❗️❗️❗️❗️❗️暂不支持int,float,BOOL等类型❗️❗️❗️❗️❗️

// 例如
// @property(nonatomic,copy)NSString *name;
// @property(nonatomic,copy)NSString *password;
// @property(nonatomic,strong)TextModel *testModel;

@end
