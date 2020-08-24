#pragma once
#include "SciWnd.h"

// CDockXmlView

class CDockXmlView : public CWnd
{
	DECLARE_DYNAMIC(CDockXmlView)

public:
	CDockXmlView();
	virtual ~CDockXmlView();

	void Init();
	void SelectXmlNode(CControlUI *pControl);
	void SelectXmlNode(xml_node node);


	CUIManager *m_pManager;
	CDocument *m_pDoc;
	CSciWnd sci;

	int m_nTargetLine; //�����ĵ��������Ŀ����
protected:
	BOOL SelectControlUI(int line, xml_node node);

	CString GetNodeName();
	void AutoCompleteNode(CString objectName);		//�Զ���ɿؼ���
	CString AutoCompleteProperty(CString objectName, CString AttrName);	//�Զ����������
protected:
	//virtual void OnDraw(CDC* pDC) {}
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSciClick(WPARAM WParam, LPARAM LParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
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
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnSciUpdateDesign();
	afx_msg void OnUpdateSciUpdateDesign(CCmdUI *pCmdUI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSciDelete();
	afx_msg void OnUpdateSciDelete(CCmdUI *pCmdUI);
	afx_msg void OnSciSelectAll();
	afx_msg void OnUpdateSciSelectAll(CCmdUI *pCmdUI);
	BOOL ApplyDocument();
	afx_msg void OnSciRefresh();
	afx_msg void OnUpdateSciRefresh(CCmdUI *pCmdUI);
};


