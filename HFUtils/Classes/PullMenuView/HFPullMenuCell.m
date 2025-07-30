//
//  HFPullMenuCell.m
//  HFUtils
//
//  Created by liuhongfei on 2025/7/30.
//

#import "HFPullMenuCell.h"

@interface HFPullMenuCell ()

@property (strong, nonatomic) UIImageView *menuImageView;
@property (strong, nonatomic) UILabel *menuTitleLab;
@property (nonatomic, strong) UIView *selectedBgView;
@property (nonatomic, strong) CAShapeLayer *lineLayer;

@end

@implementation HFPullMenuCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.selectedBgView = [[UIView alloc] initWithFrame:self.bounds];
        self.selectedBackgroundView = self.selectedBgView;
        [self addSubview:self.menuImageView];
        [self addSubview:self.menuTitleLab];
    }
    return self;
}

- (void)setPullMenuModel:(HFPullMenuModel *)pullMenuModel {
    _pullMenuModel = pullMenuModel;
    
    if (!pullMenuModel.imageName.length) {
        self.menuImageView.hidden = YES;
        self.menuTitleLab.frame = CGRectMake(self.pullMenuConfig.menuContentMargin, 0, CGRectGetWidth(self.bounds) - self.pullMenuConfig.menuContentMargin * 2, CGRectGetHeight(self.bounds));
    } else {
        self.menuImageView.hidden = NO;
        self.menuImageView.image = [UIImage imageNamed:pullMenuModel.imageName];
        self.menuImageView.frame = CGRectMake(self.pullMenuConfig.menuContentMargin, (CGRectGetHeight(self.bounds) - self.pullMenuConfig.menuImageWidth) * 0.5, self.pullMenuConfig.menuImageWidth, self.pullMenuConfig.menuImageWidth);
        self.menuTitleLab.frame = CGRectMake(self.pullMenuConfig.menuContentMargin * 2 + self.pullMenuConfig.menuImageWidth, 0, CGRectGetWidth(self.bounds) - (self.pullMenuConfig.menuContentMargin * 3 + self.pullMenuConfig.menuImageWidth), CGRectGetHeight(self.bounds));
    }
    
    self.menuTitleLab.text = pullMenuModel.title;
    self.menuTitleLab.font = [UIFont systemFontOfSize:self.pullMenuConfig.menuTitleFontSize];
}

- (void)setPullMenuStyle:(HFPullMenuStyle)pullMenuStyle {
    _pullMenuStyle = pullMenuStyle;
    
    switch (pullMenuStyle) {
        case HFPullMenuDarkStyle:
        {
            self.selectedBgView.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.2];
            self.menuTitleLab.textColor = [UIColor whiteColor];
            self.lineColor = [UIColor whiteColor];
        }
            break;
        case HFPullMenuLightStyle:
        {
            self.selectedBgView.backgroundColor = [UIColor groupTableViewBackgroundColor];
            self.menuTitleLab.textColor = [UIColor blackColor];
            self.lineColor = [UIColor lightGrayColor];
        }
            break;
        default:
            break;
    }
}

- (void)setIsFinalCell:(BOOL)isFinalCell {
    _isFinalCell = isFinalCell;
    
    if (!isFinalCell) {
        [self drawLineSep];
    } else {
        [self.lineLayer removeFromSuperlayer];
    }
}

- (void)drawLineSep {
    CAShapeLayer *lineLayer = [CAShapeLayer new];
    lineLayer.strokeColor = self.lineColor.CGColor;
    lineLayer.frame = self.bounds;
    lineLayer.lineWidth = 0.5;
    UIBezierPath *sepline = [UIBezierPath bezierPath];
    [sepline moveToPoint:CGPointMake(self.pullMenuConfig.menuContentMargin, self.bounds.size.height - lineLayer.lineWidth)];
    [sepline addLineToPoint:CGPointMake(self.bounds.size.width - self.pullMenuConfig.menuContentMargin, self.bounds.size.height - lineLayer.lineWidth)];
    lineLayer.path = sepline.CGPath;
    [self.layer addSublayer:lineLayer];
    self.lineLayer = lineLayer;
}

- (void)setLineColor:(UIColor *)lineColor {
    if (lineColor) {
        _lineColor = lineColor;
    }
}

- (UIImageView *)menuImageView {
    if (!_menuImageView) {
        _menuImageView = [[UIImageView alloc] init];
    }
    return _menuImageView;
}

- (UILabel *)menuTitleLab {
    if (!_menuTitleLab) {
        _menuTitleLab = [[UILabel alloc] init];
    }
    return _menuTitleLab;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
    // Configure the view for the selected state
}

@end
