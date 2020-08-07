Pod::Spec.new do |s|
  s.name                    = 'KarteCocos2dx'
  s.version                 = '0.1.0'
  s.summary                 = 'KARTE Cocos2d-x SDK'
  s.homepage                = 'https://karte.io'
  s.author                  = { 'PLAID' => 'dev.share@plaid.co.jp' }
  s.social_media_url        = 'https://twitter.com/karte_io'
  s.documentation_url       = 'https://developers.karte.io/docs/cocos2dx-sdk'
  s.license                 = { :type => 'Apache', :file => 'LICENSE' }

  s.cocoapods_version       = '>= 1.7.0'
  s.swift_versions          = [5.1]
  s.static_framework        = true

  s.platform                = :ios
  s.ios.deployment_target   = '9.0'
  
  s.source                  = { :git => 'https://github.com/plaidev/karte-cocos2dx.git', :tag => "v#{s.version}" }
  s.source_files            = 'sample/Cocos2dxSample/KarteBridges/**/*.{swift,h,m,mm,cpp}'
  s.exclude_files           = 'sample/Cocos2dxSample/KarteBridges/android/**/*.{h,cpp}'
  
  s.requires_arc            = true
  s.libraries = 'c++'
  s.pod_target_xcconfig = {
    'GCC_PREPROCESSOR_DEFINITIONS' => 'KRTCOCOS_VERSION=' + s.version.to_s,
    'CLANG_CXX_LANGUAGE_STANDARD' => 'c++11',
    'CLANG_CXX_LIBRARY' => 'libc++'
  }

  s.frameworks = 'WebKit','GameController','MediaPlayer'

  s.dependency 'KarteCore', '~> 2.6.0'
  s.dependency 'KarteInAppMessaging', '~> 2.5.0'
  s.dependency 'KarteVariables', '~> 2.1.0'  
  s.dependency 'KarteRemoteNotification', '~> 2.2.0'
  s.dependency 'KarteCrashReporting', '~> 2.2.0'
end
