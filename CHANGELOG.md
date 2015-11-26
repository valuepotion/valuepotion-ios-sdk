# Change Log

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