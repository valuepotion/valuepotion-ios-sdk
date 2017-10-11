//
//  ValuePotionAdColonySupport.h
//  Version 1.2.14
//
//  Copyright (c) 2016 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>


#import <ValuePotion/ValuePotion.h>



@interface ValuePotionAdColonySupport : NSObject

+ (void)use;

@end

#pragma mark -

@interface ValuePotion (AdColonySupportExtension_Deprecated)

+ (void)useAdColonyAds __deprecated_msg("use +[ValuePotionAdColonySupport use]");

@end
