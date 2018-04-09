// DlgNandFormat.cpp : implementation file
//

#include "stdafx.h"
#include "new_ezmanage.h"
#include "DlgNandFormat.h"
#include "New_EZManageDlg.h"
#include ".\fat16\FileSys.h"
#include "SkinPlusPlus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNandFormat dialog
extern CString m_gStrMsgFormatDisk;			//��ʽ��EZ����
extern CString m_gStrMsgCapacity;				//����
extern CString m_gStrMsgFileSystem;			//�ļ�ϵͳ
extern CString m_gStrMsgAllocationUint;		//���䵥Ԫ��С
extern CString m_gStrMsgVolume;				//���
extern CString m_gStrMsgFormatItem;			//��ʽ��ѡ��
extern CString m_gStrMsgQuickFormat;			//��ʽ��ѡ��
extern CString m_gStrBeginFormat;				//��ʼ��ʽ��
extern CString m_gStrCancleFormat;				//ȡ��

CDlgNandFormat::CDlgNandFormat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNandFormat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNandFormat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bFormat = FALSE;
}


void CDlgNandFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNandFormat)
	DDX_Control(pDX, IDC_PROGRESS_NANDFORMAT, m_NandFormatCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNandFormat, CDialog)
	//{{AFX_MSG_MAP(CDlgNandFormat)
	ON_BN_CLICKED(IDC_BEGIN_FORMAT, OnBeginFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNandFormat message handlers



BOOL CDlgNandFormat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_gStrMsgFormatDisk);
	CButton *pBut; 
	pBut = (CButton *)GetDlgItem(IDC_NAND_SIZE);
	pBut->SetWindowText(m_gStrMsgCapacity);

	pBut = (CButton *)GetDlgItem(IDC_NAND_FILESYSTEM);
	pBut->SetWindowText(m_gStrMsgFileSystem);

	pBut = (CButton *)GetDlgItem(IDC_NAND_ALLOC);
	pBut->SetWindowText(m_gStrMsgAllocationUint);

	pBut = (CButton *)GetDlgItem(IDC_NAND_DISK_NAME);
	pBut->SetWindowText(m_gStrMsgVolume);

	pBut = (CButton *)GetDlgItem(IDC_FORMAT_SELECT);
	pBut->SetWindowText(m_gStrMsgFormatItem);
	
	pBut = (CButton *)GetDlgItem(IDC_FORMAR_QUICKLY);
	pBut->SetWindowText(m_gStrMsgQuickFormat);

	pBut = (CButton *)GetDlgItem(IDC_BEGIN_FORMAT);
	pBut->SetWindowText(m_gStrBeginFormat);

	pBut = (CButton *)GetDlgItem(IDCANCEL);
	pBut->SetWindowText(m_gStrCancleFormat);


extern DWORD g_dwNandSize;
	CComboBox *pBox=(CComboBox *)GetDlgItem(IDC_NAND_SIZECOMBO);
	if(g_dwNandSize == 128*1024)
		pBox->SetCurSel(0);
	else if(g_dwNandSize == 128*1024*2)
		pBox->SetCurSel(1);
	else  if(g_dwNandSize == 128*1024*4)
		pBox->SetCurSel(2);	
	else if(g_dwNandSize == 128*1024*8)
		pBox->SetCurSel(3);	
	pBox=(CComboBox *)GetDlgItem(IDC_NAND_FILESYS_COMBO);
	pBox->SetCurSel(0);
	pBox=(CComboBox *)GetDlgItem(IDC_NAND_ALLOC_COMBO);
	pBox->SetCurSel(0);
	CButton *pButton = (CButton *)GetDlgItem(IDC_FORMAR_QUICKLY);
	if(pButton)
		pButton->SetCheck(TRUE);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_NAND_DISK_NAMEEDIT);
	if(pEdit)
		pEdit->SetWindowText("EZ_Disk");
	m_pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
//	m_EventHandle = CreateEvent(NULL,FALSE,FALSE,"Wait for formant Nand End");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNandFormat::OnBeginFormat() 
{
	// TODO: Add your control notification handler code here
	m_bFormat = TRUE;
	pTWThreadFormatNand = AfxBeginThread(TWThreadFormatNand,
										this);
//	WaitForSingleObject(m_EventHandle,INFINITE);
//	AfxMessageBox("��ʽ������");
}

UINT CDlgNandFormat::TWThreadFormatNand( LPVOID pParam )
{
	CDlgNandFormat  *pDlg = (CDlgNandFormat*)pParam ;
	pDlg->TWThreadFormatNand();
	AfxMessageBox("��ʽ������");
	return 1;
}
UINT CDlgNandFormat::TWThreadFormatNand()
{
	m_pDlg->KillTimer(IDENTIFY_CART_TIMER);
	m_pDlg->m_Tab.EnableWindow(FALSE);
	CButton *pBut = (CButton *)GetDlgItem(IDC_FORMAR_QUICKLY);
	BOOL bQuick = pBut->GetCheck();
//	ResetEvent(m_EventHandle);
extern CFileSys fs; 
extern DWORD g_dwNandFreeSpace;
	CString strVolume;
	GetDlgItem(IDC_NAND_DISK_NAMEEDIT)->GetWindowText(strVolume);
	fs.FormatCart(&m_NandFormatCtrl,bQuick,strVolume);
	fs.CartInit();
	if(!fs.Initialize())
	{
		fs.ClearCartInit();
		AfxMessageBox("EZ���̷�������,�����¸�ʽ��");
		return -1;
	}
	g_dwNandFreeSpace = fs.GetFreeNandSpace();
	fs.fat_mkdir("\\saver");
	fs.Uninitialize();
	fs.ClearCartInit();
	int nLower,nUpper;
	m_NandFormatCtrl.GetRange(nLower,nUpper);
	m_NandFormatCtrl.SetPos(nUpper);
	m_pDlg->m_Tab.EnableWindow(TRUE);
	m_pDlg->SetTimer(IDENTIFY_CART_TIMER,1000,NULL);
	m_pDlg->m_PageDisk.InitDiskList();
	m_pDlg->ShowNandUseInfo(NAND_TOTAL_SIZE,g_dwNandFreeSpace);
//	SetEvent(m_EventHandle);
	return 1;
}
