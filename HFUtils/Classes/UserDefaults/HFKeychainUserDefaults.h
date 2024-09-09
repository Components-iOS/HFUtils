//
//  HFKeychainUserDefaults.h
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import "HFUserObject.h"

@interface HFKeychainUserDefaults : HFUserObject

/// HFKeychainUserDefaults 是存储于Keychain中的单例对象.在安全性相比于SDUserDefaults更高,但是在越狱手机上仍然存在风险.
+ (instancetype)standardUserDefaults;

// 请在下方添加你所需要保存的属性,注意要遵循NSCoding协议,或者继承于SDCodingObject类 ❗️❗️❗️❗️❗️暂不支持int,float,BOOL等类型❗️❗️❗️❗️❗️

// 例如
// @property(nonatomic,copy)NSString *name;
// @property(nonatomic,copy)NSString *password;
// @property(nonatomic,strong)TextModel *testModel;

@end
