srcDir = './src'
dataDir = srcDir+'/base'

env = Environment(CCFLAGS='-std=c++0x')

env.StaticLibrary(target = 'datastructure',
        source = Glob(dataDir+'/*.cpp'),
        CPPPATH = dataDir)

libs = Split('datastructure')
libpath = './'

env.Program(target = 'Neros',
        source = srcDir+'/main.cpp',
        LIBS=libs,
        LIBPATH=libpath,
        CPPPATH=dataDir)
