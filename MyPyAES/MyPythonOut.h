/********************************************************************
	created:	2014/10/22
	filename: 	MyPythonOut.h
	author:		�׻���
	purpose:	
*********************************************************************/

/***
Extending and Embedding the Python Interpreter��http://www.fnal.gov/docs/products/python/v1_5_2/ext/
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

	// ��ָ��pNumber��װ��PyCObject���󣬲����ظ�������
	return PyCObject_FromVoidPtr(pNumber, PyDelNumber);
}

PyObject* numberMult(PyObject *self, PyObject *args)
{
	PyObject *pyNumber = 0;
	if (!PyArg_ParseTuple(args, "O", &pyNumber))
		return NULL;

	// ��PyCObjectת��Ϊvoidָ��
	void *pTmp = PyCObject_AsVoidPtr(pyNumber);

	// ��voidָ��ת��Ϊһ��Numbers����ָ��
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
// ����AES����
PyObject* newAES(PyObject *self, PyObject *args)
{
	unsigned char *key;
	if (!PyArg_ParseTuple(args, "s", &key))
		return NULL;

	AES *pAES = new AES(key);
	// ��ָ��pAES��װ��PyCObject���󣬲����ظ�������
	return PyCObject_FromVoidPtr(pAES, PyDelAESObject);
}
// ��������key
PyObject* resetKey(PyObject *self, PyObject *args)
{
	PyObject *pyAES = 0;
	unsigned char *key = NULL;
	if (!PyArg_ParseTuple(args, "Os", &pyAES, &key))
		return NULL;
	// ��PyObject����ת��Ϊvoidָ��
	void *pTmp = PyCObject_AsVoidPtr(pyAES);
	AES *pASE = static_cast<AES*>(pTmp);
	pASE->resetKey(key);
	return Py_BuildValue("s", key);
}
// ����
// �����б�AES�����ַ���
// ����ֵ�����ܺ���ַ���
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
// ����
// �����б�AES���󣬽����ַ���
// ����ֵ�����ܺ���ַ���
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

