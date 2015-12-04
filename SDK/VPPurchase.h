//
//  VPPurchase.h
//  Version 1.1.4
//
//  Copyright (c) 2013 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPPurchase : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *productId;
@property (nonatomic, assign) NSInteger quantity;
@property (nonatomic, copy) NSString *campaignId;
@property (nonatomic, copy) NSString *contentId;

@end
