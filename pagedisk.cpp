// PageDisk.cpp : implementation file
//

#include "stdafx.h"
#include "New_EZManage.h"
#include "PageDisk.h"
#include ".\fat16\FileSys.h"
#include <afxtempl.h>
#include "New_EZManageDlg.h"
#include "DlgNandFormat.h"
#include "SkinPlusPlus.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageDisk dialog

extern CString m_gStrdiskPage;					//1G Bits EZ-Disk ����
extern CString m_gStrDiskName;					//����
extern CString m_gStrDiskSize;					//��С
extern CString m_gStrDiskType;					//����
extern CString m_gStrDiskModifyData;			//�޸�����
extern CString m_gStrAttribute;				//����
extern CString m_gStrDiskReName;				//������
extern CString m_gStrDiskRead;					//���ļ�
extern CString m_gStrDiskDelFile;				//ɾ���ļ�
extern CString m_gStrDiskPreFolder;			//���ϼ�Ŀ¼
extern CString m_gStrDiskCreateFolder;			//�����ļ���
extern CString m_gStrDiskDelFolder;			//ɾ���ļ���
extern CString m_gStrDiskFormatDisk;			//��ʽ������
extern CString m_gStrDiskrefresh;				//ˢ�´���
//[MsgInfo]
extern CString m_gStrMsgReading	;					//���ڶ�EZ-Disk...
extern CString m_gStrMsgReadEnd;//=��EZ-Disk����
extern CString m_gStrMsgCation;//=��ʾ
extern CString m_gStrMsgNoWrited;//=δ��¼
extern CString m_gStrMsgWrited;//=����¼
extern CString m_gStrMsgUse;//=Use
extern CString m_gStrMsgLeft;//=ʣ��
extern CString m_gStrMsgReserve;//=����
extern CString m_gStrMsgFolder;//�ļ���
extern CString m_gStrMsgNoCart;//=û���ҵ�EZ3��
extern CString m_gStrMsgEZDisk;//=EZ����
extern CString m_gStrMsgInstallOS;//=���ڰ�װEZ3����ϵͳ...
extern CString m_gStrMsgInstallOSEnd;//=EZ3����ϵͳ��װ���
extern CString m_gStrMsgNoEnough;//=û���㹻��Flash ROM�ռ�
extern CString m_gStrMsgIncalideFile;//=��Ч��ROM�ļ�,������ӵ�Flash��
extern CString m_gStrMsgSelectFolder;//=��ѡ�񱾵��ļ�·��
extern CString m_gStrMsgSlectBackRom;//=��ѡ�񱸷ݵ�ROM
extern CString m_gStrMsgErrorBackRom;//=����ı���ROM
extern CString m_gStrMsgBackRomEnd;//=����ROM����
extern CString m_gStrMsgFormatNorCation;//=��ʽ��256M Bits Flash����ʧ��������
extern CString m_gStrMsgFormatingNor;//=���ڸ�ʽ��256Mfalsh��...
extern CString m_gStrMsgFormatNorEnd;//=��ʽ��256Mfalsh����
extern CString m_gStrMsgErasing;//=���ڲ���
extern CString m_gStrMsgWriting;//=����д...
extern CString m_gStrMsgWriteEnd;//=��¼����
extern CString m_gStrMsgCreatingFolder;//=���ڴ���Ŀ¼...
extern CString m_gStrMsgCreateFolderOK;//=����Ŀ¼�ɹ�
extern CString m_gStrMsgDeletingFolder;//=����ɾ��Ŀ¼...
extern CString m_gStrMsgDelSaveCation;//=saver�ļ��в��ܸ���
extern CString m_gStrMsgEnterFileName;//=������Ϸ����ļ���
extern CString m_gStrMsgSameCation;//=����,�����޸��ļ���
extern CString m_gStrMsgDelFolderEnd;//=ɾ��Ŀ¼��������
extern CString m_gStrMsgReadFileEnd;//=���ļ�����
extern CString m_gStrMsgSelectFile;//=��ѡ���ɾ���ļ�
extern CString m_gStrMsgDeletingFile;//=����ɾ���ļ�...
extern CString m_gStrMsgIsDelFile;//=ȷ��ɾ���ļ�
extern CString m_gStrMsgDleFileOK;//=ɾ���ļ�����
extern CString m_gStrMsgCompressing;//=����ѹ������...
extern CString m_gStrMsgFormatcation;//=EZ����û�и�ʽ��,�밴ȷ����ʽ��
CPageDisk::CPageDisk(CWnd* pParent /*=NULL*/)
	: CDialog(CPageDisk::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageDisk)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strNandDiskPath = "\\";
	m_pArray = new CStringArray;
	m_pArray->RemoveAll();
}


void CPageDisk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageDisk)
	DDX_Control(pDX, IDC_LIST1, m_DiskListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageDisk, CDialog)
	//{{AFX_MSG_MAP(CPageDisk)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_NAND_RENAME, OnButtonNandRename)
	ON_BN_CLICKED(IDC_BUTTON_NAND_READ, OnButtonNandRead)
	ON_BN_CLICKED(IDC_BUTTON_NAND_DELETE, OnButtonNandDelete)
	ON_BN_CLICKED(IDC_BUTTON_NAND_BACKDIR, OnButtonNandBackdir)
	ON_BN_CLICKED(IDC_BUTTON_NAND_CREATEDIR, OnButtonNandCreatedir)
	ON_BN_CLICKED(IDC_BUTTON_NAND_DELETEDIR, OnButtonNandDeletedir)
	ON_BN_CLICKED(IDC_BUTTON_NAND_FORMAT, OnButtonNandFormat)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST1, OnBeginlabeleditList1)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, OnEndlabeleditList1)
	ON_BN_CLICKED(IDC_BUTTON_NAND_REFRESH, OnButtonNandRefresh)
	ON_WM_DESTROY()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageDisk message handlers

BOOL CPageDisk::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);

	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(false, &rc); 

	MoveWindow(&rc);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_LISTCTRL);
	m_ImageListctrl.Create(16, 16, ILC_COLOR24 |ILC_MASK, 3, 1);
	m_ImageListctrl.Add(&bitmap, RGB(0,255,0));

	m_DiskListCtrl.SetImageList(&m_ImageListctrl, LVSIL_SMALL   );
	m_DiskListCtrl.InsertColumn(0, m_gStrDiskName,   LVCFMT_LEFT, 150);
	m_DiskListCtrl.InsertColumn(1, m_gStrDiskSize,   LVCFMT_LEFT, 100);
	m_DiskListCtrl.InsertColumn(2, m_gStrDiskType,   LVCFMT_LEFT, 100);
	m_DiskListCtrl.InsertColumn(3, m_gStrDiskModifyData,   LVCFMT_LEFT, 150);
	m_DiskListCtrl.InsertColumn(4, m_gStrAttribute,   LVCFMT_LEFT, 50);

	CButton *pBut = NULL;
	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_RENAME);
	pBut->SetWindowText(m_gStrDiskReName);

	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_READ);
	pBut->SetWindowText(m_gStrDiskRead);

	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_DELETE);
	pBut->SetWindowText(m_gStrDiskDelFile);

	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_BACKDIR);
	pBut->SetWindowText(m_gStrDiskPreFolder);

	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_CREATEDIR);
	pBut->SetWindowText(m_gStrDiskCreateFolder);

	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_DELETEDIR);
	pBut->SetWindowText(m_gStrDiskDelFolder);

	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_FORMAT);
	pBut->SetWindowText(m_gStrDiskFormatDisk);

	pBut = (CButton *)GetDlgItem(IDC_BUTTON_NAND_REFRESH);
	pBut->SetWindowText(m_gStrDiskrefresh);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageDisk::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	CRect r;
	GetClientRect(&r);
	int width = r.Width();
	int height = r.Height();
	
	CButton *pButton=NULL;
	if(m_DiskListCtrl)
	{
		m_DiskListCtrl.MoveWindow(0,0,width,height/10*8);
		m_DiskListCtrl.Invalidate(TRUE);
	}
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_RENAME);
	if(pButton)
	{
		pButton->MoveWindow(0,height/10*8+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}
		
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_READ);
	if(pButton)
	{
		pButton->MoveWindow(width/4,height/10*8+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}
		
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_DELETE);
	if(pButton)
	{
		pButton->MoveWindow(width/4*2,height/10*8+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}
		
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_BACKDIR);
	if(pButton)
	{
		pButton->MoveWindow(width/4*3,height/10*8+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}

		
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_CREATEDIR);
	if(pButton)
	{
		pButton->MoveWindow(0,height/10*9+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}
		
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_DELETEDIR);
	if(pButton)
	{
		pButton->MoveWindow(width/4,height/10*9+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}
		
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_FORMAT);
	if(pButton)
	{
		pButton->MoveWindow(width/4*2,height/10*9+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_NAND_REFRESH);
	if(pButton)
	{
		pButton->MoveWindow(width/4*3,height/10*9+height/20,width/4,height/20);
		pButton->Invalidate(TRUE);
	}
	
	m_strReOldName.Empty();
}
void CPageDisk::InitDiskList()
{
	FILE_ATTRIBUTE file_attribute;
	m_DiskListCtrl.DeleteAllItems();
	CString str = "saver";
	file_attribute.f_attribute = 0x10;
	memset(file_attribute.f_name,0,32);
	memcpy(file_attribute.f_name,str.GetBuffer(5),5);
	str.ReleaseBuffer(5);
	GetLocalTime (&file_attribute.filetime);
	AddItemToListCtrl(file_attribute);
	m_strNandDiskPath = "\\";

}
void CPageDisk::InitDisk()
{
	m_DiskListCtrl.DeleteAllItems();
	char name[256];
	_STAT stat;
	CString str;
	LPTSTR pStr=NULL;
	typedef CArray<FILE_ATTRIBUTE,FILE_ATTRIBUTE> FILELIST;
	FILE_ATTRIBUTE file_arribute;
	FILELIST file_list;
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)this->GetTopLevelParent();
	pDlg->KillTimer(IDENTIFY_CART_TIMER);
extern CFileSys fs;
extern DWORD g_dwNandFreeSpace;
	fs.CartInit();
	if(!fs.Initialize())
	{
		fs.ClearCartInit();
		//��ʽ������
		if(IDYES == MessageBox(m_gStrMsgFormatcation,NULL,MB_YESNO))
		{
			CDlgNandFormat DlgNandFormat;
			DlgNandFormat.DoModal();
		}
		return ;
	}
	g_dwNandFreeSpace = fs.GetFreeNandSpace();
	int ret = fs.fat_getfirst("\\",name);
	while(!ret)
	{
		str = name;
		str.Insert(0,"\\");
		pStr = str.GetBuffer(str.GetLength());
		fs.fat_get_stat(pStr,&stat);
		str.ReleaseBuffer(str.GetLength());
		
		//�����ļ�����
		memcpy(file_arribute.f_name,name,32);
		//�����ļ���С
		file_arribute.f_size = stat.FileSize;
		//�����ļ�����
		//file_arribute.f_type = stat.	
		//�����ļ�����
		file_arribute.filetime.wYear = ((stat.WrtDate&0xFE00)>>9)+1980;
		file_arribute.filetime.wMonth = (stat.WrtDate&0x1E0)>>5;
		file_arribute.filetime.wDay = (stat.WrtDate & 0x1F);
		file_arribute.filetime.wHour = (stat.WrtTime & 0xF800)>>11;
		file_arribute.filetime.wMinute =(stat.WrtTime & 0x7E0)>>5;
		//�����ļ�����
		file_arribute.f_attribute = stat.Attr;
		//�Ѷ�����Nand flash��������ӵ�����
		file_list.Add(file_arribute);
		ret = fs.fat_getnext(name);
	}
	fs.Uninitialize();
	fs.ClearCartInit();
	for(int i=0;i<file_list.GetSize();i++)
	{
		if(file_list.GetAt(i).f_attribute == 0x10)//Ŀ¼
		{
			AddItemToListCtrl(file_list.GetAt(i));
		}
	}
	for(i=0;i<file_list.GetSize();i++)
	{
		if(file_list.GetAt(i).f_attribute == 0x20)//�ļ�
		{
			AddItemToListCtrl(file_list.GetAt(i));
		}
	}
	pDlg->SetTimer(IDENTIFY_CART_TIMER,1000,NULL);
}

void CPageDisk::QuitDisk()
{
	m_DiskListCtrl.DeleteAllItems();
	m_strNandDiskPath = "\\";
}
void CPageDisk::AddItemToListCtrl(FILE_ATTRIBUTE file_attribute)
{
	CString strName = file_attribute.f_name;
	CString strSize;
	CString strType;
	if(file_attribute.f_attribute!=0x10)
	{
		strSize.Format("%d %s",(file_attribute.f_size+1023)/1024,_T("KBytes"));
	}
	else
		strSize.Empty();
	if(file_attribute.f_attribute!=0x10)
		strType = "N";
	else
		strType .Format("%s",m_gStrMsgFolder);
	CString strData;
	strData.Format("%d-%d-%d %d:%d",file_attribute.filetime.wYear,file_attribute.filetime.wMonth,file_attribute.filetime.wDay,file_attribute.filetime.wHour,file_attribute.filetime.wMinute);
	int itemcounter = m_DiskListCtrl.GetItemCount();
	strName.MakeLower();
	if(file_attribute.f_attribute!=0x10)
	{
		if(strName.Right(4) == _T(".gba") || strName.Right(4) == _T(".lz7"))
			m_DiskListCtrl.InsertItem(itemcounter,strName,1);
		else /*if(strName.Right(4) == _T(".txt") || strName.Right(4)==_T(".bmp") ||strName.Right(4) == _T(".sav"))*/
			m_DiskListCtrl.InsertItem(itemcounter,strName,2);
	}
	else
	{
		m_DiskListCtrl.InsertItem(itemcounter,strName,0);
	}
	m_DiskListCtrl.SetItem(itemcounter, 1, LVIF_TEXT, strSize, 0, NULL, NULL, NULL);
	m_DiskListCtrl.SetItem(itemcounter, 2, LVIF_TEXT, strType, 0, NULL, NULL, NULL);
	m_DiskListCtrl.SetItem(itemcounter, 3, LVIF_TEXT, strData, 0, NULL, NULL, NULL);

	m_DiskListCtrl.Invalidate();
}

void CPageDisk::OnButtonNandRename() 
{
	// TODO: Add your control notification handler code here
	if(m_DiskListCtrl.GetSelectedCount()<=0)
		return;
	POSITION pos = m_DiskListCtrl.GetFirstSelectedItemPosition();
	int nItem = m_DiskListCtrl.GetNextSelectedItem(pos);
	m_DiskListCtrl.SetFocus();
	CEdit* pmyEdit = m_DiskListCtrl.EditLabel(nItem);
}

void CPageDisk::OnButtonNandRead() 
{
	// TODO: Add your control notification handler code here
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->PostMessage(WM_READFILE,0,0);
}

void CPageDisk::OnButtonNandDelete() 
{
	// TODO: Add your control notification handler code here
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->PostMessage(WM_DELETEFILE,0,0);
}

void CPageDisk::OnButtonNandBackdir() 
{
	// TODO: Add your control notification handler code here
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->PostMessage(WM_PREFOLDER,0,0);
}

void CPageDisk::OnButtonNandCreatedir() 
{
	// TODO: Add your control notification handler code here
	//����Ŀ¼
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->PostMessage(WM_CREATEFLODER,0,0);
}


void CPageDisk::OnButtonNandDeletedir() 
{
	// TODO: Add your control notification handler code here
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->PostMessage(WM_REMOVEFOLDER,0,0);
}

void CPageDisk::OnButtonNandFormat() 
{
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->PostMessage(WM_FORMATNAND,0,0);
}

BOOL CPageDisk::CheckSameName(CString str)
{
	CString strTemp;
	
//	int nLen ;
	int counter = m_DiskListCtrl.GetItemCount();
	for(int i=0;i<counter;i++)
	{
		strTemp = m_DiskListCtrl.GetItemText(i,0);
		if(strTemp == str)
		{
			return TRUE;
		}
	}
	return FALSE;
}

CStringArray *CPageDisk::GetSelectFileName(BOOL bFolder)
{
	int  nItem = -1;
	CString strItemText;
	UINT uSelectedCount = m_DiskListCtrl.GetSelectedCount();
	m_pArray->RemoveAll();
	for (UINT i=0;i < uSelectedCount;i++)
	{
		nItem = m_DiskListCtrl.GetNextItem(nItem, LVNI_SELECTED);
		strItemText = m_DiskListCtrl.GetItemText(nItem,0);
		if(bFolder)
		{
			if(strItemText.Find('.')>0 || strItemText=="saver")
				break;
		}
		else
		{
			if(strItemText.Find('.')<=0 || strItemText=="saver")
				break;
		}
		m_pArray->Add(strItemText);
	}
	return m_pArray;
}

BOOL CPageDisk::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

void CPageDisk::RemoveSlectItem(CString str)
{
	int nIndex = -1;
	LVFINDINFO info;
	info.flags = LVFI_STRING;
	info.psz = str.GetBuffer(str.GetLength());
	while ((nIndex=m_DiskListCtrl.FindItem(&info)) != -1)
	{
		m_DiskListCtrl.DeleteItem(nIndex);
	}
	str.ReleaseBuffer(str.GetLength());
	//memcpy(info.psz,str.GetBuffer(str.GetLength()),str.GetLength());

	/*
	UINT uSelectedCount = m_DiskListCtrl.GetSelectedCount();
	if(uSelectedCount<=0)
		return;
	int  nItem = -1;
	for (UINT i=0;i < uSelectedCount;i++)
	{
		nItem = m_DiskListCtrl.GetNextItem(nItem, LVNI_SELECTED);
		m_DiskListCtrl.DeleteItem(nItem);
	}
	m_DiskListCtrl.Invalidate();
	*/
}

void CPageDisk::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNM = (NM_LISTVIEW*)pNMHDR;	
	ChangeListCtrlView(pNM);
	*pResult = 0;
}
void CPageDisk::ChangeListCtrlView(NM_LISTVIEW *pNM)
{
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	typedef CArray<FILE_ATTRIBUTE,FILE_ATTRIBUTE> FILELIST;
	char name[256];
	CString strItemTextName,strItemText;
	CString strPath,str;
	FILE_ATTRIBUTE file_arribute;
	FILELIST file_list;
	char *pStr;
	_STAT stat;
	CStringArray arr;

	
	strPath = m_strNandDiskPath;
	strItemText =  m_DiskListCtrl.GetItemText(pNM->iItem,2);
	if(strItemText != m_gStrMsgFolder)
		return;	
	strItemTextName = m_DiskListCtrl.GetItemText(pNM->iItem,pNM->iSubItem);
	m_strNandDiskPath +=strItemTextName+"\\";
	m_DiskListCtrl.DeleteAllItems();
	strPath +=strItemTextName;
	pDlg->KillTimer(IDENTIFY_CART_TIMER);
	pDlg->m_Tab.EnableWindow(FALSE);
	extern DWORD g_dwNandFreeSpace;
	pDlg->ShowNandUseInfo(NAND_TOTAL_SIZE,g_dwNandFreeSpace);
	extern CFileSys fs; 
	fs.CartInit();
	if(!fs.Initialize())
	{
		pDlg->SetTimer(IDENTIFY_CART_TIMER,1000,NULL);
		pDlg->m_Tab.EnableWindow(TRUE);
		return;
	}
	int ret = fs.fat_getfirst(strPath,name);
		while(!ret)
	{
		str = name;
		str.Insert(0,"\\");
		if(strPath != "\\")
			str = strPath+_T("\\")+name;
		pStr = str.GetBuffer(str.GetLength());
		fs.fat_get_stat(pStr,&stat);
		str.ReleaseBuffer(str.GetLength());
		//
		//�����ļ�����
		memcpy(file_arribute.f_name,name,32);
		//�����ļ���С
		file_arribute.f_size = stat.FileSize;
		//�����ļ�����
		//file_arribute.f_type = stat.	
		//�����ļ�����
		file_arribute.filetime.wYear = ((stat.WrtDate&0xFE00)>>9)+1980;
		file_arribute.filetime.wMonth = (stat.WrtDate&0x1E0)>>5;
		file_arribute.filetime.wDay = (stat.WrtDate & 0x7E);
		file_arribute.filetime.wHour = (stat.WrtTime & 0xF800)>>11;
		file_arribute.filetime.wMinute =(stat.WrtTime & 0x7E0)>>5;
		//�����ļ�����
		file_arribute.f_attribute = stat.Attr;
		//�Ѷ�����Nand flash��������ӵ�����
		file_list.Add(file_arribute);
		//pMainView->AddItemToListCtrl(file_arribute);
		//
		ret = fs.fat_getnext(name);
	}
	for(int i=0;i<file_list.GetSize();i++)
	{
		if(file_list.GetAt(i).f_attribute == 0x10)//Ŀ¼
		{
			AddItemToListCtrl(file_list.GetAt(i));
		}
	}
	for(i=0;i<file_list.GetSize();i++)
	{
		if(file_list.GetAt(i).f_attribute == 0x20)//�ļ�
		{
			AddItemToListCtrl(file_list.GetAt(i));
		}
	}
	fs.ClearCartInit();

	pDlg->SetTimer(IDENTIFY_CART_TIMER,1000,NULL);
	pDlg->m_Tab.EnableWindow(TRUE);
}

void CPageDisk::OnBeginlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_strReOldName = m_DiskListCtrl.GetItemText(pDispInfo->item.iItem,0);
	*pResult = 0;
}

void CPageDisk::OnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	
	CString str,strarribute,strPath;
	int row = pDispInfo->item.iItem;
	int col = pDispInfo->item.iSubItem;
	CString s;
	strarribute = m_DiskListCtrl.GetItemText(row,2);
	CEdit *pEdit = m_DiskListCtrl.GetEditControl();
	pEdit->GetWindowText(str);
	if(m_strReOldName == "saver")
	{
		AfxMessageBox(m_gStrMsgDelSaveCation);
		return;
	}
	if(strarribute ==m_gStrMsgFolder)
	{
	}
	else
	{
		s = str.Right(4);
		s = s.Left(1);
		if(s !=".")
		{
			AfxMessageBox(m_gStrMsgEnterFileName);
			return;
		}
	}		
	if(pDlg->HasSameNameInList(str))
	{
		AfxMessageBox(m_gStrMsgSameCation);
		return;
	}
	m_DiskListCtrl.SetItemText(pDispInfo->item.iItem,0,str);
	strPath = m_strNandDiskPath;
	pDlg->KillTimer(IDENTIFY_CART_TIMER);
	pDlg->m_Tab.EnableWindow(FALSE);
extern CFileSys fs; 
	fs.CartInit();
	if(!fs.Initialize())
	{
		fs.ClearCartInit();
		return;
	}
	fs.fat_rename(strPath+m_strReOldName,str.GetBuffer(8));
	str.ReleaseBuffer(8);
	fs.Uninitialize();
	fs.ClearCartInit();

	pDlg->SetTimer(IDENTIFY_CART_TIMER,1000,NULL);
	pDlg->m_Tab.EnableWindow(TRUE);
	*pResult = 0;
}

void CPageDisk::OnButtonNandRefresh() 
{
	// TODO: Add your control notification handler code here
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->PostMessage(WM_BAKCUPFOLDER,0,0);
	/*
	CNew_EZManageDlg *pDlg = (CNew_EZManageDlg *)GetTopLevelParent();
	pDlg->KillTimer(IDENTIFY_CART_TIMER);
	pDlg->m_Tab.EnableWindow(FALSE);

	pDlg->ReadNandFlash();
	pDlg->SetTimer(IDENTIFY_CART_TIMER,1000,NULL);
	pDlg->m_Tab.EnableWindow(TRUE);
	*/
}

void CPageDisk::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_pArray)
	{
		m_pArray->RemoveAll();
		delete m_pArray;
		m_pArray = NULL;
	}
}

void CPageDisk::OnDropFiles(HDROP hDropInfo) 
{
	int i=0;
	i++;
}