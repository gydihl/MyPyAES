// MyPyAES.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <python.h>

#pragma comment(lib, "python27.lib")

#include "MyPythonOut.h"

static PyMethodDef AESMethods[] = {
	{"newNumber", newNumber, METH_VARARGS},
	{"numberMult", numberMult, METH_VARARGS},
	// 测试字符传递
	{"testBuff", testBuff, METH_VARARGS},
	// 生成AES对象
	{"newAES", newAES, METH_VARARGS},
	// 重设密码key
	{"resetKey", resetKey, METH_VARARGS},
	// 加密
	{"encode", encode, METH_VARARGS},
	// 解密
	{"decode", decode, METH_VARARGS},
	{NULL, NULL, NULL}
};

PyMODINIT_FUNC initMyPyAES()
{
	Py_InitModule("MyPyAES", AESMethods);
}
