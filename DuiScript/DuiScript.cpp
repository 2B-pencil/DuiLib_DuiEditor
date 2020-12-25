// DuiScript.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#include "ScriptEngine.h"

//////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) IScriptEngine* __stdcall CreateScriptEngine()
{
	return new CScriptEngine;
}

extern "C" __declspec(dllexport) void __stdcall DeleteScriptEngine(IScriptEngine *pEngine)
{
	if(pEngine)
	{
		delete (CScriptEngine *)pEngine;
		pEngine = NULL;
	}
}