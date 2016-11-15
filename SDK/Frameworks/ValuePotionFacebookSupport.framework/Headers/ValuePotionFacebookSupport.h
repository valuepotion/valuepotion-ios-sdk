//
//  ValuePotionFacebookSupport.h
//  Version 1.2.1
//
//  Copyright (c) 2016 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>


#import <ValuePotion/ValuePotion.h>


OBJC_EXTERN NSString *const __nonnull VPValuePotionDidReceiveFacebookAppLinkNotification;



@interface ValuePotionFacebookSupport : NSObject

+ (void)useDeepLink;
+ (void)useAudienceNetwork;

@end

#pragma mark -

@interface ValuePotion (FacebookSupportExtension_Deprecated)

+ (void)useFacebookDeepLink __deprecated_msg("use +[ValuePotionFacebookSupport useDeepLink]");
+ (void)useFacebookAudienceNetwork __deprecated_msg("use +[ValuePotionFacebookSupport useAudienceNetwork]");

@end
