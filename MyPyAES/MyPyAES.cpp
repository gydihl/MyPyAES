// MyPyAES.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <python.h>

#pragma comment(lib, "python27.lib")

#include "MyPythonOut.h"

static PyMethodDef AESMethods[] = {
	{"newNumber", newNumber, METH_VARARGS},
	{"numberMult", numberMult, METH_VARARGS},
	// �����ַ�����
	{"testBuff", testBuff, METH_VARARGS},
	// ����AES����
	{"newAES", newAES, METH_VARARGS},
	// ��������key
	{"resetKey", resetKey, METH_VARARGS},
	// ����
	{"encode", encode, METH_VARARGS},
	// ����
	{"decode", decode, METH_VARARGS},
	{NULL, NULL, NULL}
};

PyMODINIT_FUNC initMyPyAES()
{
	Py_InitModule("MyPyAES", AESMethods);
}
