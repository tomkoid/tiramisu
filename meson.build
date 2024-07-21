project('tiramisu', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

x11_dep = dependency('x11')
xrandr_dep = dependency('xrandr')
boost_dep = dependency('boost', modules : ['filesystem'])
raylib_dep = dependency('raylib')

src = [
  'main.cpp',
  'framerate.cpp',
  'collision.cpp',
  'textures.cpp',
  'ui.cpp',
  'utils.cpp',
]

exe = executable('tiramisu', src,
  dependencies : [x11_dep, xrandr_dep, boost_dep, raylib_dep],
  install : true)

test('basic', exe)
