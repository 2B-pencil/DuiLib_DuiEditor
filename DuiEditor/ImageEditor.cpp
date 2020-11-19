// ImageEditor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DuiEditor.h"
#include "ImageEditor.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "UIManager.h"

// CImageEditor �Ի���
CImageEditor *g_pEditorImage = NULL;
IMPLEMENT_DYNAMIC(CImageEditor, CDialogEx)

CImageEditor::CImageEditor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageEditor::IDD, pParent)
{
	m_pFrame = NULL;
	m_pParentGrid = NULL;
}

CImageEditor::~CImageEditor()
{
}

void CImageEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageEditor, CDialogEx)
	ON_BN_CLICKED(IDOK, &CImageEditor::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CImageEditor::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CImageEditor ��Ϣ�������


BOOL CImageEditor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	g_pEditorImage = this;

	CRect rectDummy;
	GetClientRect(rectDummy);
	DWORD dwStyle = WS_CHILD|WS_VISIBLE;
	m_pFrame = (CImageEditorFrame* )RUNTIME_CLASS(CImageEditorFrame)->CreateObject();
	m_pFrame->Create(NULL, _T(""), dwStyle, rectDummy, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CImageEditor::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CImageEditor::OnBnClickedCancel()
{

	CDialogEx::OnCancel();
}


void CImageEditor::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(!m_pFrame)	return;
	if(!m_pFrame->GetSafeHwnd())	return;
	m_pFrame->MoveWindow(0, 0, cx, cy);
}


void CImageEditor::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if(m_pFrame && m_pFrame->GetSafeHwnd())
	{
		m_pFrame->DestroyWindow();
	}
	g_pEditorImage = NULL;
}

BOOL CImageEditor::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}

void CImageEditor::SetAttributeValue(LPCTSTR szAttribute)
{
	CString strXML = _T("<IMAGE ");
	strXML += szAttribute;
	strXML += _T(" />");
	xml_parse_result ret = m_nodeImage.load(T2XML(strXML));
	if(ret.status != pugi::status_ok)//���ƥ�䲻�ɹ�, ����Ϊֻ���ļ���, ����������
	{
		strXML = _T("<IMAGE />");
		ret = m_nodeImage.load(T2XML(strXML));
		m_nodedata = m_nodeImage.child(XTEXT("IMAGE"));

		g_duiProp.AddAttribute(m_nodedata, _T("file"), szAttribute, NULL);
	}
	else
	{
		m_nodedata = m_nodeImage.child(XTEXT("IMAGE"));
	}

	/*
	//�Ȱ�����������Ĭ�ϵ����ϣ������ھʹ���
	xml_node nodePropertyControl = g_duiProp.FindControl(_T("IMAGE"));
	if(!nodePropertyControl) return;
	
	for (xml_node node=nodePropertyControl.first_child(); node; node=node.next_sibling())
	{
		if(node.type() != node_element) continue;
		if(!CompareString(node.name(), _T("Attribute"))) continue;

		CString strName = XML2T(node.attribute(XTEXT("name")).as_string());
		xml_attribute attr = m_nodedata.attribute(node.attribute(XTEXT("name")).as_string());
		if(!attr)
		{
			CString strDefault = XML2T(node.attribute(XTEXT("default")).as_string());
			g_duiProp.AddAttribute(m_nodedata, strName, strDefault, NULL);
		}
	}
	*/

	//����ͼƬ
	CString strSkinDir = GetUIManager()->GetDocument()->GetSkinPath();
	m_image.DestroyFrames(); m_image.Destroy();
	m_image.Load(strSkinDir + XML2T(m_nodedata.attribute(XTEXT("file")).value()));
	m_rcImage.SetRect(0, 0, m_image.GetWidth(), m_image.GetHeight());

	//����Ĭ��source
// 	xml_attribute attr = m_nodedata.attribute(XTEXT("file"));
// 	if(attr)
// 	{
// 		xml_attribute attr2 = m_nodedata.attribute(XTEXT("source"));
// 		if(!attr2)
// 		{
// 			m_nodedata.attribute_auto(XTEXT("source")).set_value(T2XML(RectToString(m_rcImage)));
// 		}
// 	}

	return;
}

void CImageEditor::SetControlImage(CxImage &img)
{
	m_imgControlX.Transfer(img);

	CRect rc(0, 0, m_imgControlX.GetWidth(), m_imgControlX.GetHeight());
	m_rcControl = rc;

	//����Ĭ��dest
// 	xml_attribute attrDest = m_nodedata.attribute(XTEXT("dest"));
// 	if(!attrDest)
// 	{
// 		m_nodedata.attribute_auto(XTEXT("dest")).set_value(T2XML(RectToString(rc)));
// 	}
}

void CImageEditor::SetImageFile(LPCTSTR lpstrPathName)
{
	CString strDocPath = GetUIManager()->GetDocument()->GetSkinPath(); //CPaintManagerUI::GetResourcePath();
	CString strFileName = lpstrPathName;

	//ֻ��ȡ��Ŀ¼���ļ�
	if(strFileName.Find(strDocPath) == 0)
	{
		strFileName = strFileName.Right(strFileName.GetLength() - strDocPath.GetLength());
	}
	else
	{
		::MessageBoxA(NULL, "ֻ��ʹ�õ�ǰĿ¼������Ŀ¼���ļ�", "ERROR", MB_OK);
		return;
	}

	g_duiProp.AddAttribute(g_pEditorImage->m_nodedata, _T("file"), strFileName, NULL);

	m_image.DestroyFrames(); m_image.Destroy();
	m_image.Load(lpstrPathName);
	m_rcImage.SetRect(0, 0, m_image.GetWidth(), m_image.GetHeight());
}

CString CImageEditor::GetAttributeValue()
{
	xml_node node = m_nodeImage.child(XTEXT("IMAGE"));

	//����Ĭ������
	g_duiProp.FilterDefaultValue(node, NULL);
	g_duiProp.FilterPosWidthHeight(node, NULL);

	//�ж�dest�Ƿ����ͼ��ԭʼ��С, ������ɾ��dest���Զ���
	xml_attribute attr = node.attribute(XTEXT("dest"));
	if(attr)
	{
		CDuiRect rc(XML2T(attr.value()));
		if(m_rcControl == rc)
			node.remove_attribute(attr);
	}

	//�ж�source�Ƿ����ͼ��ԭʼ��С, ������ɾ��source���Զ���
	xml_attribute attr2 = node.attribute(XTEXT("source"));
	if(attr2)
	{
		CDuiRect rc(XML2T(attr2.value()));
		if(m_rcImage == rc)
			node.remove_attribute(attr2);
	}

	CString strImage, temp;
	//�ж��Ƿ�ֻ���ļ�������
	BOOL bCustomDefine = FALSE;
	for (xml_attribute attr=node.first_attribute(); attr; attr=attr.next_attribute())
	{
		if(CompareString(attr.name(), _T("file")))
		{
			continue;
		}
		bCustomDefine = TRUE;
	}

	if(bCustomDefine)
	{
		for (xml_attribute attr=node.first_attribute(); attr; attr=attr.next_attribute())
		{
			temp.Format(_T("%s='%s' "), XML2T(attr.name()), XML2T(attr.value()));
			strImage += temp;
		}
	}
	else
	{
		strImage = node.attribute(XTEXT("file")).value();
	}

	return strImage;
}

LRESULT CImageEditor::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(message == WM_KICKIDLE)
	{
		if(m_pFrame && m_pFrame->GetSafeHwnd())
		{
			m_pFrame->SendMessage(WM_IDLEUPDATECMDUI, wParam, lParam);
		}
	}

	return CDialogEx::DefWindowProc(message, wParam, lParam);
}


BOOL CImageEditor::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
	{
		if(m_pFrame && m_pFrame->GetSafeHwnd())
		{
			CWnd *pWnd = m_pFrame->GetFocus();
			if(pWnd)
				pWnd->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
