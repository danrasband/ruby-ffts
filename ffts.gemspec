Gem::Specification.new do |s|
  s.name        = 'ffts'
  s.version     = '0.0.0'
  s.date        = '2015-10-25'
  s.summary     = 'FFTS'
  s.description = 'A native extension for the FFTS library.'
  s.authors     = ['Dan Rasband']
  s.email       = 'danrasband@gmail.com'
  s.homepage    = 'https://github.com/danrasband/ruby-ffts'
  s.license     = 'MIT'

  files  = `git ls-files`.split("\n") rescue []
  files &= (
    Dir['lib/**/*.rb'] +
    Dir['ext/**/*.{h,c,rb,yml}'] +
    Dir['*.md'])

  s.add_development_dependency 'rake-compiler', '~> 0.9.0'
end
