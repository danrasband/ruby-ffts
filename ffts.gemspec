Gem::Specification.new do |s|
  s.name        = 'ffts'
  s.version     = '0.0.0'
  s.date        = '2015-10-25'
  s.summary     = 'FFTS'
  s.description = 'A native extension for the FFTS library.'
  s.authors     = ['Dan Rasband']
  s.email       = 'danrasband@gmail.com'
  s.files       = ['lib/ffts.rb']
  s.homepage    = 'https://github.com/danrasband/ruby-ffts'
  s.license     = 'MIT'

  s.add_development_dependency 'rake-compile'
end
