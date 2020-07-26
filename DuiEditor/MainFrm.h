
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "DockFileViewWnd.h"
#include "DockControlTreeWnd.h"
#include "DockPropertyWnd.h"
#include "DockOutputWnd.h"
#include "DockXmlWnd.h"
#include "ToolBoxWnd.h"

#include "DuiEditorViewDesign.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:
	UINT_PTR m_uTimerReOpenFile;
	CString m_strReOpenFile;
	CDuiEditorDoc *m_pDocReOpen;
// ����
public:
	CDuiEditorViewDesign *GetActiveUIView();

	void ShowAllPane();
	void HideAllPane();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();

	CMFCToolBar			 m_wndToolBar2;
	CDockPropertyWnd	 m_wndProperty;
	CDockControlTreeWnd	 m_wndControl;
	CDockFileViewWnd	 m_wndFileView;
	CDockXmlWnd			 m_wndDockXml;
protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CDockOutputWnd	  m_wndOutput;
	CDockToolBoxWnd	  m_wndToolBox;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg LRESULT OnGetTabTooltip(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileCloseAll();
	afx_msg void OnUpdateFileCloseAll(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAll();
	afx_msg void OnUpdateFileSaveAll(CCmdUI *pCmdUI);
	afx_msg void OnEditOptions();
	afx_msg void OnClose();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg LRESULT OnReOpenFile(WPARAM wparam, LPARAM lparam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnViewControlTree();
};


