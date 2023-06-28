#pragma once
#ifndef __DUISTRING_H__
#define __DUISTRING_H__


#ifdef __GNUC__
//ת��д
inline char* strupr(char* src)
{
	while (*src != '\0')
	{
		if (*src > 'a' && *src <= 'z') {
			//*src -= 32;
			*src = static_cast<char>(*src - 32);
		}
		src++;
	}
	return src;
}

//תСд
inline char* strlwr(char* src)
{
	while (*src != '\0')
	{
		if (*src > 'A' && *src <= 'Z') {
			//*src += 32;
			*src = static_cast<char>(*src + 32);
		}
		src++;
	}
	return src;
}

inline int MulDiv(int nNumber, int nNumerator, int nDenominator)
{
	long long x = nNumber;
	x *= nNumerator;
	x = (x + nDenominator - 1) / nDenominator;
	return static_cast<int>(x);
}

inline LPTSTR CharNext(LPCTSTR lpsz)
{
	return (LPTSTR)lpsz + 1;
}
#endif

namespace DuiLib
{
	/////////////////////////////////////////////////////////////////////////////////////
	// CDuiString�ڴ�ذ汾
	//
	class UILIB_API CDuiString
	{
	public:
		CDuiString();
		CDuiString(const TCHAR ch);
		CDuiString(const CDuiString& src);
		CDuiString(LPCTSTR lpsz, int nLen = -1);
		CDuiString(int int_to_string);
		~CDuiString();

		//���û���������
		void SetBufferLength(int iLength);

		//��ȡ���������ȣ�����ֵ���ܴ������õĳ���
		int GetBufferLength();

		//�����ַ���������, nMinBufferLength>0ʱ����ǰ������С��nMinBufferLength�����·��仺������
		//û�ж�Ӧ��ReleaseBuffer().
		LPTSTR GetBuffer(int nMinBufferLength = -1);

		void Empty();
		int GetLength() const;
		bool IsEmpty() const;
		void Append(LPCTSTR pstr);
		void Assign(LPCTSTR pstr, int nLength = -1);
		LPCTSTR GetData() const;

		void SetAt(int nIndex, TCHAR ch);
		TCHAR GetAt(int nIndex) const;
		operator LPCTSTR() const;

		TCHAR operator[] (int nIndex) const;
		const CDuiString& operator=(const CDuiString& src);
		const CDuiString& operator=(const TCHAR ch);
		const CDuiString& operator=(LPCTSTR pstr);
#ifdef _UNICODE
		const CDuiString& operator=(LPCSTR lpStr);
		const CDuiString& operator+=(LPCSTR lpStr);
#else
		const CDuiString& operator=(LPCWSTR lpwStr);
		const CDuiString& operator+=(LPCWSTR lpwStr);
#endif
		CDuiString operator+(const CDuiString& src) const;
		CDuiString operator+(LPCTSTR pstr) const;
		const CDuiString& operator+=(const CDuiString& src);
		const CDuiString& operator+=(LPCTSTR pstr);
		const CDuiString& operator+=(const TCHAR ch);

		bool operator == (LPCTSTR str) const;
		bool operator != (LPCTSTR str) const;
		bool operator <= (LPCTSTR str) const;
		bool operator <  (LPCTSTR str) const;
		bool operator >= (LPCTSTR str) const;
		bool operator >  (LPCTSTR str) const;

		int Compare(LPCTSTR pstr) const;
		int CompareNoCase(LPCTSTR pstr) const;

		void MakeUpper();
		void MakeLower();

		CDuiString Left(int nLength) const;
		CDuiString Mid(int iPos, int nLength = -1) const;
		CDuiString Right(int nLength) const;

		int Find(TCHAR ch, int iPos = 0) const;
		int Find(LPCTSTR pstr, int iPos = 0) const;
		int ReverseFind(TCHAR ch) const;
		int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

		int __cdecl AppendFormat(LPCTSTR pstrFormat, ...);
		int __cdecl Format(LPCTSTR pstrFormat, ...);
		int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

		int __cdecl InnerFormat(LPCTSTR pstrFormat, va_list Args);

	protected:
		void AllocString(int strlength);
		void FreeString();
	protected:
		LPTSTR m_pstr;
	};

	class UILIB_API CBufferUI
	{
	public:
		CBufferUI();
		~CBufferUI();

		void Reset();

		LPBYTE GetBuffer();
		int GetLength();

		int AddBuffer(const void *buffer, int len);

	protected:
		void Alloc(UINT size);
	protected:
		BYTE *_buffer;
		int _bufferLen;
	};
	//////////////////////////////////////////////////////////////////////////
	//
	//
	class UILIB_API StringConverterUI
	{
	public:
		StringConverterUI();
		#ifdef WIN32
		StringConverterUI(UINT codepage);
		#endif //#ifdef WIN32
		~StringConverterUI();

	public:
		LPCTSTR A_to_T(const void *buffer, int bufferlen = -1);

		LPCSTR T_to_A(const void *buffer, int bufferlen = -1);

		LPCTSTR W_to_T(const void *buffer, int bufferlen = -1);

		LPCWSTR T_to_W(const void *buffer, int bufferlen = -1);

		LPCTSTR utf8_to_T(const void *buffer, int bufferlen = -1);

		LPCSTR T_to_utf8(const void *buffer, int bufferlen = -1);

		LPCWSTR A_to_W(const void *buffer, int bufferlen = -1);

		LPCSTR W_to_A(const void *buffer, int bufferlen = -1);

		LPCSTR A_to_utf8(const void *buffer, int bufferlen = -1);

		LPCSTR utf8_to_A(const void *buffer, int bufferlen = -1);

		LPCSTR W_to_utf8(const void *buffer, int bufferlen = -1);

		LPCWSTR utf8_to_W(const void *buffer, int bufferlen = -1);

	protected:
		void Alloc(UINT size);
		void Release();
	private:
		BYTE *_block;
#ifdef WIN32
		UINT m_cp;
#else
		CDuiString m_from;
		CDuiString m_to;
#endif // #ifdef WIN32
	};


#define UISTRING_CONVERSION					StringConverterUI _UISTRINGCONVERT_TEMP_INSTANCE_;
#define UISTRING_CONVERSION_EX(codepage)	StringConverterUI _UISTRINGCONVERT_TEMP_INSTANCE_(codepage);

#define UIA2T(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.A_to_T(p))
#define UIA2W(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.A_to_W(p))
#define UIA2UTF8(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.A_to_utf8(p))

#define UIW2T(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.W_to_T(p))
#define UIW2A(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.W_to_A(p))
#define UIW2UTF8(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.W_to_utf8(p))

#define UIT2A(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.T_to_A(p))
#define UIT2W(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.T_to_W(p))
#define UIT2UTF8(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.T_to_utf8(p))

#define UIUTF82T(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.utf8_to_T(p))
#define UIUTF82A(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.utf8_to_A(p))
#define UIUTF82W(p)	(_UISTRINGCONVERT_TEMP_INSTANCE_.utf8_to_W(p))

}// namespace DuiLib

#endif // __DUISTRING_H__
