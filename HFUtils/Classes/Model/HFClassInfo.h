//
//  HFClassInfo.h
//  HFUtils
//
//  Created by liuhongfei on 2023/9/5.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Type encoding's type.
 */
typedef NS_OPTIONS(NSUInteger, HFEncodingType) {
    HFEncodingTypeMask       = 0xFF, ///< mask of type value
    HFEncodingTypeUnknown    = 0, ///< unknown
    HFEncodingTypeVoid       = 1, ///< void
    HFEncodingTypeBool       = 2, ///< bool
    HFEncodingTypeInt8       = 3, ///< char / BOOL
    HFEncodingTypeUInt8      = 4, ///< unsigned char
    HFEncodingTypeInt16      = 5, ///< short
    HFEncodingTypeUInt16     = 6, ///< unsigned short
    HFEncodingTypeInt32      = 7, ///< int
    HFEncodingTypeUInt32     = 8, ///< unsigned int
    HFEncodingTypeInt64      = 9, ///< long long
    HFEncodingTypeUInt64     = 10, ///< unsigned long long
    HFEncodingTypeFloat      = 11, ///< float
    HFEncodingTypeDouble     = 12, ///< double
    HFEncodingTypeLongDouble = 13, ///< long double
    HFEncodingTypeObject     = 14, ///< id
    HFEncodingTypeClass      = 15, ///< Class
    HFEncodingTypeSEL        = 16, ///< SEL
    HFEncodingTypeBlock      = 17, ///< block
    HFEncodingTypePointer    = 18, ///< void*
    HFEncodingTypeStruct     = 19, ///< struct
    HFEncodingTypeUnion      = 20, ///< union
    HFEncodingTypeCString    = 21, ///< char*
    HFEncodingTypeCArray     = 22, ///< char[10] (for example)
    
    HFEncodingTypeQualifierMask   = 0xFF00,   ///< mask of qualifier
    HFEncodingTypeQualifierConst  = 1 << 8,  ///< const
    HFEncodingTypeQualifierIn     = 1 << 9,  ///< in
    HFEncodingTypeQualifierInout  = 1 << 10, ///< inout
    HFEncodingTypeQualifierOut    = 1 << 11, ///< out
    HFEncodingTypeQualifierBycopy = 1 << 12, ///< bycopy
    HFEncodingTypeQualifierByref  = 1 << 13, ///< byref
    HFEncodingTypeQualifierOneway = 1 << 14, ///< oneway
    
    HFEncodingTypePropertyMask         = 0xFF0000, ///< mask of property
    HFEncodingTypePropertyReadonly     = 1 << 16, ///< readonly
    HFEncodingTypePropertyCopy         = 1 << 17, ///< copy
    HFEncodingTypePropertyRetain       = 1 << 18, ///< retain
    HFEncodingTypePropertyNonatomic    = 1 << 19, ///< nonatomic
    HFEncodingTypePropertyWeak         = 1 << 20, ///< weak
    HFEncodingTypePropertyCustomGetter = 1 << 21, ///< getter=
    HFEncodingTypePropertyCustomSetter = 1 << 22, ///< setter=
    HFEncodingTypePropertyDynamic      = 1 << 23, ///< @dynamic
};

/**
 Get the type from a Type-Encoding string.
 
 @param typeEncoding  A Type-Encoding string.
 @return The encoding type.
 */
HFEncodingType HFEncodingGetType(const char *typeEncoding);

/**
 Instance variable information.
 */
@interface HFClassIvarInfo : NSObject

@property (nonatomic, assign, readonly) Ivar ivar;              ///< ivar opaque struct
@property (nonatomic, strong, readonly) NSString *name;         ///< Ivar's name
@property (nonatomic, assign, readonly) ptrdiff_t offset;       ///< Ivar's offset
@property (nonatomic, strong, readonly) NSString *typeEncoding; ///< Ivar's type encoding
@property (nonatomic, assign, readonly) HFEncodingType type;    ///< Ivar's type

/**
 Creates and returns an ivar info object.
 
 @param ivar ivar opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithIvar:(Ivar)ivar;

@end

/**
 Method information.
 */
@interface HFClassMethodInfo : NSObject

@property (nonatomic, assign, readonly) Method method;                  ///< method opaque struct
@property (nonatomic, strong, readonly) NSString *name;                 ///< method name
@property (nonatomic, assign, readonly) SEL sel;                        ///< method's selector
@property (nonatomic, assign, readonly) IMP imp;                        ///< method's implementation
@property (nonatomic, strong, readonly) NSString *typeEncoding;         ///< method's parameter and return types
@property (nonatomic, strong, readonly) NSString *returnTypeEncoding;   ///< return value's type
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *argumentTypeEncodings; ///< array of arguments' type

/**
 Creates and returns a method info object.
 
 @param method method opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithMethod:(Method)method;

@end

/**
 Property information.
 */
@interface HFClassPropertyInfo : NSObject

@property (nonatomic, assign, readonly) objc_property_t property; ///< property's opaque struct
@property (nonatomic, strong, readonly) NSString *name;           ///< property's name
@property (nonatomic, assign, readonly) HFEncodingType type;      ///< property's type
@property (nonatomic, strong, readonly) NSString *typeEncoding;   ///< property's encoding value
@property (nonatomic, strong, readonly) NSString *ivarName;       ///< property's ivar name
@property (nullable, nonatomic, assign, readonly) Class cls;      ///< may be nil
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *protocols; ///< may nil
@property (nonatomic, assign, readonly) SEL getter;               ///< getter (nonnull)
@property (nonatomic, assign, readonly) SEL setter;               ///< setter (nonnull)

/**
 Creates and returns a property info object.
 
 @param property property opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithProperty:(objc_property_t)property;

@end

/**
 Class information for a class.
 */
@interface HFClassInfo : NSObject

@property (nonatomic, assign, readonly) Class cls; ///< class object
@property (nullable, nonatomic, assign, readonly) Class superCls; ///< super class object
@property (nullable, nonatomic, assign, readonly) Class metaCls;  ///< class's meta class object
@property (nonatomic, readonly) BOOL isMeta; ///< whether this class is meta class
@property (nonatomic, strong, readonly) NSString *name; ///< class name
@property (nullable, nonatomic, strong, readonly) HFClassInfo *superClassInfo; ///< super class's class info
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, HFClassIvarInfo *> *ivarInfos; ///< ivars
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, HFClassMethodInfo *> *methodInfos; ///< methods
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, HFClassPropertyInfo *> *propertyInfos; ///< properties

/**
 If the class is changed (for example: you add a method to this class with
 'class_addMethod()'), you should call this method to refresh the class info cache.
 
 After called this method, `needUpdate` will returns `YES`, and you should call 
 'classInfoWithClass' or 'classInfoWithClassName' to get the updated class info.
 */
- (void)setNeedUpdate;

/**
 If this method returns `YES`, you should stop using this instance and call
 `classInfoWithClass` or `classInfoWithClassName` to get the updated class info.
 
 @return Whether this class info need update.
 */
- (BOOL)needUpdate;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param cls A class.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClass:(Class)cls;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param className A class name.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClassName:(NSString *)className;

@end

NS_ASSUME_NONNULL_END
