//
//  HFCodingObject.m
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import "HFCodingObject.h"
#import <objc/runtime.h>

@implementation HFCodingObject

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self testPropertyConformsToNSCodingProtocol];
    }
    return self;
}

- (nullable instancetype)initWithCoder:(nonnull NSCoder *)aDecoder {
    if (self = [super init]) {
        unsigned int propertyCount = 0;
        objc_property_t *propertyList = class_copyPropertyList([self class], &propertyCount);
        
        for (int i = 0; i < propertyCount; i++) {
            objc_property_t *thisProperty = &propertyList[i];
            const char *name = property_getName(*thisProperty);
            NSString *propertyName = [NSString stringWithFormat:@"%s",name];
            [self setValue:[aDecoder decodeObjectForKey:propertyName] forKey:propertyName];
        }
        
        free(propertyList);
    }
    return self;
}

// 检测所有成员变量是否遵循NSCoding协议
- (void)testPropertyConformsToNSCodingProtocol {
    unsigned int propertyCount = 0;
    objc_property_t *propertyList = class_copyPropertyList([self class], &propertyCount);
    
    for (int i = 0; i < propertyCount; i++) {
        objc_property_t thisProperty = propertyList[i];
        const char *type = property_getAttributes(thisProperty);
        NSString *typeString = [NSString stringWithUTF8String:type];
        NSArray *attributes = [typeString componentsSeparatedByString:@","];
        NSString *typeAttribute = [attributes objectAtIndex:0];
        
        if ([typeAttribute hasPrefix:@"T@"] && [typeAttribute length] > 1) {
            // turns @"NSDate" into NSDate
            NSString *typeClassName = [typeAttribute substringWithRange:NSMakeRange(3, [typeAttribute length] - 4)];
            Class typeClass = NSClassFromString(typeClassName);
            
            BOOL isConforms = [typeClass conformsToProtocol:@protocol(NSCoding)];
            if (!isConforms) {
                NSLog(@"未遵循NSCoding协议错误,请查看下面的错误日志👇👇👇");
                NSString *exceptionContent = [NSString stringWithFormat:@"%@ 类中的 %@属性 未遵循NSCoding协议,请手动调整",NSStringFromClass([self class]),typeClassName];
                @throw [NSException exceptionWithName:@"property has not NSCoding Protocol" reason:exceptionContent userInfo:nil];
            }
        }
    }
    
    free(propertyList);
}

// 检测用户写的忽略数组是否含有位置属性名,例如@"name" 写成 @"names" 等,默认会有提示.
- (void)setUnEncodePropertys:(NSArray<NSString *> *)unEncodePropertys {
    _unEncodePropertys = unEncodePropertys;
    if (!_closeAlertLog) {
        unsigned int propertyCount = 0;
        objc_property_t *propertyList = class_copyPropertyList([self class], &propertyCount);
        NSMutableArray *propertyNames = [NSMutableArray arrayWithCapacity:16];
        
        for (int i = 0; i < propertyCount; i++) {
            objc_property_t *thisProperty = &propertyList[i];
            const char *name = property_getName(*thisProperty);
            NSString *propertyName = [NSString stringWithFormat:@"%s",name];
            [propertyNames addObject:propertyName];
        }
        
        for (int i = 0; i < _unEncodePropertys.count; i++) {
            if (![propertyNames containsObject:_unEncodePropertys[i]]) {
                NSLog(@"%@ 类中未含有需要忽略归档的属性 %@ ,请检查",NSStringFromClass([self class]),_unEncodePropertys[i]);
            }
        }
        
        free(propertyList);
    }
}

#pragma mark - 归档与解档
- (void)encodeWithCoder:(nonnull NSCoder *)aCoder {
    @try {
        unsigned int propertyCount = 0;
        objc_property_t *propertyList = class_copyPropertyList([self class], &propertyCount);
        for (int i = 0; i < propertyCount; i++) {
            objc_property_t *thisProperty = &propertyList[i];
            const char *name = property_getName(*thisProperty);
            NSString *propertyName = [NSString stringWithFormat:@"%s",name];
            if (_unEncodePropertys != nil && [_unEncodePropertys containsObject:propertyName]) {
                continue;
            }
            id propertyValue = [self valueForKey:propertyName];
            [aCoder encodeObject:propertyValue forKey:propertyName];
        }
        free(propertyList);
    } @catch (NSException *exception) {
        if ([exception.name isEqualToString:@"NSInvalidArgumentException"]) {
            NSLog(@"未遵循NSCoding协议错误,请查看下面的错误日志中的类名👇👇👇");
            @throw exception;
        } else {
            NSLog(@"其他错误,请查看下面的错误日志👇👇👇");
            @throw exception;
        }
    }
}

@end
