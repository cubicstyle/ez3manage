// EZListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "new_ezmanage.h"
#include "EZListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZListCtrl
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
extern CString m_gStrMsgInstallOSUp;
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
CEZListCtrl::CEZListCtrl()
{
}

CEZListCtrl::~CEZListCtrl()
{
}


BEGIN_MESSAGE_MAP(CEZListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CEZListCtrl)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEZListCtrl message handlers

void CEZListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	int nItem = lpDrawItemStruct->itemID;
	
	CRect rcAllLabels;
	GetItemRect(nItem,rcAllLabels,LVIR_BOUNDS);

	pDC->SaveDC();
	
	BOOL bSelected = false;
	if(GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
	{
		//pDC->SetTextColor(RGB(200,0,0));//::GetSysColor(COLOR_HIGHLIGHTTEXT));
		//pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		pDC->FillRect(rcAllLabels,&CBrush(RGB(10,36,106)));
		bSelected = true;
	}
	else
		pDC->FillRect(rcAllLabels,&CBrush(RGB(255,255,255)));
	TCHAR buffer[255];
	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvc.pszText = buffer;
	lvc.cchTextMax = 255;

	CRect rcItem;
	rcItem.left = rcAllLabels.left;
	rcItem.right = rcAllLabels.left;
	rcItem.top = rcAllLabels.top;
	rcItem.bottom = rcAllLabels.bottom;
	CRect rcLabel;

	for(int nColumn = 0; GetColumn(nColumn, &lvc); nColumn++)
	{
		rcItem.left=rcItem.right;
		rcItem.right += lvc.cx;

		rcLabel=rcItem;
		rcLabel.DeflateRect(1,1);
		
		GetItemText(nItem,nColumn,buffer,255);
		if(GetItemText(nItem,4) == m_gStrMsgNoWrited)
			pDC->SetTextColor(RGB(255,0,0));
		else
			pDC->SetTextColor(RGB(0,0,0));
		if(GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED && (GetItemText(nItem,4) != m_gStrMsgNoWrited))
			pDC->SetTextColor(RGB(255,255,255));
		pDC->DrawText(buffer , rcLabel , DT_LEFT|DT_VCENTER);

		pDC->MoveTo(rcItem.left, rcItem.top);
		pDC->LineTo(rcItem.left, rcItem.bottom-1);
		pDC->LineTo(rcItem.right, rcItem.bottom-1);
		pDC->LineTo(rcItem.right, rcItem.top);
	}
	pDC->RestoreDC(-1);
}
