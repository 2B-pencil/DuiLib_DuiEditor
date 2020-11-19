// dllmain.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>

#include "Include/DuiPlugins.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE DuiPluginsDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DuiPlugins.DLL ���ڳ�ʼ��!\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(DuiPluginsDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL (�� ActiveX �ؼ�)��ʽ���ӵ���
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(DuiPluginsDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DuiPlugins.DLL ������ֹ!\n");

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(DuiPluginsDLL);
	}
	return 1;   // ȷ��
}

UILIB_PLUGIN_API void DuiPluginsRegister()
{
	REGIST_DUICONTROL(CGridCtrlUI);
	REGIST_DUICONTROL(CMsgWndUI);
	REGIST_DUICONTROL(CKeyBoardUI);
	REGIST_DUICONTROL(CKeyBoardNumberUI);
	REGIST_DUICONTROL(CKeyBoardSimpleUI);
	REGIST_DUICONTROL(CImageBoxUI);
	REGIST_DUICONTROL(CPictureControlUI);
	REGIST_DUICONTROL(CComboExUI);
	REGIST_DUICONTROL(CIconButtonUI);
	REGIST_DUICONTROL(CDateTimeExUI);
	REGIST_DUICONTROL(CAccordionPaneUI);
	REGIST_DUICONTROL(CAnimationPaneUI);
	REGIST_DUICONTROL(CImageBoxExUI);
	REGIST_DUICONTROL(CRollTextExUI);
}

extern "C" UILIB_PLUGIN_API CControlUI *CreateControl(LPCTSTR pstrClass)
{
	if( _tcscmp(pstrClass, _T("GridCtrl")) == 0 ) 
	{
		return new CGridCtrlUI;
	}
	else if( _tcscmp(pstrClass, _T("MsgWnd")) == 0 ) 
	{
		return new CMsgWndUI;
	}
	else if( _tcscmp(pstrClass, _T("KeyBoard")) == 0 ) 
	{
		return new CKeyBoardUI;
	}
	else if( _tcscmp(pstrClass, _T("KeyBoardNumber")) == 0 ) 
	{
		return new CKeyBoardNumberUI;
	}
	else if( _tcscmp(pstrClass, _T("KeyBoardSimple")) == 0 ) 
	{
		return new CKeyBoardSimpleUI;
	}
	else if( _tcscmp(pstrClass, _T("ImageBox")) == 0 ) 
	{
		return new CImageBoxUI;
	}
	else if( _tcscmp(pstrClass, _T("PictureControl")) == 0 ) 
	{
		return new CPictureControlUI;
	}
	else if( _tcscmp(pstrClass, _T("ComboEx")) == 0 ) 
	{
		return new CComboExUI;
	}
	else if( _tcscmp(pstrClass, _T("IconButton")) == 0 ) 
	{
		return new CIconButtonUI;
	}
	else if( _tcscmp(pstrClass, _T("DateTimeEx")) == 0 ) 
	{
		return new CDateTimeExUI;
	}
	else if( _tcscmp(pstrClass, _T("AccordionPane")) == 0 ) 
	{
		return new CAccordionPaneUI;
	}
	else if( _tcscmp(pstrClass, _T("AnimationPane")) == 0 ) 
	{
		return new CAnimationPaneUI;
	}
	else if( _tcscmp(pstrClass, _T("ImageBoxEx")) == 0 ) 
	{
		return new CImageBoxExUI;
	}
	else if( _tcscmp(pstrClass, _T("RollTextEx")) == 0 ) 
	{
		return new CRollTextExUI;
	}
	return NULL;
}

UILIB_PLUGIN_API void InsertMsgUI(LPCTSTR pstring, COLORREF cr)
{
	CMsgWndUI::InsertMsg(pstring, cr);
}

UILIB_PLUGIN_API void InsertMsgUiV(LPCTSTR lpszFormat, ...)
{
	ASSERT(AfxIsValidString(lpszFormat));

	CString strText;

	va_list argList;
	va_start(argList, lpszFormat);
	strText.FormatV(lpszFormat, argList);
	va_end(argList);

	CMsgWndUI::InsertMsg(strText, RGB(0,0,0));
}