#pragma once
#include "SciWnd.h"
#include "SciFind.h"
#include "SciXmlWriter.h"
// CDuiEditorCode ��ͼ

class CUIManager;
class CDuiEditorViewCode : public CView
{
	DECLARE_DYNCREATE(CDuiEditorViewCode)
public:
	CDuiEditorViewCode();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDuiEditorViewCode();

	CDuiEditorDoc* GetDocument() const;
	void LoadDocument();
	BOOL ApplyDocument();
	BOOL IsModify() { return sci.sci_GetModify(); }

	void SelectXmlNode(CControlUI *pControl);
	void SelectXmlNode(xml_node node);



	CSciWnd *GetSciWnd() { return &sci; }
public:
	CUIManager *GetUIManager() const { return m_pUIManager; }
	void SetUIManager(CUIManager *pManager) { m_pUIManager = pManager; }
private:
	CUIManager *m_pUIManager;
protected:
	CSciFind		*m_pDlgFind;
	HWND			m_hDlgFind;
	CSciWnd sci;
	int m_nTargetLine; //�����ĵ��������Ŀ����

protected:
	BOOL SelectControlUI(int line, xml_node node);
	void UpdateFrameStatus();

	CString GetNodeName();
	void AutoCompleteNode(CString objectName);		//�Զ���ɿؼ���
	CString AutoCompleteProperty(CString objectName, CString AttrName);	//�Զ����������

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg LRESULT OnSciClick(WPARAM WParam, LPARAM LParam);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnEditFind();
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnEditRefresh();
	afx_msg void OnEditSelectAll();
	afx_msg void OnSciUpdateDesign();
	afx_msg void OnUpdateSciUpdateDesign(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
