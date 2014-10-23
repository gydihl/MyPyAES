#coding: utf-8
#__author__ = 'gydihl'

# 警告：原文件目录不要和加密后文件目录一样，否则文件将丢失

# 工作原理：
# 删除目的文件目录下的文件
# 复制原文件目录至目的文件目录
# 加密目的文件目录下的文件

import os
import time
import os.path
import shutil
from MyAESObject import *

# 原文件目录
SOURCE_DIR = ur'Resources'
# 目的文件目录
PURPOSE_DIR = ur'ResourcesEncode'

AES_KEY     = r'1234567980abcdef'

copyFileCounts = 0
ENCODE_COUNT    = 0

## 当前时间
def curTime():
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))

## 删除目录下的文件以及文件夹
def removeFileDir(targetDir):
    if os.path.isdir(targetDir):
        for file in os.listdir(targetDir):
            filePath = os.path.join(targetDir, file)
            if os.path.isfile(filePath):
                os.remove(filePath)
                print(filePath+'removed!')
            elif os.path.isdir(filePath):
                shutil.rmtree(filePath, True)
                print('dir: '+filePath+'removed!')


def copyFiles(sourceDir, targetDir):
    global copyFileCounts
    global pngFileCounts
    if sourceDir.find('.svn') > 0:
        return
    print ur'%s: 当前处理文件夹%s已处理%d个文件'%(curTime(), sourceDir, copyFileCounts)
    for file in os.listdir(sourceDir):
        sourceFile = os.path.join(sourceDir, file)
        targetFile = os.path.join(targetDir, file)
        if os.path.isfile(sourceFile):
            ## 创建目录
            if not os.path.exists(targetDir):
                os.makedirs(targetDir)
            copyFileCounts += 1
            ## 文件不存在，或者大小不同则覆盖
            if not os.path.exists(targetFile) or \
                (os.path.getsize(targetFile) != os.path.getsize(sourceFile)):
                ## open(targetFile, 'wb').write(open(sourceFile, 'rb').read())
                shutil.copy(sourceFile, targetFile)
                print ur'%s: %s复制完毕'%(curTime(), targetFile)
            else:
                print ur'%s: %s已存在，不重复复制'%(curTime(), targetFile)
        elif os.path.isdir(sourceFile):
            copyFiles(sourceFile, targetFile)

def AESEncode(dir, aes):
    global ENCODE_COUNT
    if not os.path.isdir(dir):
        return
    for file in os.listdir(dir):
        fileName = os.path.join(dir, file)
        if os.path.isfile(fileName):
            f = open(fileName, 'rb')
            try:
                buff = f.read()
                encode = aes.encode(buff)
            finally:
                f.close()
            f = open(fileName, 'wb')
            try:
                f.write(encode)
            finally:
                f.close()
            ENCODE_COUNT += 1
            print(ur'%s: %s加密完成'%(curTime(), fileName))
            print(ur'加密完成百分比：%.3f%%'%(ENCODE_COUNT*100.0/copyFileCounts))
        elif os.path.isdir(fileName):
            AESEncode(fileName, aes)

def AESDecode(dir, aes):
    if not os.path.isdir(dir):
        return
    for file in os.listdir(dir):
        fileName = os.path.join(dir, file)
        if os.path.isfile(fileName):
            f = open(fileName, 'rb')
            try:
                buff = f.read()
                decode = aes.decode(buff)
            finally:
                f.close()
            f = open(fileName, 'wb')
            try:
                f.write(decode)
            finally:
                f.close()
        elif os.path.isdir(fileName):
            AESDecode(fileName, aes)

if '__main__' == __name__:
    # 删除目的目录下的文件
    removeFileDir(PURPOSE_DIR)
    # 复制文件
    copyFiles(SOURCE_DIR, PURPOSE_DIR)
    # 加密文件
    myAES = MyAESObject(AES_KEY)
    AESEncode(PURPOSE_DIR, myAES)
    print(ur'加密完成')
#    AESDecode(PURPOSE_DIR, myAES)
#    print(ur'解密完成')
    os.system('pause')


