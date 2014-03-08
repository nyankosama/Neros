srcDir = './src'
dataDir = srcDir+'/base'

env = Environment(CCFLAGS='-std=c++0x -g')

env.StaticLibrary(target = 'datastructure',
        source = Glob(dataDir+'/*.cpp'),
        CPPPATH = srcDir)

libs = Split('datastructure')
libpath = './'

env.Program(target = 'lightdis',
        source = srcDir+'/main.cpp',
        LIBS=libs,
        LIBPATH=libpath,
        CPPPATH=srcDir)

env.Program(target = "unittest",
        source = srcDir+'/unittest/unittest_example.cpp',
        LIBS=libs,
        LIBPATH=libpath,
        CPPPATH=srcDir)
