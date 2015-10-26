require 'mkmf'
require 'pry-byebug'

header_dirs = [
  # First search /opt/local for macports
  '/opt/local/include',

  # Then search /usr/local for people that installed from source
  '/usr/local/include',

  # Finally fall back to /usr
  '/usr/include',
]

lib_dirs = [
  # First search /opt/local for macports
  '/opt/local/lib',

  # Then search /usr/local for people that installed from source
  '/usr/local/lib',

  # Finally fall back to /usr
  '/usr/lib',
]

dir_config('ffts', header_dirs, lib_dirs)

unless find_header('ffts/ffts.h')
  abort "FFTS is missing. Please install FFTS."
end

unless find_library('ffts', 'ffts_free', *lib_dirs)
  abort "FFTS library cannot be found. Please install FFTS."
end

create_makefile 'ffts/ffts'
