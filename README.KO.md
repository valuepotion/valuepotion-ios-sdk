# Valuepotion iOS SDK 통합 가이드

## 기본 설정

### 1. 앱 정보 등록
먼저 [밸류포션](https://valuepotion.com) 웹사이트에 방문하여 SDK를 적용할 앱의 정보를 등록합니다. 앱 정보 등록을 완료하면 Client ID 와 Secret Key 가 발급됩니다.

### 2. Xcode 프로젝트에 SDK 임포트
다운로드 받으신 파일의 압축을 해제한 후 `libValuePotion.a`, `ValuePotion.h`, `VPPurchase.h`, `VPReward.h` 4개의 파일을 프로젝트에 추가합니다.

### 3. Build Settings 설정
Xcode 프로젝트의 Build Settings 탭에서 Other Linker Flags 항목에 `-ObjC` 플래그를 추가합니다.

### 4. Build Phases 설정
Xcode 프로젝트의 Build Phases 탭에서 Link Binary With Libraries 항목에 다음의 framework 들을 추가합니다.
* `UIKit.framework`
* `Foundation.framework`
* `CoreGraphics.framework`
* `SystemConfiguration.framework`
* `CoreTelephony.framework`
* `AdSupport.framework`


## SDK 초기화
다음은 SDK를 초기화 하는 예제입니다. 게임 실행 초기에 불려질 수 있도록 `AppDelegate` 클래스의  `-(BOOL)application:didFinishLaunchingWithOptions:` 메소드 내에서 사용하는 것을 권장합니다. 여기까지 설정하면 기본적인 session / install / update 이벤트 트래킹이 가능합니다.

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  ...

  // 밸류포션 웹사이트에서 발급받은 Client ID 와 Secret Key 를 사용해 SDK를 초기화 합니다.
  NSString clientId = @"cdc078fe55df31a6b62a42b9ed326a5b";
  NSString secretKey = @"35e3dc1de668f94c";
  [[ValuePotion sharedInstance] initializeWithClientId:clientId secretKey:secretKey];
  return YES;
}
```

## 인터스티셜 광고 연동

### 1. 인터스티셜 광고 노출하기
[밸류포션](https://valuepotion.com) 웹 사이트에서 생성한 캠페인을 인터스티셜 광고의 형태로 자신의 앱에 노출시킬 수 있습니다. 인터스티셜 광고를 화면에 띄우기 위해서는 플레이스먼트를 지정해야 하며, 지정하지 않는 경우 "default" 플레이스먼트가 사용됩니다.

플레이스먼트는 게임 내의 여러 지점에서 원하는 광고를 노출 시킬 수 있도록 하기 위해 부여하는 이름으로, 특별한 제약 없이 원하는 이름을
문자열로 지정하면 됩니다.

```objective-c
// "default" 플레이스먼트에 대해 광고를 노출 합니다.
[[ValuePotion sharedInstance] openInterstitial:nil];

// "main_menu" 플레이스먼트에 대해 광고를 노출 합니다.
[[ValuePotion sharedInstance] openInterstitial:@"main_menu"];
```


### 2. 인터스티셜 광고 캐싱하기
`openInterstitial:` 메소드를 사용하면 HTTP 를 통해 광고 데이터를 받아온 후 화면에 보여주기 때문에, 네트워크 상태에 따라 다소 지연이 발생할 수 있습니다. 최초 게임 구동 시 원하는 플레이스먼트에 대해 광고를 캐싱해두면,
이후 원하는 시점에 지연 없이 해당 광고를 화면에 노출시킬 수 있습니다.

```objective-c
// 최초 "after_login" 플레이스먼트에 대해 광고를 캐싱합니다.
[[ValuePotion sharedInstance] cacheInterstitial:@"after_login"];

...

// 원하는 시점에 "after_login" 플레이스먼트에 대해 광고를 노출합니다.
[[ValuePotion sharedInstance] openInterstitial:@"after_login"];
```

### 3. 캐시가 있을 때만 인터스티셜 광고 노출하기
특정 플레이스먼트에 캐싱된 광고가 확실히 존재할 때에만 광고를 노출시킬 수도 있습니다.

```objective-c
// "item_shop" 플레이스먼트에 캐싱된 광고가 존재하는지 체크합니다.
if ([[ValuePotion sharedInstance] hasCachedInterstitial:@"item_shop"]) {
  // "item_shop" 플레이스먼트에 대해 광고를 노출합니다.
  [[ValuePotion sharedInstance] openInterstitial:@"item_shop"];
}
```


## 이벤트 트래킹
이벤트 트래킹 기능을 통해 게임에 대한 보다 세밀한 분석이 가능합니다. 또한, 이를 기반으로 유저 코호트를 생성하여 마케팅에 활용할 수 있습니다. 이벤트는 크게 비결제 이벤트와 결제 이벤트로 나뉩니다.

### 1.비결제 이벤트 트래킹
비결제 이벤트는 게임 내 결제와 무관한 이벤트로, 주로 사용자 행태 분석을 위해 사용합니다. 비결제 이벤트 트래킹을 위해서는 이벤트의 이름과 값을 지정해야 합니다. 다음은 비결제 이벤트를 전송하는 예제입니다.

```objective-c
// 사용자가 3번째 스테이지를 클리어
[[ValuePotion sharedInstance] trackEvent:@"stage_clear" value:@3];
```

특별한 값이 필요치 않은 이벤트인 경우, 간단히 이벤트 이름만을 지정하여도 됩니다.

```objective-c
// 사용자가 item shop 메뉴에 방문
[[ValuePotion sharedInstance] trackEvent:@"enter_item_shop" value:nil];
```


### 2. 결제 이벤트 트래킹
결제 이벤트는 게임 내 구매(In App Purchase)가 발생했을 때 전송하는 이벤트입니다. 결제 이벤트를 트래킹하면 매출액, ARPU, ARPPU, PPU 등 유용한 지표들의 추이를 매일 확인할 수 있습니다. 다음은 게임 내에서 발생한 결제 이벤트를 전송하는 예제입니다.

```objective-c
// 0.99 달러의 코인 아이템 구매가 발생
[[ValuePotion sharedInstance] trackPurchaseEvent:@"purchase_coin" revenueAmount:0.99 currency:@"USD"];
```

밸류포션은 In App Purchase (이하 IAP) 타입의 캠페인을 제공합니다. 게임 사용자가 IAP 타입의 광고를 통해 매출을 발생시킨 경우, 결제 이벤트에 추가 정보를 더해 전송하면 더욱 상세한 캠페인 별 매출 리포트를 제공 받으실 수 있습니다. 다음은 IAP 광고로부터 발생한 결제 이벤트를 전송하는 예제입니다.

`-(void)didRequestPurchase:placement` 델리게이트 메소드에 대한 보다 자세한 정보는 **고급: 델리게이트 메소드** 섹션의 **didRequestPurchase:placement:** 항목을 참고하십시오.

```objective-c
- (void)didRequestPurchase:(VPPurchase *)purchase placement:(NSString *)placement
{
  // 요청 받은 결제를 진행합니다

  ...

  // 1,200원의 다이아몬드 아이템 구매가 발생. purchase 객체를 함께 전송
  [[ValuePotion sharedInstance] trackPurchaseEvent:@"iap_diamond" revenueAmount:1200 currency:@"KRW" purchase:purchase];
}
```

#### 참고
* 정확한 집계를 위해, 결제 이벤트 전송 시에는 실제 발생한 결제 금액과 통화 코드를 지정해주십시오.
* 통화 코드는 [ISO 4217](http://en.wikipedia.org/wiki/ISO_4217) 표준을 따릅니다.

### 3. 이벤트 트래킹 테스트
SDK의 테스트 모드를 통해 정상적으로 이벤트가 전송되는지 여부를 쉽게 확인할 수 있습니다. 테스트 모드를 활성화 시키는 방법은 다음과 같습니다.

```objective-c
// 테스트 모드로 설정. 기본값은 NO
[[ValuePotion sharedInstance] setTest:YES];
```

테스트 모드로 빌드된 앱에서 전송되는 이벤트는 [밸류포션](https://valuepotion.com) 웹사이트의 개발자 콘솔 메뉴에서 실시간으로 확인 가능합니다.

**주의** : 앱 스토어에 제출하기 위한 최종 빌드 시에는 반드시 테스트 모드를 해제하십시오. 테스트 모드에서 전송된 이벤트는 개발자 콘솔 메뉴에서만 출력되고, 실제 집계에서는 제외됩니다.



## 사용자 정보 연동
이벤트 트래킹과는 별도로, 게임 사용자의 추가 정보에 대한 수집이 가능합니다. 현재 밸류포션에서 지원하는 사용자 정보는 사용자의 계정 ID, 사용자가 속한 게임 서버의 ID, 생년월일, 성별, 레벨, 친구 수의 6가지입니다. 모든 항목은 선택적이므로, 필요치 않다면 어떤 것도 설정할 필요가 없습니다.

이 정보들을 이용해 유저 코호트를 생성하여 마케팅에 활용할 수있습니다. 사용자 정보는 게임의 진행 중 변경이 있을 때마다 새로이 설정하여 주시면 자동으로 밸류포션과 연동됩니다.

```objective-c
[[ValuePotion sharedInstance] setUserId:@"support@valuepotion.com"];
[[ValuePotion sharedInstance] setUserServerId:@"server1"];
[[ValuePotion sharedInstance] setUserBirth:@"19830328"];
[[ValuePotion sharedInstance] setUserGender:@"M"];
[[ValuePotion sharedInstance] setUserLevel:32];
[[ValuePotion sharedInstance] setUserFriends:219];
```

각 사용자 정보 항목에 대한 세부 내용은 다음과 같습니다.

이름            | 설명
-------------- | ------------
**userId**    | 게임 내에서 사용되는 사용자의 계정 id를 설정합니다.
**serverId**  | 게임 유저를 서버 별로 식별해야 하는 경우 유저가 속한 서버의 id를 설정합니다.<br>serverId를 기준으로 서버별 통계를 확인할 수 있습니다.
**birth**     | 사용자의 생년월일 8자리를 문자열로 세팅합니다.<br>연도 정보만 아는 경우 "19840000"과 같이 뒤 4자리를 0으로 채웁니다.<br>생일 정보만 아는 경우 "00001109"와 같이 앞 4자리를 0으로 채웁니다.
**gender**    | 남성인 경우 "M", 여성인 경우 "F" 문자열로 설정합니다.
**level**     | 사용자의 게임 내 레벨을 설정합니다.
**friends**   | 사용자의 친구 수를 설정합니다.


## Push Notification 연동
밸류포션 Push Notification API와 연동하면, 손쉽게 Push 타입의 캠페인을 생성하여 사용자에게 메시지를 전송할 수 있습니다. 장기간 게임을 플레이 하지 않은 유저들이 다시 접속하도록 유도하거나, 게임 내 이벤트 소식을 알리는 등 다방면으로 활용이 가능합니다.

### 1. 인증서 등록
[밸류포션](https://valuepotion.com) 웹사이트에서 앞서 등록한 앱 정보를 업데이트 해야 합니다. 앱 정보 수정 페이지에서 Push Notification 인증서 파일(*.pem)을 업로드 하십시오.

### 2. Push Notification 활성화
Push Notification 을 활성화 시키려면 `AppDelegate` 클래스의 3 가지 메소드를 추가 구현해야 합니다. 다음 예제를 참고하여 구현하시기 바랍니다.

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  ...

  NSString clientId = @"cdc078fe55df31a6b62a42b9ed326a5b";
  NSString secretKey = @"35e3dc1de668f94c";
  [[ValuePotion sharedInstance] initializeWithClientId:clientId secretKey:secretKey];

  // Push Notification 수신 가능 상태가 됩니다.
  [[ValuePotion sharedInstance] registerForPushNotification];

  // 집계를 위해 Push 정보를 밸류포션과 연동합니다.
  [[ValuePotion sharedInstance] forwardPushInfo:launchOptions];

  return YES;
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
  ...

  // 집계를 위해 Push 정보를 밸류포션과 연동합니다.
  [[ValuePotion sharedInstance] forwardPushInfo:userInfo];
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
  ...

  // deviceToken 을 밸류포션으로 전달합니다.
  [[ValuePotion sharedInstance] registerPushToken:deviceToken];
}
```

### 3. Push Notification 비활성화
Push Notification 을 비활성화 시키거나 Push Notification 활성화 여부를 판단해야 하는 경우, 다음 예제를 참고하십시오.

```objective-c
// Push Notification 을 받지 않도록 변경됩니다.
[[ValuePotion sharedInstance] unregisterForPushNotification];

// Push Notification 활성화 여부를 BOOL 타입으로 리턴합니다.
[[ValuePotion sharedInstance] isPushNotificationEnabled];
```


## 고급: 델리게이트 메소드
`ValuePotionDelegate` 프로토콜에는 캠페인 연동 시 활용 가능한 델리게이트 메소드가 정의되어 있습니다. 모든 델리게이트 메소드는 optional이므로, 필요한 델리게이트 메소드만 구현하여 사용하시면 됩니다.

### 1. Interstitial 노출 관련
#### - (void)willOpenInterstitial:
`openInterstitial:` 메소드 호출 후, 인터스티셜 광고가 성공적으로 화면에 노출되는 시점에 호출됩니다.

```objective-c
- (void)willOpenInterstitial:(NSString *)placement
{
  // 인터스티셜 광고가 열릴 때 필요한 작업이 있다면 여기에 구현합니다.
  // 실행 중인 게임을 pause 시키는 등의 처리를 할 수 있습니다.
}
```

#### - (void)didFailToOpenInterstitial:error:
`openInterstitial:` 메소드 호출 후, 인터스티셜 광고가 화면에 노출되지 못하는 경우 호출됩니다.

```objective-c
- (void)didFailToOpenInterstitial:(NSString *)placement error:(NSError *)error
{
  // 인터스티셜 광고 노출에 실패했을 때 필요한 작업이 있다면 여기에 구현합니다.
  // 실패한 원인은 error 를 통해 확인할 수 있습니다.
}
```

#### - (void)didCloseInterstitial:
인터스티셜 광고가 열려있는 상태에서 닫힐 때 호출됩니다.

```objective-c
- (void)didCloseInterstitial:(NSString *)locaion
{
  // 인터스티셜 광고가 닫힐 때 필요한 작업이 있다면 여기에 구현합니다.
  // 광고가 열려있는 동안 게임을 pause 시켰다면, 여기서 resume 시키는 등의 처리를 할 수 있습니다.
}
```

### 2. Interstitial 캐싱 관련
#### - (void)didCacheInterstitial:
`cacheInterstitial:` 메소드 호출 후, 성공적으로 광고가 캐싱 되었을 때 호출됩니다.

```objective-c
- (void)didCacheInterstitial:(NSString *)placement
{
  // 인터스티셜 광고 캐싱이 완료된 후 필요한 작업이 있다면 여기에 구현합니다.
}
```

#### - (void)didFailToCacheInterstitial:error:
`cacheInterstitial:` 메소드 호출 후, 광고 캐싱에 실패했을 때 호출됩니다.

```objective-c
- (void)didFailToCacheInterstitial:(NSString *)placement error:(NSError *)error
{
  // 인터스티셜 광고 캐싱에 실패했을 때 필요한 작업이 있다면 여기에 구현합니다.
  // 실패한 원인은 error 를 통해 확인할 수 있습니다.
}
```

### 3. Interstitial 액션 관련
#### - (void)didRequestOpenURL:placement:
인터스티셜 광고 노출 상태에서 사용자가 외부 링크를 클릭하는 경우 발생합니다.

```objective-c
- (void)didRequestOpenURL:(NSURL *)URL placement:(NSString *)placement
{
  // 외부 링크를 열 때 필요한 작업이 있다면 여기에 구현합니다.
  // 앱이 Background로 진입하게 되므로, 사용자 데이터를 저장하는 등의 처리를 할 수 있습니다.
}
```

#### - (void)didRequestPurchase:placement:
IAP 타입의 인터스티셜 광고 노출 상태에서 사용자가 '결제하기'를 선택하는 경우 발생합니다.

```objective-c
- (void)didRequestPurchase:(VPPurchase *)purchase placement:(NSString *)placement
{
  // 인자로 전달된 purchase 오브젝트를 가지고 실제 결제를 진행하도록 구현합니다.
  // purchase 오브젝트는 name, productId, quantity, campaignId, contentId 프로퍼티를 담고 있습니다.
  // 결제가 완료된 이후 trackPurchaseEvent:revenueAmount:currency:purchase: 메소드를 사용해
  // 결제 이벤트를 전송하면 매출 리포트가 집계됩니다.
}
```

#### - (void)didRequestReward:placement:
Reward 타입의 인터스티셜 광고가 노출될 때 발생합니다.

```objective-c
- (void)didRequestReward:(NSArray *)rewards placement:(NSString *)placement
{
  // rewards 배열에는 해당 광고를 통해 사용자에게 지급하고자 하는 리워드 오브젝트들이 담겨있습니다.
  // 이 정보들을 가지고 사용자에게 리워드를 지급하는 코드를 구현합니다.
  [rewards enumerateObjectsUsingBlock:^(VPReward *reward, NSUInteger idx, BOOL *stop) {
    // 지급할 리워드 아이템의 이름과 수량.
    NSLog(@"name: %@, quantity: %d", reward.name, (int)reward.quantity);
  }];
}
```
