
def isCppFile(fileName):
    try:
        fileName.index(".cpp")
    except Exception, e:
        return False

    return True

def isTestFile(fileName):
    try:
        fileName.index("_TEST__")
    except Exception, e:
        return False

    return True
