// ScriptLoader.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ScriptLoader.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	if(!AfxWinInit(::GetModuleHandle(NULL),NULL,::GetCommandLine(),0))
	{
		return 1;
	}

	//_CrtSetBreakAlloc(2445);

	//���������ڵ�����
	uiApp.SetAppName(_T("DuiLib Script"));

	//����xml��Դ���뷽ʽ��ѡ��һ�־���	
//#ifdef _DEBUG
	uiApp.SetResType_File(_T("skin"));								//���ļ���������xml�ļ�
//#else
//	uiApp.SetResType_ZipResource(_T("skin"), _T(""), IDR_ZIPRES1, _T("ZIPRES"));	//�ӳ�����Դ�ļ�������xml�ļ�
//#endif

	//��ʼ��duilib, ע����������������
	if(!uiApp.InitInstance(hInstance)) 
		return 0;

	//������Ϣѭ��
	uiApp.Run();

	//������Դ��
	uiApp.ExitInstance();
	return 0;
}