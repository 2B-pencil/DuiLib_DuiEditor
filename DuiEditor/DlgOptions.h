#pragma once


// CDlgOptions �Ի���

class CDlgOptions : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOptions)

public:
	CDlgOptions(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOptions();

// �Ի�������
	enum { IDD = IDD_DLG_OPTIONS };

	tagXmlEditorOpt m_xmlEditorOpt;
	void SetXmlOptions(const tagXmlEditorOpt &opt);
	void SetXmlOptions(CSciWnd *pSciWnd, const tagXmlEditorOpt &opt);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	BOOL m_bUpdateSizeWhenModifyPos;
	UINT m_nTreeDeep;
	afx_msg void OnBnClickedButton1();
	CString m_strAttachTestCommand;
	CMFCColorButton m_ctrlBkColor;
	CMFCFontComboBox m_cbFont;
	CMFCColorButton m_ctrlBkColor2;
	CMFCColorButton m_ctrlBkColor3;
	CMFCColorButton m_ctrlBkColor4;
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeMfcfontcombo1();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnClickedMfccolorbutton2();
	afx_msg void OnClickedMfccolorbutton3();
	afx_msg void OnClickedMfccolorbutton4();
};
