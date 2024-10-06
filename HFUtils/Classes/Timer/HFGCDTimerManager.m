//
//  HFGCDTimerManager.m
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#define BIWeakObj(o)   @autoreleasepool {} __weak typeof(o) o ## Weak = o;
#define kStringIsEmpty(str) ([str isKindOfClass:[NSNull class]] || str == nil || [str length] < 1 ? YES : NO )

#import "HFGCDTimerManager.h"

static HFGCDTimerManager *_HFGCDTimerManager = nil;

@interface HFGCDTimerManager ()

@property (nonatomic, strong) NSMutableDictionary *timerArray;
@property (nonatomic, strong) NSMutableDictionary *timerActionBlockCacheArray;

@end

@implementation HFGCDTimerManager

#pragma mark - 单例的初始化
+ (HFGCDTimerManager *)defaultManager {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _HFGCDTimerManager = [[HFGCDTimerManager alloc] init];
    });
    
    return _HFGCDTimerManager;
}

#pragma mark - Public Method
/// 启动一个timer
- (void)scheduleGCDTimerWithName:(NSString *)timerName
                        interval:(double)interval
                           queue:(dispatch_queue_t)queue
                         repeats:(BOOL)repeats
                          option:(TimerActionOption)option
                          action:(dispatch_block_t)action {
    if (kStringIsEmpty(timerName)) {
        return;
    }
    
    if (nil == queue) {
        queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    }
    
    // 创建dispatch_source_t的timer
    dispatch_source_t timer = [self.timerArray objectForKey:timerName];
    if (nil == timer) {
        timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
        dispatch_resume(timer);
        [self.timerArray setObject:timer  forKey:timerName];
    }
    
    // 设置首次执行事件、执行间隔和精确度(默认为0.1s)
    dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, interval * NSEC_PER_SEC), interval * NSEC_PER_SEC, 1 * NSEC_PER_SEC);
    
    BIWeakObj(self)
    if (option == CancelPreviousTimerAction) {
        // 取消上一次timer任务
        [self removeActionCacheForTimer:timerName];
        
        dispatch_source_set_event_handler(timer, ^{
            action();
            if (!repeats) {
                [selfWeak cancelTimerWithName:timerName];
            }
        });
    } else if (option == MergePreviousTimerAction) {
        // 合并上一次timer任务
        [self cacheAction:action forTimer:timerName];
        
        dispatch_source_set_event_handler(timer, ^{
            NSMutableArray *actionArray = [self.timerActionBlockCacheArray objectForKey:timerName];
            [actionArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
                dispatch_block_t actionBlock = obj;
                actionBlock();
            }];
            
            [selfWeak removeActionCacheForTimer:timerName];
            
            if (!repeats) {
                [selfWeak cancelTimerWithName:timerName];
            }
        });
    }
}

/// 取消timer
- (void)cancelTimerWithName:(NSString *)timerName {
    dispatch_source_t timer = [self.timerArray objectForKey:timerName];
    if (!timer) return;
    
    [self.timerArray removeObjectForKey:timerName];
    [self.timerActionBlockCacheArray removeObjectForKey:timerName];
    dispatch_source_cancel(timer);
}

#pragma mark - private method
- (void)cacheAction:(dispatch_block_t)action forTimer:(NSString *)timerName {
    id actionArray = [self.timerActionBlockCacheArray objectForKey:timerName];
    
    if (actionArray && [actionArray isKindOfClass:[NSMutableArray class]]) {
        [(NSMutableArray *)actionArray addObject:action];
    } else {
        NSMutableArray *array = [NSMutableArray arrayWithObject:action];
        [self.timerActionBlockCacheArray setObject:array forKey:timerName];
    }
}

- (void)removeActionCacheForTimer:(NSString *)timerName {
    if (![self.timerActionBlockCacheArray objectForKey:timerName]) return;
    
    [self.timerActionBlockCacheArray removeObjectForKey:timerName];
}

#pragma mark - getter && setter
- (NSMutableDictionary *)timerArray {
    if (!_timerArray) {
        _timerArray = [[NSMutableDictionary alloc] init];
    }
    return _timerArray;
}

- (NSMutableDictionary *)timerActionBlockCacheArray {
    if (!_timerActionBlockCacheArray) {
        _timerActionBlockCacheArray = [[NSMutableDictionary alloc] init];
    }
    return _timerActionBlockCacheArray;
}

@end
