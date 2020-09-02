
// DuiEditor.h : DuiEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "DuiPropertyFile.h"
#include "DuiEditorCommandHistory.h"
#include "EditorConfig.h"

#include "DuiProject.h"
extern CDuiProject g_proj;

extern CString g_strAppPath;							//Ӧ�ó���·��
extern CDuiPropertyFile g_duiProp;

inline BOOL CompareString(LPCTSTR str1, LPCTSTR str2)
{
	return _tcscmp(str1, str2) == 0;
}

inline BOOL SplitCString(CStringArray &arrstr, LPCTSTR strtemp)
{
	CString str(strtemp);

	CString temp;
	for (int i=0; i<str.GetLength(); i++)
	{
		if(_istalnum(str[i]))
			temp += str[i];
		else
		{
			if(!temp.IsEmpty()) 
			{
				arrstr.Add(temp);
				temp.Empty();
			}
		}
	}

	if(!temp.IsEmpty())
	{
		arrstr.Add(temp);
	}

	return TRUE;
}

inline CString RectToString(LPRECT rc)
{
	CString temp;
	temp.Format(_T("%d,%d,%d,%d"), rc->left, rc->top, rc->right, rc->bottom);
	return temp;
}

extern HWND g_hWndMsg;
#define WM_INSERT_MSG		WM_USER + 345
inline void InsertMsg(LPCTSTR strLog)
{
	if(::IsWindow(g_hWndMsg))
	{
		::SendMessage(g_hWndMsg, WM_INSERT_MSG, (WPARAM)strLog, 0);
	}
}

#define WM_REOPEN_FILE			WM_USER + 221
#define WM_INIT_VIEW_DESIGN		WM_USER + 222
// CDuiEditorApp:
// �йش����ʵ�֣������ DuiEditor.cpp
//

class CDuiEditorApp : public CWinAppEx
{
public:
	CDuiEditorApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	void LoadStdProfileSettings(UINT nMaxMRU);
	afx_msg void OnUpdateRecentFileMenu(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNewXml();
	afx_msg void OnFileNewXmlFromTemplate();
	afx_msg void OnFileNewAsScript();
};

extern CDuiEditorApp theApp;
