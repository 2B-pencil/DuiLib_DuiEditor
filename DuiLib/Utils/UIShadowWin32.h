#ifndef __UISHADOW_WIN32_H__
#define __UISHADOW_WIN32_H__

#pragma once
#include <map>

#ifdef DUILIB_WIN32
namespace DuiLib
{

class UILIB_API CShadowWin32UI : public CShadowBaseUI
{
public:
	CShadowWin32UI(void);
	virtual ~CShadowWin32UI(void);

public:
	// bShowΪ��ʱ�Żᴴ����Ӱ
	virtual void ShowShadow(bool bShow) override;	
	virtual bool IsShowShadow() const override;

	virtual void DisableShadow(bool bDisable) override;
	virtual bool IsDisableShadow() const override;

	// �㷨��Ӱ�ĺ���
	virtual bool SetSize(int NewSize = 0) override;
	virtual bool SetSharpness(unsigned int NewSharpness = 5) override;
	virtual bool SetDarkness(unsigned int NewDarkness = 200) override;
	virtual bool SetPosition(int NewXOffset = 5, int NewYOffset = 5) override;
	virtual bool SetColor(COLORREF NewColor = 0) override;

	// ͼƬ��Ӱ�ĺ���
	virtual bool SetImage(LPCTSTR szImage) override;
	virtual bool SetShadowCorner(RECT rcCorner) override;	// �Ź���ʽ������Ӱ

	// ���Լ�����Ӱ��ʽ���Ƶ��������
	virtual bool CopyShadow(CShadowBaseUI* pShadow) override;

	//	������Ӱ���壬��CPaintManagerUI�Զ�����,�����Լ�Ҫ����������Ӱ
	virtual void Create(CPaintManagerUI* pPaintManager) override;

	// ������ı��С���ƶ������������ػ���Ӱʱ����
	virtual void Update(HWND hParent) override;

public:

	//	��ʼ����ע����Ӱ��
	static bool Initialize(HINSTANCE hInstance);

	// �����Ѿ����ӵĴ������������������Ӱ��,������ParentProc()������ͨ������õ���Ӱ��
	static std::map<HWND, CShadowUI *>& GetShadowMap();

	//	���໯������
	static LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// ͨ���㷨������Ӱ
	void MakeShadow(UINT32 *pShadBits, HWND hParent, RECT *rcParent);

	// ����alphaԤ��ֵ
	inline DWORD PreMultiply(COLORREF cl, unsigned char nAlpha)
	{
		return (GetRValue(cl) * (DWORD)nAlpha / 255) |
			(GetGValue(cl) * (DWORD)nAlpha / 255) << 8 |
			(GetBValue(cl) * (DWORD)nAlpha / 255) << 16 ;
	}

protected:
	enum ShadowStatus
	{
		SS_ENABLED = 1,				// Shadow is enabled, if not, the following one is always false
		SS_VISABLE = 1 << 1,		// Shadow window is visible
		SS_PARENTVISIBLE = 1<< 2	// Parent window is visible, if not, the above one is always false
	};


	static bool s_bHasInit;

	CPaintManagerUI	*m_pManager;		// �������CPaintManagerUI��������ȡ�ز���Դ�͸�������
	HWND			 m_hWnd;			// ��Ӱ����ľ��
	LONG_PTR		 m_OriParentProc;	// ���໯������
	BYTE			 m_Status;
	bool			 m_bIsImageMode;	// �Ƿ�ΪͼƬ��Ӱģʽ
	bool			 m_bIsShowShadow;	// �Ƿ�Ҫ��ʾ��Ӱ
	bool			m_bIsDisableShadow;
	// �㷨��Ӱ��Ա����
	unsigned char m_nDarkness;	// Darkness, transparency of blurred area
	unsigned char m_nSharpness;	// Sharpness, width of blurred border of shadow window
	signed char m_nSize;	// Shadow window size, relative to parent window size

	// The X and Y offsets of shadow window,
	// relative to the parent window, at center of both windows (not top-left corner), signed
	signed char m_nxOffset;
	signed char m_nyOffset;

	// Restore last parent window size, used to determine the update strategy when parent window is resized
	LPARAM m_WndSize;

	// Set this to true if the shadow should not be update until next WM_PAINT is received
	bool m_bUpdate;

	COLORREF m_Color;	// Color of shadow

	// ͼƬ��Ӱ��Ա����
	CDuiString	m_sShadowImage;
	RECT		m_rcShadowCorner;
};

}
#endif //#ifdef DUILIB_WIN32

#endif //__UISHADOW_H__