#pragma once
#include "RegCControlUI.h"

namespace DuiLib
{

static CControlUI *CPaintManagerUI_FindControl(const CDuiString &sName, CPaintManagerUI &Obj)
{
	return Obj.FindControl(sName);
}

static void CControlUI_SetText(const CDuiString &str, CPaintManagerUI &obj)
{
	
}

class regCPaintManagerUI
{
protected:
	//DECL_FACTORY(CPaintManagerUI);
	static CPaintManagerUI *CPaintManagerUI_Ref_Factory() { return new DuiLibPaintManagerUI(); }
public:
	static bool Register_Prepare(asIScriptEngine *engine)
	{
		CDuiStringA classname = "CPaintManagerUI";

		int r = 0;
		r = engine->RegisterObjectType(classname, 0, asOBJ_REF|asOBJ_NOCOUNT); 
		REG_FACTORY(CPaintManagerUI);

		return r>=0;
	}

	static void Register_Extra(asIScriptEngine *engine)
	{
		CDuiStringA classname = "CPaintManagerUI";
		int r = 0;
		REG_METHOD_FUNPR(CPaintManagerUI, CControlUI*, GetRoot, () const);
		REG_METHOD_FUNPR(CPaintManagerUI, CControlUI*, FindControl, (LPCTSTR pstrName) const);
		REG_METHOD_FUNPR(CPaintManagerUI, UIWND, GetPaintWindow, () const);

		//r = engine->RegisterObjectMethod("CPaintManagerUI", "CControlUI *FindControl(const string &sName)", asFUNCTIONPR(CPaintManagerUI_FindControl, (const CDuiString &, CPaintManagerUI *), CControlUI *), asCALL_CDECL_OBJLAST); assert( r >= 0 );
		//r = engine->RegisterObjectMethod("CPaintManagerUI", "CControlUI *FindControl(const string &sName)", asFUNCTION(CPaintManagerUI_FindControl), asCALL_CDECL_OBJLAST); assert( r >= 0 );
		
		//r = engine->RegisterObjectMethod("CPaintManagerUI", "void SetText(const string &in)", asFUNCTIONPR(CControlUI_SetText, (const CDuiString &, CPaintManagerUI &), void), asCALL_CDECL_OBJLAST);  assert( r >= 0 );
	}
};

} //namespace DuiLib
