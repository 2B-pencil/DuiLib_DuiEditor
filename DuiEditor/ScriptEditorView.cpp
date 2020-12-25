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
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_UNDO, &CScriptEditorView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CScriptEditorView::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CScriptEditorView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CScriptEditorView::OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_CUT, &CScriptEditorView::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CScriptEditorView::OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CScriptEditorView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CScriptEditorView::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, &CScriptEditorView::OnEditClear)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CScriptEditorView::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_PASTE, &CScriptEditorView::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CScriptEditorView::OnUpdateEditPaste)
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
	sci.InitCpp();
	sci.sci_UsePopup(FALSE);

	COLORREF crfComment = RGB(0,150,0);
	sci.sci_StyleSetFore(SCE_C_COMMENT,			crfComment); //��ע��  /*...*/
	sci.sci_StyleSetFore(SCE_C_COMMENTLINE,		crfComment); //��ע��  //...
	sci.sci_StyleSetFore(SCE_C_COMMENTDOC,			crfComment); //�ĵ�ע��  /**...*/
	sci.sci_StyleSetFore(SCE_C_COMMENTLINEDOC,		RGB(255,0,0)); //
	sci.sci_StyleSetFore(SCE_C_COMMENTDOCKEYWORD,	RGB(255,0,0));
	sci.sci_StyleSetFore(SCE_C_COMMENTDOCKEYWORDERROR, crfComment);


	sci.sci_StyleSetFore(SCE_C_NUMBER, RGB(100,100,100));

	sci.sci_StyleSetFore(SCE_C_STRING,			RGB(100,100,100));
	sci.sci_StyleSetFore(SCE_C_CHARACTER,		RGB(100,100,100));
	sci.sci_StyleSetFore(SCE_C_UUID,			RGB(100,100,100));

	//Ԥ�����궨��
	sci.sci_StyleSetFore(SCE_C_PREPROCESSOR,	RGB(160,0,160));

	//������,���� ( ) { } = ; + - * / % < > <= >= == && || 
	sci.sci_StyleSetFore(SCE_C_OPERATOR,		RGB(0,0,0));

	//��־��
	sci.sci_StyleSetFore(SCE_C_IDENTIFIER,		RGB(0,0,0));

	//�ַ���˫����δ���ʱ
	sci.sci_StyleSetFore(SCE_C_STRINGEOL,		RGB(255,0,0));

	//???
	sci.sci_StyleSetFore(SCE_C_VERBATIM,		RGB(0,128,0));

	//???
	sci.sci_StyleSetFore(SCE_C_REGEX,			RGB(0,128,0));	

	//???
	sci.sci_StyleSetFore(SCE_C_GLOBALCLASS,	RGB(255,0,0));

	//???
	sci.sci_StyleSetFore(SCE_C_STRINGRAW,		RGB(255,0,0));

	//???
	sci.sci_StyleSetFore(SCE_C_TRIPLEVERBATIM, RGB(0,128,0));

	InitLexer();
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
	sci.sci_SetSavePoint();
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
			GetDocument()->SetModifiedFlag(FALSE);
		}
		break;
	case SCN_SAVEPOINTLEFT: //�ļ����޸�
		{			
			GetDocument()->SetModifiedFlag(TRUE);
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


BOOL CScriptEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return CView::PreCreateWindow(cs);
}


void CScriptEditorView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CPoint pt = point;
	ScreenToClient(&pt);
	CMenu popmenu;
	popmenu.LoadMenu(IDR_MENU_SCRIPT_EDIT);
	theApp.GetContextMenuManager()->ShowPopupMenu(popmenu.GetSubMenu(0)->m_hMenu, point.x, point.y, AfxGetMainWnd(), TRUE);
}


void CScriptEditorView::OnEditUndo()
{
	sci.sci_Undo();
}


void CScriptEditorView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(sci.sci_CanUndo());
}


void CScriptEditorView::OnEditRedo()
{
	sci.sci_Redo();
}


void CScriptEditorView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(sci.sci_CanRedo());
}


void CScriptEditorView::OnEditCut()
{
	sci.sci_Cut();
}


void CScriptEditorView::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(sci.sci_CanCut());
}


void CScriptEditorView::OnEditCopy()
{
	sci.sci_Copy();
}


void CScriptEditorView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(sci.sci_CanCopy());
}


void CScriptEditorView::OnEditPaste()
{
	sci.sci_Paste();
}


void CScriptEditorView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(sci.sci_CanPaste());
}


void CScriptEditorView::OnEditClear()
{
	sci.sci_Clear();
}

void CScriptEditorView::OnEditSelectAll()
{
	sci.sci_SelectAll();
}
