# Change Log

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
