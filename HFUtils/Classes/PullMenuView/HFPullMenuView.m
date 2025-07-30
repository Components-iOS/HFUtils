//
//  HFPullMenuView.m
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFPullMenuView.h"
#import "HFPullMenuModel.h"
#import "HFPullMenuCell.h"

@interface HFPullMenuView () <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) UIView *contentView;
/// Llist
@property (nonatomic, strong) UITableView *tableView;
/// Rect
@property (nonatomic, assign) CGRect anchorRect;

@end

@implementation HFPullMenuView

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self setupUI];
    }
    return self;
}

- (void)setupUI {
    self.triangleHeight = 8;
    self.menuCellHeight = 50;
    self.menuMaxHeight = 5 * self.menuCellHeight;
    self.pullMenuStyle = HFPullMenuDarkStyle;
    
    [self addSubview:self.contentView];
    [self.tableView registerClass:[HFPullMenuCell class]
        forCellReuseIdentifier:@"HFPullMenuCell"];
}

#pragma mark - 初始化方法
+ (instancetype)pullMenuAnchorView:(UIView *)anchorView
                     currentWindow:(nullable UIWindow *)currentWindow {
    return [self pullMenuAnchorView:anchorView titleArray:nil currentWindow:currentWindow];
}

+ (instancetype)pullMenuAnchorView:(UIView *)anchorView
                        titleArray:(NSArray *)titleArray
                     currentWindow:(nullable UIWindow *)currentWindow {
    return [self pullMenuAnchorView:anchorView titleArray:titleArray imageArray:nil currentWindow:currentWindow];
}

+ (instancetype)pullMenuAnchorView:(UIView *)anchorView
                        titleArray:(NSArray *)titleArray
                        imageArray:(NSArray *)imageArray
                     currentWindow:(nullable UIWindow *)currentWindow {
    HFPullMenuView *menuView = [self pullMenuAnchorView:anchorView menuArray:nil currentWindow:currentWindow];
    menuView.titleArray = titleArray;
    menuView.imageArray = imageArray;
    return menuView;
}

+ (instancetype)pullMenuAnchorView:(UIView *)anchorView
                         menuArray:(NSArray <HFPullMenuModel *>*)menuArray
                     currentWindow:(nullable UIWindow *)currentWindow {
    if (currentWindow == nil) {
        currentWindow = [[[UIApplication sharedApplication] delegate] window];
    }
    
    HFPullMenuView *menuView = [[HFPullMenuView alloc] init];
    menuView.frame = [UIScreen mainScreen].bounds;
    [currentWindow addSubview:menuView];
    menuView.anchorRect = [anchorView convertRect:anchorView.bounds toView:currentWindow];
    menuView.menuArray = menuArray;
    return menuView;
}

+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint
                      currentWindow:(nullable UIWindow *)currentWindow {
    return [self pullMenuAnchorPoint:anchorPoint titleArray:nil currentWindow:currentWindow];
}

+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint titleArray:(NSArray *)titleArray
                      currentWindow:(nullable UIWindow *)currentWindow {
    return [self pullMenuAnchorPoint:anchorPoint titleArray:titleArray imageArray:nil currentWindow:currentWindow];
}

+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint
                         titleArray:(NSArray *)titleArray
                         imageArray:(NSArray *)imageArray
                      currentWindow:(nullable UIWindow *)currentWindow {
    HFPullMenuView *menuView = [self pullMenuAnchorPoint:anchorPoint menuArray:nil currentWindow:currentWindow];
    menuView.titleArray = titleArray;
    menuView.imageArray = imageArray;
    return menuView;
}

+ (instancetype)pullMenuAnchorPoint:(CGPoint)anchorPoint
                          menuArray:(NSArray <HFPullMenuModel *>*)menuArray
                      currentWindow:(nullable UIWindow *)currentWindow {
    if (currentWindow == nil) {
        currentWindow = [[[UIApplication sharedApplication] delegate] window];
    }
    
    HFPullMenuView *menuView = [[HFPullMenuView alloc] init];
    menuView.frame = [UIScreen mainScreen].bounds;
    [currentWindow addSubview:menuView];
    menuView.anchorRect = CGRectMake(anchorPoint.x, anchorPoint.y, 0, 0);
    menuView.menuArray = menuArray;
    return menuView;
}

#pragma mark - UITableViewDelegate & UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.menuArray.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return self.menuCellHeight;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    HFPullMenuModel *cellModel = self.menuArray[indexPath.row];

    HFPullMenuCell *cell = [tableView dequeueReusableCellWithIdentifier:@"HFPullMenuCell" forIndexPath:indexPath];
    cell.pullMenuConfig = self.pullMenuConfig;
    cell.pullMenuModel = cellModel;
    cell.pullMenuStyle = self.pullMenuStyle;
    cell.lineColor = self.lineColor;
    cell.isFinalCell = indexPath.row == (self.menuArray.count - 1);
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (self.selected_callback) {
        self.selected_callback(indexPath.row);
    }
    
    [self animateRemoveView];
}

#pragma mark - Helper

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self animateRemoveView];
}

- (void)animateRemoveView {
    [UIView animateWithDuration:0.5 animations:^{
        self.alpha = 0.f;
        self.contentView.transform = CGAffineTransformMakeScale(0.001f, 0.001f);
        self.contentView.alpha = 0.f;
    } completion:^(BOOL finished) {
        [self removeFromSuperview];
    }];
}

- (void)refreshUI {
    [self.contentView removeFromSuperview];
    self.contentView = nil;
    [self addSubview:self.contentView];
    [self drawmTableFrame];
    [self.tableView reloadData];
}

- (CGFloat)cacuateCellWidth {
    __block CGFloat maxTitleWidth = 0;
    
    [self.menuArray enumerateObjectsUsingBlock:^(HFPullMenuModel * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        CGFloat width = [obj.title sizeWithAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:self.pullMenuConfig.menuTitleFontSize]}].width;
        if (obj.imageName.length) {
            width = width + self.pullMenuConfig.menuContentMargin + self.pullMenuConfig.menuImageWidth;
        }
        if (width > maxTitleWidth) {
            maxTitleWidth = width;
        }
    }];
    
    return maxTitleWidth + self.pullMenuConfig.menuContentMargin * 2;
}

- (void)handleMenuModelArray:(NSArray *)array {
    NSMutableArray *tempArray = [NSMutableArray array];
    
    [array enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        HFPullMenuModel *model = [[HFPullMenuModel alloc] init];
        model.title = self.titleArray[idx];
        model.imageName = self.imageArray[idx];
        [tempArray addObject:model];
    }];
    
    self.menuArray = tempArray;
}

- (void)drawmTableFrame {
    CGPoint layerAnchor = CGPointZero;
    CGPoint layerPosition = CGPointZero;
    CGFloat x = CGRectGetMidX(self.anchorRect);
    CGFloat y = 0;
    CGFloat h = self.menuArray.count * self.menuCellHeight;
    CGFloat w = [self cacuateCellWidth];
    
    // 最大高度围栏限制
    if (h > self.menuMaxHeight) {
        h = self.menuMaxHeight;
    }
    
    // X中点位置：居左：table右偏 居右：table左偏
    if (x > CGRectGetMidX(self.bounds)) {
        x = x - 3 * w / 4.f;
        layerAnchor.x = 1;
        layerPosition.x = x + w;
    } else {
        x = x - w / 4.f;
        layerAnchor.x = 0;
        layerPosition.x = x;
    }
    
    // 围栏
    if (x < self.pullMenuConfig.menuBorderMinMargin) {
        x = self.pullMenuConfig.menuBorderMinMargin;
        layerPosition.x = x;
    }
    if (x + w > self.bounds.size.width) {
        x = self.bounds.size.width - w - self.pullMenuConfig.menuBorderMinMargin;
        layerPosition.x = x + w;
    }
    
    // 需要偏转Y对比中心点 默认比对屏幕中心点
    CGFloat offsetCenterY = CGRectGetMidY(self.bounds);
    // 优先菜单下拉
    if (self.adjustPullDown) {
        // 下偏移区间距离
        offsetCenterY = self.bounds.size.height - h - self.triangleHeight;
    }
    
    // Y中心位置 居上：下拉 居下：上拉
    if (CGRectGetMidY(self.anchorRect) < offsetCenterY) {
        y = CGRectGetMaxY(self.anchorRect);
        self.tableView.frame = CGRectMake(0, self.triangleHeight, w, h);
        layerAnchor.y = 0;
        layerPosition.y = y;
    } else {
        y = CGRectGetMinY(self.anchorRect) - self.triangleHeight - h;
        self.tableView.frame = CGRectMake(0, 0, w, h);
        layerAnchor.y = 1;
        layerPosition.y = y + h;
    }
    
    self.contentView.frame = CGRectMake(x, y, w, h + self.triangleHeight);
    [self drawTriangle];
    
    // 动画锚点
    self.contentView.layer.position = layerPosition;
    self.contentView.layer.anchorPoint = layerAnchor;
}

// 三角形
- (void)drawTriangle {
    CGFloat x = CGRectGetMidX(self.anchorRect) - CGRectGetMinX(self.contentView.frame);
    CGFloat y = 0;
    CGPoint p = CGPointZero;
    CGPoint q = CGPointZero;
    CGFloat h = self.menuArray.count * self.menuCellHeight;
    
    // 围栏
    if (x < 2 * self.triangleHeight) {
        x = 2 * self.triangleHeight;
    }
    if (x > CGRectGetWidth(self.contentView.bounds) - 2 * self.triangleHeight) {
        x = CGRectGetWidth(self.contentView.bounds) - 2 * self.triangleHeight;
    }
    
    // 需要偏转Y对比中心点 默认比对屏幕中心点
    CGFloat offsetCenterY = CGRectGetMidY(self.bounds);
    // 优先菜单下拉
    if (self.adjustPullDown) {
        // 下偏移区间距离
        offsetCenterY = self.bounds.size.height - h - self.triangleHeight;
    }
    
    // Y中心位置 居上：下拉 居下：上拉
    if (CGRectGetMidY(self.anchorRect) < offsetCenterY) {
        y = 0;
        p = CGPointMake(x + self.triangleHeight, y + self.triangleHeight);
        q = CGPointMake(x - self.triangleHeight, y + self.triangleHeight);
     } else {
        y = CGRectGetHeight(self.contentView.frame);
        p = CGPointMake(x + self.triangleHeight, y - self.triangleHeight);
        q = CGPointMake(x - self.triangleHeight, y - self.triangleHeight);
    }
    
    CAShapeLayer *triangleLayer = [CAShapeLayer new];
    triangleLayer.frame = self.contentView.bounds;
    triangleLayer.fillColor = self.menuBgColor.CGColor;
    UIBezierPath *bezier = [UIBezierPath bezierPath];
    [bezier moveToPoint:CGPointMake(x, y)];
    [bezier addLineToPoint:p];
    [bezier addLineToPoint:q];
    bezier.lineJoinStyle = kCGLineJoinRound;
    triangleLayer.path = bezier.CGPath;
    [self.contentView.layer addSublayer:triangleLayer];
}

#pragma mark - layzing
- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] initWithFrame:CGRectZero];
        [_contentView addSubview:self.tableView];
    }
    return _contentView;
}

- (UITableView *)tableView {
    if (!_tableView) {
        _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
        _tableView.delegate = self;
        _tableView.dataSource = self;
        _tableView.layer.cornerRadius = 5;
        _tableView.backgroundColor = self.menuBgColor;
        _tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    }
    return _tableView;
}

- (HFPullMenuConfig *)pullMenuConfig {
    if (!_pullMenuConfig) {
        _pullMenuConfig = [[HFPullMenuConfig alloc] init];
        _pullMenuConfig.menuContentMargin = HFMenuContentMargin;
        _pullMenuConfig.menuImageWidth = HFMenuImageWidth;
        _pullMenuConfig.menuBorderMinMargin = HFMenuBorderMinMargin;
        _pullMenuConfig.menuTitleFontSize = HFMenuTitleFontSize;
    }
    return _pullMenuConfig;
}

- (void)setPullMenuStyle:(HFPullMenuStyle)pullMenuStyle {
    _pullMenuStyle = pullMenuStyle;
    
    switch (pullMenuStyle) {
        case HFPullMenuDarkStyle:
        {
            self.coverBgColor = [UIColor clearColor];
            self.menuBgColor  = [[UIColor blackColor] colorWithAlphaComponent:0.6];
        }
            break;
        case HFPullMenuLightStyle:
        {
            self.coverBgColor = [[UIColor grayColor] colorWithAlphaComponent:0.3];
            self.menuBgColor  = [UIColor whiteColor];
        }
            break;
        default:
            break;
    }
}

- (void)setMenuArray:(NSArray<HFPullMenuModel *> *)menuArray {
    _menuArray = menuArray;
    
    [self refreshUI];
}

- (void)setTitleArray:(NSArray *)titleArray {
    if (!titleArray.count) return;
    _titleArray = titleArray;
    
    if (self.menuArray.count &&
        self.menuArray.count != titleArray.count) {
        NSLog(@"文字图片数量不匹配！");
        return;
    }
    
    [self handleMenuModelArray:titleArray];
}

- (void)setImageArray:(NSArray *)imageArray {
    if (!imageArray.count) return;
    _imageArray = imageArray;
    
    if (self.menuArray.count &&
        self.menuArray.count != imageArray.count) {
        NSLog(@"文字图片数量不匹配！");
        return;
    }
    
    [self handleMenuModelArray:imageArray];
}

- (void)setCoverBgColor:(UIColor *)coverBgColor {
    _coverBgColor = coverBgColor;
    
    self.backgroundColor = self.coverBgColor;
}

- (void)setMenuBgColor:(UIColor *)menuBgColor {
    _menuBgColor = menuBgColor;
    
    self.tableView.backgroundColor = self.menuBgColor;
    
    [self refreshUI];
}

- (void)setAnchorRect:(CGRect)anchorRect {
    _anchorRect = anchorRect;
}

- (void)setLineColor:(UIColor *)lineColor {
    _lineColor = lineColor;
    
    [self refreshUI];
}

- (void)setMenuCellHeight:(CGFloat)menuCellHeight {
    _menuCellHeight = menuCellHeight;
    
    [self refreshUI];
}

- (void)setAdjustPullDown:(BOOL)adjustPullDown {
    _adjustPullDown = adjustPullDown;
    
    [self refreshUI];
}

@end
