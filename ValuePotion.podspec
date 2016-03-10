Pod::Spec.new do |s|
  s.name     = 'ValuePotion'
  s.version  = '1.1.15'
  s.summary  = 'ValuePotion Library for analysis and ad networking.'
  s.homepage = 'https://developers.valuepotion.com'
  s.requires_arc = true
  s.authors  = {'ValuePotion' => 'support@valuepotion.com' }
  s.license  = {
    :type => 'Copyright',
    :text => 'Copyright to ValuePotion 2015. All right reserved.'
  }
  
  s.platform = :ios, "6.0"

  s.source_files = "SDK/*.h"
  s.public_header_files = "SDK/*.h"
  s.vendored_libraries = "SDK/*.a"
  s.module_name = "ValuePotion"

  s.frameworks = 'UIKit', 'Foundation', 'CoreGraphics', 'SystemConfiguration', 'CoreTelephony', 'AdSupport'
  s.weak_frameworks = 'AVFoundation'

  s.source = { :git => "https://github.com/valuepotion/valuepotion-ios-sdk.git", :tag => s.version }
end

