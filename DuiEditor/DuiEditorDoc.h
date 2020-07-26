
// DuiEditorDoc.h : CDuiEditorDoc ��Ľӿ�
//
#pragma once
#include "DockControlTreeCtrl.h"
#include "DockXmlView.h"

class CDuiEditorTabView;
class CDuiEditorViewDesign;
class CDuiEditorDoc : public CDocument
{
protected: // �������л�����
	CDuiEditorDoc();
	DECLARE_DYNCREATE(CDuiEditorDoc)

// ����
public:
	pugi::xml_document m_doc;
	BOOL m_bMenuWnd;

// ����
public:
	void FilterDefaultValue(xml_node nodeDoc);	//�����ĵ�Ĭ������
	CDockControlTreeCtrl *GetTreeView() { return m_pTreeView; }
	CDockXmlView *GetXmlPane() const { return m_pSciWnd; }
	CDuiEditorViewDesign *GetDesignView() const;
	CView *GetCodeView() const;
	CDuiEditorTabView *GetTabView() const;

	CString GetSkinPath();
	CString GetSkinFileName();

	void InitFileView(CDocument *pDocCurrentClose);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnNewDocumentFromUiTemplate();
#ifdef SHARED_HANDLERS
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CDuiEditorDoc();

protected:
	CDockControlTreeCtrl *m_pTreeView;
	CDockXmlView *m_pSciWnd;
	CString m_strDefaultTitle;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDocumentEvent(DocumentEvent deEvent);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void SetModifiedFlag(BOOL bModified = TRUE);
	afx_msg void OnFileReopen();
};
