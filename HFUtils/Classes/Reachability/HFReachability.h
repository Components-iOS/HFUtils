//
//  HFReachability.h
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>

//! Project version number for MacOSReachability.
FOUNDATION_EXPORT double HFReachabilityVersionNumber;

//! Project version string for MacOSReachability.
FOUNDATION_EXPORT const unsigned char HFReachabilityVersionString[];

/** 
 * Create NS_ENUM macro if it does not exist on the targeted version of iOS or OS X.
 *
 * @see http://nshipster.com/ns_enum-ns_options/
 **/
#ifndef NS_ENUM
#define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#endif

extern NSString *const kHFReachabilityChangedNotification;

typedef NS_ENUM(NSInteger, HFNetworkStatus) {
    // Apple NetworkStatus Compatible Names.
    HFNotReachable = 0,
    HFReachableViaWiFi = 2,
    HFReachableViaWWAN = 1
};

@class HFReachability;

typedef void (^HFNetworkReachable)(HFReachability * reachability);
typedef void (^HFNetworkUnreachable)(HFReachability * reachability);
typedef void (^HFNetworkReachability)(HFReachability * reachability, SCNetworkConnectionFlags flags);


@interface HFReachability : NSObject

@property (nonatomic, copy) HFNetworkReachable reachableBlock;
@property (nonatomic, copy) HFNetworkUnreachable unreachableBlock;
@property (nonatomic, copy) HFNetworkReachability reachabilityBlock;

@property (nonatomic, assign) BOOL reachableOnWWAN;

+ (instancetype)reachabilityWithHostname:(NSString *)hostname;
// This is identical to the function above, but is here to maintain
// compatibility with Apples original code. (see .m)
+ (instancetype)reachabilityWithHostName:(NSString *)hostname;
+ (instancetype)reachabilityForInternetConnection;
+ (instancetype)reachabilityWithAddress:(void *)hostAddress;
+ (instancetype)reachabilityForLocalWiFi;
+ (instancetype)reachabilityWithURL:(NSURL *)url;

- (instancetype)initWithReachabilityRef:(SCNetworkReachabilityRef)ref;

- (BOOL)startNotifier;
- (void)stopNotifier;

- (BOOL)isReachable;
- (BOOL)isReachableViaWWAN;
- (BOOL)isReachableViaWiFi;

// WWAN may be available, but not active until a connection has been established.
// WiFi may require a connection for VPN on Demand.
// Identical DDG variant.
- (BOOL)isConnectionRequired;
// Apple's routine.
- (BOOL)connectionRequired;
// Dynamic, on demand connection?
- (BOOL)isConnectionOnDemand;
// Is user intervention required?
- (BOOL)isInterventionRequired;

- (HFNetworkStatus)currentReachabilityStatus;
- (SCNetworkReachabilityFlags)reachabilityFlags;
- (NSString *)currentReachabilityString;
- (NSString *)currentReachabilityFlags;

@end
