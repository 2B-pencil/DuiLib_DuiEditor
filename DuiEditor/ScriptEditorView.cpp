// ScriptEditorView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DuiEditor.h"
#include "ScriptEditorView.h"


//#include "../DuiLib/3rd/DuiAngelScript/angelscript/source/as_tokendef.h"
// CScriptEditorView

IMPLEMENT_DYNCREATE(CScriptEditorView, CView)

CScriptEditorView::CScriptEditorView()
{

}

CScriptEditorView::~CScriptEditorView()
{
}

BEGIN_MESSAGE_MAP(CScriptEditorView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CScriptEditorView ��ͼ

void CScriptEditorView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CScriptEditorView ��Ϣ�������


int CScriptEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rectDummy;
	rectDummy.SetRect(0,0,100,100);
	if (!sci.Create(0, WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, rectDummy, this, ID_SCI_WND))
	{
		return -1;      // δ�ܴ���
	}
	//sci.InitCPP();
	InitLexer();
	sci.sci_ClearTextAll();

	return 0;
}


void CScriptEditorView::InitLexer()
{/*
	CScriptMgr mgr;
	mgr.Init();
	asIScriptEngine *pEngine = mgr.GetEngine();
	if(!pEngine)	return;

	CStringA strKeyWord; CStringA strKeyWord2;

	asUINT n=0;
	//�ؼ���
	for( n = 0; n < numTokenWords; n++ )
	{
		CStringA strWord = tokenWords[n].word;
		if((strWord[0]>='a' && strWord[0]<='z') || (strWord[0]>='A' && strWord[0]<='Z'))
		{
			strKeyWord += tokenWords[n].word;
			strKeyWord += " ";
		}
	}

	//ȫ�ֺ���
	n = pEngine->GetGlobalFunctionCount();	
	for (asUINT i=0; i<n; i++)
	{
		asIScriptFunction *pFun = pEngine->GetGlobalFunctionByIndex(i);
		strKeyWord2 += pFun->GetName();
		strKeyWord2 += " ";
	}

	//ȫ�ֱ���
	n = pEngine->GetGlobalPropertyCount();
	for (asUINT i=0; i<n; i++)
	{
		const char *name;
		int nRet = pEngine->GetGlobalPropertyByIndex(i, &name); 
		if(nRet >= 0)
		{
			strKeyWord2 += name;
			strKeyWord2 += " ";
		}
	}

	//ϵͳ��
	n = pEngine->GetObjectTypeCount();
	for (asUINT i=0; i<n; i++)
	{
		asITypeInfo *pObject = pEngine->GetObjectTypeByIndex(i);
		strKeyWord += pObject->GetName();
		strKeyWord += " ";
	}

	//enum
	n = pEngine->GetEnumCount();
	for (asUINT i=0; i<n; i++)
	{
		asITypeInfo *pObject = pEngine->GetEnumByIndex(i);
		strKeyWord += pObject->GetName();
		strKeyWord += " ";

		int nValueCount = pObject->GetEnumValueCount();
		for (int j=0; j<nValueCount; j++)
		{
			int nValue;
			const char * szValueName = pObject->GetEnumValueByIndex(j, &nValue);
			strKeyWord2 += szValueName;
			strKeyWord2 += " ";
		}
	}

	//typedef
	n = pEngine->GetTypedefCount();
	for (asUINT i=0; i<n; i++)
	{
		asITypeInfo *pObject = pEngine->GetTypedefByIndex(i);
		strKeyWord += pObject->GetName();
		strKeyWord += " ";
	}

	sci.sci_SetKeyWords(0, strKeyWord);
	sci.sci_SetKeyWords(1, strKeyWord2);
	*/
}

void CScriptEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	sci.LoadFile(GetDocument()->GetPathName());
}


void CScriptEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(!sci.GetSafeHwnd())	return;

	CRect rcClient;
	GetClientRect(rcClient);
	sci.MoveWindow(rcClient);
}


BOOL CScriptEditorView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR *phDR;
	phDR = (NMHDR*)lParam;

	if (phDR == NULL || phDR->hwndFrom != sci.m_hWnd)
	{
		return __super::OnNotify(wParam, lParam, pResult);
	}

	SCNotification *pMsg = (SCNotification*)lParam;
	sci.OnParentNotify(pMsg);

	switch (pMsg->nmhdr.code)
	{
	case SCK_BACK:
		{
			
		}
		break;
	case SCN_CHARADDED:	//�����ַ�
		{
				
		}
		break;
	case SCN_MODIFIED:
		{
			
		}
		break;
	case SCN_SAVEPOINTREACHED:	//�ļ�������
		{
			
		}
		break;
	case SCN_SAVEPOINTLEFT: //�ļ����޸�
		{
			
		}
		break;
	case SCN_UPDATEUI:
		break;
	}	

	// 	CString temp;
	// 	temp.Format(_T("sciwnd msg=%d"), pMsg->nmhdr.code);
	// 	InsertMsg(temp);
	return __super::OnNotify(wParam, lParam, pResult);
}
