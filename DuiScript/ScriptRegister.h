#pragma once

//ע����ֿؼ�
class CScriptRegister
{
public:
	CScriptRegister(asIScriptEngine *engine);
	~CScriptRegister();

	void RegisterAll();

private:
	asIScriptEngine *engine;
};

