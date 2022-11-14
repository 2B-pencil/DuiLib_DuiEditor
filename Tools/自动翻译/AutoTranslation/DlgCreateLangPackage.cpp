#include "stdafx.h"
#include "DlgCreateLangPackage.h"

CDlgCreateLangPackage::CDlgCreateLangPackage()
{
	m_bFolder = TRUE;
	m_bFile = FALSE;
}

CDlgCreateLangPackage::~CDlgCreateLangPackage()
{
}

void CDlgCreateLangPackage::InitWindow()
{
	UI_BINDCONTROL(COptionUI, m_opt_folder, _T("opt_folder"));
	UI_BINDCONTROL(COptionUI, m_opt_file, _T("opt_file"));
	UI_BINDCONTROL(CEditUI, m_edit_path, _T("edit_path"));
	UI_BINDCONTROL(CEditUI, m_edit_file, _T("edit_file"));

	//�������ļ���ʼ���ؼ�����
	CXmlNodeUI node = uiApp.Config.GetRoot().child_auto(_T("Config")).child_auto(_T("DlgCreateLangPackage"));
	uiApp.Config.LoadControl(node, m_edit_path, _T("E:\\MyLibrary\\DuiLib\\bin\\skin\\lang\\ChineseSimplified"));
	uiApp.Config.LoadControl(node, m_opt_folder, TRUE);
	uiApp.Config.LoadControl(node, m_edit_file);
	uiApp.Config.LoadControl(node, m_opt_file, FALSE);

	//�ؼ��ͱ��������ݽ���
	ddxSetManager(GetManager());
	ddxCheckBox(_T("opt_folder"), m_bFolder);
	ddxCheckBox(_T("opt_file"), m_bFile);
	ddxText(_T("edit_path"), m_sFolder);
	ddxText(_T("edit_file"), m_sFile);
}

static int CALLBACK BrowserCallbackProc(HWND hWnd,UINT   uMsg, LPARAM   lParam, LPARAM   lpData)  
{  
	switch(uMsg)  
	{  
	case   BFFM_INITIALIZED: //����Ĭ��ѡ����ļ���  
		::SendMessage(hWnd,BFFM_SETSELECTION,1,lpData);  
		break;  
	default:  
		break;  
	}  
	return   0;  
} 

void CDlgCreateLangPackage::OnNotifyClick(TNotifyUI& msg)
{

	if(IsControl(msg, _T("btn_select_path")))
	{
		CString strPath;
		GetCurrentDirectory(MAX_PATH, strPath.GetBuffer(MAX_PATH));
		strPath.ReleaseBuffer();

		TCHAR szDir[MAX_PATH];  
		BROWSEINFO bi;   
		bi.hwndOwner      = GetHWND();  
		bi.pidlRoot       = NULL;  
		bi.pszDisplayName = NULL;   
		bi.lpszTitle      = TEXT("ѡ��ͼ�󱣴��ַ");   
		bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;  
		bi.lpfn           = BrowserCallbackProc;   
		bi.lParam         = (LPARAM)(LPCTSTR)strPath;  
		bi.iImage         = 0;   

		LPITEMIDLIST pidl = SHBrowseForFolder(&bi);  
		if (pidl == NULL) return;  

		if (!SHGetPathFromIDList(pidl, szDir))  
			return;
		m_edit_path->SetText(szDir);
		m_opt_folder->Selected(true);
		return;
	}


	if(IsControl(msg, _T("btn_select_file")))
	{
		static TCHAR BASED_CODE szFilter[] = _T("�����ļ�(*.*)|*.*|���԰��ļ�(*.lng)|*.lng|StringRes(*.xml)|*.xml||");
		//CFileDialog fileDlg(FALSE, _T("lng"), GetUIManager()->GetManager()->GetResourcePath() + (LPCTSTR)file, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
		CFileDialog fileDlg(TRUE, _T(""), (LPCTSTR)NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,szFilter);
		fileDlg.m_ofn.lStructSize = 88;

		if(fileDlg.DoModal() != IDOK)	
		{
			return;
		}
		m_edit_file->SetText(fileDlg.GetPathName());
		m_opt_file->Selected(true);
		return;
	}
}

void CDlgCreateLangPackage::OnClickOK()
{
	UpdateDataUI(true);

	//����ؼ����ݵ������ļ�
	CXmlNodeUI node = uiApp.Config.GetRoot().child_auto(_T("Config")).child_auto(_T("DlgCreateLangPackage"));
	uiApp.Config.SaveControl(node, m_edit_path);
	uiApp.Config.SaveControl(node, m_opt_folder);
	uiApp.Config.SaveControl(node, m_edit_file);
	uiApp.Config.SaveControl(node, m_opt_file);

	// ��һ�����ĵ����԰����ƣ�����ÿ�����Ե����԰���
	// ���������
	// 1��ÿ�����԰����Լ����ļ��С�Լ�����������Ե�Ӣ�����ƣ��磺ChineseSimplified, English...
	// 2��ÿ�����԰�ֻ����һ���ļ��У�Լ�����������Ե�Ӣ�����ƣ�����res�·��õ�stringtable, ��ChineseSimplified.xml, English.xml��

	//////////////////////////////////////////////////////////////////////////
	//��һ�������
	if(m_bFolder)
	{
		CString strBasePath = m_sFolder;
		PathAddBackslash(strBasePath.GetBuffer(MAX_PATH)); //����β��б��
		strBasePath.ReleaseBuffer();
		PathRemoveFileSpec(strBasePath.GetBuffer()); //ȥ��β��б��
		strBasePath.ReleaseBuffer();

		CString sFolderName = strBasePath; //��ǰ�ļ�������
		PathStripPath(sFolderName.GetBuffer());
		sFolderName.ReleaseBuffer();

		CString sParentPath = strBasePath.Left(strBasePath.GetLength()-sFolderName.GetLength()); //���ļ���Ŀ¼

		PathAddBackslash(strBasePath.GetBuffer(MAX_PATH)); //����β��б�ܣ��ţ��ӻ�ȥ
		strBasePath.ReleaseBuffer();

		for (int i=0; i<GetMainWnd()->m_arrLangCode.size(); i++)
		{
			tagLanguageCode &code = GetMainWnd()->m_arrLangCode[i];

			CString newPath = CString(sParentPath) + code.sNameEn + _T('\\');
			if(newPath == strBasePath)
				continue;

// 			if(!PathFileExists(newPath))
// 			{
// 				CreateDirectory(newPath, NULL);
// 			}

			CopyFromPath(sFolderName, code.sNameEn, sParentPath);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	//�ڶ��������
	if(m_bFile)
	{
		CString strBaseFile = m_sFile;

		CString sFileFolder = strBaseFile;
		PathRemoveFileSpec(sFileFolder.GetBuffer());
		sFileFolder.ReleaseBuffer();
		if(sFileFolder.GetAt(sFileFolder.GetLength()-1) != _T('\\')) sFileFolder += _T('\\');

		for (int i=0; i<GetMainWnd()->m_arrLangCode.size(); i++)
		{
			tagLanguageCode &code = GetMainWnd()->m_arrLangCode[i];

			CString newFile = sFileFolder + code.sNameEn + _T(".xml");
			if(strBaseFile == newFile)
				continue;

			CFileFind finder;
			if(!finder.FindFile(newFile))
			{
				if(::CopyFile(strBaseFile, newFile, FALSE))
				{
					CMsgWndUI::InsertMsgV(_T("Copy new file: %s"), newFile);
				}
			}
			else //����ļ��Ѿ����ڣ�ֻ�������ݣ�����ֱ�Ӹ���
			{
				UpdateXmlFile(strBaseFile, newFile);
			}
		}
	}

	MessageBox(GetMainWnd()->GetHWND(), _T("�������"), _T(""), MB_OK);
	__super::OnClickOK();
}

void CDlgCreateLangPackage::CopyFromPath(LPCTSTR sBaseFolder, LPCTSTR newFolder, LPCTSTR sParentPath)
{
	if(!PathFileExists(CString(sParentPath) + newFolder))
	{
		CreateDirectory(CString(sParentPath) + newFolder, NULL);
	}

	CFileFind finder;
	BOOL bFind = finder.FindFile(CString(sParentPath) + sBaseFolder + ("\\*.*"));
	if(!bFind) return;
	while (bFind)
	{
		bFind = finder.FindNextFile();
		if(finder.IsDots())
			continue;

		CString FileName = finder.GetFileName();
		CString FilePath = finder.GetFilePath();
		if(finder.IsDirectory())
		{
			//ȡ�����·��
			CString s = CString(sParentPath) + sBaseFolder + ("\\");
			CString s1 = finder.GetFilePath();
			int n = s1.Find(s);
			CString s2 = s1.Right(s1.GetLength()-s.GetLength());
			CopyFromPath(CString(sBaseFolder) + _T('\\') + s2, CString(newFolder)+ _T('\\') + s2, sParentPath);
			continue;
		}

		CString sNewFilePath = CString(sParentPath) + newFolder + _T('\\') + FileName;
		if(!PathFileExists(sNewFilePath))
		{
			if(::CopyFile(finder.GetFilePath(), sNewFilePath, FALSE))
			{
				CMsgWndUI::InsertMsgV(_T("Copy new file: %s"), sNewFilePath);
			}
		}
		else //����ļ��Ѿ����ڣ�ֻ�������ݣ�����ֱ�Ӹ���
		{
			UpdateXmlFile(finder.GetFilePath(), sNewFilePath);
		}		
	}	
}

void CDlgCreateLangPackage::UpdateXmlFile(LPCTSTR sBaseFile, LPCTSTR sNewFile)
{
	CXmlDocumentUI xmlBase;
	xmlBase.load_file(sBaseFile);

	CXmlDocumentUI xmlNew;
	xmlNew.load_file(sNewFile);
	for (CXmlNodeUI nodeBase=xmlBase.child(_T("Language")).first_child(); nodeBase; nodeBase=nodeBase.next_sibling())
	{
		CDuiString name = nodeBase.name();
		CDuiString id = nodeBase.attribute(_T("id")).as_string();

		CXmlNodeUI nodeNew = xmlNew.child_auto(_T("Language")).find_child_by_attribute(name, _T("id"), id);
		if(!nodeNew)
		{
			nodeNew = xmlNew.child_auto(_T("Language")).append_copy(nodeBase);
			CMsgWndUI::InsertMsgV(_T("Append node: name=%s, id=%s. %s."), name, id, sNewFile);
		}					
	}
	xmlNew.save_to_default_file();
}