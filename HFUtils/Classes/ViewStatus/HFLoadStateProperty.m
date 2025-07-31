//
//  HFLoadStateProperty.m
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFLoadStateProperty.h"

#define defaultNoDataImageKey         @"defaultNoDataImage"
#define defaultErrorImageKey          @"defaultErrorImageKey"
#define defaultNetworkFailImageKey    @"defaultNetworkFailImageKey"
#define defaultNoDataTitleKey         @"defaultNoDataTitleKey"
#define defaultErrorTitleKey          @"defaultErrorTitleKey"
#define defaultNetworkFailTitleKey    @"defaultNetworkFailTitleKey"

@interface HFLoadStateProperty ()

@property (nonatomic, strong) NSMutableDictionary *customerViewDictionary;

@end

@implementation HFLoadStateProperty

+ (instancetype)sharedInstance
{
    static HFLoadStateProperty *property;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        property = [[self alloc] init];
    });
    
    return property;
}

+ (void)setImageNoData:(UIImage *)noData error:(UIImage *)error network:(UIImage *)networkfail
{
    [[[self sharedInstance] customerViewDictionary] setObject:noData forKey:defaultNoDataImageKey];
    [[[self sharedInstance] customerViewDictionary] setObject:error forKey:defaultErrorImageKey];
    [[[self sharedInstance] customerViewDictionary] setObject:networkfail forKey:defaultNetworkFailImageKey];
}

+ (void)setTitleNoData:(NSString *)noData error:(NSString *)error network:(NSString *)networkfail
{
    [[[self sharedInstance] customerViewDictionary] setObject:noData forKey:defaultNoDataTitleKey];
    [[[self sharedInstance] customerViewDictionary] setObject:error forKey:defaultErrorTitleKey];
    [[[self sharedInstance] customerViewDictionary] setObject:networkfail forKey:defaultNetworkFailTitleKey];
}

+ (instancetype)defaultProperties
{
    HFLoadStateProperty *properties = [[HFLoadStateProperty alloc] init];
    return properties;
}

- (void)setText:(NSString *)text forLoadState:(HFViewState)loadState
{
    if (text)
    {
        [self.customerViewDictionary setObject:text forKey:[NSString stringWithFormat:@"text_%@",@(loadState)]];
    }
}

- (NSString *)textForState:(HFViewState)loadState
{
    NSString *text = [self.customerViewDictionary objectForKey: [NSString stringWithFormat:@"text_%@",@(loadState)]];
    if (text == nil) {
        switch (loadState) {
            case HFViewStateNoData:
                text = [[[HFLoadStateProperty sharedInstance] customerViewDictionary] valueForKey:defaultNoDataTitleKey];
                break;
            case HFViewStateError:
                text = [[[HFLoadStateProperty sharedInstance] customerViewDictionary] valueForKey:defaultErrorTitleKey];
                break;
            default:
                text = [[[HFLoadStateProperty sharedInstance] customerViewDictionary] valueForKey:defaultNetworkFailTitleKey];
                break;
        }
    }
    return text;
}

- (void)setDetail:(NSString *)text forLoadState:(HFViewState)loadState
{
    if (text) {
        [self.customerViewDictionary setObject:text forKey:[NSString stringWithFormat:@"detail_%@",@(loadState)]];
    }
}

- (NSString *)detailForState:(HFViewState)loadState
{
    NSString *text = [self.customerViewDictionary objectForKey: [NSString stringWithFormat:@"detail_%@",@(loadState)]];
    if (text == nil) {
        switch (loadState) {
            default:
                text = @"";
                break;
        }
    }
    return text;
}

- (void)setImage:(UIImage *)image forLoadState:(HFViewState)loadState
{
    if (image) {
        [self.customerViewDictionary setObject:image forKey: [NSString stringWithFormat:@"img_%@",@(loadState)]];
    }
}

- (UIImage *)imageForState:(HFViewState)loadState
{
    UIImage *img = [self.customerViewDictionary objectForKey: [NSString stringWithFormat:@"img_%@",@(loadState)]];
    if (img == nil) {
        switch (loadState) {
            case HFViewStateNoData:
                img = [[[HFLoadStateProperty sharedInstance] customerViewDictionary] valueForKey:defaultNoDataImageKey];
                break;
            case HFViewStateError:
                img = [[[HFLoadStateProperty sharedInstance] customerViewDictionary] valueForKey:defaultErrorImageKey];
                break;
            case HFViewStateNetworkFail:
                img = [[[HFLoadStateProperty sharedInstance] customerViewDictionary] valueForKey:defaultNetworkFailImageKey];
                break;
            default:
                img = [[[HFLoadStateProperty sharedInstance] customerViewDictionary] valueForKey:defaultErrorImageKey];
                break;
        }
    }
    return img;
}

- (void)setCustomerView:(UIView *)view forLoadState:(HFViewState)loadState
{
    if (view) {
        [self.customerViewDictionary setObject:view forKey:@(loadState)];
    }
}

- (UIView *)customerViewForLoadState:(HFViewState)loadState
{
    return [self.customerViewDictionary objectForKey:@(loadState)];
}

- (NSMutableDictionary *)customerViewDictionary
{
    if (!_customerViewDictionary) {
        _customerViewDictionary = [NSMutableDictionary dictionaryWithCapacity:15];
    }
    return _customerViewDictionary;
}

@end
