//
//  ValuePotionAdxSupport.h
//  Version 1.2.1
//
//  Copyright (c) 2016 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>


#import <ValuePotion/ValuePotion.h>


@interface ValuePotionAdxSupport : NSObject

+ (void)use;

@end

#pragma mark -

@interface ValuePotion (AdxSupportExtension_Deprecated)

+ (void)useGoogleMobileAds __deprecated_msg("use +[ValuePotionAdxSupport use]");

@end

