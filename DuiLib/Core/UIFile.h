#ifndef __UIFILE_H__
#define __UIFILE_H__

#pragma once

namespace DuiLib {
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CUIFile
	{
	public:
// 		enum OpenFlags {
// 			modeRead =         (int) 0x00000,
// 			modeWrite =        (int) 0x00001,
// 			modeReadWrite =    (int) 0x00002,
// 			modeCreate =       (int) 0x01000,
// 			modeNoTruncate =   (int) 0x02000,	//����ļ����ڣ�׷�����ݣ�����ļ������ڴ������ļ���
// 			typeBinary =       (int) 0x08000,
// 		};
		enum CharSet {
			FILE_ANSI =  (int) 0x00000,
			FILE_UTF8 =  (int) 0x00001,
		};
	public:
		CUIFile();
		~CUIFile();

		LPBYTE GetData() const;
		DWORD  GetSize() const;
		void Empty();

		BOOL LoadFile(const STRINGorID &bitmap, LPCTSTR type=NULL, HINSTANCE instance=NULL);
		BOOL LoadFile(LPCTSTR pStrImage, LPCTSTR type=NULL, HINSTANCE instance=NULL);
#ifdef WIN32
		BOOL LoadFile(UINT nID, LPCTSTR type=NULL, HINSTANCE instance=NULL);
#endif

		//BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags);
		BOOL Open(LPCTSTR lpszFileName, LPCTSTR mode);
		void Close();
		UINT Read(void* lpBuf, UINT nCount);
		UINT Write(const void* lpBuf, UINT nCount);
		UINT WriteV(const char* lpszFormat, ...);
		UINT WriteV(const wchar_t* lpszFormat, ...);
		UINT WriteLine(const char* lpszFormat, ...);
		UINT WriteLine(const wchar_t* lpszFormat, ...);
		UINT GetFileLength() const;
		int SeekToEnd();
		void SeekToBegin();
		int Seek(UINT lOff, UINT nFrom);
		BOOL IsEOF();
		void SetCharSet(CUIFile::CharSet charset);
	protected:
		BOOL __LoadFromSkinPath(const STRINGorID& bitmap, LPCTSTR type, HINSTANCE instance);
		BOOL __LoadFromZip(const STRINGorID& bitmap, LPCTSTR type, HINSTANCE instance);
#ifdef WIN32
		BOOL __LoadFromResource(const STRINGorID& bitmap, LPCTSTR type, HINSTANCE instance);
#endif
		BOOL __LoadFromDiskPath(LPCTSTR sFilePath);
	private:
		LPBYTE m_pData; 
		DWORD m_dwSize;

		FILE *m_fp;
		UINT m_charset;

	// --- static functions --
	public:
		static BOOL CopyFile(LPCTSTR sSourceFilePathName, LPCTSTR sDestFilePathName, BOOL bFailIfExists); //�����ļ�
		static BOOL DeleteFile(LPCTSTR sFilePathName); //ɾ���ļ�
		static BOOL IsFileExist(LPCTSTR sFilePathName);	//�ļ��Ƿ����
		
		static BOOL CreateDirectory(LPCTSTR sPathName, BOOL bCreateMultiLevelDirectory = FALSE); //����Ŀ¼
		static BOOL RemoveDirectory(LPCTSTR sPathName, BOOL bDeleteNonEmptyDirectory = FALSE); //ɾ��Ŀ¼
		static BOOL IsDirectoryExist(LPCTSTR sPathName); //Ŀ¼�Ƿ����
	};
	
	class UILIB_API CUIFileFind
	{
	public:
		CUIFileFind();
		~CUIFileFind();

		BOOL FindFile(LPCTSTR lpFileName);
		BOOL FindNextFile();
		void FindClose();

		//��ȡ�ҵ����ļ������ƣ�������չ����
		CDuiString GetFileName();

		//��ȡ�ҵ����ļ�������·���� ����·�����ļ�������չ��
		CDuiString GetFilePath();

// 		//��ȡ�ҵ����ļ������ƣ�û�а�����չ����
// 		CDuiString GetFileTitleName();
// 
// 		//��ȡ�ҵ����ļ�����չ��
// 		CDuiString GetFileExtName();

		//ȷ���ҵ����ļ��������Ƿ�������� "." �� "..."����ָʾʵ������һ��Ŀ¼��
		BOOL IsDots();

		//ȷ���ҵ����ļ��Ƿ�ΪĿ¼
		BOOL IsDirectory();

	protected:
		void MakeFullPath(CDuiString& sPath);
	private:
		CDuiString m_strRoot;
		BOOL m_bFindInZip;

#ifdef WIN32
		HANDLE m_hFind;
		void* m_pFoundInfo;
		void* m_pNextInfo;
#elif defined __linux__
		DIR* m_dir;
		struct dirent* m_dirFoundInfo;
		struct dirent* m_dirNextInfo;

		struct dirent** m_scandirList;
		int m_scandirCount;
		int m_scandirIterator;
#elif defined __APPLE__
        DIR* m_dir;
        struct dirent* m_dirFoundInfo;
        struct dirent* m_dirNextInfo;

        struct dirent** m_scandirList;
        int m_scandirCount;
        int m_scandirIterator;
#endif
	};
	
} // namespace DuiLib

#endif // __UIFILE_H__
