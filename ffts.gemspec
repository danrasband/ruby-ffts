require './lib/ffts/version'

Gem::Specification.new do |s|
  s.name        = 'ffts'
  s.version     = FFTS::VERSION
  s.summary     = 'FFTS'
  s.description = 'A native extension for the FFTS library.'
  s.authors     = ['Dan Rasband']
  s.email       = 'danrasband@gmail.com'
  s.homepage    = 'https://github.com/danrasband/ruby-ffts'
  s.license     = 'MIT'

  s.files  = `git ls-files`.split("\n") rescue []
  s.files &= (
    Dir['lib/**/*.rb'] +
    Dir['ext/**/*.{h,c,rb,yml}'] +
    Dir['*.md'])

  s.extensions = %w[ext/ffts/extconf.rb]

  s.add_development_dependency 'rake-compiler', '~> 0.9.0'
  s.add_development_dependency 'pry-byebug', '~> 3.2'
end
