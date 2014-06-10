## SDK 설치

#### 프로젝트 요구 사항

* Xcode: 5.0 이상
* Base SDK: iOS 7.0 이상
* Deployment Target: iOS 4.3 이상

#### 구성
ValuePotion iOS SDK는 다음과 같이 구성되어 있습니다.

* libValuePotion.a
* ValuePotion.h
* VPPurchase.h
* VPReward.h

#### 통합 및 설정
##### SDK 파일 복사
SDK 파일의 압축을 해제한 후, 구성 파일 모두를 프로젝트에 복사합니다.

(캡쳐 이미지 삽입)

##### 필수 framework 설정
프로젝트에 다음의 framework들을 포함시킵니다.

* Foundation.framework
* UIKit.framework
* CoreGraphics.framework
* StoreKit.framework
* SystemConfiguration.framework
* CoreTelephony.framework
* AdSupport.framework

(캡쳐 이미지 삽입)

## 기본 연동
#### SDK 초기화
ValuePotion 클래스의 initializeWithClientId:secretKey: 메소드를 이용해 간단하게 SDK를 초기화 할 수 있습니다.
초기화 위치는 어느 곳이나 상관 없지만, 가능한 앱이 실행될 때 즉시 호출되는 위치에 추가하는 것이 좋습니다.
일반적으로 AppDelegate 클래스의 application:didFinishLaunchingWithOptions: 메소드 내부에 추가하는 것이 적당합니다.
client id와 secret key는 [valuepotion|http://valuepotion.com]에서 등록하신 앱 정보 화면에서 확인 가능합니다.

```objc
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    ...
    ...
    [[ValuePotion sharedInstance] initializeWithClientId:@"app client id" secretKey:@"app secret key"];
    return YES;
}
```
여기까지만 설정하셔도 기본적인 세션 트래킹과 install / update 이벤트 트래킹이 가능합니다.

#### 사용자 추가 정보 설정
사용자의 추가 정보에 대한 수집이 가능합니다. 해당 정보를 이용해 유저 코호트를 생성하여 활용할 수 있습니다.
현재는 사용자의 계정 id, 성별, 연령 정보를 추가로 설정하실 수 있습니다.

```objc
[[ValuePotion sharedInstance] setUserInfo:@{@"userId": @"valuepotion",
                                            @"birth": @"19841109",
                                            @"gender": @"M"}];
```

##### 추가 정보 항목
이름    |   설명
------- | ----------
userId  |  게임 내에서 사용되는 사용자의 계정 id를 할당합니다.
birth   |  사용자의 생년월일 8자리를 문자열로 할당합니다.
        |  연도 정보만 아는 경우 @"19840000"과 같이 생일 4자리를 0으로 채워 할당합니다.
        | 생일 정보만 아는 경우 @"00001109"와 같이 연도 4자리를 0으로 채워 할당합니다.
gender  |  남성인 경우 @"M", 여성인 경우 @"F" 문자열로 할당합니다.

## 캠페인 연동
[valuepotion](http://valuepotion.com)에서 생성한 캠페인을 interstitial 형태로 앱에 노출시킬 수 있습니다.
모든 interstitial은 로케이션 단위로 관리되며, 로케이션 이름은 정해진 규칙 없이 자유롭게 할당하실 수 있습니다.

#### interstitial 캐싱하기
앱 실행 초기에 미리 캠페인 데이터를 받아 캐싱하고, 이후 필요한 시점에 즉시 interstitial을 보여줄 수 있습니다.
다음의 코드는 main_menu, item_shop 이라는 2가지 로케이션에 대해 interstitial을 캐싱하는 예제입니다.
```objc
[[ValuePotion sharedInstance] cacheInterstitial:@"main_menu"];
[[ValuePotion sharedInstance] cacheInterstitial:@"item_shop"];
```

#### interstitial 노출하기
interstitial을 화면에 보여주고자 할 때에는 openInterstitial: 메소드를 사용합니다.
openInterstitial: 메소드는 지정된 로케이션에 캐시가 존재하는 경우 해당 캐시를 가지고 즉시 화면에 보여줍니다.
만약 해당 로케이션에 캐시가 존재하지 않으면 서버와 통신하여 데이터를 가져와 화면에 노출시키게 됩니다.
다음은 main_menu 로케이션에서 interstitial을 띄우는 예제입니다.
```objc
[[ValuePotion sharedInstance] openInterstitial:@"main_menu"];
```

#### 캐시가 있을 때만 interstitial 노출하기
interstitial 데이터를 필요 시마다 서버로부터 받아와서 화면에 보여주게 되면 다소 딜레이가 발생할 수 있습니다.
따라서 앱 실행 초기에 모든 로케이션에 대해 캐싱해 두고, 캐시가 존재하는 로케이션에 대해서만 interstitial을 노출하고 싶을 수도 있습니다.
다음은 item_shop 로케이션에 캐시가 존재하는 경우에만 interstitial을 노출하도록 처리한 예제입니다.
```objc
if ([[ValuePotion sharedInstance] hasCachedInterstitial:@"item_shop"]) {
    [[ValuePotion sharedInstance] openInterstitial:@"item_shop"];
}
```

#### Delegate 메소드
ValuePotionDelegate 프로토콜에는 캠페인 연동 시 활용 가능한 delegate 메소드들이 정의되어 있습니다.
모든 delegate 메소드는 optional이므로, 필요하지 않은 경우 구현할 필요가 없습니다.

##### 캐싱 관련 delegate
interstitial의 캐싱 성공 / 실패에 대한 delegate 처리를 할 수 있습니다.
```objc
- (void)didCacheInterstitial:(NSString *)location
{
    // interstitial 캐싱이 완료되었을 때 필요한 작업을 추가합니다.
}

- (void)didFailToCacheInterstitial:(NSString *)location error:(NSError *)error
{
    // interstitial 캐싱에 실패했을 때 필요한 작업을 추가합니다. 
}
```

##### 노출 관련 delegate
interstitial의 노출 성공 / 실패 / 종료에 대한 delegate 처리를 할 수 있습니다.
```objc
- (void)willOpenInterstitial:(NSString *)location
{
    // interstitial이 노출될 때 필요한 작업을 추가합니다.
}

- (void)didFailToOpenInterstitial:(NSString *)location error:(NSError *)error
{
    // interstitial 노출에 실패했을 때 필요한 작업을 추가합니다.
}

- (void)didCloseInterstitial:(NSString *)location
{
    // interstitial이 닫힐 때 필요한 작업을 추가합니다.
}
```

##### 액션 관련 delegate
사용자가 interstitial 내부에서 발생시킨 액션에 대한 delegate 처리를 할 수 있습니다.
```objc
- (void)didRequestOpenURL:(NSString *)URL location:(NSString *)location
{
    // interstitial에서 외부 링크에 대한 클릭이 발생했을 때 호출됩니다.
    // 일반적으로 외부 링크를 클릭하면 현재 앱은 background로 들어가게 되므로, 이 경우 필요한 처리를 여기서 구현합니다.
}

- (void)didRequestPurchase:(VPPurchase *)purchase location:(NSString *)location
{
    // In App Purchase 캠페인의 interstitial 내부에서 사용자가 구매하기를 선택했을 때 호출됩니다.
    // purchase 객체는 productIdentifier, quantity, name 속성을 가지고 있습니다.
    // 이 속성 정보를 가지고 실제 결제 진행을 위한 코드를 여기에서 구현합니다.
}

- (void)didRequestReward:(VPReward *)reward location:(NSString *)location
{
    // 리워드 캠페인의 interstitial이 화면에 보여질 때 호출됩니다.
    // reward 객체는 name, quantity 속성을 가지고 있습니다.
    // 이 속성 정보를 가지고 해당 리워드 아이템을 사용자에게 지급하는 코드를 여기에서 구현합니다.
}
```

## 커스텀 이벤트 연동
커스텀 이벤트 전송 기능을 통해 앱에 대한 보다 세밀한 분석이 가능합니다.
또한, 커스텀 이벤트를 활용해 유저 코호트를 생성할 수도 있습니다.
커스텀 이벤트는 크게 비결제 이벤트와 결제 이벤트로 나뉩니다.

#### 비결제 이벤트 전송하기
비결제 이벤트는 게임 내 결제와 무관한 이벤트로, 이벤트 이름과 값을 인자로 받습니다.
비결제 이벤트의 경우 trackEvent:value: 메소드와 trackEvent:values: 메소드를 이용하여 전송할 수 있습니다.
각각의 사용법은 다음과 같습니다.
```objc
// value가 한 개인 경우. NSNumber 객체를 value 인자로 사용합니다.
[[ValuePotion sharedInstance] trackEvent:@"stage_clear" value:@3];

// value가 여러 개인 경우. NSDictionary 객체를 value 인자로 사용합니다.
// NSDictionary의 key-value 쌍에서 모든 value 값들은 NSNumber 객체여야 합니다.
[[ValuePotion sharedInstance] trackEvent:@"stage_clear" values:@{@"item_use":@2, @"score":@192990, @"play_time":@36.27}];
```

특별한 값이 존재하지 않는 이벤트인 경우 value 인자를 nil로 넘기면 됩니다.
```objc
[[ValuePotion sharedInstance] trackEvent:@"login" value:nil];
```

#### 결제 이벤트 전송하기
결제 이벤트는 게임 내 결제(In App Purchase)가 발생했을 때 사용되는 이벤트입니다.
비결제 이벤트와 같이 이벤트 이름과 값을 인자로 받으며, 추가로 결제 금액과 결제 통화 정보를 필요로 합니다.
다음은 결제 이벤트를 전송하는 예제입니다.
```objc
[[ValuePotion sharedInstance] trackPurchaseEvent:@"gold_purchase" revenueAmount:0.99 currency:@"USD"];
```
결제 통화를 나타내는 currency 인자는 SKProduct 객체의 priceLocale.localeIdentifier 속성 값을 그대로 사용하면 됩니다.

## Push Notification 연동

Push Notification API를 연동하면, 손쉽게 Push 타입의 캠페인을 생성하여 사용자에게 메시지를 전송할 수 있습니다.
또한, 사용자 Push 메시지를 클릭하여 게임을 실행한 경우 특정 캠페인의 interstitial을 노출시키도록 하는 것도 가능합니다.
Push Notification 연동을 위해서는 AppDelegate 클래스에서 다음과 같이 구현합니다.

```objc
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    ...

    [[ValuePotion sharedInstance] initializeWithClientId:@"app client id" secretKey:@"app secret key"];     // SDK 초기화
    [[ValuePotion sharedInstance] registerForPushNotification];                                             // SDK에서 Push Notification 사용하도록 설정
    [[ValuePotion sharedInstance] forwardPushInfo:launchOptions];                                           // Push 메시지를 클릭해 앱 실행되었을 때 해당 정보를 SDK로 전달

    return YES;
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    [[ValuePotion sharedInstance] forwardPushInfo:userInfo];                                                // Push 메시지를 받았을 때 해당 정보를 SDK로 전달
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    [[ValuePotion sharedInstance] registerPushToken:deviceToken];                                           // device token 데이터를 SDK로 전달
}
```


