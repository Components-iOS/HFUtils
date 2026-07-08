//
//  HFPathManager.h
//  HFUtils
//
//  Created by liuhongfei on 2026/7/8.
//  Copyright © 2024 liuhongfei. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HFCheckBox.h"

/** Path object used by HFCheckBox to generate paths.
 */
@interface HFPathManager : NSObject

/** The paths are assumed to be created in squares. 
 * This is the size of width, or height, of the paths that will be created.
 */
@property (nonatomic) CGFloat size;

/** The width of the lines on the created paths.
 */
@property (nonatomic) CGFloat lineWidth;

/** The corner radius of the path when the boxType is HFBoxTypeSquare.
 */
@property (nonatomic) CGFloat cornerRadius;

/** The type of box.
 * Depending on the box type, paths may be created differently
 * @see HFBoxType
 */
@property (nonatomic) HFBoxType boxType;

/** Returns a UIBezierPath object for the box of the checkbox
 * @returns The path of the box.
 */
- (UIBezierPath *)pathForBox;

/** Returns a UIBezierPath object for the checkmark of the checkbox
 * @returns The path of the checkmark.
 */
- (UIBezierPath *)pathForCheckMark;

/** Returns a UIBezierPath object for an extra long checkmark which is in contact with the box.
 * @returns The path of the checkmark.
 */
- (UIBezierPath *)pathForLongCheckMark;

/** Returns a UIBezierPath object for the flat checkmark of the checkbox
 * @see HFAnimationTypeFlat
 * @returns The path of the flat checkmark.
 */
- (UIBezierPath *)pathForFlatCheckMark;

@end
