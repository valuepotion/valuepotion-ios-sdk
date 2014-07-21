# Valuepotion SDK for iOS - Getting Started

## Before You Begin

### 1. Register Your App
Visit [ValuePotion](https://valuepotion.com) website and register the information of your app. After that, you will be given a **Client ID** and a **Secret Key**.

### 2. Import the SDK into your Xcode project
Unzip the sdk downloaded, and add four files `libValuePotion.a`, `ValuePotion.h`, `VPPurchase.h`, `VPReward.h` to your project.

### 3. Configure Build Settings
Open Build Settings tab from Xcode project, and add `-ObjC` flag to Other Linker Flags item.

### 4. Configure Build Phases
Open Build Phases tab, and add the following frameworks to Link Binary With Libraries item.
* `UIKit.framework`
* `Foundation.framework`
* `CoreGraphics.framework`
* `SystemConfiguration.framework`
* `CoreTelephony.framework`
* `AdSupport.framework`


## Initialize SDK

The following code is to initialize SDK. We recommend you to initialize SDK at `-(BOOL)application:didFinishLaunchingWithOptions:` from `AppDelegate` class so that it's done at initial timing of launching game. If you've done all right so far, you should be able to see statistics of session, install and update events on ValuePotion dashboard.

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  ...

  // Initialize SDK using Client ID and Secret Key that you got from ValuePotion website.
  NSString clientId = @"cdc078fe55df31a6b62a42b9ed326a5b";
  NSString secretKey = @"35e3dc1de668f94c";
  [[ValuePotion sharedInstance] initializeWithClientId:clientId secretKey:secretKey];
  return YES;
}
```

## Integrate with Interstitial Ads

### 1. Display Interstitial Ads
If you've created a campaign at [ValuePotion](https://valuepotion.com), you can display it as an interstitial ad at your own app. Before displaying interstitial ads, you should set up a placement. Otherwise, "default" placement will be used by default.

**placement** is a name to distinguish many points where you want to display ads. There's no restriction but it just should be a string.

```objective-c
// Display ads at "default" placement.
[[ValuePotion sharedInstance] openInterstitial:nil];

// Display ads at "main_menu" placement.
[[ValuePotion sharedInstance] openInterstitial:@"main_menu"];
```


### 2. Cache Interstitial Ads
Using `openInterstitial:` method, the SDK will download data for ads via HTTP and display on screen. So it takes some time. If you cache ads when your game launches, you can display the ads at any time with no delay.

```objective-c
// If you cache an ad for "after_login" placement once,
[[ValuePotion sharedInstance] cacheInterstitial:@"after_login"];

...

// Later on, you can display the ad with no delay.
[[ValuePotion sharedInstance] openInterstitial:@"after_login"];
```

### 3. Display Interstitial Ads Only When Caches are Available
You can display interstitial ads only when caches are available.

```objective-c
// Check if the cache for "item_shop" placement exists.
if ([[ValuePotion sharedInstance] hasCachedInterstitial:@"item_shop"]) {
  // then, display the ad for "item_shop" placement.
  [[ValuePotion sharedInstance] openInterstitial:@"item_shop"];
}
```


## Event Tracking
You can analyze your game with event tracking. And based on events you can create cohort to use for marketing. There are non-payment event and payment event.

### 1. Non-Payment Event
Non-payment event is not related to In-App Purchase. You can use non-payment event to analyze user behavior. To use non-payment event, you should define its name and values. The following code is an example to send non-payment event.

```objective-c
// User has been cleared 3rd stage.
[[ValuePotion sharedInstance] trackEvent:@"stage_clear" value:@3];
```

If there's no specific value needed, you can use event name only.

```objective-c
// User has visited "item shop" menu.
[[ValuePotion sharedInstance] trackEvent:@"enter_item_shop" value:nil];
```


### 2. Payment Event
Payment event is tracked when In-App Purchase(In-App Billing) has occurred. If you track payment events, you can check daily statistics of Revenue, ARPU, ARPPU, PPU, etc.
The following code is an example to send payment event occurred in your game.

```objective-c
// User purchased $0.99 coin item.
[[ValuePotion sharedInstance] trackPurchaseEvent:@"purchase_coin" revenueAmount:0.99 currency:@"USD"];
```

ValuePotion provides campaign of In-App Purchase (IAP) type. When a user makes revenue via an ad of IAP type, if you add extra info to payment event, you can get revenue report per campaign in detail. The following code is how to send payment event which occurred from IAP ad.

To see more information about delegate method `-(void)didRequestPurchase:placement`, please see **didRequestPurchase:placement:** item under **Advanced: Delegate Methods** section.

```objective-c
- (void)didRequestPurchase:(VPPurchase *)purchase placement:(NSString *)placement
{
	// Proceed the requested payment

	...
  // User purchased some Diamond item for KRW 1,200. So you're attaching purchase object as payment event parameters.
  [[ValuePotion sharedInstance] trackPurchaseEvent:@"iap_diamond" revenueAmount:1200 currency:@"KRW" purchase:purchase];
}
```

#### Reference
* For accurate analysis, please specify real purchase amount and currency.
* We follow [ISO 4217](http://en.wikipedia.org/wiki/ISO_4217) for currency.

### 3. Test If Event Tracking Works
You can test if event tracking works by using test mode of the SDK. The following code will activate test mode.

```objective-c
// Activate test mode. Default is NO
[[ValuePotion sharedInstance] setTest:YES];
```

If you send events from an app built with test mode, you should see the events on developer's console at [ValuePotion](https://valuepotion.com) at real time.

**Warning** : Before submitting your app to app store, please disable test mode. Events sent form test mode are only displayed on Developer's console but excluded from analysis.



## Integrate User Information
You can collect user information as well as events. Possible fields of user information are user id, server id which user belongs to, birthdate, gender, level and number of friends. All of them are optional so you can choose which fields to collect.

You can use this information for marketing by creating user cohort. You can update your information when it changes to integrate with ValuePotion.

```objective-c
[[ValuePotion sharedInstance] setUserId:@"support@valuepotion.com"];
[[ValuePotion sharedInstance] setUserServerId:@"server1"];
[[ValuePotion sharedInstance] setUserBirth:@"19830328"];
[[ValuePotion sharedInstance] setUserGender:@"M"];
[[ValuePotion sharedInstance] setUserLevel:32];
[[ValuePotion sharedInstance] setUserFriends:219];
```

The following is the detail on each field.

Field         | Description
------------- | ------------
**userId**    | User account id used in game
**serverId**  | If you need to distinguish users by server which they belong to, you should set serverId.<br>Then you can get statistics based on serverId.
**birth**     | Date of birth in YYYYMMDD. <br>If you know only year of birth, fill last four digits with "0" like "19840000".<br>If you know only date of birth(but not year), fill first four digits with "0" like "00001109".
**gender**    | "M" for male, "F" for female.
**level**     | Level of user in game.
**friends**   | Number of user's friends.


## Integrate Push Notification
If you integrate with Push Notification API, you can easily create campaigns of Push type and send message to users. So you can wake up users who haven't played game for long time, or you can also notify users new events in game, etc.

### 1. Register Certificate
Visit [ValuePotion](https://valuepotion.com) website and update your app information. Upload Push Notification Certificate file(*.pem) at **App Edit** page.

### 2. Enable Push Notification
To enable Push Notification, you should implement three methods at `AppDelegate` class. Refer to the following example.

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  ...

  NSString clientId = @"cdc078fe55df31a6b62a42b9ed326a5b";
  NSString secretKey = @"35e3dc1de668f94c";
  [[ValuePotion sharedInstance] initializeWithClientId:clientId secretKey:secretKey];

  // Make Push Notification enable
  [[ValuePotion sharedInstance] registerForPushNotification];

  // Integrate push information with ValuePotion.
  [[ValuePotion sharedInstance] forwardPushInfo:launchOptions];

  return YES;
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
  ...

  // Integrate push information with ValuePotion.
  [[ValuePotion sharedInstance] forwardPushInfo:userInfo];
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
  ...

  // Deliver deviceToken to ValuePotion.
  [[ValuePotion sharedInstance] registerPushToken:deviceToken];
}
```

### 3. Disable Push Notification
If you need to disable Push Notification or check whether Push Notification is enabled, use the following code.

```objective-c
// Disable Push Notification
[[ValuePotion sharedInstance] unregisterForPushNotification];

// Returns BOOL value indicating whether Push Notification is enabled.
[[ValuePotion sharedInstance] isPushNotificationEnabled];
```


## Advanced: Delegate Methods
In `ValuePotionDelegate` protocol, some delegate methods are defined to integrate with campaigns. All the delegate methods are optional. You can choose and implement delegate methods as you need.

### 1. Delegate Methods for Displaying Interstitial Ad
#### - (void)willOpenInterstitial:
This delegate method is called when displaying interstitial ad is successfully done after calling `openInterstitial:` method.

```objective-c
- (void)willOpenInterstitial:(NSString *)placement
{
	// Put something you need to do when interstitial ad is displayed.
	// For example, you can pause game here.
}
```

#### - (void)didFailToOpenInterstitial:error:
This delegate method is called when displaying interstitial ad is failed after calling `openInterstitial:` method.

```objective-c
- (void)didFailToOpenInterstitial:(NSString *)placement error:(NSError *)error
{
	// Put something you need to do when interstitial ad gets failed.
	// You can check reason of failure via error object.
}
```

#### - (void)didCloseInterstitial:
This delegate method is called when interstitial ad closes.

```objective-c
- (void)didCloseInterstitial:(NSString *)placement
{
	// Put something you need to do when interstitial ad closes.
	// If you paused your game during ad is open, now you can resume it here.
}
```

### 2. Delegate Methods for Caching Interstitial Ad
#### - (void)didCacheInterstitial:
This delegate method is called when caching interstitial ad is successfully done after calling `cacheInterstitial:` method.

```objective-c
- (void)didCacheInterstitial:(NSString *)placement
{
	// Put something you need to do when caching interstitial ad is successfully done
}
```

#### - (void)didFailToCacheInterstitial:error:
This delegate method is called when caching interstitial ad is failed after calling `cacheInterstitial:` method.

```objective-c
- (void)didFailToCacheInterstitial:(NSString *)placement error:(NSError *)error
{
	// Put something you need to do when caching interstitial ad is failed.
	// You can check reason of failure via error object.
}
```

### 3. Delegate Methods for Interstitial Ad Action
#### - (void)didRequestOpenURL:placement:
This delegate method is called when user clicks external url while interstitial ad is displayed.

```objective-c
- (void)didRequestOpenURL:(NSURL *)URL placement:(NSString *)placement
{
	// Put something you need to do when external url gets opened.
	// App soon goes background, so you can do something like saving user data, etc.
}
```

#### - (void)didRequestPurchase:placement:
This delegate method is called when user pressed 'Purchase' button while interstitial ad of IAP type is displayed.

```objective-c
- (void)didRequestPurchase:(VPPurchase *)purchase placement:(NSString *)placement
{
	// Put codes to process real purchase by using parameters: productId, quantity.
	// purchase object contains properties: name, productId, quantity, campaignId, contentId.
	// After purchase, call trackPurchaseEvent:revenueAmount:currency:purchase: method for revenue report.
}
```

#### - (void)didRequestReward:placement:
This delegate method is called when interstitial ad of Reward type is displayed.

```objective-c
- (void)didRequestReward:(NSArray *)rewards placement:(NSString *)placement
{
  // Array 'rewards' contains rewards which ad is about to give users.
  // With this information you should implement actual code to give rewards to users.
  [rewards enumerateObjectsUsingBlock:^(VPReward *reward, NSUInteger idx, BOOL *stop) {
    // The names of quantities of rewards to give
    NSLog(@"name: %@, quantity: %d", reward.name, (int)reward.quantity);
  }];
}
```
