//
//  VPAdRequestOptions.h
//  Version 1.1.4
//
//  Copyright (c) 2015 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>

@class VPAdDimension;
@class VPAdContainer;


typedef void (^VPAdRequestCallback)(VPAdContainer *container, NSError *error);


@interface VPAdRequestOptions : NSObject

/**
 * 광고 placement 값
 */
@property (nonatomic, copy, readonly) NSString *placement;

/**
 * 광고 크기
 */
@property (nonatomic, strong, readonly) VPAdDimension *dimension;

/**
 * 동시 요청하는 item 갯수. default는 1.
 */
@property (nonatomic) NSInteger numberToRequest;

/**
 * asset 을 모두 로드하기 전에 callback 을 호출한다.
 */
@property (nonatomic) BOOL callbackBeforeCachingAssets;

+ (instancetype)optionsWithPlacement:(NSString *)placement dimension:(VPAdDimension *)dimension;

- (instancetype)initWithPlacement:(NSString *)placement dimension:(VPAdDimension *)dimension;

- (instancetype)init __unavailable;

@end
