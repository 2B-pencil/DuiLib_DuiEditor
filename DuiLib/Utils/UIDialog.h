#pragma once

#ifdef DUILIB_WIN32
namespace DuiLib {

#define TMD_ADD		1
#define TMD_MODIFY	2
#define TMD_DELETE	3

class UILIB_API CUIDialog : public CUIFrameWnd
{
public:
	CUIDialog(void);
	CUIDialog(LPCTSTR sSkinFile);
	virtual ~CUIDialog(void);
	int m_nMode;

	virtual LPCTSTR GetWindowClassName() const override;
	virtual CDuiString GetSkinFile() override;

	virtual void OnFinalMessage( HWND hWnd );
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	//������Ӧ�س�����ESC��Ĭ�ϴ���ʽ
	virtual void SetDefaultKeyEvent(BOOL bEnterCloseOK=TRUE, BOOL bEscCloseCancel=TRUE);
	virtual BOOL IsEnterCloseOK() const;
	virtual BOOL IsEscCloseCancel() const;

	//��ʾģ̬�Ի�����
	virtual UINT DoModal(HWND hWndParent);
	virtual UINT DoModal(CUIFrmBase *pParentWnd = NULL);

	//��ʾ��ģ̬�Ի�����, ע���ģ̬���ڱ�����new�����ġ�
	virtual void ShowDialog(HWND hWndParent);
	virtual void ShowDialog(CUIFrmBase *pParentWnd = NULL);

	virtual void Notify(TNotifyUI& msg);

	virtual void InitWindow();

	virtual void OnClickOK();
	virtual void OnClickCancel();

	virtual void on_tmd_add_initwindow();
	virtual bool on_tmd_add();

	virtual void on_tmd_modify_initwindow();
	virtual bool on_tmd_modify();

	virtual void on_tmd_delete_initwindow();
	virtual bool on_tmd_delete();

	void __AddRef();
	void __ReleaseRef();

	//ע��ű���ӦNotify�ĺ���
	virtual void RegScriptNotify(LPCTSTR sNotifyType, LPCTSTR sFunName);
private:
	bool _bModal;
	BOOL m_bEnterCloseOK;
	BOOL m_bEscCloseCancel;

	CDuiString m_sSkinFile, m_sWindowClassName;
	std::map<CDuiString, CDuiString> m_mScriptNotify;

	int __refCount;
};

} //namespace DuiLib {
#endif //#ifdef DUILIB_WIN32