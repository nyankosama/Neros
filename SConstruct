srcDir = './src'
dataDir = srcDir+'/data'

SharedLibrary(target = 'lib/datastructure',
        source = Glob(dataDir+'/*.cpp'),
        CPPPATH = dataDir)

libs = Split('datastructure')
libpath = './lib'

Program(target = 'Neros',
        source = srcDir+'/Main.cpp',
        LIBS=libs,
        LIBPATH=libpath,
        CPPPATH=dataDir)
