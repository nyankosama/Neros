srcDir = './src'
dataDir = srcDir+'/ds'

StaticLibrary(target = 'datastructure',
        source = Glob(dataDir+'/*.cpp'),
        CPPPATH = dataDir)

libs = Split('datastructure')
libpath = './'

Program(target = 'Neros',
        source = srcDir+'/Main.cpp',
        LIBS=libs,
        LIBPATH=libpath,
        CPPPATH=dataDir)
