#pragma once


// CThreadWork
extern DWORD g_nThreadWorkID;
extern HANDLE g_hThreadWorkHandle;

class CThreadWork : public CWinThread
{
	DECLARE_DYNCREATE(CThreadWork)

public:
	CThreadWork();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadWork();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void Trans(CXmlDocumentUI &xml);

	void AutoSelectDestLanguage(LPCTSTR lpszFileName);

	void EndWork();
public:
	CString m_sFileContent;
	CStringArray m_arrFileList;

	tagLanguageCode m_langCode;
protected:
	BOOL m_bTerminateExit;	//�Ƿ���ֹ����
	DECLARE_MESSAGE_MAP()
};


