project('m0dular-framework', 'cpp', 'c', default_options : ['c_std=c11', 'cpp_std=c++17', 'b_ndebug=if-release'])
compile_args = ['-DMAX_PLAYERS=64', '-DMAX_BONES=128', '-DBACKTRACK_TICKS=64', '-DRESOLVEBASECOUNT=7', '-DMULTIPOINT_COUNT=8', '-DNUM_THREADS=4', '-Werror', '-Wno-unused-command-line-argument', '-Wno-non-virtual-dtor', '-Wno-strict-aliasing']
linker_args = compile_args

if not get_option('buildtype').startswith('debug')
	compile_args += ['-Ofast', '-msse4.2']
	linker_args += ['-flto', '-O0']
else
  compile_args += ['-g', '-O0', '-fsanitize=address']
  linker_args += ['-lasan']
endif

includes = []
libraries = []
deps = []

cc = meson.get_compiler('cpp')

if host_machine.system() == 'linux'
  linker_args += '-ldl'
endif

thread_dep = dependency('threads')

mfix = executable('movefix_test', files(['tests/movefix.cpp']), cpp_args : compile_args, link_args : linker_args, dependencies : thread_dep)

test('movement fix', mfix)
