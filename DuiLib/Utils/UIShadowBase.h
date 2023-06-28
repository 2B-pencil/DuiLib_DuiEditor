#ifndef __UISHADOW_BASE_H__
#define __UISHADOW_BASE_H__

#pragma once
#include <map>

namespace DuiLib
{

class UILIB_API CShadowBaseUI
{
public:
	CShadowBaseUI(void);
	virtual ~CShadowBaseUI(void);

	// bShowΪ��ʱ�Żᴴ����Ӱ
	virtual void ShowShadow(bool bShow) { }	
	virtual bool IsShowShadow() const { return false; }

	virtual void DisableShadow(bool bDisable) {}
	virtual bool IsDisableShadow() const { return false; }

	// �㷨��Ӱ�ĺ���
	virtual bool SetSize(int NewSize = 0) { return false; }
	virtual bool SetSharpness(unsigned int NewSharpness = 5) { return false; }
	virtual bool SetDarkness(unsigned int NewDarkness = 200) { return false; }
	virtual bool SetPosition(int NewXOffset = 5, int NewYOffset = 5) { return false; }
	virtual bool SetColor(COLORREF NewColor = 0) { return false; }

	// ͼƬ��Ӱ�ĺ���
	virtual bool SetImage(LPCTSTR szImage) { return false; }
	virtual bool SetShadowCorner(RECT rcCorner) { return false; }	// �Ź���ʽ������Ӱ

	// ���Լ�����Ӱ��ʽ���Ƶ��������
	virtual bool CopyShadow(CShadowBaseUI* pShadow) { return false; }

	//	������Ӱ���壬��CPaintManagerUI�Զ�����,�����Լ�Ҫ����������Ӱ
	virtual void Create(CPaintManagerUI* pPaintManager) {}

	// ������ı��С���ƶ������������ػ���Ӱʱ����
	virtual void Update(UIWND hParent) {}
};

}

#endif //__UISHADOW_BASE_H__