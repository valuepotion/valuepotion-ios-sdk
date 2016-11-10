//
//  ValuePotionFacebookSupport.h
//  Version 1.2.0
//
//  Copyright (c) 2016 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>


#import <ValuePotion/ValuePotion.h>


OBJC_EXTERN NSString *const __nonnull VPValuePotionDidReceiveFacebookAppLinkNotification;


@interface ValuePotion (FacebookSupportExtension)

+ (void)useFacebookDeepLink;
+ (void)useFacebookAudienceNetwork;

- (BOOL)handleAppLinkUrl:(nonnull NSURL *)url VP_SWIFT_NAME(handle(appLink:));
- (BOOL)handleAppLinkUrl:(nonnull NSURL *)url sourceApplication:(nullable NSString *)sourceApplication VP_SWIFT_NAME(handle(appLink:sourceApplication:));
- (BOOL)handleAppLinkUrl:(nonnull NSURL *)url options:(nonnull NSDictionary<NSString*, id> *)options VP_SWIFT_NAME(handle(appLink:options:));

@end
