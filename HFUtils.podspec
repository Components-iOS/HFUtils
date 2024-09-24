#
# Be sure to run `pod lib lint HFUtils.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'HFUtils'
  s.version          = '0.1.3'
  s.summary          = '工具类'
  s.description      = <<-DESC
常用工具
                       DESC

  s.homepage         = 'https://github.com/Components-iOS'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'liuhongfei' => 'hongfei_liu@bizconf.cn' }
  s.source           = { :git => 'https://github.com/Components-iOS/HFUtils.git', :tag => s.version.to_s }
  s.ios.deployment_target = '12.0'
  
  s.resource_bundles = {
      'HFUtils' => ['HFUtils/Assets/*']
  }

  s.source_files = 'HFUtils/Classes/*.{h}'
  
  s.subspec 'Window' do |window|
      window.source_files = 'HFUtils/Classes/Window/**/*'
  end
  
  s.subspec 'UserDefaults' do |user|
      user.source_files = 'HFUtils/Classes/UserDefaults/**/*'
  end
  
  s.subspec 'HUD' do |hud|
      hud.source_files = 'HFUtils/Classes/HUD/**/*'
      hud.dependency 'HFUtils/Window'
  end
  
  s.subspec 'AlertView' do |alert|
      alert.source_files = 'HFUtils/Classes/AlertView/**/*'
      alert.dependency 'HFUtils/Window'
  end
end
