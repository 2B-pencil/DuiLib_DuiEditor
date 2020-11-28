#include "StdAfx.h"
#include "FormSciEditor.h"


CFormSciEditor::CFormSciEditor(void)
{
}


CFormSciEditor::~CFormSciEditor(void)
{
}

void CFormSciEditor::InitWindow()
{
	m_pSci = (CSciEditUI *)FindControl(_T("sciedit_1"));

	m_pSci->GetSciWnd()->InitXML(); //ʹ��XML�ʷ�������
	int x = m_pSci->GetSciWnd()->sci_GetMargins();
#ifdef _DEBUG
	//���뵱ǰ�Ĳ����ļ�
	m_pSci->GetSciWnd()->LoadFile(GetManager()->GetResourcePath() + GetMainWnd()->GetSkinFile());
#else
	//Release�汾����Դ�������ļ�, 
	//������ļ���UTF8���룬����ʹ��CSciEdit::SetText(LPCTSTR pstrText)
	LPBYTE pByte = NULL;
	int size = CRenderEngine::LoadImage2Memory(GetMainWnd()->GetSkinFile().GetData(), 0, pByte);
	CStringA str((const char *)pByte, size);
	m_pSci->GetSciWnd()->sci_SetText(str);
	CRenderEngine::FreeMemory(pByte);
#endif
}

void CFormSciEditor::OnNotifySciNotify(TNotifyUI &msg)
{
	if(IsControl(msg, _T("sciedit_1")))
	{
		SCNotification *pMsg = (SCNotification*)msg.lParam;
		switch (pMsg->nmhdr.code)
		{
		case SCK_BACK:
			break;
		case SCN_CHARADDED:	//�����ַ�
			break;
		case SCN_MODIFIED:	//�ĵ����޸�
			break;
		case SCN_SAVEPOINTREACHED:	//�ļ�������
			break;
		case SCN_SAVEPOINTLEFT: //�ļ����޸�
			break;
		case SCN_UPDATEUI:
			break;
		case SCN_AUTOCSELECTION: //�﷨��ʾ�Զ��Զ�ʱ
			break;
		}	
	}
}