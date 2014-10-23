#coding: utf-8
#__author__ = 'gydihl'

from MyAESObject import *

myAES = MyAESObject('1234567980abcdef')
fileOrg = open(r'D:\gameloading.json', 'rb')
fileEncode = open(r'D:\gameloading_1.json', 'wb+')
fileDecode = open(r'D:\gameloading_1_1.json', 'wb+')

try:
    chunk = fileOrg.read()

    chunkEncode = myAES.encode(chunk)
    fileEncode.write(chunkEncode)

    chunkDecode = myAES.decode(chunkEncode)
    fileDecode.write(chunkDecode)
finally:
    fileOrg.close()
    fileEncode.close()
    fileDecode.close()


