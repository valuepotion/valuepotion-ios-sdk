Pod::Spec.new do |s|
  s.name     = 'ValuePotion'
  s.version  = '1.2.0'
  s.summary  = 'ValuePotion Library for analysis and ad networking.'
  s.homepage = 'https://developers.valuepotion.com'
  s.requires_arc = true
  s.authors  = {'ValuePotion' => 'dev.support@valuepotion.com' }
  s.license  = {
    :type => 'Copyright',
    :text => 'Copyright to ValuePotion 2015. All right reserved.'
  }
  
  s.platform = :ios, "6.0"
  s.module_name = "ValuePotion"

  puts "version: #{s.version}"
  s.preserve_paths = 'SDK/Frameworks/*.framework'
  s.source = { :git => "https://github.com/valuepotion/valuepotion-ios-sdk.git" }

  s.default_subspec = 'Core'

  s.subspec 'Core' do |core|
    core.vendored_frameworks = "SDK/Frameworks/ValuePotion.framework"
    core.resource = "SDK/Frameworks/ValuePotion.framework/ValuePotion.bundle"

    core.frameworks = 'UIKit', 'Foundation', 'CoreGraphics', 'SystemConfiguration', 'CoreTelephony', 'AdSupport', 'MediaPlayer'
    core.weak_frameworks = 'AVFoundation'
  end

  s.subspec 'AdxSupport' do |adx|
    adx.dependency "ValuePotion/Core"
    adx.platform = :ios, "6.0"
    adx.vendored_frameworks = "SDK/Frameworks/ValuePotionAdxSupport.framework"

    adx.frameworks = "GoogleMobileAds"
  end

  s.subspec 'FacebookSupport' do |fb|
    fb.dependency "ValuePotion/Core"
    fb.platform = :ios, "7.0"
    fb.vendored_frameworks = "SDK/Frameworks/ValuePotionFacebookSupport.framework"

    fb.frameworks = "Bolts", "FBSDKCoreKit"
  end

  s.subspec 'AdColonySupport' do |adc|
    adc.dependency "ValuePotion/Core"
    adc.platform = :ios, "6.0"
    adc.vendored_frameworks = "SDK/Frameworks/ValuePotionAdColonySupport.framework"

    adc.libraries = "z.1"
    adc.frameworks = "AdColony", "EventKit", "EventKitUI", "MessageUI", "AudioToolbox", "CoreMedia"
    adc.weak_frameworks = "Social", "StoreKit", "WebKit"
  end
end

