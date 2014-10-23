#coding: utf-8
#__author__ = 'gydihl'

import MyPyAES

class MyAESObject(object):
    def __init__(self, key):
        self._key = key
        self._aes = MyPyAES.newAES(key)

    def getKey(self):
        return self._key

    def resetKey(self, key):
        self._key = key
        MyPyAES.resetKey(self._aes, key)

    def encode(self, buff):
        length = 16
        count = len(buff)
        add = (length-(count % length))
        buff = buff + ('\0' * add)
        return MyPyAES.encode(self._aes, buff)

    def decode(self, buff):
        decode = MyPyAES.decode(self._aes, buff)
        return  decode.rstrip('\0')

