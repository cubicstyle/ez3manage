// ChtFileInfo.h: interface for the CChtFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHTFILEINFO_H__265F96C1_3F3C_4659_8BAC_63D73A3A48EE__INCLUDED_)
#define AFX_CHTFILEINFO_H__265F96C1_3F3C_4659_8BAC_63D73A3A48EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>

typedef struct _CHT_DATA{
	CString		strFunction;
	CString		strSetup;		//����ָ������
	DWORD		dw_Address;		//��ַ
	DWORD		dw_Data;		//����
	BYTE		m_dataType;		//��������
	DWORD		loopcounter;	//�Ƿ�ѭ��
	BOOL		m_bUsePre;		//�ñ�����ʾ�������Ƿ�ͬǰһ��������һ���	
	_CHT_DATA	*pChtData;	
}CHT_DATA, *PCHT_DATA;
typedef CArray<PCHT_DATA,PCHT_DATA> CHT_DATA_ARRAY;

/*class CChtFileInfo����cht�ļ��Ķ�ȡ*/
class CChtFileInfo  
{
public:
	CChtFileInfo(CString str=_T(""));
	virtual ~CChtFileInfo();
	CList<PCHT_DATA,PCHT_DATA> m_GoldList;
	void DeleteBuffer();
	void ClearData();
private:
	CString m_strChtFileName;
	CString strName;
	CString strSystem;
	CString	strText;
	int			m_LineCounter;
	int			CounterEqualSign(CString strData);
	int			CountersemicolonSign(CString strData);
	void		Parse_Data(CHT_DATA_ARRAY &cht_data_array,CString strData);
	CHT_DATA	*Parse_Data1(CString strData);//û�зֺŵ����
	void		Parse_Data2(CHT_DATA_ARRAY &cht_data_array,CString strData);//�зֺŵ����
	CString		GetFunction(CString str);
public:
	void SetChtFileName(CString str);
	CString Getdescriptor(int index=0);//���ؽ���ָ����������
	CString GetSetUp(int index=0);
	CString GetName();
	CString GetSystem();
	CString GetText();
	void	GetData();
	CList<PCHT_DATA,PCHT_DATA> *ReturnList();//��listָ��ָ���������cht�ļ��еĽ���ָ���ݵ�����
public:
	CString ReadLine(int index=0);//��'['��'['֮�������
	int GetLineCounter();		//��������
	CString GetLastLine();
	BYTE	*pData;
	BYTE	*m_pData;
	DWORD	m_length;
	void RemoveAllItem();
};

#endif // !defined(AFX_CHTFILEINFO_H__265F96C1_3F3C_4659_8BAC_63D73A3A48EE__INCLUDED_)
