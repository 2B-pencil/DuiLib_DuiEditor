
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "DuiEditor.h"

#include "ChildFrm.h"
#include "MainFrm.h"
#include "DuiEditorTabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_LINE,
	ID_INDICATOR_COL,
	ID_INDICATOR_CURRENT_POS,
	ID_INDICATOR_LENGTH,
	ID_INDICATOR_TOTAL_LINE,
};

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_MDIACTIVATE()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_DESIGNER_VIEW, &CChildFrame::OnDesignerView)
	ON_UPDATE_COMMAND_UI(ID_DESIGNER_VIEW, &CChildFrame::OnUpdateDesignerView)
	ON_COMMAND(ID_DESIGNER_CODE, &CChildFrame::OnDesignerCode)
	ON_UPDATE_COMMAND_UI(ID_DESIGNER_CODE, &CChildFrame::OnUpdateDesignerCode)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	m_nCurrentView = 0;
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}
// CChildFrame ��Ϣ�������


void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: �ڴ˴������Ϣ����������
	if(bActivate)
	{
		CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
		CDuiEditorDoc* pDoc = (CDuiEditorDoc *)GetActiveDocument();
		pMain->m_wndControl.SetActiveTreeView(pDoc->GetTreeView());
		pMain->m_wndDockXml.SetActiveSciWnd(pDoc->GetXmlPane());
	}

/*	
	CChildFrame *pChildFrame = DYNAMIC_DOWNCAST(CChildFrame, pActivateWnd);
	if(!pChildFrame) return;
	CDuiEditorViewDesign *pVeiw = DYNAMIC_DOWNCAST(CDuiEditorViewDesign, pChildFrame->GetActiveView());
	if(!pVeiw) return;
	
	if(pVeiw->m_Manager.GetUiWindow() && pVeiw->m_Manager.GetUiWindow()->GetSafeHwnd())
	{
		CShadowUI *pShadowUI = pVeiw->m_Manager.GetManager()->GetShadow();
		if(bActivate)
		{
			if(pShadowUI->IsShowShadow() && pShadowUI->IsDisableShadow() )
			{
				pShadowUI->DisableShadow(false);
			}
		}
		else
		{
			if(pShadowUI->IsShowShadow() && !pShadowUI->IsDisableShadow() )
			{
				pShadowUI->DisableShadow(true);
			}
		}
	}
*/	
	
// 	InsertMsg(_T("CChildFrame::OnMDIActivate"));
}


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
// 	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TB_UIDESIGNER_VIEW);
// 	m_wndToolBar.LoadToolBar(IDR_TB_UIDESIGNER_VIEW, 0, 0, TRUE );
// 	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
// 	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
// 
// 	m_wndToolBar.SetOwner(this);
// 	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
// 	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
// 
//   	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_DESIGNER_VIEW), _T("���"));
// 	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_DESIGNER_CODE), _T("����"));
	
	//////////////////////////////////////////////////////////////////////////
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneWidth(1, 100);
	m_wndStatusBar.SetPaneText(1, _T("row: "));
	m_wndStatusBar.SetPaneWidth(2, 100);
	m_wndStatusBar.SetPaneText(2, _T("col: "));
	m_wndStatusBar.SetPaneWidth(3, 100);
	m_wndStatusBar.SetPaneText(3, _T("pos: "));
	m_wndStatusBar.SetPaneWidth(4, 100);
	m_wndStatusBar.SetPaneText(4, _T("length: "));
	m_wndStatusBar.SetPaneWidth(5, 100);
	m_wndStatusBar.SetPaneText(5, _T("lines: "));

	m_wndStatusBar.ShowPane(FALSE, TRUE, TRUE);

//	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
	EnableDocking(CBRS_ALIGN_ANY);
//	DockPane(&m_wndToolBar);

	return 0;
}


void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
// 	if(!m_wndToolBar.GetSafeHwnd())
// 		return;
}


void CChildFrame::OnDesignerView()
{
	
	CDuiEditorViewDesign *pView = (CDuiEditorViewDesign *)GetActiveView();
	if(!pView)	return;
	CDuiEditorDoc *pDoc = pView->GetDocument();
	if(!pDoc)	return;

	for (POSITION pos = pDoc->GetFirstViewPosition(); pos != NULL;)
	{
		CView *pView = pDoc->GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CDuiEditorTabView)))
		{
			CDuiEditorTabView *pTabView = (CDuiEditorTabView *)pView;
			if(pTabView->SetActiveView(0))
			{
				m_nCurrentView = 0;
				m_wndStatusBar.ShowPane(FALSE, TRUE, TRUE);
				//((CMainFrame *)AfxGetMainWnd())->ShowAllPane();
				SendMessage(WM_SIZE);
			}
		}
	}
	
}


void CChildFrame::OnUpdateDesignerView(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nCurrentView == 0);
}


void CChildFrame::OnDesignerCode()
{
	CDuiEditorViewDesign *pView = (CDuiEditorViewDesign *)GetActiveView();
	if(!pView)	return;
	CDuiEditorDoc *pDoc = pView->GetDocument();
	if(!pDoc)	return;

	for (POSITION pos = pDoc->GetFirstViewPosition(); pos != NULL;)
	{
		CView *pView = pDoc->GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CDuiEditorTabView)))
		{
			CDuiEditorTabView *pTabView = (CDuiEditorTabView *)pView;
			if(pTabView->SetActiveView(1))
			{
				m_nCurrentView = 1;
				m_wndStatusBar.ShowPane(TRUE, TRUE, TRUE);
				//((CMainFrame *)AfxGetMainWnd())->HideAllPane();
				SendMessage(WM_SIZE);
			}
		}
	}
}


void CChildFrame::OnUpdateDesignerCode(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nCurrentView == 1);
}
