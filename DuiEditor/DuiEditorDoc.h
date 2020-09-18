
// DuiEditorDoc.h : CDuiEditorDoc ��Ľӿ�
//
#pragma once

class CUIManager;
class CDuiEditorDoc : public CDocument
{
protected: // �������л�����
	CDuiEditorDoc();
	DECLARE_DYNCREATE(CDuiEditorDoc)

// ����
public:
	pugi::xml_document m_doc;
	BOOL m_bMenuWnd;

public:
	CUIManager *GetUIManager() const { return m_pUIManager; }
	void SetUIManager(CUIManager *pManager) { m_pUIManager = pManager; }
private:
	CUIManager *m_pUIManager;

// ����
public:
	void FilterDefaultValue(xml_node nodeDoc);	//�����ĵ�Ĭ������
	void FilterPosWidthHeight(xml_node nodeDoc);

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

private:
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
