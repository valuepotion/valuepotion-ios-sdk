//
//  ValuePotion.h
//  Version 1.1.27
//
//  Copyright (c) 2015 ValuePotion. All rights reserved.
//


#import <UIKit/UIKit.h>

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED

#ifndef __IPHONE_9_0
# define __IPHONE_9_0   90000
#endif

#ifndef __IPHONE_10_0
# define __IPHONE_10_0  100000
#endif

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_9_0
#   define AVAILABLE_SWIFT2_GENERIC
#endif

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0
#   define AVAILABLE_SWIFT3_NAME
#   define VP_SWIFT_NAME(_x) NS_SWIFT_NAME(_x)
#   define VP_SWIFT_UNAVAILABLE(_x) NS_SWIFT_UNAVAILABLE(_x)
#   define VP_EXTENSIBLE_STRING_ENUM NS_EXTENSIBLE_STRING_ENUM
#else
#   ifndef VP_SWIFT_NAME
#       define VP_SWIFT_NAME(_x)
#   endif
#   ifndef VP_SWIFT_UNAVAILABLE
#       define VP_SWIFT_UNAVAILABLE(_x)
#   endif
#   ifndef VP_EXTENSIBLE_STRING_ENUM
#       define VP_EXTENSIBLE_STRING_ENUM
#   endif
#endif

#else  // __IPHONE_OS_VERSION_MAX_ALLOWED

#   ifndef VP_SWIFT_NAME
#       define VP_SWIFT_NAME(_x)
#   endif
#   ifndef VP_SWIFT_UNAVAILABLE
#       define VP_SWIFT_UNAVAILABLE(_x)
#   endif
#   ifndef VP_EXTENSIBLE_STRING_ENUM
#       define VP_EXTENSIBLE_STRING_ENUM
#   endif

#endif // __IPHONE_OS_VERSION_MAX_ALLOWED



#ifdef __TV_OS_VERSION_MAX_ALLOWED

#ifndef __TV_OS_VERSION_MAX_ALLOWED >= __TVOS_9_0
#   define __TVOS_PROHIBITED
#endif

#endif


@protocol ValuePotionDelegate;

@class VPPurchase;
@class VPReward;
@class VPAdDimension;
@class VPAdRequestOptions;
@class VPAdContainer;
@class VPAdItem;
@class VPAdView;


typedef NS_ENUM(NSInteger, VPInterstitialBackgroundStyle) {
    VPInterstitialBackgroundBlackTranslucent = 0,
    VPInterstitialBackgroundLightTranslucent,
    VPInterstitialBackgroundBlackOpaque,
    VPInterstitialBackgroundLightOpaque,
};

typedef void (^VPAdRequestCallback)(VPAdContainer * __nullable container , NSError * __nullable error);


OBJC_EXTERN NSString *const __nonnull VPValuePotionWillPresentVideoAdNotification;
OBJC_EXTERN NSString *const __nonnull VPValuePotionDidDismissVideoAdNotification;


/**
 * The ValuePotion provides many methods for presenting interstitial ads, tracking events,
 * handling push notifications and insert banners.
 *
 * @see http://developers.valuepotion.com/en/sdk_ios/ for more information.
 */
@interface ValuePotion : NSObject

@property (nonatomic, weak, nullable) id<ValuePotionDelegate> delegate;

/**
 * The Client Identifier. If you don't initialize library yet, it will be nil.
 */
@property (nonatomic, copy, readonly, nullable) NSString *clientId;

/**
 * The Secret Key. If you don't initialize library yet, it will be nil.
 */
@property (nonatomic, copy, readonly, nullable) NSString *secretKey;

/**
 * A boolean value indicating whether a video ad is presented.
 */
@property (nonatomic, readonly, getter=isVideoPresented) BOOL videoPresented;

/**
 * Set to YES, if you are developing app on test. Default is NO.
 */
@property (nonatomic, assign) BOOL test;

/**
 * Set to YES, if you want to log checkpoints for sdk integration. Default is NO.
 */
@property (nonatomic, assign) BOOL logCheckpoints;

/**
 * Almost ValuePotion functions are implemented in the `ValuePotion` instance.
 *
 * @return ValuePotion singleton instance.
 */
+ (nonnull ValuePotion *)sharedInstance VP_SWIFT_NAME(shared());

/**
 * Initialize valuepotion library.
 *
 * @param clientId The client id to use ValuePotion sdk
 * @param secretKey The secret key
 */
- (void)initializeWithClientId:(nonnull NSString *)clientId secretKey:(nonnull NSString *)secretKey VP_SWIFT_NAME(initialize(clientId:secretKey:));

#pragma mark - Interstitial Methods
- (BOOL)hasCachedInterstitial:(nonnull NSString *)placement __TVOS_PROHIBITED;
- (void)cacheInterstitial:(nonnull NSString *)placement __TVOS_PROHIBITED;
- (void)openInterstitial:(nullable NSString *)placement __TVOS_PROHIBITED;

#pragma mark - Interstitial Methods with contentSeq
- (BOOL)hasCachedInterstitial:(nonnull NSString *)placement contentSeq:(nullable NSString *)contentSeq __TVOS_PROHIBITED;
- (void)cacheInterstitial:(nonnull NSString *)placement contentSeq:(nullable NSString *)contentSeq __TVOS_PROHIBITED;
- (void)openInterstitial:(nullable NSString *)placement contentSeq:(nullable NSString *)contentSeq __TVOS_PROHIBITED;

#pragma mark - RequestOptions Methods
- (void)requestAdWithOptions:(nonnull VPAdRequestOptions *)options completion:(nonnull VPAdRequestCallback)completion __TVOS_PROHIBITED VP_SWIFT_NAME(requestAd(options:completion:));

#pragma mark - Tracking Methods
- (void)trackEvent:(nonnull NSString *)eventName value:(nullable NSNumber *)value VP_SWIFT_NAME(track(event:value:));
- (void)trackEvent:(nonnull NSString *)eventName category:(nullable NSString *)category label:(nullable NSString *)label value:(nullable NSNumber *)value VP_SWIFT_NAME(track(event:category:label:value:));
- (void)trackPurchaseEvent:(nonnull NSString *)eventName revenueAmount:(double)revenueAmount currency:(nonnull NSString *)currency transactionId:(nullable NSString *)transactionId productId:(nullable NSString *)productId VP_SWIFT_NAME(track(purchaseEvent:revenueAmount:currency:transactionId:productId:));
- (void)trackPurchaseEvent:(nonnull NSString *)eventName revenueAmount:(double)revenueAmount currency:(nonnull NSString *)currency transactionId:(nullable NSString *)transactionId productId:(nullable NSString *)productId campaignId:(nullable NSString *)campaignId contentId:(nullable NSString *)contentId VP_SWIFT_NAME(track(purchaseEvent:revenueAmount:currency:transactionId:productId:campaignId:contentId:));
- (void)trackPurchaseEvent:(nonnull NSString *)eventName category:(nullable NSString *)category label:(nullable NSString *)label revenueAmount:(double)revenueAmount currency:(nonnull NSString *)currency transactionId:(nullable NSString *)transactionId productId:(nullable NSString *)productId campaignId:(nullable NSString *)campaignId contentId:(nullable NSString *)contentId VP_SWIFT_NAME(track(purchaseEvent:category:label:revenueAmount:currency:transactionId:productId:campaignId:contentId:));

#pragma mark - Push Notification Methods
- (void)registerForPushNotification __TVOS_PROHIBITED;
- (void)unregisterForPushNotification __TVOS_PROHIBITED;
- (BOOL)isPushNotificationEnabled __TVOS_PROHIBITED;
- (void)registerPushToken:(nonnull NSData *)token __TVOS_PROHIBITED;
- (void)forwardPushInfo:(nullable NSDictionary *)info __TVOS_PROHIBITED;

#pragma mark - UserInfo Methods
- (nullable NSDictionary *)userInfo;
- (void)setUserId:(nullable NSString *)userId;
- (void)setUserServerId:(nullable NSString *)serverId;
- (void)setUserBirth:(nullable NSString *)birth;
- (void)setUserGender:(nullable NSString *)gender;
- (void)setUserLevel:(double)level;
- (void)setUserFriends:(double)friends;
- (void)setUserAccountType:(nullable NSString *)accountType;
- (void)setUserValue:(nonnull id)value forKey:(nonnull NSString *)key;

#pragma mark - Interstitial Settings

/**
 * Prevent inadvertent call to present interstitial ad.
 *
 * @param interval second for interval. default is 1 sec.
 */
- (void)setInterstitialMinimumInterval:(NSTimeInterval)interval __TVOS_PROHIBITED;

/**
 * Set the style of interstitial ad's background. Default is VPInterstitialBackgroundBlackTranslucent.
 */
@property (nonatomic, assign) VPInterstitialBackgroundStyle interstitialBackgroundStyle;

@end

#pragma mark - Deprecated Methods

@interface ValuePotion (Deprecated)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

- (void)trackEvent:(NSString *)eventName values:(NSDictionary *)values __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency purchase:(VPPurchase *)purchase __deprecated;
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId purchase:(VPPurchase *)purchase __deprecated;

- (void)setUserInfo:(NSDictionary *)userInfo __deprecated;

#pragma clang diagnostic pop


@end


#pragma mark - Delegate Methods
@protocol ValuePotionDelegate <NSObject>
@optional
/**
 * Sent after caching interstitial ad success.
 *
 * @param placement The interstitial ad's placement
 */
- (void)didCacheInterstitial:(nonnull NSString *)placement;

/**
 * Sent if it failed to cache interstitial ad.
 *
 * @param placement The interstitial ad's placement
 * @param error The error that occurred during caching
 */
- (void)didFailToCacheInterstitial:(nonnull NSString *)placement error:(nullable NSError *)error;

/**
 * Sent before interstitial view present on window.
 *
 * @param placement The interstitial ad's placement
 */
- (void)willOpenInterstitial:(nonnull NSString *)placement;
	
/**
 * Sent if it failed to present interstitial ad's view.
 *
 * @param placement The interstitial ad's placement
 * @param error The error that occurred during presenting view
 */
- (void)didFailToOpenInterstitial:(nonnull NSString *)placement error:(nullable NSError *)error;

/**
 * Sent after interstitial view is dismissed.
 *
 * @param placement The interstitial ad's placement
 */
- (void)didCloseInterstitial:(nonnull NSString *)placement;

/**
 * Sent after a user select a hyperlink in interstitial ad's view.
 *
 * @param urlString The link url that a user select
 * @param placement The interstitial ad's placement
 */
- (void)didRequestOpenURL:(nonnull NSString *)urlString placement:(nonnull NSString *)placement;

/**
 * Sent after a user select a purchase in interstitial ad's view.
 *
 * @param purchase The purchase information url that a user select.
 * @param placement The interstitial ad's placement
 */
- (void)didRequestPurchase:(nonnull VPPurchase *)purchase placement:(nonnull NSString *)placement;

/**
 * Sent after interstitial ad's view of reward campaign is presented.
 *
 * @param rewards The array of reward campaign's information
 * @param placement The interstitial ad's placement
 */
#ifdef AVAILABLE_SWIFT2_GENERIC
- (void)didRequestRewards:(nonnull NSArray<VPReward *> *)rewards placement:(nonnull NSString *)placement;
#else
- (void)didRequestRewards:(nonnull NSArray *)rewards placement:(nonnull NSString *)placement;
#endif

/**
 * Sent after inplay view did complete conversion.
 *
 * @param placement The interstitial ad's placement
 */
- (void)didCompleteConversion:(nonnull NSString *)placement;

/**
 * Decides whether to allow or cancel to play a video ad.
 * Call a code block decisionHandler with `YES` if you allow, otherwise call it with `NO`.
 *
 * If you don't implement this method, video ads are played automatically.
 */
- (void)decideToPlayVideo:(nonnull NSString *)placement contentSeq:(nonnull NSString *)contentSeq decisionHandler:(nonnull void (^)(BOOL play))decisionHandler;

/**
 * Sent after a user watches the video ad until the end.
 * Call a code block closingHandler when you want to close. If you want to close the interstitial ad also, call with parameter `YES`, otherwise `NO`.
 *
 * If you don't implement this method, the interstitial ad will be closed automatically.
 */
- (void)didCompleteVideoWatching:(nonnull NSString *)placement contentSeq:(nonnull NSString *)contentSeq closingHandler:(nonnull void (^)(BOOL closeInterstitial))closingHandler;

/**
 * Sent when a video loading is failed.
 */
- (void)didFailToLoadVideo:(nonnull NSString *)placement error:(nonnull NSError *)error;

/**
 * Sent after a user cancels playing the video ad before the end.
 * Call a code block closingHandler when you want to close. If you want to close the interstitial ad also, call with parameter `YES`, otherwise `NO`.
 *
 * If you don't implement this method, only the video view will be closed without closing the interstitial ad.
 */
- (void)didCancelToWatchVideo:(nonnull NSString *)placement duration:(float)duration position:(float)position closingHandler:(nonnull void (^)(BOOL closeInterstitial))closingHandler;

@end


#pragma mark -


/**
 * The VPPurchase is passed from '-[ValuePotion didRequestPurchase:placement:]' delegate method.
 *
 * @see http://developers.valuepotion.com/en/sdk_ios/advanced.html
 */
@interface VPPurchase : NSObject

@property (nonatomic, copy, readonly, nonnull) NSString *name;
@property (nonatomic, copy, readonly, nonnull) NSString *productId;
@property (nonatomic, assign) NSInteger quantity;
@property (nonatomic, copy, readonly, nullable) NSString *campaignId;
@property (nonatomic, copy, readonly, nullable) NSString *contentId;

@end


#pragma mark -


/**
 * The VPReward is passed in '-[ValuePotion didRequestRewards:placement:]' as argument.
 */
@interface VPReward : NSObject

@property (nonatomic, strong, readonly, nonnull) NSString *name;
@property (nonatomic, assign) NSInteger quantity;
@property (nonatomic, strong, readonly, nullable) NSString *campaignId;

@end


#pragma mark -

typedef NS_ENUM(NSInteger, VPAdDimensionType) {
    /** The default dimension type */
    VPAdDimensionTypeDefault __deprecated_msg("use VPAdDimensionTypeInterstitial") VP_SWIFT_UNAVAILABLE("use .interstitial") VP_SWIFT_NAME(default),
    /** The dimension type for interstitial ad */
    VPAdDimensionTypeInterstitial VP_SWIFT_NAME(interstitial),
    /** The dimension type for native banner */
    VPAdDimensionTypeNativeBanner VP_SWIFT_NAME(nativeBanner),
    /** The dimension type that has 320w x 50h */
    VPAdDimensionTypeBanner VP_SWIFT_NAME(banner),
    /** The dimension type that has 320w x 100h */
    VPAdDimensionTypeLargeBanner VP_SWIFT_NAME(largeBanner),
    /** The dimension type that has 300w x 250h */
    VPAdDimensionTypeMediumRectangle VP_SWIFT_NAME(mediumRectangle),
    /** The dimension type that has 728w x 90h */
    VPAdDimensionTypeLeaderboard VP_SWIFT_NAME(leaderboard),
    /** The dimension type that has 320w x 480h */
    VPAdDimensionTypeW320H480 VP_SWIFT_NAME(w320h480),
    /** The dimension type that has 320w x 50h */
    VPAdDimensionTypeW320H50 __deprecated_msg("use VpAdDimensionTypeBanner") VP_SWIFT_UNAVAILABLE("use .banner") VP_SWIFT_NAME(W320H50) = VPAdDimensionTypeBanner,
    /** The dimension type that has 320w x 100h */
    VPAdDimensionTypeW320H100 __deprecated_msg("use VpAdDimensionTypeLargeBanner") VP_SWIFT_UNAVAILABLE("use .largeBanner") VP_SWIFT_NAME(W320H100) = VPAdDimensionTypeLargeBanner,
    /** The dimension type that has 300w x 250h */
    VPAdDimensionTypeW300H250 __deprecated_msg("use VpAdDimensionTypeMediumRectangle") VP_SWIFT_UNAVAILABLE("use .mediumRectangle") VP_SWIFT_NAME(W320H250) = VPAdDimensionTypeMediumRectangle,
};


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
 * The dimension that has 320w x 50h
 */
+ (nonnull instancetype)dimensionForBanner VP_SWIFT_NAME(banner());

/**
 * The dimension that has 320w x 100h
 */
+ (nonnull instancetype)dimensionForLargeBanner VP_SWIFT_NAME(largeBanner());

/**
 * The dimension that has 300w x 250h
 */
+ (nonnull instancetype)dimensionForMediumRectangle VP_SWIFT_NAME(mediumRectangle());

/**
 * This dimension is for native banner. It is 728w x 90h currently.
 */
+ (nonnull instancetype)dimensionForLeaderboard VP_SWIFT_NAME(leaderboard());

/**
 * This dimension is for interstitial ad. It is 320w x 480h currently.
 */
+ (nonnull instancetype)dimensionForInterstitial VP_SWIFT_NAME(interstitial());

/**
 * This dimension is for native banner. It is 320w x 100h currently.
 */
+ (nonnull instancetype)dimensionForNativeBanner VP_SWIFT_NAME(nativeBanner());

/**
 * The dimension that has 320w x 480h
 */
+ (nonnull instancetype)dimensionWith320x480 VP_SWIFT_NAME(fullscreen());

/**
 * A dimension that has any width and height.
 * @param width The banner width
 * @param height The banner height
 */
+ (nonnull instancetype)dimensionWithWidth:(NSInteger)width height:(NSInteger)height;

/**
 * Create dimension with VPAdDimensionType.
 */
+ (nonnull instancetype)dimensionWithType:(VPAdDimensionType)type;

/**
 * @return a CGSize structure with placementWidth and placementHeight
 */
- (CGSize)getSize;


- (nonnull instancetype)init __unavailable;


@end

@interface VPAdDimension (Deprecated)

/**
 * The default dimension. This dimension is for interstitial ad. It is 320w x 480h currently.
 */
+ (nonnull instancetype)defaultDimension __deprecated_msg("use +[VPAdDimension dimensionWith320x480]");

/**
 * The dimension that has 320w x 50h
 */
+ (nonnull instancetype)dimensionWith320x50 __deprecated_msg("use +[VPAdDimension dimensionForBanner]");

/**
 * The dimension that has 320w x 100h
 */
+ (nonnull instancetype)dimensionWith320x100 __deprecated_msg("use +[VPAdDimension dimensionForLargeBanner]");

/**
 * The dimension that has 300w x 250h
 */
+ (nonnull instancetype)dimensionWith300x250 __deprecated_msg("use +[VPAdDimension dimensionWithMediumRectangle]");

/**
 * The dimension that has 320w x 300h
 */
+ (nonnull instancetype)dimensionWith320x300 __deprecated_msg("use +[VPAdDimension dimensionWithMediumRectangle]");

@end


#pragma mark -


@interface VPAdRequestOptions : NSObject

/**
 * The placement for an ad
 */
@property (nonatomic, copy, readonly, nonnull) NSString *placement;

/**
 * The dimension for an ad
 */
@property (nonatomic, strong, readonly, nonnull) VPAdDimension *dimension;

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

+ (nonnull instancetype)optionsWithPlacement:(nonnull NSString *)placement dimension:(nonnull VPAdDimension *)dimension;

- (nonnull instancetype)initWithPlacement:(nonnull NSString *)placement dimension:(nonnull VPAdDimension *)dimension;

- (nonnull instancetype)init __unavailable;

@end


#pragma mark -


/**
 * The VPAdContainer is passed from '-[ValuePotion requestAdWithOptions:completion:]' delegate method.
 *
 * You must use the property 'items' and '-[VPAdContainer popAd]' exclusively.
 */
@interface VPAdContainer : NSObject

@property (nonatomic, strong, readonly, nonnull) NSString *placement;
@property (nonatomic, strong, readonly, nonnull) VPAdDimension *dimension;

/**
 * Pop ad item from the item queue. If container has no more ad, returns nil.
 */
- (nullable VPAdItem *)popAd;

/**
 * The array contains ad items.
 */
#ifdef AVAILABLE_SWIFT2_GENERIC
@property (nonatomic, readonly, nonnull) NSArray<VPAdItem *>* items;
#else
@property (nonatomic, readonly, nonnull) NSArray* items;
#endif

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
- (nonnull instancetype)initWithAdItem:(nonnull VPAdItem *)adItem;

/**
 * Initialize the view with ad item.
 *
 * @param adItem an ad item gained from a VPAdContainer
 * @param closeBlock a code block is called when a user touches close button in banner.
 */
- (nonnull instancetype)initWithAdItem:(nonnull VPAdItem *)adItem closeBlock:(nonnull dispatch_block_t)closeBlock;

/**
 * Load ad item and set view up.
 *
 * @param adItem an ad item gained from a VPAdContainer
 */
- (void)loadAdItem:(nonnull VPAdItem *)adItem;

/**
 * Load ad item and set view up.
 *
 * @param adItem an ad item gained from a VPAdContainer
 * @param closeBlock a code block is called when a user touches close button in banner.
 */
- (void)loadAdItem:(nonnull VPAdItem *)adItem closeBlock:(nonnull dispatch_block_t)closeBlock;

@end

#pragma mark - NSError Information

typedef NS_ENUM(NSInteger, VPErrorType) {
    /** Unknown error. */
    VPErrorTypeUnknown = 0,
    /** Not initialized. */
    VPErrorTypeNotInitialized,
    /** No ad. */
    VPErrorTypeNoFill,
    /** Opened interstitial exists. */
    VPErrorTypeOpenedInterstitialExists,
    /** Cached interstitial exists. */
    VPErrorTypeCachedInterstitialExists,
    /** Cached interstitial is expired. */
    VPErrorTypeExpiredInterstitial,
    /** Interstitial is not support current orientation. */
    VPErrorTypeInvalidOrientation,
    /** Interstitial is blocked by user. (eg. Don't show today) */
    VPErrorTypeBlocked,
    /** Request is canceled by same placement reqeusts so quickly. */
    VPErrorTypeRequestTooSoon,
    /** Server error. */
    VPErrorTypeServerError,
    /** Empty interstitial. */
    VPErrorTypeEmptyInterstitial = VPErrorTypeNoFill,
};

OBJC_EXTERN NSString *const __nonnull kVPErrorDomain;
