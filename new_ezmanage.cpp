// New_EZManage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "New_EZManage.h"
#include "New_EZManageDlg.h"
#include "SkinPlusPlus.h"
#include "DlgLanguageSelect.h"
#include <Afxtempl.h> //CArray����Ҫ��ͷ�ļ�
#include "Tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNew_EZManageApp
//������õ����ַ���
//1.�˵�
extern CString m_gMenuSysConfig;				//ϵͳ����
extern CString m_gMenuInstallLoader;			//��װEZ3����ϵͳ
extern CString m_gMenuInstallNdsLoader;			//��װEZ3 Nds����ϵͳ
extern CString m_gMenuSynClock;					//ͬ��ϵͳʱ��;
extern CString m_gMenuDownLoadFiler;			//���������ļ�;
extern CString m_gMenuPassMe2;
extern CString m_gMenuLanguage;					//����ѡ��;
//2.�����ļ���
extern CString m_gStrLocalDisk;					//���ش���
extern CString m_gStrPath;						//����·��
//3.Tab
extern CString m_gStrConfig;					//��¼����
extern CString m_gStrCapacityInfo;				//������Ϣ
extern CString m_gStrWriteInfo;				//��¼��Ϣ

extern CString m_gStrNorFlashPage;				//256M Bits EZ Flash ����
extern CString m_gStrNorIndex;					//���
extern CString m_gStrNorRomName;				//ROM��
extern CString	m_gStrNorRomSize;				//ROM��С
extern CString	m_gStrNorRomEdit;				//ROM��Ϣ�༭
extern CString m_gStrNorRomState;				//ROM״̬
extern CString m_gStrAddRom;					//���Rom
extern CString m_gStrDelRom;					//ɾ��Rom
extern CString m_gStrBackupRom;					//����Rom
extern CString m_gStrRefresh;					//ˢ��Rom
extern CString m_gStrFormatRom;					//��ʽ��Rom
extern CString m_gStrWriteRom;					//��¼Rom

extern CString m_gStrdiskPage;					//1G Bits EZ-Disk ����
extern CString m_gStrDiskName;					//����
extern CString m_gStrDiskSize;					//��С
extern CString m_gStrDiskType;					//����
extern CString m_gStrDiskModifyData;			//�޸�����
extern CString m_gStrAttribute;					//����
extern CString m_gStrDiskReName;				//������
extern CString m_gStrDiskRead;					//���ļ�
extern CString m_gStrDiskDelFile;				//ɾ���ļ�
extern CString m_gStrDiskPreFolder;			//���ϼ�Ŀ¼
extern CString m_gStrDiskCreateFolder;			//�����ļ���
extern CString m_gStrDiskDelFolder;			//ɾ���ļ���
extern CString m_gStrDiskFormatDisk;		//��ʽ������
extern CString m_gStrDiskrefresh;				//ˢ�´���
//[DiskFormat]
extern CString m_gStrMsgFormatDisk;			//��ʽ��EZ����
extern CString m_gStrMsgCapacity;				//����
extern CString m_gStrMsgFileSystem;			//�ļ�ϵͳ
extern CString m_gStrMsgAllocationUint;		//���䵥Ԫ��С
extern CString m_gStrMsgVolume;				//���
extern CString m_gStrMsgFormatItem;			//��ʽ��ѡ��
extern CString m_gStrMsgQuickFormat;			//��ʽ��ѡ��
extern CString m_gStrBeginFormat;				//��ʼ��ʽ��
extern CString m_gStrCancleFormat;				//ȡ��
//[RomEdit]
extern CString m_gStrMsgRomEditInfo;			//ROM��Ϣ�༭
extern CString m_gStrMsbBaseInfo;				//������Ϣ
extern CString m_gStrMsgRomName;				//ROM ��
extern CString m_gStrMsgRomSize;				//ROM��С
extern CString m_gStrMsgSoftReset;				//��λ
extern CString m_gStrMsgInstantSave;
extern CString m_gStrMsgCompress;				//ѹ��
extern CString m_gStrMsgSaveType;				//�浵��ʽ
extern CString m_gStrMsgSaveSize;				//�浵��С
extern CString m_gStrMsgAddPatch;				//��浵����
extern CString m_gStrMsgChectInfo;				//����ָ��Ϣ
extern CString m_gStrMsgOK;						//ȷ��
extern CString m_gStrMsgCancle;					//ȡ��
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
extern CString m_gStrMsgInstallOSUp;
extern CString m_gStrMsgInstallOSEnd;//=EZ3����ϵͳ��װ���
extern CString m_gStrMsgInstallOSU;
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
extern CString m_gStrMsgCurrent;//=��ǰĿ¼
extern CString m_gStrMsgRootDir;//=��ǰĿ¼�Ǹ�Ŀ¼
extern CString m_gStrMsgMore128MInfo;
extern CString m_gStrMsgLanguageChange;
extern CString m_gStrMsgOSChange;
extern CString m_gStrMsgDownLoad;//=�������������ļ�;
extern CString m_gStrMsgDownLoadEnd;
BEGIN_MESSAGE_MAP(CNew_EZManageApp, CWinApp)
	//{{AFX_MSG_MAP(CNew_EZManageApp)
	ON_COMMAND(IDD_ADD_LOADER, OnAddLoader)
	ON_UPDATE_COMMAND_UI(IDD_ADD_LOADER, OnUpdateAddLoader)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNew_EZManageApp construction

CNew_EZManageApp::CNew_EZManageApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_strLanguage.Empty();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNew_EZManageApp object

CNew_EZManageApp theApp;
HANDLE m_externMutexHandle = NULL;
BOOL IsEz2SoftRun()
{
	CArray<PROCESSENTRY32,PROCESSENTRY32 &> m_PEArray;
	m_PEArray.RemoveAll();
    HANDLE hProcessSnap=NULL;
    PROCESSENTRY32 pe32;
    hProcessSnap=::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    pe32.dwSize=sizeof(PROCESSENTRY32);
    if(::Process32First(hProcessSnap,&pe32))
    {
        do
        {
            m_PEArray.Add(pe32);
        }
        while(::Process32Next(hProcessSnap,&pe32));
        
    }
    int i;
    for(i=0;i<m_PEArray.GetSize();i++)
    {
        CString str;
        str.Format("%s",m_PEArray.GetAt(i).szExeFile);
        if(str.Find("EZClient.exe")!=-1)
        {
			/*
            HANDLE hProcess;
            DWORD ProcessID;
            ProcessID=m_PEArray.GetAt(i).th32ProcessID;
            hProcess=::OpenProcess(PROCESS_ALL_ACCESS,FALSE,ProcessID);
            ::TerminateProcess(hProcess,99);
            CloseHandle(hProcess);
			*/
			return TRUE;
        }
    }
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CNew_EZManageApp initialization

BOOL CNew_EZManageApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	m_externMutexHandle = ::CreateMutex(NULL, true, m_pszExeName);
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CWnd *pPrevWnd = CWnd::GetDesktopWindow()->GetWindow(GW_CHILD);
		while(pPrevWnd)
		{
			if(::GetProp(pPrevWnd->GetSafeHwnd(), m_pszExeName))
			{
				if(pPrevWnd->IsIconic())
					pPrevWnd->ShowWindow(SW_RESTORE);
				pPrevWnd->SetForegroundWindow();
				CWnd *pPopupWnd = pPrevWnd->GetLastActivePopup();
				if(pPopupWnd)
					pPopupWnd->SetForegroundWindow();
				return FALSE;
			}
			pPrevWnd = pPrevWnd->GetWindow(GW_HWNDNEXT);
		}
		TRACE(_T("Could not find previous instance main window.\n"));
		return FALSE;
	}

	char	*pstr = new char[256]; 
	CString str ,strPath;
	GetCurrentDirectory(256,pstr);
	strPath = pstr;
	CString m_strWindowsDir;
	GetWindowsDirectory (pstr,1024);
	m_strWindowsDir = pstr;
	
	CString s = strPath +_T("\\SoftCrystal.ssk");
	memset(&osvi, 0, sizeof(OSVERSIONINFO)); 
	osvi.dwOSVersionInfoSize = 148;//sizeof(OSVERSIONINFOEX);
	GetVersionEx(&osvi);
	if(osvi.dwPlatformId !=VER_PLATFORM_WIN32_WINDOWS)
	{
		InitializeSkin(s.GetBuffer(s.GetLength()));
		s.ReleaseBuffer(s.GetLength());
	}
/*
	//����3210�Ŀ�,���bin�ļ�**********lichuan add date 2005.08.26********************************************
	CEzFlashBase base;
	HANDLE hDev;
	base.OpenCartDevice(hDev);
	if(base.m_readsize == 64)
	{
		base.CloseCartDevice(hDev);
	}
	else
	{
		//�Ƚ�ϵͳ�е�bin�ļ�
		CFile file1,file2;
		BYTE *pBuf1=NULL,*pBuf2=NULL;
		DWORD len1,len2;
		CString str1,str2;
		str1 = m_strWindowsDir +_T("\\system32\\drivers\\TUSBEZ.BIN");
		str2 = strPath+_T("\\driver_writr2\\TUSBEZ.BIN");
		if(file1.Open(str1,CFile::modeRead))
		{
			len1 = file1.GetLength();
			pBuf1 = new BYTE[len1];
			file1.Read(pBuf1,len1);
			file1.Close();
		}
		else
			len1=0;

		if(file2.Open(str2,CFile::modeRead))
		{
			len2 = file2.GetLength();
			pBuf2 = new BYTE[len2];
			file2.Read(pBuf2,len2);
			file2.Close();
		}
		else
			len2=0;
		
		if( (len1 != len2) || (len1== 0 && len2==0))
		{
			if(GetFileAttributes((LPCTSTR )str1)&&FILE_ATTRIBUTE_READONLY )
			{
				SetFileAttributes((LPCTSTR )str1,FILE_ATTRIBUTE_NORMAL);
			}
			CopyFile((LPCTSTR )str2,(LPCTSTR )str1,FALSE);
			AfxMessageBox("�����²��д����һ�������г���");
			return FALSE;
		}
		else
		{
			if(memcmp(pBuf1,pBuf2,len1)!=0)
			{
			}
		}
		delete []pBuf1;
		delete []pBuf2;
		base.CloseCartDevice(hDev);
	
	//**********************************************************************************************************
*/
	//AfxMessageBox("End");���ٰ�
	CDlgLanguageSelect DlgLanguageSelect ;

	::GetPrivateProfileString("Language","Version","",pstr,256,m_strWindowsDir+("\\temp\\conf.ini"));
	str = pstr;
	if(str.GetLength()<=0)
	{
		if(DlgLanguageSelect.DoModal() == IDOK)
		{
			str = DlgLanguageSelect.GetSelectLanguage();
			::WritePrivateProfileString("Language","Version",str,m_strWindowsDir+("\\temp\\conf.ini"));
		}
		else
		{
			return -1;
		}
	}
	delete []pstr;

	AfxEnableControlContainer();
    AfxOleInit();

	//extern CString m_gMenuSysConfig;
	//str = strPath + _T("\\langdata\\")+_T("English.ini");
	//Menu
	//::GetPrivateProfileString("Menu","m_gMenuSysConfig","",pstr,1024,str);
	//m_gMenuSysConfig = pstr;

	InitLanguageFile(strPath);
	InitAllString(strPath);
	if(IsEz2SoftRun())
	{
		if(m_strLanguage=_T("��������"))
			AfxMessageBox("EzClient��������,��ر�EzClient��������EzManage");
		else
			AfxMessageBox("EzClient is running ,Please Close it and run EzManage again");
		return FALSE;
	}

	CNew_EZManageDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CNew_EZManageApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	if(osvi.dwPlatformId !=VER_PLATFORM_WIN32_WINDOWS)
		ExitSkin();
	return CWinApp::ExitInstance();
}

void CNew_EZManageApp::OnAddLoader() 
{
	// TODO: Add your command handler code here
	int i=0;
	i++;
}

void CNew_EZManageApp::OnUpdateAddLoader(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int i=0;
	i++;
}

BOOL CNew_EZManageApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::PreTranslateMessage(pMsg);
}

void CNew_EZManageApp::InitAllString(CString m_strWorkPath)
{   
	CString str;
	char *pstr = new char[1024];
	if(m_strLanguage == "��������")
		m_strLanguage = "china-simple";
	//1.�˵�
	str = m_strWorkPath + _T("\\langdata\\")+m_strLanguage+_T(".ini");
	::GetPrivateProfileString("Menu","m_gMenuSysConfig","",pstr,1024,str);
	m_gMenuSysConfig = pstr;
	::GetPrivateProfileString("Menu","m_gMenuInstallLoader","",pstr,1024,str);
	m_gMenuInstallLoader= pstr;
	::GetPrivateProfileString("Menu","m_gMenuInstallNdsLoader","",pstr,1024,str);
	m_gMenuInstallNdsLoader = pstr;
	::GetPrivateProfileString("Menu","m_gMenuSynClock","",pstr,256,str);
	m_gMenuSynClock= pstr;
	::GetPrivateProfileString("Menu","m_gMenuSynClock","",pstr,256,str);
	m_gMenuSynClock= pstr;
	::GetPrivateProfileString("Menu","m_gMenuDownLoadFiler","",pstr,256,str);
	m_gMenuDownLoadFiler= pstr;
	
	::GetPrivateProfileString("Menu","m_gMenuPassMe2","",pstr,256,str);
	m_gMenuPassMe2= pstr;
	::GetPrivateProfileString("Menu","m_gMenuLanguage","",pstr,256,str);
	m_gMenuLanguage= pstr;
	//2.�����ļ���
	::GetPrivateProfileString("ListTree","m_gStrLocalDisk","",pstr,256,str);
	m_gStrLocalDisk= pstr;
	::GetPrivateProfileString("ListTree","m_gStrPath","",pstr,256,str);
	m_gStrPath= pstr;
	//3.Tab
	::GetPrivateProfileString("Tab","m_gStrConfig","",pstr,256,str);
	m_gStrConfig= pstr;
	::GetPrivateProfileString("Tab","m_gStrCapacityInfo","",pstr,256,str);
	m_gStrCapacityInfo= pstr;
	::GetPrivateProfileString("Tab","m_gStrWriteInfo","",pstr,256,str);
	m_gStrWriteInfo= pstr;

	::GetPrivateProfileString("NorFlashPage","m_gStrNorFlashPage","",pstr,256,str);
	m_gStrNorFlashPage= pstr;
	::GetPrivateProfileString("NorFlashPage","m_gStrNorIndex","",pstr,256,str);
	m_gStrNorIndex= pstr;	
	::GetPrivateProfileString("NorFlashPage","m_gStrNorRomName","",pstr,256,str);
	m_gStrNorRomName= pstr;	
	::GetPrivateProfileString("NorFlashPage","m_gStrNorRomSize","",pstr,256,str);
	m_gStrNorRomSize= pstr;	
	::GetPrivateProfileString("NorFlashPage","m_gStrNorRomEdit","",pstr,256,str);
	m_gStrNorRomEdit= pstr;	
	::GetPrivateProfileString("NorFlashPage","m_gStrNorRomState","",pstr,256,str);
	m_gStrNorRomState= pstr;	
	::GetPrivateProfileString("NorFlashPage","m_gStrAddRom","",pstr,256,str);
	m_gStrAddRom= pstr;
	::GetPrivateProfileString("NorFlashPage","m_gStrDelRom","",pstr,256,str);
	m_gStrDelRom= pstr;
	::GetPrivateProfileString("NorFlashPage","m_gStrBackupRom","",pstr,256,str);
	m_gStrBackupRom= pstr;
	::GetPrivateProfileString("NorFlashPage","m_gStrRefresh","",pstr,256,str);
	m_gStrRefresh= pstr;
	::GetPrivateProfileString("NorFlashPage","m_gStrFormatRom","",pstr,256,str);
	m_gStrFormatRom= pstr;
	::GetPrivateProfileString("NorFlashPage","m_gStrWriteRom","",pstr,256,str);
	m_gStrWriteRom= pstr;


	::GetPrivateProfileString("DiskPage","m_gStrdiskPage","",pstr,256,str);
	m_gStrdiskPage= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskName","",pstr,256,str);
	m_gStrDiskName= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskSize","",pstr,256,str);
	m_gStrDiskSize= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskType","",pstr,256,str);
	m_gStrDiskType= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskModifyData","",pstr,256,str);
	m_gStrDiskModifyData= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrAttribute","",pstr,256,str);
	m_gStrAttribute= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskReName","",pstr,256,str);
	m_gStrDiskReName= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskRead","",pstr,256,str);
	m_gStrDiskRead= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskDelFile","",pstr,256,str);
	m_gStrDiskDelFile= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskPreFolder","",pstr,256,str);
	m_gStrDiskPreFolder= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskCreateFolder","",pstr,256,str);
	m_gStrDiskCreateFolder= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskDelFolder","",pstr,256,str);
	m_gStrDiskDelFolder= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskFormatDisk","",pstr,256,str);
	m_gStrDiskFormatDisk= pstr;
	::GetPrivateProfileString("DiskPage","m_gStrDiskrefresh","",pstr,256,str);
	m_gStrDiskrefresh= pstr;
	//[DiskFormat]
	::GetPrivateProfileString("DiskFormat","m_gStrMsgFormatDisk","",pstr,256,str);
	m_gStrMsgFormatDisk= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrMsgCapacity","",pstr,256,str);
	m_gStrMsgCapacity= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrMsgFileSystem","",pstr,256,str);
	m_gStrMsgFileSystem= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrMsgAllocationUint","",pstr,256,str);
	m_gStrMsgAllocationUint= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrMsgVolume","",pstr,256,str);
	m_gStrMsgVolume= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrMsgFormatItem","",pstr,256,str);
	m_gStrMsgFormatItem= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrMsgQuickFormat","",pstr,256,str);
	m_gStrMsgQuickFormat= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrBeginFormat","",pstr,256,str);
	m_gStrBeginFormat= pstr;
	::GetPrivateProfileString("DiskFormat","m_gStrCancleFormat","",pstr,256,str);
	m_gStrCancleFormat= pstr;
	//[RomEdit]
	::GetPrivateProfileString("RomEdit","m_gStrMsgRomEditInfo","",pstr,256,str);
	m_gStrMsgRomEditInfo= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsbBaseInfo","",pstr,256,str);
	m_gStrMsbBaseInfo= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgRomName","",pstr,256,str);
	m_gStrMsgRomName= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgRomSize","",pstr,256,str);
	m_gStrMsgRomSize= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgSoftReset","",pstr,256,str);
	m_gStrMsgSoftReset= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgInstantSave","",pstr,256,str);
	m_gStrMsgInstantSave= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgCompress","",pstr,256,str);
	m_gStrMsgCompress= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgSaveType","",pstr,256,str);
	m_gStrMsgSaveType= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgSaveSize","",pstr,256,str);
	m_gStrMsgSaveSize= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgAddPatch","",pstr,256,str);
	m_gStrMsgAddPatch= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgChectInfo","",pstr,256,str);
	m_gStrMsgChectInfo= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgOK","",pstr,256,str);
	m_gStrMsgOK= pstr;
	::GetPrivateProfileString("RomEdit","m_gStrMsgCancle","",pstr,256,str);
	m_gStrMsgCancle= pstr;
	
//[MsgInfo]
	::GetPrivateProfileString("MsgInfo","m_gStrMsgReading","",pstr,256,str);
	m_gStrMsgReading= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgReadEnd","",pstr,256,str);
	m_gStrMsgReadEnd= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgCation","",pstr,256,str);
	m_gStrMsgCation= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgNoWrited","",pstr,256,str);
	m_gStrMsgNoWrited= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgWrited","",pstr,256,str);
	m_gStrMsgWrited= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgUse","",pstr,256,str);
	m_gStrMsgUse= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgLeft","",pstr,256,str);
	m_gStrMsgLeft= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgReserve","",pstr,256,str);
	m_gStrMsgReserve= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgFolder","",pstr,256,str);
	m_gStrMsgFolder= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgNoCart","",pstr,256,str);
	m_gStrMsgNoCart= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgEZDisk","",pstr,256,str);
	m_gStrMsgEZDisk= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgInstallOS","",pstr,256,str);
	m_gStrMsgInstallOS= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgInstallOSUp","",pstr,256,str);
	m_gStrMsgInstallOSUp= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgInstallOSEnd","",pstr,256,str);
	m_gStrMsgInstallOSEnd= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgNoEnough","",pstr,256,str);
	m_gStrMsgNoEnough= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgIncalideFile","",pstr,256,str);
	m_gStrMsgIncalideFile= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgSelectFolder","",pstr,256,str);
	m_gStrMsgSelectFolder= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgSlectBackRom","",pstr,256,str);
	m_gStrMsgSlectBackRom= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgErrorBackRom","",pstr,256,str);
	m_gStrMsgErrorBackRom= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgBackRomEnd","",pstr,256,str);
	m_gStrMsgBackRomEnd= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgFormatNorCation","",pstr,256,str);
	m_gStrMsgFormatNorCation= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgFormatingNor","",pstr,256,str);
	m_gStrMsgFormatingNor= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgFormatNorEnd","",pstr,256,str);
	m_gStrMsgFormatNorEnd= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgErasing","",pstr,256,str);
	m_gStrMsgErasing= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgWriting","",pstr,256,str);
	m_gStrMsgWriting= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgWriteEnd","",pstr,256,str);
	m_gStrMsgWriteEnd= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgCreatingFolder","",pstr,256,str);
	m_gStrMsgCreatingFolder= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgCreateFolderOK","",pstr,256,str);
	m_gStrMsgCreateFolderOK= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgDeletingFolder","",pstr,256,str);
	m_gStrMsgDeletingFolder= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgDelSaveCation","",pstr,256,str);
	m_gStrMsgDelSaveCation= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgEnterFileName","",pstr,256,str);
	m_gStrMsgEnterFileName= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgSameCation","",pstr,256,str);
	m_gStrMsgSameCation= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgDelFolderEnd","",pstr,256,str);
	m_gStrMsgDelFolderEnd= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgReadFileEnd","",pstr,256,str);
	m_gStrMsgReadFileEnd= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgSelectFile","",pstr,256,str);
	m_gStrMsgSelectFile= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgDeletingFile","",pstr,256,str);
	m_gStrMsgDeletingFile= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgIsDelFile","",pstr,256,str);
	m_gStrMsgIsDelFile= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgDleFileOK","",pstr,256,str);
	m_gStrMsgDleFileOK= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgCompressing","",pstr,256,str);
	m_gStrMsgCompressing= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgFormatcation","",pstr,256,str);
	m_gStrMsgFormatcation= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgCurrent","",pstr,256,str);
	m_gStrMsgCurrent= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgRootDir","",pstr,256,str);
	m_gStrMsgRootDir= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgMore128MInfo","",pstr,256,str);
	m_gStrMsgMore128MInfo= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgLanguageChange","",pstr,256,str);
	m_gStrMsgLanguageChange= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgOSChange","",pstr,256,str);
	m_gStrMsgOSChange= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgDownLoad","",pstr,256,str);
	m_gStrMsgDownLoad= pstr;
	::GetPrivateProfileString("MsgInfo","m_gStrMsgDownLoadEnd","",pstr,256,str);
	m_gStrMsgDownLoadEnd= pstr;
	delete []pstr;

}

void CNew_EZManageApp::InitLanguageFile(CString m_strWorkPath)
{
	CString str;
	char *pstr = new char[1024];
	char *pChar = new char[1024];
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	str = m_strWorkPath+_T("\\langdata\\*.ini");
	BOOL bFind;
	hFind = FindFirstFile(str,&FindFileData);
	m_stringArray.RemoveAll();
	if (hFind == INVALID_HANDLE_VALUE) 
		return ;
	do
	{
		m_stringArray.Add(FindFileData.cFileName);
		bFind=FindNextFile(hFind,&FindFileData);
	}while(bFind!=FALSE);
	FindClose(hFind);
	GetWindowsDirectory (pChar,1024);
	CString m_strWindowsDir = pChar;
	
	str = m_strWindowsDir+("\\temp\\conf.ini");
	::GetPrivateProfileString("Language","Version","",pstr,256,str);
	m_strLanguage = pstr;
	delete []pstr;
	delete []pChar;
/*
	for(UINT i=0;i<m_stringArray.GetSize();i++)
	{
		::GetPrivateProfileString("Language","LanguageVersion","",pstr,256,m_strWorkPath+_T("\\langdata\\")+m_stringArray.GetAt(i));
		m_MenustringArray.Add(pstr);
	}
	CMenu *pRootMenu = GetMenu();
	CMenu *pSubRoot,*pSub;
	CMenu *pSubMenuLanguage;
	pSubRoot = pRootMenu->GetSubMenu(0);
	pSub = pSubRoot->GetSubMenu(3);
	::GetPrivateProfileString("Language","Version","",pstr,256,m_strWorkPath+("\\ini\\conf.ini"));
	m_strLanguage = pstr;
	for(i=0;i<m_MenustringArray.GetSize();i++)
	{
		CString str = m_MenustringArray.GetAt(i);
		if(i==0)
		{
			pSub->RemoveMenu(0,MF_BYPOSITION);
		}
		if(m_strLanguage == str)
			pSub->AppendMenu(MF_ENABLED|MF_STRING|MF_BYCOMMAND|MF_MOUSESELECT|MF_CHECKED,IDD_CHINESE+i,str);
		else
			pSub->AppendMenu(MF_ENABLED|MF_STRING|MF_BYCOMMAND|MF_MOUSESELECT,IDD_CHINESE+i,str);
	}
	*/
}