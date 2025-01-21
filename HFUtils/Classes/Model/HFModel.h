//
//  HFModel.h
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import <Foundation/Foundation.h>

#if __has_include(<HFModel/HFModel.h>)
FOUNDATION_EXPORT double HFModelVersionNumber;
FOUNDATION_EXPORT const unsigned char HFModelVersionString[];
#import <HFModel/NSObject+HFModel.h>
#import <HFModel/HFClassInfo.h>
#else
#import "NSObject+HFModel.h"
#import "HFClassInfo.h"
#endif
