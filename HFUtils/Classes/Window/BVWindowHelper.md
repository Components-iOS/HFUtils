# BVWindowHelper 扩展功能使用指南

BVWindowHelper 现在已经扩展了丰富的实用方法，涵盖了 iOS 开发中的常见需求。以下是各个功能模块的使用示例：

## 📱 基础窗口和视图控制器管理

### 获取当前视图控制器
```objective-c
// 获取当前最顶层的视图控制器
UIViewController *currentVC = [BVWindowHelper currentViewController];

// 获取根视图控制器
UIViewController *rootVC = [BVWindowHelper rootViewController];

// 获取当前导航控制器
UINavigationController *navVC = [BVWindowHelper currentNavigationController];

// 获取当前 TabBar 控制器
UITabBarController *tabVC = [BVWindowHelper currentTabBarController];
```

### 视图控制器导航
```objective-c
// 推送新的视图控制器
MyViewController *vc = [[MyViewController alloc] init];
[BVWindowHelper pushViewController:vc animated:YES];

// 弹出当前视图控制器
[BVWindowHelper popViewControllerAnimated:YES];

// 模态展示视图控制器
[BVWindowHelper presentViewController:vc animated:YES completion:^{
    NSLog(@"展示完成");
}];
```

## 🔔 弹窗和提示功能

### 显示简单提示
```objective-c
// 显示简单提示
[BVWindowHelper showSimpleAlertWithTitle:@"提示" message:@"操作成功"];
```

### 显示确认对话框
```objective-c
[BVWindowHelper showAlertWithTitle:@"确认删除" 
                           message:@"删除后无法恢复，确定要删除吗？"
                       cancelTitle:@"取消"
                      confirmTitle:@"删除"
                     cancelHandler:^{
    NSLog(@"用户取消了删除");
} confirmHandler:^{
    NSLog(@"用户确认删除");
    // 执行删除逻辑
}];
```

### 显示 ActionSheet
```objective-c
NSArray *actions = @[
    @{
        @"title": @"拍照",
        @"style": @(UIAlertActionStyleDefault),
        @"handler": ^{
            NSLog(@"用户选择拍照");
        }
    },
    @{
        @"title": @"从相册选择",
        @"style": @(UIAlertActionStyleDefault),
        @"handler": ^{
            NSLog(@"用户选择从相册选择");
        }
    },
    @{
        @"title": @"删除照片",
        @"style": @(UIAlertActionStyleDestructive),
        @"handler": ^{
            NSLog(@"用户选择删除照片");
        }
    }
];

[BVWindowHelper showActionSheetWithTitle:@"选择操作" 
                                 message:@"请选择图片来源"
                                 actions:actions 
                             cancelTitle:@"取消"];
```

## 📐 屏幕和设备信息

### 屏幕尺寸信息
```objective-c
// 获取屏幕尺寸
CGFloat width = [BVWindowHelper screenWidth];
CGFloat height = [BVWindowHelper screenHeight];
CGSize size = [BVWindowHelper screenSize];
CGFloat scale = [BVWindowHelper screenScale];

NSLog(@"屏幕尺寸: %.0f x %.0f, 缩放比例: %.1f", width, height, scale);
```

### 设备和方向判断
```objective-c
// 设备类型判断
if ([BVWindowHelper isIPad]) {
    NSLog(@"当前设备是 iPad");
} else if ([BVWindowHelper isIPhone]) {
    NSLog(@"当前设备是 iPhone");
}

// 屏幕方向判断
if ([BVWindowHelper isLandscape]) {
    NSLog(@"当前是横屏");
} else if ([BVWindowHelper isPortrait]) {
    NSLog(@"当前是竖屏");
}

// 刘海屏判断
if ([BVWindowHelper hasNotch]) {
    NSLog(@"当前设备有刘海屏/Face ID");
}
```

## ⌨️ 键盘管理

### 键盘控制
```objective-c
// 隐藏键盘
[BVWindowHelper dismissKeyboard];

// 获取当前第一响应者
UIView *firstResponder = [BVWindowHelper firstResponder];
if (firstResponder) {
    NSLog(@"当前第一响应者: %@", firstResponder);
}
```

## 📸 截图功能

### 截图操作
```objective-c
// 截取整个屏幕
UIImage *screenImage = [BVWindowHelper captureScreen];

// 截取指定视图
UIImage *viewImage = [BVWindowHelper captureView:someView];

if (screenImage) {
    // 保存到相册或进行其他处理
    UIImageWriteToSavedPhotosAlbum(screenImage, nil, nil, nil);
}
```

## 🔧 实用工具方法

### 线程管理
```objective-c
// 在主线程执行代码
[BVWindowHelper executeOnMainThread:^{
    // 更新 UI 的代码
    someLabel.text = @"更新完成";
}];

// 延迟执行
[BVWindowHelper executeAfterDelay:2.0 block:^{
    NSLog(@"2秒后执行");
}];

// 判断当前是否为主线程
if ([BVWindowHelper isMainThread]) {
    NSLog(@"当前在主线程");
}
```

## 🎯 实际使用场景示例

### 场景1：登录成功后的处理
```objective-c
// 登录成功后显示提示并跳转
[BVWindowHelper showSimpleAlertWithTitle:@"登录成功" message:@"欢迎回来"];

[BVWindowHelper executeAfterDelay:1.5 block:^{
    // 1.5秒后跳转到主页
    UIViewController *homeVC = [[HomeViewController alloc] init];
    [BVWindowHelper pushViewController:homeVC animated:YES];
}];
```

### 场景2：网络错误处理
```objective-c
[BVWindowHelper showAlertWithTitle:@"网络错误" 
                           message:@"网络连接失败，请检查网络设置"
                       cancelTitle:@"取消"
                      confirmTitle:@"重试"
                     cancelHandler:nil
                    confirmHandler:^{
    // 重新发起网络请求
    [self retryNetworkRequest];
}];
```

### 场景3：相机功能选择
```objective-c
- (void)showImagePickerOptions {
    NSArray *actions = @[
        @{
            @"title": @"拍照",
            @"style": @(UIAlertActionStyleDefault),
            @"handler": ^{
                [self openCamera];
            }
        },
        @{
            @"title": @"从相册选择",
            @"style": @(UIAlertActionStyleDefault),
            @"handler": ^{
                [self openPhotoLibrary];
            }
        }
    ];
    
    [BVWindowHelper showActionSheetWithTitle:nil 
                                     message:@"选择图片来源"
                                     actions:actions 
                                 cancelTitle:@"取消"];
}
```

## 💡 最佳实践建议

1. **统一使用**: 项目中所有需要获取 window、视图控制器的地方都应该使用 `BVWindowHelper`
2. **主线程安全**: UI 相关操作使用 `executeOnMainThread` 确保在主线程执行
3. **错误处理**: 在调用方法前检查返回值是否为 nil
4. **内存管理**: 弹窗的回调 block 注意避免循环引用
5. **设备适配**: 使用设备判断方法来适配不同尺寸的设备

## 🔄 与原有代码的替换

如果项目中还有使用旧的获取方式，可以按照以下方式替换：

```objective-c
// 旧的方式 ❌
UIWindow *window = [UIApplication sharedApplication].delegate.window;
UIViewController *vc = window.rootViewController;

// 新的方式 ✅
UIWindow *window = [BVWindowHelper currentWindow];
UIViewController *vc = [BVWindowHelper rootViewController];
```

通过使用这些扩展方法，可以大大简化日常开发工作，提高代码的一致性和可维护性。