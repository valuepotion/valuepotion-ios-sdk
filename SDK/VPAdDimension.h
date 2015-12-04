//
//  VPAdDimension.h
//  Version 1.1.4
//
//  Copyright (c) 2015 ValuePotion. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * 광고의 dimension 을 지정하기 위한 class
 */
@interface VPAdDimension : NSObject

/**
 * 광고 width
 */
@property (nonatomic, readonly) NSInteger placementWidth;

/**
 * 광고 height
 */
@property (nonatomic, readonly) NSInteger placementHeight;

/**
 * 기본 광고 크기. 320 x 480
 */
+ (instancetype)defaultDimension;

/**
 * 320 x 50 의 크기를 가진 dimension
 */
+ (instancetype)dimensionWith320x50;

/**
 * 320 x 100 의 크기를 가진 dimension
 */
+ (instancetype)dimensionWith320x100;

/**
 * 320 x 300 의 크기를 가진 dimension
 */
+ (instancetype)dimensionWith320x300;

/**
 * 320 x 480 의 크기를 가진 dimension
 */
+ (instancetype)dimensionWith320x480;

/**
 * Interstitial 광고 표시를 위한 dimension
 */
+ (instancetype)dimensionForInterstitial;

/**
 * 임의의 크기를 가진 dimension 생성
 */
+ (instancetype)dimensionWithWidth:(NSInteger)width height:(NSInteger)height;


- (CGSize)getSize;


- (instancetype)init __unavailable;


@end
