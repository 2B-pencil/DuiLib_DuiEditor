#ifndef __UIMENU_WND_GTK_H__
#define __UIMENU_WND_GTK_H__

#pragma once

#ifdef DUILIB_GTK
namespace DuiLib {
//////////////////////////////////////////////////////////////////////////////////////////////
//
//
class UILIB_API CMenuWndGtk : public CWindowWnd, public MenuReceiverImpl, public INotifyUI, public IDialogBuilderCallback
{
public:
	static MenuObserverImpl& GetGlobalContextMenuObserver()
	{
		static MenuObserverImpl s_context_menu_observer;
		return s_context_menu_observer;
	}
	static CMenuWndGtk* CreateMenu(CMenuElementUI* pOwner, STRINGorID xml, POINT point,
		CPaintManagerUI* pMainPaintManager, CStdStringPtrMap* pMenuCheckInfo = NULL,
		DWORD dwAlignment = eMenuAlignment_Left | eMenuAlignment_Top);
	static void DestroyMenu();
	static MenuItemInfo* SetMenuItemInfo(LPCTSTR pstrName, bool bChecked);

public:
	CMenuWndGtk();
	~CMenuWndGtk();
	void Close(UINT nRet = IDOK);
	bool isClosing;
	/*
	 *	@pOwner һ���˵���Ҫָ��������������ǲ˵��ڲ�ʹ�õ�
	 *	@xml	�˵��Ĳ����ļ�
	 *	@point	�˵������Ͻ�����
	 *	@pMainPaintManager	�˵��ĸ����������ָ��
	 *	@pMenuCheckInfo	����˵��ĵ�ѡ�͸�ѡ��Ϣ�ṹָ��
	 *	@dwAlignment		�˵��ĳ���λ�ã�Ĭ�ϳ������������²ࡣ
	 */

    void Init(CMenuElementUI* pOwner, STRINGorID xml, POINT point,
		CPaintManagerUI* pMainPaintManager, CStdStringPtrMap* pMenuCheckInfo = NULL,
		DWORD dwAlignment = eMenuAlignment_Left | eMenuAlignment_Top);
    LPCTSTR GetWindowClassName() const;
    void OnFinalMessage(UIWND hWnd);
	void Notify(TNotifyUI& msg);
	CControlUI* CreateControl(LPCTSTR pstrClassName);

	//modify by liqs99, ����4��������Ϊ�麯��
	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL Receive(ContextMenuParam param);

	// ��ȡ���˵��ؼ������ڶ�̬����Ӳ˵�
	CMenuUI* GetMenuUI();

	// ���µ����˵��Ĵ�С
	void ResizeMenu();

	// ���µ����Ӳ˵��Ĵ�С
	void ResizeSubMenu();
	void setDPI(int DPI);

public:

	POINT			m_BasedPoint;
	STRINGorID		m_xml;
    DuiLibPaintManagerUI m_pm;
    CMenuElementUI* m_pOwner;
    CMenuUI*	m_pLayout;
	DWORD		m_dwAlignment;	//�˵����뷽ʽ
	bool		m_bAutoDestroy;
};

} // namespace DuiLib

#endif // #ifdef DUILIB_GTK
#endif // __UIMENU_WND_GTK_H__

