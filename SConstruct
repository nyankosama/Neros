import os
import buildUtil as util

srcDir = './src'
dataDir = srcDir+'/base'
testDir = srcDir + '/test'

env = Environment(CCFLAGS='-std=c++0x -g')

env.StaticLibrary(target = 'datastructure',
        source = Glob(dataDir+'/*.cpp'),
        CPPPATH = srcDir)

libs = Split('datastructure')
libpath = './'

binCom = env.Program(target = 'lightdis',
        source = srcDir+'/main.cpp',
        LIBS=libs,
        LIBPATH=libpath,
        CPPPATH=srcDir)

testCom = env.Program(target = "unittest",
        source = srcDir+'/unittest/unittest_example.cpp',
        LIBS=libs,
        LIBPATH=libpath,
        CPPPATH=srcDir)

den = Depends(testCom, binCom)

#build and run the unittest cases
testSrcList = os.listdir(testDir)
testList = list()
for fileName in testSrcList:
    if util.isCppFile(fileName) is not True:
        continue

    testTarget = env.Program(target = testDir + os.path.sep + "_TEST__" + fileName[: fileName.index(".cpp")],
            source = testDir + os.path.sep + fileName,
            LIBS=libs,
            LIBPATH=libpath,
            CPPPATH=srcDir)
    testList.append(testTarget)

def runTest(target, source, env):
    testList = os.listdir(testDir)
    for fileName in testList:
        if util.isTestFile(fileName) == True:
            os.system(testDir + os.path.sep + fileName)

test = Command('test', [], runTest)
Depends(test, testCom)
