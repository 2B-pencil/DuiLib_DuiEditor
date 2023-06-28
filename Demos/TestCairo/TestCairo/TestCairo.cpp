// DuiLibTemplate.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestCairo.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	if(!AfxWinInit(::GetModuleHandle(NULL),NULL,::GetCommandLine(),0))
	{
		return 1;
	}

	//_CrtSetBreakAlloc(1282);

	//���������ڵ�����
	uiApp.SetAppName(_T("TestCairo"));

	//���ó���Ϊ��һִ��ʵ���������ʵ���Ļ����Ͳ���Ҫ�����ˡ�
	uiApp.SetSingleApplication(true, _T("A99A7DB0-5421-4D3F-B950-B7F4DB49C7E0"));

	//����xml��Դ���뷽ʽ��ѡ��һ�־���	
#ifdef _DEBUG
	uiApp.SetResType_File(_T("skin"));								//���ļ���������xml�ļ�
#else
	uiApp.SetResType_ZipResource(_T("skin"), _T(""), IDR_ZIPRES1, _T("ZIPRES"));	//�ӳ�����Դ�ļ�������xml�ļ�
#endif


	CPaintManagerUI::SetRenderEngineType(DuiLib_Render_Default);
	CPaintManagerUI::SetRenderEngineType(DuiLib_Render_GdiPlus);
	CPaintManagerUI::SetRenderEngineType(DuiLib_Render_Cairo);

	//��ʼ��duilib, ע����������������
	if(!uiApp.InitInstance(hInstance)) 
		return 0;

	//������Ϣѭ��
	uiApp.Run();

	//������Դ��
	uiApp.ExitInstance();
	return 0;
}
