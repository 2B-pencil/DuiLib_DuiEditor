#ifndef __UISCRIPT_H__
#define __UISCRIPT_H__

#pragma once

namespace DuiLib {
	/////////////////////////////////////////////////////////////////////////////////////
	//
	//�ű�ִ�������ģ��ű�����ʵ��
	class UILIB_API IScriptContext
	{
	public:
		virtual ~IScriptContext(void) {}

		//������ں���, ����������
		virtual int SetFunByName(LPCTSTR lpszFunName) = 0;
		//������ں���, ������������
		virtual int SetFunByDecl(LPCTSTR lpszFunDecl) = 0;

		//�������
		virtual int	SetArgByte(UINT arg, BYTE value) = 0;
		virtual int	SetArgWord(UINT arg, WORD value) = 0;
		virtual int	SetArgDWord(UINT arg, DWORD value) = 0;
		virtual int	SetArgFloat(UINT arg, float value) = 0;
		virtual int	SetArgDouble(UINT arg, double value) = 0;
		virtual int	SetArgAddress(UINT arg, void *addr) = 0;
		virtual int	SetArgObject(UINT arg, void *obj) = 0;
		virtual void *GetAddressOfArg(UINT arg) = 0;

		//�ű�ִ�г�ʱʱ�䣬����, dwTimeOut < 0�����жϳ�ʱ��Ĭ��ֵ��5�롣
		virtual void SetTimeOut(int dwTimeOut) = 0;

		//ִ�нű�
		virtual int Execute() = 0;

		//��ȡ����ֵ
		virtual BYTE	GetReturnByte() = 0;
		virtual WORD	GetReturnWord() = 0;
		virtual DWORD	GetReturnDWord() = 0;
		virtual float	GetReturnFloat() = 0;
		virtual double	GetReturnDouble() = 0;
		virtual void *	GetReturnAddress() = 0;
		virtual void *	GetReturnObject() = 0;
		virtual void *	GetAddressOfReturnValue() = 0;
	};

	class UILIB_API IScriptManager
	{
	public:
		//����ű��ļ�
		virtual bool AddScriptFile(LPCTSTR pstrFileName) = 0;

		//����ű�����
		virtual bool AddScriptCode(LPCTSTR pstrCode) = 0;

		//����ű��� һ���Լ���ű��ļ���ϣ�Ȼ��ֻ�ܱ���һ�Ρ�
		virtual bool CompileScript() = 0;

		//����ִ��������
		virtual IScriptContext *CreateContext() = 0;

		//ɾ��ִ��������
		virtual void ReleaseContext(IScriptContext *ctx) = 0;
	};
	typedef IScriptManager* (__stdcall *CREATE_SCRIPT_ENGINE_INSTANCE)();
	typedef void (__stdcall *DELETE_SCRIPT_ENGINE_INSTANCE)(IScriptManager *pEngine);

	class UILIB_API CAutoScriptContext
	{
	public:
		CAutoScriptContext(IScriptManager *mgr);
		~CAutoScriptContext();

		IScriptContext* operator->() const throw();
		bool operator!() const throw();
	protected:
		IScriptManager *mgr;
		IScriptContext *ctx;
	private:
	};
} // namespace DuiLib

#endif // __UISCRIPT_H__
