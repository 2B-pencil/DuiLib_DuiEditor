#pragma once

#include "ScriptEditorDoc.h"
// CScriptEditorView ��ͼ

class CScriptEditorView : public CView
{
	DECLARE_DYNCREATE(CScriptEditorView)

protected:
	CScriptEditorView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CScriptEditorView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ

public:
	CScriptEditorDoc* GetDocument() const
	{ return reinterpret_cast<CScriptEditorDoc*>(m_pDocument); }

	void InitLexer();

	CSciWnd sci;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnInitialUpdate();
};


