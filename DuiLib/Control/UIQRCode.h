#pragma once

namespace DuiLib
{

class CQRCodeUI : public CDynamicLayoutUI
{
	DECLARE_DUICONTROL(CQRCodeUI)
public:
	CQRCodeUI(void);
	virtual ~CQRCodeUI(void);

	virtual LPCTSTR GetClass() const override;
	virtual LPVOID GetInterface(LPCTSTR pstrName) override;

	//����ȼ�
	void SetQrLevel(int nValue);
	int GetQrLevel() const;

	//�汾
	void SetQrVersion(int nValue);
	int GetQrVersion() const;

	//����ȼ�
	void SetQrMarkNo(int nValue);
	int GetQrMarkNo() const;

	//ͼ���С
	void SetQrSize(int nValue);
	int GetQrSize() const;

	//�߾�
	void SetQrMargin(int nValue);
	int GetQrMargin() const;

	//���ö�ά�����ݣ���GetText()Ϊ��ʱ��Ч��
	void SetQrCodeText(LPVOID pData, int len);

	//��ά���ı��ַ������룬��GetText()��Ϊ��ʱ��Ч��
	void SetQrCodeEncoding(LPCTSTR sEncoding);

	virtual void SetPos(RECT rc, bool bNeedInvalidate = true) override;
	virtual void PaintText(UIRender *pRender) override;

	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;

protected:
	void MakeQrImage();
protected:
	//����ȼ�
	int m_qrLevel;

	//��ά��汾
	int m_qrVersion;

	//����ȼ�
	int m_qrMarkNo;

	//ͼ�δ�С
	int m_qrSize;

	//��Ե��С
	int m_qrMargin;

	CDuiString m_sEncoding;

	CBufferUI m_qrText;
	CDuiRect m_rcCode;
	CStdRefPtr<UIRender> m_qrRender;
};

}
