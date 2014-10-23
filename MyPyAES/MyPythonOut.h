/********************************************************************
	created:	2014/10/22
	filename: 	MyPythonOut.h
	author:		底会雷
	purpose:	
*********************************************************************/

/***
Extending and Embedding the Python Interpreter：http://www.fnal.gov/docs/products/python/v1_5_2/ext/
PyArg_ParseTuple: http://www.fnal.gov/docs/products/python/v1_5_2/ext/parseTuple.html
Py_BuildValue: http://blog.chinaunix.net/uid-22920230-id-3443571.html
***/

#pragma once

#include <python.h>

#pragma comment(lib, "python27.lib")

#include "AES/Numbers.h"
#include "AES/AES.h"

void PyDelNumber(void *ptr)
{
	Numbers *pNum = static_cast<Numbers*>(ptr);
	delete pNum;
	return;
}

PyObject* newNumber(PyObject *self, PyObject *args)
{
	int first;
	double second;
	if (!PyArg_ParseTuple(args, "id", &first, &second))
		return NULL;
	Numbers *pNumber = new Numbers(first, second);

	// 把指针pNumber包装成PyCObject对象，并返回给解释器
	return PyCObject_FromVoidPtr(pNumber, PyDelNumber);
}

PyObject* numberMult(PyObject *self, PyObject *args)
{
	PyObject *pyNumber = 0;
	if (!PyArg_ParseTuple(args, "O", &pyNumber))
		return NULL;

	// 把PyCObject转换为void指针
	void *pTmp = PyCObject_AsVoidPtr(pyNumber);

	// 把void指针转换为一个Numbers对象指针
	Numbers *pNumber = static_cast<Numbers*>(pTmp);

	double result = pNumber->memberMult();

	return Py_BuildValue("d", result);
}

void PyDelAESObject(void *ptr)
{
	AES *pAES = static_cast<AES*>(ptr);
	delete pAES;
	return;
}
// 生成AES对象
PyObject* newAES(PyObject *self, PyObject *args)
{
	unsigned char *key;
	if (!PyArg_ParseTuple(args, "s", &key))
		return NULL;

	AES *pAES = new AES(key);
	// 把指针pAES包装成PyCObject对象，并返回给解释器
	return PyCObject_FromVoidPtr(pAES, PyDelAESObject);
}
// 重设密码key
PyObject* resetKey(PyObject *self, PyObject *args)
{
	PyObject *pyAES = 0;
	unsigned char *key = NULL;
	if (!PyArg_ParseTuple(args, "Os", &pyAES, &key))
		return NULL;
	// 把PyObject对象转换为void指针
	void *pTmp = PyCObject_AsVoidPtr(pyAES);
	AES *pASE = static_cast<AES*>(pTmp);
	pASE->resetKey(key);
	return Py_BuildValue("s", key);
}
// 加密
// 参数列表：AES对象，字符串
// 返回值：加密后的字符串
PyObject* encode(PyObject *self, PyObject *args)
{
	PyObject *pyAES = 0;
	char *buf = NULL;
	int length = 0;
//	if (!PyArg_ParseTuple(args, "Osi", &pyAES, &buf, &length))
	if (!PyArg_ParseTuple(args, "Os#", &pyAES, &buf, &length))
		return NULL;
	void *pTmp = PyCObject_AsVoidPtr(pyAES);
	AES *pAES = static_cast<AES*>(pTmp);
	pAES->encode(buf, length);
	return Py_BuildValue("s#", buf, length);
}
// 解密
// 参数列表：AES对象，解密字符串
// 返回值：解密后的字符串
PyObject* decode(PyObject *self, PyObject *args)
{
	PyObject *pyAES = 0;
	char *buf = NULL;
	int length = 0;
	int orgLength = 0;
	if (!PyArg_ParseTuple(args, "Os#", &pyAES, &buf, &length))
		return NULL;
	void *pTmp = PyCObject_AsVoidPtr(pyAES);
	AES *pAES = static_cast<AES*>(pTmp);
	pAES->decode(buf, length);
	return Py_BuildValue("s#", buf, length);
}

PyObject* testBuff(PyObject *self, PyObject *args)
{
	void *buf = NULL;
	int length = 0;
	if (!PyArg_ParseTuple(args, "s#", &buf, &length))
		return NULL;
	return Py_BuildValue("s#", buf, length);
}

