//
//  ValuePotion.h
//  Version 1.1.7
//
//  Copyright (c) 2015 ValuePotion. All rights reserved.
//


#import <UIKit/UIKit.h>


@protocol ValuePotionDelegate;

@class VPPurchase;
@class VPReward;
@class VPAdDimension;
@class VPAdRequestOptions;
@class VPAdContainer;
@class VPAdItem;
@class VPAdView;


typedef void (^VPAdRequestCallback)(VPAdContainer *container, NSError *error);



/**
 * The ValuePotion provides many methods for presenting interstitial ads, tracking events,
 * handling push notifications and insert banners.
 *
 * @see http://developers.valuepotion.com/en/sdk_ios/ for more information.
 */
@interface ValuePotion : NSObject

@property (nonatomic, weak) id<ValuePotionDelegate> delegate;
@property (nonatomic, copy) NSString *clientId;
@property (nonatomic, copy) NSString *secretKey;
@property (nonatomic, assign) BOOL test;

/**
 * Almost ValuePotion functions are implemented in the `ValuePotion` instance.
 *
 * @return ValuePotion singleton instance.
 */
+ (ValuePotion *)sharedInstance;

/**
 *
 * @param clientId The client id to use ValuePotion sdk
 * @param secretKey The secret key
 */
- (void)initializeWithClientId:(NSString *)clientId secretKey:(NSString *)secretKey;

#pragma mark - Interstitial Methods
- (BOOL)hasCachedInterstitial:(NSString *)placement;
- (void)cacheInterstitial:(NSString *)placement;
- (void)openInterstitial:(NSString *)placement;

#pragma mark - RequestOptions Methods
- (void)requestAdWithOptions:(VPAdRequestOptions *)options completion:(VPAdRequestCallback)completion;

#pragma mark - Tracking Methods
- (void)trackEvent:(NSString *)eventName value:(NSNumber *)value;
- (void)trackEvent:(NSString *)eventName category:(NSString *)category label:(NSString *)label value:(NSNumber *)value;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId productId:(NSString *)productId;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId productId:(NSString *)productId campaignId:(NSString *)campaignId contentId:(NSString *)contentId;
- (void)trackPurchaseEvent:(NSString *)eventName category:(NSString *)category label:(NSString *)label revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId productId:(NSString *)productId campaignId:(NSString *)campaignId contentId:(NSString *)contentId;
- (void)trackEvent:(NSString *)eventName values:(NSDictionary *)values __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency purchase:(VPPurchase *)purchase __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId purchase:(VPPurchase *)purchase __deprecated;

#pragma mark - Push Notification Methods
- (void)registerForPushNotification;
- (void)unregisterForPushNotification;
- (BOOL)isPushNotificationEnabled;
- (void)registerPushToken:(NSData *)token;
- (void)forwardPushInfo:(NSDictionary *)info;

#pragma mark - UserInfo Methods
- (NSDictionary *)userInfo;
- (void)setUserId:(NSString *)userId;
- (void)setUserServerId:(NSString *)serverId;
- (void)setUserBirth:(NSString *)birth;
- (void)setUserGender:(NSString *)gender;
- (void)setUserLevel:(double)level;
- (void)setUserFriends:(double)friends;
- (void)setUserAccountType:(NSString *)accountType;
- (void)setUserValue:(id)value forKey:(NSString *)key;
- (void)setUserInfo:(NSDictionary *)userInfo __deprecated;

#pragma mark - Interstitial Settings

/**
 * Prevent inadvertent call to present interstitial ad.
 *
 * @param interval second for interval. default is 1 sec.
 */
- (void)setInterstitialMinimumInterval:(NSTimeInterval)interval;

@end


#pragma mark - Delegate Methods
@protocol ValuePotionDelegate <NSObject>
@optional
/**
 * Sent after caching interstitial ad success.
 *
 * @param placement The interstitial ad's placement
 */
- (void)didCacheInterstitial:(NSString *)placement;

/**
 * Sent if it failed to cache interstitial ad.
 *
 * @param placement The interstitial ad's placement
 * @param error The error that occurred during caching
 */
- (void)didFailToCacheInterstitial:(NSString *)placement error:(NSError *)error;

/**
 * Sent before interstitial view present on window.
 *
 * @param placement The interstitial ad's placement
 */
- (void)willOpenInterstitial:(NSString *)placement;
	
/**
 * Sent if it failed to present interstitial ad's view.
 *
 * @param placement The interstitial ad's placement
 * @param error The error that occurred during presenting view
 */
- (void)didFailToOpenInterstitial:(NSString *)placement error:(NSError *)error;

/**
 * Sent after interstitial view is dismissed.
 *
 * @param placement The interstitial ad's placement
 */
- (void)didCloseInterstitial:(NSString *)placement;

/**
 * Sent after a user select a hyperlink in interstitial ad's view.
 *
 * @param urlString The link url that a user select
 * @param placement The interstitial ad's placement
 */
- (void)didRequestOpenURL:(NSString *)urlString placement:(NSString *)placement;

/**
 * Sent after a user select a purchase in interstitial ad's view.
 *
 * @param purchase The purchase information url that a user select.
 * @param placement The interstitial ad's placement
 */
- (void)didRequestPurchase:(VPPurchase *)purchase placement:(NSString *)placement;

/**
 * Sent after interstitial ad's view of reward campaign is presented.
 *
 * @param rewards The array of reward campaign's information
 * @param placement The interstitial ad's placement
 */
- (void)didRequestRewards:(NSArray *)rewards placement:(NSString *)placement;

/**
 * Send after inplay view did complete conversion.
 *
 * @param placement The interstitial ad's placement
 */
- (void)didCompleteConversion:(NSString *)placement;

@end


#pragma mark -


/**
 * The VPPurchase is passed from '-[ValuePotion didRequestPurchase:placement:]' delegate method.
 *
 * @see http://developers.valuepotion.com/en/sdk_ios/4.-Advanced.html#inapp-purchase-campaign
 */
@interface VPPurchase : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *productId;
@property (nonatomic, assign) NSInteger quantity;
@property (nonatomic, copy) NSString *campaignId;
@property (nonatomic, copy) NSString *contentId;

@end


#pragma mark - 


/**
 * The VPReward is passed in '-[ValuePotion didRequestRewards:placement:]' as argument.
 */
@interface VPReward : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) NSInteger quantity;

@end


#pragma mark - 


/**
 * The VPAdDimension contains width and height to reqeust ads.
 */
@interface VPAdDimension : NSObject

/**
 * The width of ad
 */
@property (nonatomic, readonly) NSInteger placementWidth;

/**
 * The height of ad
 */
@property (nonatomic, readonly) NSInteger placementHeight;

/**
 * The default dimension. This dimension is for interstitial ad. It is 320w x 480h currently.
 */
+ (instancetype)defaultDimension;

/**
 * The dimension that has 320w x 50h
 */
+ (instancetype)dimensionWith320x50;

/**
 * The dimension that has 320w x 100h
 */
+ (instancetype)dimensionWith320x100;

/**
 * The dimension that has 320w x 300h
 */
+ (instancetype)dimensionWith320x300;

/**
 * The dimension that has 320w x 480h
 */
+ (instancetype)dimensionWith320x480;

/**
 * This dimension is for interstitial ad. It is 320w x 480h currently.
 */
+ (instancetype)dimensionForInterstitial;

/**
 * A dimension that has any width and height.
 * @param width The banner width
 * @param height The banner height
 */
+ (instancetype)dimensionWithWidth:(NSInteger)width height:(NSInteger)height;

/**
 * @return a CGSize structure with placementWidth and placementHeight
 */
- (CGSize)getSize;


- (instancetype)init __unavailable;


@end


#pragma mark -


@interface VPAdRequestOptions : NSObject

/**
 * The placement for an ad
 */
@property (nonatomic, copy, readonly) NSString *placement;

/**
 * The dimension for an ad
 */
@property (nonatomic, strong, readonly) VPAdDimension *dimension;

/**
 * The number of requesting items at same time. Default is 1.
 */
@property (nonatomic) NSInteger numberToRequest;

/**
 * When you receive some banner's responses, desides when you receive the callback.
 * If you want to receive it immediately, set this to YES, otherwise NO. Default is NO.
 *
 * Every request for ad has a main body and assets.
 * If this is YES, when callback method is called, one or more items of VPAdContainer contain only metadata and body data except other assets.
 * But do not worry. As all assets are received, a VPAdView can present the content fully.
 * If this is NO, when callback method is called, a VPAdView can present full content just right.
 */
@property (nonatomic) BOOL callbackBeforeCachingAssets;

/**
 * YES if you want to start rendering ad item immediately when callback received, otherwise NO. Default is NO.
 */
@property (nonatomic) BOOL startRenderingAtCallback;

+ (instancetype)optionsWithPlacement:(NSString *)placement dimension:(VPAdDimension *)dimension;

- (instancetype)initWithPlacement:(NSString *)placement dimension:(VPAdDimension *)dimension;

- (instancetype)init __unavailable;

@end


#pragma mark -


/**
 * The VPAdContainer is passed from '-[ValuePotion requestAdWithOptions:completion:]' delegate method.
 *
 * You must use the property 'items' and '-[VPAdContainer popAd]' exclusively.
 */
@interface VPAdContainer : NSObject

@property (nonatomic, strong, readonly) NSString *placement;
@property (nonatomic, strong, readonly) VPAdDimension *dimension;

/**
 * Pop ad item from the item queue. If container has no more ad, returns nil.
 */
- (VPAdItem *)popAd;

/**
 * The array contains ad items.
 */
@property (nonatomic, readonly) NSArray<VPAdItem *>* items;

@end


#pragma mark -


/**
 * The VPAdItem contains a information to show in VPAdView.
 */
@interface VPAdItem : NSObject {
@private
    id _internal;
}

@end


#pragma mark -


/**
 * The VPAdView is a view contains a banner with VPAdItem.
 */
@interface VPAdView : UIView {
@private
    id _internal;
}

/**
 * Initialize the view with ad item.
 *
 * @param adItem an ad item gained from a VPAdContainer
 */
- (instancetype)initWithAdItem:(VPAdItem *)adItem;

/**
 * Load ad item and set view up.
 *
 * @param adItem an ad item gained from a VPAdContainer
 */
- (void)loadAdItem:(VPAdItem *)adItem;

@end
