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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditClear();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
};


