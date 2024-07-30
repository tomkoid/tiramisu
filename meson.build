project('tiramisu', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

boost_dep = dependency('boost', modules : ['filesystem'])
raylib_dep = dependency('raylib')

src = [
  'src/main.cpp',
  'src/collision.cpp',
  'src/textures.cpp',
  'src/ui.cpp',
  'src/utils.cpp',
  'src/controls/volume.cpp',
  'src/ui/center_directions.cpp',
  'src/ui/acceleration.cpp',
  'src/ui/bounces.cpp',
  'src/ui/volume.cpp',
]

exe = executable('tiramisu', src,
  dependencies : [boost_dep, raylib_dep],
  install : true)

test('basic', exe)
