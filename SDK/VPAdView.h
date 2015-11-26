//
//  VPAdView.h
//  SDK
//  Version 1.1.0
//
//  Copyright (c) 2015 ValuePotion. All rights reserved.
//

#import <UIKit/UIKit.h>


@class VPAdItem;


/**
 * 배너광고 View
 */
@interface VPAdView : UIView {
@private
    id _internal;
}

/**
 * adItem 을 통해 VPAdView 를 생성한다.
 */
- (instancetype)initWithAdItem:(VPAdItem *)adItem;

/**
 * 이미 생성된 View 에 adItem 을 로드한다.
 */
- (void)loadAdItem:(VPAdItem *)adItem;

@end
