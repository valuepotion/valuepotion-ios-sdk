# Change Log

## v1.1.7
* Fixed that a UIScrollView has a VPAdView can't be scrolled to top by touching the status bar.

## v1.1.6
* Fixed bugs that occurs when requesting multiple banners at once.

## v1.1.5
* Added a property - startRenderingAtCallback of VPAdRequestOptions
* Improved memory management.

## v1.1.4
* Set default background color of VPAdView transparent.

## v1.1.3
* Fixed that interstitials may not cache assets.

## v1.1.2
* Cache assets at Library/Caches

## v1.1.1
* Improved stability.

## v1.1.0
* Support banner
* Support Xcode7 bitcode

## v1.0.7
* Improved stability.

## v1.0.6
* You can now specify category and label for payment events.
```objective-c
  - (void)trackPurchaseEvent:(NSString *)eventName category:(NSString *)category label:(NSString *)label revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId productId:(NSString *)productId campaignId:(NSString *)campaignId contentId:(NSString *)contentId;
```

## v1.0.5
* Improved stability of interstitial view.
* Fixed a bug in campaign blocking function.

## v1.0.4
* Fixed a bug that incorrect session measurements occasionally occur.

## v1.0.3
* New APIs
```objective-c
  - (void)trackEvent:(NSString *)eventName category:(NSString *)category label:(NSString *)label value:(NSNumber *)value;
  - (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId productId:(NSString *)productId;
  - (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId productId:(NSString *)productId campaignId:(NSString *)campaignId contentId:(NSString *)contentId;
  - (void)setUserAccountType:(NSString *)accountType;
```
* Deprecated APIs
```objective-c
  - (void)trackEvent:(NSString *)eventName values:(NSDictionary *)values;
  - (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency;
  - (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId;
  - (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency purchase:(VPPurchase *)purchase;
  - (void)trackPurchaseEvent:(NSString *)eventName revenueAmount:(double)revenueAmount currency:(NSString *)currency transactionId:(NSString *)transactionId purchase:(VPPurchase *)purchase;
  - (void)setUserInfo:(NSDictionary *)userInfo;
```

## v1.0.2
* iOS 8 support.

## v1.0.1
* Remove unneeded device identifier.
