
// DuiEditorDoc.cpp : CDuiEditorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DuiEditor.h"
#endif

#include "DuiEditorDoc.h"
#include "DuiEditorView.h"
#include "DuiEditorViewDesign.h"
#include "DuiEditorViewCode.h"

#include <propkey.h>

#include "MainFrm.h"
#include "UIManager.h"
#include "DlgCreateDuiDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDuiEditorDoc

IMPLEMENT_DYNCREATE(CDuiEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CDuiEditorDoc, CDocument)
	ON_COMMAND(ID_FILE_REOPEN, &CDuiEditorDoc::OnFileReopen)
END_MESSAGE_MAP()


// CDuiEditorDoc ����/����

CDuiEditorDoc::CDuiEditorDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_bMenuWnd = FALSE;

	CUIManager *pManager = new CUIManager;
	SetUIManager(pManager);

	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	CDockControlTreeCtrl *pTreeView = pMain->m_wndControl.CreateTreeView();
	pTreeView->SetUIManager(GetUIManager());

	CUIPropertyGridCtrl *pPropList = pMain->m_wndProperty.CreatePropList();
	pPropList->SetUIManager(GetUIManager());

	GetUIManager()->_setPorpList(pPropList);
	GetUIManager()->_setControllTree(pTreeView);
	GetUIManager()->_setDocument(this);
}

CDuiEditorDoc::~CDuiEditorDoc()
{
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	pMain->m_wndProperty.RemovePropList(GetUIManager()->GetPropList());
	GetUIManager()->_setPorpList(NULL);

	pMain->m_wndControl.RemoveTreeView(GetUIManager()->GetTreeView());
	GetUIManager()->_setControllTree(NULL);

	InitFileView(this);

	CUIManager *pUIManager = GetUIManager();
	if(pUIManager)
	{
		delete pUIManager;
		SetUIManager(NULL);
	}
}

BOOL CDuiEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	xml_node nodeWindow = m_doc.child_auto(_T("Window"));
	nodeWindow.append_attribute(_T("size")).set_value(_T("400,300"));
	nodeWindow.append_child(_T("VerticalLayout"));

	GetUIManager()->GetTreeView()->InitTreeContent();
	m_strDefaultTitle = m_strTitle;
	return TRUE;
}

BOOL CDuiEditorDoc::OnNewDocumentFromUiTemplate()
{
	CDlgCreateDuiDocument dlg;
	if(dlg.DoModal() != IDOK) return FALSE;

	CString strFile = g_strAppPath + _T("DuiTemplate\\") + dlg.m_strModuleName + _T("\\skin.xml");
	if(!m_doc.load_file(strFile))
	{
		AfxMessageBox(_T("����ģ��ҳʧ��!"));
		xml_node nodeWindow = m_doc.root().append_child(_T("Window"));
		nodeWindow.append_attribute(_T("size")).set_value(_T("400,300"));
		nodeWindow.append_child(_T("VerticalLayout"));
	}	

	GetUIManager()->GetTreeView()->InitTreeContent();
	m_strDefaultTitle = m_strTitle;
	return TRUE;
}

#ifdef SHARED_HANDLERS
// ����ͼ��֧��
void CDuiEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
// 	CView *pView;
// 	for (POSITION pos = GetFirstViewPosition(); pos != NULL;)
// 	{
// 		pView = GetNextView(pos);
// 		if(pView->IsKindOf(RUNTIME_CLASS(CDuiEditorViewDesign)))
// 		{
// 			CDuiEditorViewDesign *pViewDesign = (CDuiEditorViewDesign *)pView;
// 
// 			CImage image;
// 			CControlUI *pRoot = pViewDesign->m_Manager.GetManager()->GetRoot();
// 			CSize szForm = pViewDesign->m_Manager.GetManager()->GetInitSize();
// 			image.Create(szForm.cx, szForm.cy, 32);
// 			CRect rcPaint(0,0,szForm.cx,szForm.cy);
// 			pRoot->DoPaint(image.GetDC(), rcPaint, NULL);
// 			image.Draw(dc.m_hDC, rcPaint);
// 			image.ReleaseDC();
// 		}
// 	}	
}
#endif // SHARED_HANDLERS

// CDuiEditorDoc ����
void CDuiEditorDoc::OnDocumentEvent(DocumentEvent deEvent)
{
	__super::OnDocumentEvent(deEvent);

	switch (deEvent)
	{
	case onAfterNewDocument:
		{
			break;
		}

	case onAfterOpenDocument:
		{
			InitFileView(NULL);
			break;
		}

	case onAfterSaveDocument:
		{
			InitFileView(NULL);
			break;
		}

	case onAfterCloseDocument:
		{
			//InitFileView();
			break;
		}
	}
}

void CDuiEditorDoc::InitFileView(CDocument *pDocCurrentClose)
{
	CDocument *pDoc = NULL;
	int nCount = 0;
	POSITION pos = GetDocTemplate()->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument *p = GetDocTemplate()->GetNextDoc(pos);
		if(p != pDocCurrentClose)
		{
			pDoc = p;
			nCount++;
		}
	}

	if(pDoc && nCount == 1)
	{
		CString strPath;
		CString strTemp = pDoc->GetPathName();
		int nPos = strTemp.ReverseFind(_T('\\'));
		if(nPos != -1)
		{
			strPath = strTemp.Left(nPos + 1);
		}

		if(!strPath.IsEmpty())
		{
			((CMainFrame *)AfxGetMainWnd())->m_wndFileView.m_wndFileView.InitFolder(strPath);
		}
	}
}

BOOL CDuiEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	m_doc.load_file(lpszPathName, XML_PARSER_OPTIONS);

	xml_node root = m_doc.child(_T("Window"));
	if(root)
	{
		xml_node node = root.child(_T("Menu"));
		if(node)
		{
			m_bMenuWnd = TRUE;
		}
	}
	return TRUE;
}

BOOL CDuiEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	//����Ĭ������
	xml_node root = m_doc.root().child(_T("Window"));
	FilterDefaultValue(root);
	FilterPosWidthHeight(root);

	//����һ������, Ȼ�󱣴濽��
	xml_document doc;
	doc.root().append_copy(root);
	bool bSave = doc.save_file(lpszPathName, PUGIXML_TEXT("\t"), format_default, encoding_utf8);
	if(!bSave)	return FALSE;

	SetModifiedFlag(FALSE);
	return TRUE;
}


void CDuiEditorDoc::OnCloseDocument()
{
	CDocument::OnCloseDocument();
}

void CDuiEditorDoc::SetModifiedFlag(BOOL bModified)
{
	if(m_bModified != bModified)
	{
		CString strTitle;
		if(GetPathName().IsEmpty())
		{
			strTitle = m_strDefaultTitle;
		}
		else
		{
			LPCTSTR lpszPathName = (LPCTSTR)GetPathName();

			// always capture the complete file name including extension (if present)
			LPTSTR lpszTemp = (LPTSTR)lpszPathName;
			for (LPCTSTR lpsz = lpszPathName; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
			{
				// remember last directory/drive separator
				if (*lpsz == '\\' || *lpsz == '/' || *lpsz == ':')
					lpszTemp = (LPTSTR)_tcsinc(lpsz);
			}

			strTitle = lpszTemp;
		}

		if(bModified)
			SetTitle(strTitle + " *");
		else
			SetTitle(strTitle);
	}

	__super::SetModifiedFlag(bModified);
}

CString CDuiEditorDoc::GetSkinPath()
{
	CString strTemp;
	strTemp = GetPathName();
	int nPos = strTemp.ReverseFind(_T('\\'));
	if(nPos != -1)
	{
		return strTemp.Left(nPos + 1);
	}

	return _T("");
}

CString CDuiEditorDoc::GetSkinFileName()
{
	CString strTemp;
	strTemp = GetPathName();
	int nPos = strTemp.ReverseFind(_T('\\'));
	if(nPos != -1)
	{
		return strTemp.Right(strTemp.GetLength() - nPos - 1);
	}

	return _T("");
}

void CDuiEditorDoc::FilterDefaultValue(xml_node nodeDoc)
{
	xml_node nodeDuiProp = g_duiProp.FindControl(nodeDoc.name());
	for (xml_node nodeAttr=nodeDuiProp.first_child(); nodeAttr; nodeAttr=nodeAttr.next_sibling())
	{
		xml_attribute attr = nodeDoc.attribute(nodeAttr.attribute(_T("name")).value());
		if(attr)
		{
			if(attr.value() == '\0' || attr.value() == NULL)
			{
				nodeDoc.remove_attribute(attr);
			}
			else if(CompareString(attr.value(), nodeAttr.attribute(_T("default")).value()))
			{
				nodeDoc.remove_attribute(attr);
			}
		}
	}

	for (pugi::xml_node node = nodeDoc.first_child(); node; node = node.next_sibling())
	{
		FilterDefaultValue(node);
	}
}

void CDuiEditorDoc::FilterPosWidthHeight(xml_node nodeDoc)
{
	if(!g_cfg.bFilterPosWidthHeight) return;

	//float�ؼ�������
	if(!nodeDoc.attribute(_T("float")).as_bool())
	{
		//���û��pos���ԣ�������
		xml_attribute attrPos = nodeDoc.attribute(_T("pos"));
		if(attrPos) 
		{
			xml_attribute attrWidth = nodeDoc.attribute(_T("width"));
			xml_attribute attrHeight = nodeDoc.attribute(_T("height"));

			//pos�����޷�ת����rect��������
			CDuiRect rc;
			if(rc.FromString(attrPos.as_string()))
			{
				//pos���ԵĴ�С ������ width��height���ԣ������� ��Ϊ��д��ͬѧ����д���ˣ���Ҫ���Դ���
				if(rc.GetWidth() == attrWidth.as_int() && rc.GetHeight() == attrHeight.as_int())
				{
					//���ˣ���pos����ȥ����
					nodeDoc.remove_attribute(attrPos);
				}	
			}	
		}
	}

	for (pugi::xml_node node = nodeDoc.first_child(); node; node = node.next_sibling())
	{
		FilterPosWidthHeight(node);
	}
}

void CDuiEditorDoc::OnFileReopen()
{
	if(!SaveModified())
		return;

	CString strFile = GetPathName();// + m_strFileName;
	if(!strFile.IsEmpty())
	{
		AfxGetMainWnd()->SendMessage(WM_REOPEN_FILE, (WPARAM)(LPCTSTR)strFile, (LPARAM)this);
	}

	OnFileClose();
	return;
}	