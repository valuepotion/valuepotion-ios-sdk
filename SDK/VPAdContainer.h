//
//  VPAdContainer.h
//  Version 1.1.4
//
//  Created by KimHansaem on 2015. 10. 28..
//  Copyright © 2015년 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>


@class VPAdDimension;
@class VPAdItem;

/**
 * -[ValuePotion requestAdWithOptions:completion:] 을 통해 callback 으로 받는 광고 컨테이너 객채.
 * items를 이용할 경우 popAd 와 혼용하지 않는 것이 좋다.
 */
@interface VPAdContainer : NSObject

@property (nonatomic, strong, readonly) NSString *placement;
@property (nonatomic, strong, readonly) VPAdDimension *dimension;

/**
 * 광고를 순서대로 하나씩 pop 하여 리턴한다. 더이상 광고가 없으면 nil을 리턴한다.
 */
- (VPAdItem *)popAd;

/**
 * 광고 item 목록
 */
@property (nonatomic, readonly) NSArray<VPAdItem *>* items;

@end
