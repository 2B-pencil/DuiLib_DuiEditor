#pragma once

namespace DuiLib {

class CUIFrameWnd;

//���������ⴰ��
class UILIB_API CUIForm : public CUIFrmBase
{
//	friend class CUIFrameWnd;
public:
	CUIForm(void);
	virtual ~CUIForm(void);
	virtual CDuiString GetFormName() { return _T(""); }

	virtual void InitWindow(){};
	virtual CControlUI *CreateControl(LPCTSTR pstrClass) { return NULL; }

	void SetFrameWnd(CUIFrameWndBase *pFrame) { m_pFrame = pFrame; m_pManager=m_pFrame->GetManager(); }
	CUIFrameWndBase *GetFrameWnd() const { return m_pFrame; }

	virtual CPaintManagerUI* GetManager() { return m_pManager; } //{ return GetFrameWnd()->GetManager(); }
	virtual CControlUI *GetRoot();

	virtual void OnUpdateView() {} //���ã�Ϊ�˼��ݱ���

	BOOL IsForm(LPCTSTR formName) { return GetFormName() == formName; }

	virtual void OnActiveForm() {}	//ҳ���������л�����ʾʱ
	virtual void OnHideForm() {}	//ҳ������ʾ�л�������ʱ

	void __InitWindow();
protected:
	CPaintManagerUI *m_pManager;
	CControlUI *m_pRoot;
	CUIFrameWndBase *m_pFrame;
};

} //namespace DuiLib {