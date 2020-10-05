#pragma once

//namespace DuiLib{
using namespace DuiLib;

class CUIFrameWnd;

//���������ⴰ��
class UILIB_API CUIForm : public CNotifyPump
{

public:
	CUIForm(void);
	virtual ~CUIForm(void);

	//virtual LPCTSTR GetWindowClassName() const =0; //{ return _T(""); }	//���ⴰ�����ƣ����ֱ���Ψһ

	virtual void InitWindow(){};
	virtual CControlUI *CreateControl(LPCTSTR pstrClass) { return NULL; }

	BOOL IsControl(TNotifyUI& msg, LPCTSTR name) { return _tcsicmp(msg.pSender->GetName(), name) == 0; }
	BOOL IsClass(TNotifyUI& msg, LPCTSTR classname) { return _tcsicmp(msg.pSender->GetClass(), classname) == 0; }
	BOOL IsInterface(TNotifyUI &msg, LPCTSTR pstrName) { return msg.pSender->GetInterface(pstrName) != NULL; }
	CControlUI *FindControl(LPCTSTR pstrName){ return GetManager()->FindControl(pstrName); }
	BOOL IsMenuCommand(const MenuCmd *cmd, LPCTSTR name) { return _tcsicmp(cmd->szName, name) == 0; }

	void SetFrameWnd(CUIFrameWnd *pFrame) { m_pFrame = pFrame; }
	CUIFrameWnd *GetFrameWnd() const { return m_pFrame; }

	CPaintManagerUI *GetManager() { return GetFrameWnd()->GetManager(); }

	CMenuWnd *CreateMenu(STRINGorID xml);

	virtual void OnUpdateView() {}

public:
	//��Ϣ����
	virtual void OnNotifyClick(TNotifyUI& msg) {}
	virtual void OnNotifyRClick(TNotifyUI& msg){}
	virtual void OnNotifyDbClick(TNotifyUI& msg){}
	virtual void OnNotifyMenu(TNotifyUI& msg) {}
	virtual void OnNotifyLink(TNotifyUI& msg) {}
	virtual void OnNotifyTimer(TNotifyUI& msg) {}
	virtual void OnNotifyReturn(TNotifyUI& msg) {}
	virtual void OnNotifyScroll(TNotifyUI& msg) {}
	virtual void OnNotifyDropDown(TNotifyUI& msg) {}
	virtual void OnNotifySetFocus(TNotifyUI& msg) {}
	virtual void OnNotifyKillFocus(TNotifyUI& msg) {}
	virtual void OnNotifyItemClick(TNotifyUI& msg) {}
	virtual void OnNotifyItemRClick(TNotifyUI& msg) {}
	virtual void OnNotifyTabSelect(TNotifyUI& msg) {}
	virtual void OnNotifyItemSelect(TNotifyUI& msg) {}
	virtual void OnNotifyItemExpand(TNotifyUI& msg) {}
	virtual void OnNotifyWindowPrepare(TNotifyUI& msg) {}
	virtual void OnNotifyButtonDown(TNotifyUI& msg) {}
	virtual void OnNotifyMouseEnter(TNotifyUI& msg) {}
	virtual void OnNotifyMouseLeave(TNotifyUI& msg) {}
	virtual void OnNotifyTextChanged(TNotifyUI& msg) {}
	virtual void OnNotifyHeaderClick(TNotifyUI& msg) {}
	virtual void OnNotifyItemDBClick(TNotifyUI& msg) {}
	virtual void OnNotifyShowActivex(TNotifyUI& msg) {}
	virtual void OnNotifyItemCollapse(TNotifyUI& msg) {}
	virtual void OnNotifyItemActivate(TNotifyUI& msg) {}
	virtual void OnNotifyValueChanged(TNotifyUI& msg) {}
	virtual void OnNotifySelectChanged(TNotifyUI& msg) {}
	virtual void OnNotityGridClick(TNotifyUI &msg) {}
	virtual void OnNotityGridDBClick(TNotifyUI &msg) {}
	virtual void OnNotityGridRClick(TNotifyUI &msg) {}

	//���ղ˵���Ϣ������true�����������·�����Ϣ
	virtual bool OnMenuCommand(const MenuCmd *cmd) { return false; }

	//�Զ�����Ϣ����, ����TRUE, ��ʾ�Ѿ�����, �ײ㲻������������Ϣ, 
	virtual bool OnCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return false; }
public:
	virtual void Notify(TNotifyUI& msg);
protected:
	CPaintManagerUI *m_pManager;
	CUIFrameWnd *m_pFrame;

	DUI_DECLARE_MESSAGE_MAP()
};

//}