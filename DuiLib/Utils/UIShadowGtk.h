#pragma once
#ifndef __UISHADOW_GTK_H__
#define __UISHADOW_GTK_H__

#ifdef DUILIB_GTK
namespace DuiLib
{

class UILIB_API CShadowGtkUI : public CShadowBaseUI
{
public:
	CShadowGtkUI(void);
	virtual ~CShadowGtkUI(void);

public:
	//	��ʼ����ע����Ӱ��
	static bool Initialize(HINSTANCE hInstance);
};

}
#endif //#ifdef DUILIB_GTK

#endif //__UISHADOW_H__