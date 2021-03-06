//
//  ValuePotionInstance.h
//
//  Copyright © 2016년 ValuePotion. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <ValuePotion/ValuePotionDefines.h>


@class VPAdContainer;
@class VPAdRequestOptions;
@class VPPurchase;
@class VPReward;


@protocol ValuePotionDelegate;


NS_ASSUME_NONNULL_BEGIN


OBJC_EXTERN NSString *const VPValuePotionWillPresentVideoAdNotification;
OBJC_EXTERN NSString *const VPValuePotionDidDismissVideoAdNotification;


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
+ (ValuePotion *)sharedInstance VP_SWIFT_NAME(shared());

/**
 * Initialize valuepotion library.
 *
 * @param clientId The client id to use ValuePotion sdk
 * @param secretKey The secret key
 */
- (void)initializeWithClientId:(NSString *)clientId secretKey:(NSString *)secretKey VP_SWIFT_NAME(initialize(clientId:secretKey:));

#pragma mark - Interstitial Methods
- (BOOL)hasCachedInterstitial:(NSString *)placement __TVOS_PROHIBITED;
- (void)cacheInterstitial:(NSString *)placement __TVOS_PROHIBITED;
- (void)openInterstitial:(nullable NSString *)placement __TVOS_PROHIBITED;

#pragma mark - Interstitial Methods with contentSeq
- (BOOL)hasCachedInterstitial:(NSString *)placement contentSeq:(nullable NSString *)contentSeq __TVOS_PROHIBITED;
- (void)cacheInterstitial:(NSString *)placement contentSeq:(nullable NSString *)contentSeq __TVOS_PROHIBITED;
- (void)openInterstitial:(nullable NSString *)placement contentSeq:(nullable NSString *)contentSeq __TVOS_PROHIBITED;

#pragma mark - RequestOptions Methods
- (void)requestAdWithOptions:(VPAdRequestOptions *)options completion:(VPAdRequestCallback)completion __TVOS_PROHIBITED VP_SWIFT_NAME(requestAd(with:completion:));

#pragma mark - Tracking Methods
- (void)trackEvent:(NSString *)eventName value:(nullable NSNumber *)value VP_SWIFT_NAME(track(event:value:));
- (void)trackEvent:(NSString *)eventName category:(nullable NSString *)category label:(nullable NSString *)label value:(nullable NSNumber *)value VP_SWIFT_NAME(track(event:category:label:value:));
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(nullable NSString *)transactionId productId:(nullable NSString *)productId VP_SWIFT_NAME(track(purchaseEvent:revenueAmount:currency:transactionId:productId:));
- (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(nullable NSString *)transactionId productId:(nullable NSString *)productId campaignId:(nullable NSString *)campaignId contentId:(nullable NSString *)contentId VP_SWIFT_NAME(track(purchaseEvent:revenueAmount:currency:transactionId:productId:campaignId:contentId:));
- (void)trackPurchaseEvent:(NSString *)eventName category:(nullable NSString *)category label:(nullable NSString *)label revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(nullable NSString *)transactionId productId:(nullable NSString *)productId campaignId:(nullable NSString *)campaignId contentId:(nullable NSString *)contentId VP_SWIFT_NAME(track(purchaseEvent:category:label:revenueAmount:currency:transactionId:productId:campaignId:contentId:));

#pragma mark - Push Notification Methods
- (void)registerForPushNotification __TVOS_PROHIBITED;
- (void)unregisterForPushNotification __TVOS_PROHIBITED;
- (BOOL)isPushNotificationEnabled __TVOS_PROHIBITED;
- (void)registerPushToken:(NSData *)token __TVOS_PROHIBITED;
- (void)registerPushTokenString:(NSString *)tokenString __TVOS_PROHIBITED;
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
- (void)setUserValue:(id)value forKey:(NSString *)key;

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
- (void)didCacheInterstitial:(NSString *)placement;

/**
 * Sent if it failed to cache interstitial ad.
 *
 * @param placement The interstitial ad's placement
 * @param error The error that occurred during caching
 */
- (void)didFailToCacheInterstitial:(NSString *)placement error:(nullable NSError *)error;

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
- (void)didFailToOpenInterstitial:(NSString *)placement error:(nullable NSError *)error;

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
#ifdef AVAILABLE_SWIFT2_GENERIC
- (void)didRequestRewards:(NSArray<VPReward *> *)rewards placement:(NSString *)placement;
#else
- (void)didRequestRewards:(NSArray *)rewards placement:(NSString *)placement;
#endif

/**
 * Sent after inplay view did complete conversion.
 *
 * @param placement The interstitial ad's placement
 */
- (void)didCompleteConversion:(NSString *)placement;

/**
 * Decides whether to allow or cancel to play a video ad.
 * Call a code block decisionHandler with `YES` if you allow, otherwise call it with `NO`.
 *
 * If you don't implement this method, video ads are played automatically.
 */
- (void)decideToPlayVideo:(NSString *)placement contentSeq:(NSString *)contentSeq decisionHandler:(void (^)(BOOL play))decisionHandler;

/**
 * Sent after a user watches the video ad until the end.
 * Call a code block closingHandler when you want to close. If you want to close the interstitial ad also, call with parameter `YES`, otherwise `NO`.
 *
 * If you don't implement this method, the interstitial ad will be closed automatically.
 */
- (void)didCompleteVideoWatching:(NSString *)placement contentSeq:(NSString *)contentSeq closeOnCall:(BOOL)closeOnCall closingHandler:(void (^)(BOOL closeInterstitial))closingHandler;

/**
 * Sent when a video loading is failed.
 */
- (void)didFailToLoadVideo:(NSString *)placement error:(NSError *)error closeOnCall:(BOOL)closeOnCall closingHandler:(void (^)(BOOL closeInterstitial))closingHandler;

/**
 * Sent after a user cancels playing the video ad before the end.
 * Call a code block closingHandler when you want to close. If you want to close the interstitial ad also, call with parameter `YES`, otherwise `NO`.
 *
 * If you don't implement this method, only the video view will be closed without closing the interstitial ad.
 */
- (void)didCancelToWatchVideo:(NSString *)placement duration:(float)duration position:(float)position closeOnCall:(BOOL)closeOnCall closingHandler:(void (^)(BOOL closeInterstitial))closingHandler;

@end

NS_ASSUME_NONNULL_END
