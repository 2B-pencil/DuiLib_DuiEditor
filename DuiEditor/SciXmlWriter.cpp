#include "StdAfx.h"
#include "SciXmlWriter.h"


CSciXmlWriter::CSciXmlWriter(CSciWnd *pSciWnd) : m_pSciWnd(pSciWnd)
{
}


CSciXmlWriter::~CSciXmlWriter(void)
{
}

void CSciXmlWriter::print(xml_node node)
{
	m_pSciWnd->sci_ClearTextAll();
	m_strTempBuffer.Empty();

	if(node)
	{
		int row = 0;
		int depth = 0;
		node_output(node, row, depth);
	}

	m_pSciWnd->sci_SetSavePoint();
	//m_pSciWnd->sci_EmptyUndoBuffer(); //��������ʷ��¼��xmlд��ʱ���Ϳ������޺�����
}

void CSciXmlWriter::write(LPCTSTR text)
{
	m_strTempBuffer += text;
}

void CSciXmlWriter::write(TCHAR text)
{
	m_strTempBuffer += text;
}

void CSciXmlWriter::flush()
{
	LSSTRING_CONVERSION;
	const char *pstring = LST2UTF8(m_strTempBuffer);
	m_pSciWnd->SendEditor(SCI_APPENDTEXT, strlen(pstring), (LPARAM)pstring);
	m_strTempBuffer.Empty();
}

void CSciXmlWriter::node_output(xml_node root, int &row, int depth)
{
	xml_node node = root;

	if(node.type() == node_comment)
	{
		node_output_comment(node, row, depth);
		flush();
		return;
	}

	//����ڵ��Ӧ�����ı���
	node.set_row(row);

	for (int i=0; i<depth; i++)
		write(_T("\t"));
	write(_T("<"));
	write(node.name());
	
	//��ӡ����
	node_output_attribute(node);

	if(!node.first_child())
	{
		write(_T(" />\n"));
		row++;
	}
	else
	{
		if(node.first_attribute())
			write(_T(" >\n"));
		else
			write(_T(">\n"));
		row++;
	}

	//��ӡ��һ�У�flushһ��
	flush();

	//��ӡ�ӽڵ�
	if(node.first_child()) depth++;
	for (xml_node nodeChild=node.first_child(); nodeChild; nodeChild=nodeChild.next_sibling())
	{
		node_output(nodeChild, row, depth);
	}
	if(node.first_child()) depth--;

	//��ӡ�ֵܽڵ�
	while (node != root)
	{
		if(node.next_sibling())
			node_output(node.next_sibling(), row, depth);
	}

	//���ӽڵ㣬���ӡ��β </xxxx>
	if(node.first_child())
	{
		for (int i=0; i<depth; i++)
			write(_T("\t"));

		write(_T("</"));
		write(node.name());
		write(_T(">\n"));
		row++;
	}

	//��ӡ��һ�У�flushһ��
	flush();
}

void CSciXmlWriter::node_output_attribute(xml_node node)
{
	for (xml_attribute attr=node.first_attribute(); attr; attr=attr.next_attribute())
	{
		write(_T(" "));
		write(attr.name());
		write(_T("=\""));
		text_output(attr.value()); 
		write(_T("\""));
	}
}

void CSciXmlWriter::node_output_comment(xml_node node, int &row, int depth)
{
	if(!node) return;

	for (int i=0; i<depth; i++)
		write(_T("\t"));
	write(_T("<!--"));

	CString strValue = node.value();
	write(strValue);

	//strValue�м��У�
	int pos = 0;
	for (;;)
	{
		int posx = strValue.Find('\n', pos);
		if(posx < 0)
			break;

		row++;
		pos = posx + 1;
	}

	for (int i=0; i<depth; i++)
		write(_T("\t"));
	write(_T("-->\n"));
	row++;
}

void CSciXmlWriter::text_output(LPCTSTR text)
{
	LPCTSTR s = text;

	//����Ƿ���ת���ַ�
	BOOL IsEscapeChar = FALSE;
	while (*s)
	{
		switch (*s)
		{
		case 0: break;
		case '&':
			IsEscapeChar = TRUE;
			break;
		case '<':
			IsEscapeChar = TRUE;
			break;
		case '>':
			IsEscapeChar = TRUE;
			break;
		case '"':
			IsEscapeChar = TRUE;
			break;
		default:
			break;
		}

		if(IsEscapeChar)
			break;

		++s;
	}

	if(!IsEscapeChar)
	{
		write(text);
		return;
	}

	s = text;
	while (*s)
	{
		switch (*s)
		{
		case 0: break;
		case '&':
			write(_T("&amp;"));
			++s;
			break;
		case '<':
			write(_T("&lt;"));
			++s;
			break;
		case '>':
			write(_T("&gt;"));
			++s;
			break;
		case '"':
			write(_T("&quot;"));
			++s;
			break;
		default: 
			write(*s);
			++s;
			break;
		}
	}
}