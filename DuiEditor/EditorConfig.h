#pragma once

//XML�༭�������ò���
struct tagEditorConfig 
{
	CString strXmlFontName;			//xml�༭����������
	int		nXmlFontSize;			//xml�༭�������С
	int		nXmlLineSpace;			//xml�༭���м��
	COLORREF crXmlBkColor;			//xml�༭������ɫ
	COLORREF crXmlSelBkColor;		//xml�༭��ѡ���ı�����ɫ
	COLORREF crXmlCaretLineBkColor;	//xml�༭�������б���ɫ

	COLORREF crDesignerBkColor;		//��ƽ���ı���ɫ
	BOOL bDesignerShowShadow;		//��ƽ����duilib������Ӱ
	CString strPropertyFile;		//ָ��duilib.xml��·�����������������������Ŀ¼��duilib.xml�������Ǿ���·����
	CString strAttachTestCommand;	//���Ӳ��Դ���ĳ��򣬿��԰���Ŀ�е�ִ�г���������
	int nControlTreeDeep;			//����ؼ���ʱ��Ĭ��չ���Ĳ�����
	BOOL bFilterPosWidthHeight;

	void CopyFrom(const tagEditorConfig &cfg)
	{
		strXmlFontName = cfg.strXmlFontName;
		nXmlFontSize = cfg.nXmlFontSize;
		nXmlLineSpace = cfg.nXmlLineSpace;
		crXmlBkColor = cfg.crXmlBkColor;
		crXmlSelBkColor = cfg.crXmlSelBkColor;
		crXmlCaretLineBkColor = cfg.crXmlCaretLineBkColor;

		crDesignerBkColor = cfg.crDesignerBkColor;
		bDesignerShowShadow = cfg.bDesignerShowShadow;
		strPropertyFile = cfg.strPropertyFile;
		strAttachTestCommand = cfg.strAttachTestCommand;
		nControlTreeDeep = cfg.nControlTreeDeep;
		bFilterPosWidthHeight = cfg.bFilterPosWidthHeight;
	}

	void LoadConfig(LPCTSTR filename)
	{
		xml.load_file(filename, pugi::parse_full);
		xml_node root = xml.child(_T("DuiEditor"));

		strXmlFontName = root.child(_T("XmlFontName")).text().as_string(_T("Courier New"));
		nXmlFontSize = root.child(_T("XmlFontSize")).text().as_int(14);
		nXmlLineSpace = root.child(_T("XmlLineSpace")).text().as_int(1);
		crXmlBkColor = root.child(_T("XmlBkColor")).text().as_int(RGB(255,255,255));
		crXmlSelBkColor = root.child(_T("XmlSelBkColor")).text().as_int(RGB(0xA0,0xCA,0xF0));
		crXmlCaretLineBkColor = root.child(_T("XmlCaretLineBkColor")).text().as_int(RGB(215,215,247));

		crDesignerBkColor = root.child(_T("DesignerBkColor")).text().as_int(RGB(0xF0, 0xF0, 0xF0));
		bDesignerShowShadow = root.child(_T("DesignerShowShadow")).text().as_bool();
		strPropertyFile = root.child(_T("PropertyFile")).text().as_string();
		strAttachTestCommand = root.child(_T("AttachTestCommand")).text().as_string();
		nControlTreeDeep = root.child(_T("ControlTreeDeep")).text().as_int(10);
		bFilterPosWidthHeight = root.child(_T("FilterPosWidthHeight")).text().as_bool();
	}

	void SaveConfig()
	{
		xml_node root = xml.child_auto(_T("DuiEditor"));

		root.child_auto(_T("XmlFontName")).text().set(strXmlFontName);
		root.child_auto(_T("XmlFontSize")).text().set(nXmlFontSize);
		root.child_auto(_T("XmlLineSpace")).text().set(nXmlLineSpace);
		root.child_auto(_T("XmlBkColor")).text().set((int)crXmlBkColor);
		root.child_auto(_T("XmlSelBkColor")).text().set((int)crXmlSelBkColor);
		root.child_auto(_T("XmlCaretLineBkColor")).text().set((int)crXmlCaretLineBkColor);

		root.child_auto(_T("DesignerBkColor")).text().set((int)crDesignerBkColor);
		root.child_auto(_T("DesignerShowShadow")).text().set(bDesignerShowShadow);
		root.child_auto(_T("PropertyFile")).text().set(strPropertyFile);
		root.child_auto(_T("AttachTestCommand")).text().set(strAttachTestCommand);
		root.child_auto(_T("ControlTreeDeep")).text().set(nControlTreeDeep);
		root.child_auto(_T("FilterPosWidthHeight")).text().set(bFilterPosWidthHeight);

		xml.save_to_default_file();
	}
private:
	xml_document xml;
};