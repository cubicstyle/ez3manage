// GoldenCheat.cpp: implementation of the CGoldenCheat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GoldenCheat.h"
#include "cheatcode.h"
#include "New_EZManageDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGoldenCheat::CGoldenCheat()
{

}

CGoldenCheat::~CGoldenCheat()
{

}

BOOL CGoldenCheat::CheatAddNewGame(BYTE *pLoader ,/*��С1Mbit*/
								   BYTE	*pGame , /*��Ϸ����*/
								   BYTE *pXCode ,/*��xcode����*/
								   BYTE *pCheatList,/*����ָ�б�*/
								   BYTE	entryIndex, /*�������,��0��ʼ*/
								   int  xcodeIndex/*��Ϸ������,��0*/)
{
#define CODESIZE 280
#define MODIFYBASE 0xF0
	PXCODE		pxcode = (PXCODE)pXCode ;
	PCODE		pcode = (PCODE)(pXCode+24) ;
	PGOLD_DATA	pgolddata = (PGOLD_DATA)pCheatList ;
	BYTE		gamedata[0x120] ;
	int			ixcode = xcodeIndex ;
	int 		iDataIndex = 0 , iSize = 0 ;
	BYTE rx0 , rx1 ;
	WORD  ui16Replaced;
	DWORD dwCheatDataAddress , dwCodeAddress , dwDataOffset , secondOff, secondLdr = 0;

//������Ҫ�޸�loader 
	//1.��xcode���õ�����λ�� 
	PXCODE pxtmp = (PXCODE)(pLoader+0x8000);
	while(ixcode)
	{
		if(pxtmp->sign != 'XCDE')
			return FALSE ;
		iDataIndex += pxtmp->dataSize ;
		pxtmp = (PXCODE)((UINT)pxtmp+pxtmp->CodeSize*8+24);
		ixcode -- ;
	}
	memcpy(pxtmp,pxcode,(pxcode->CodeSize*8+24));
	//2.����Ϸ����ָ���ݷ��ں���λ��
	iSize = pxcode->dataSize ;
	if(iSize>0)
	{
		PGOLD_DATA pgoldtmp = (PGOLD_DATA)(pLoader+0x14400+iDataIndex*0x20);
		memcpy(pgoldtmp,pgolddata,iSize*0x20);
	}
	//3.׼����Ϸ���ݵ��޸�
	for(int i=0 ; i<pxcode->CodeSize ; i++)
	{
		memset(gamedata,0,0x120);
		memcpy(gamedata,cheatcode,CODESIZE);
		dwCodeAddress = pcode[i].m_dwAddress ;
		rx1 = pcode[i].m_register ;
		rx0 = GetReturnRegisterFromGame(dwCodeAddress,pGame);
		//�õ���һ�䱻�滻�Ĵ���
		dwCodeAddress &= 0x07FFFFFF ;
		ui16Replaced = *(WORD*)((DWORD)pGame+dwCodeAddress+2);
		//�õ�0x04000130 ���ڵ�ַ
		dwDataOffset = CountOffset(dwCodeAddress,*(WORD*)(dwCodeAddress+(BYTE*)pGame));
		if(*(DWORD*)(pGame+dwDataOffset) !=  0x04000130)
			return FALSE ;
		dwCheatDataAddress = 0x09FE0000+0x9000+0x120*(entryIndex+i);
		//�޸ĳ�������Ҫ�Ķ������ݣ��Լ��Ĵ���
		*((DWORD*)(gamedata+0x10C)) = dwCheatDataAddress + 0x118 ;
		dwCodeAddress |= 0x08000000 ;
		*((DWORD*)(gamedata+0x114)) = dwCodeAddress + 5 ;
		//�޸�pop {rx0}
		Set_POP_Reg((WORD*)(gamedata+MODIFYBASE),rx0);
		//�޸� mov lr ,rx0
		Set_MOV_Reg((WORD*)(gamedata+MODIFYBASE+2),rx0);
		//�޸�ldr rx0 , =0x04000130
		Set_LDR_Reg((WORD*)(gamedata+MODIFYBASE+4),rx0);
		//��ԭ�������ݿ��������ڵ�����
		if((ui16Replaced&0x4800) == 0x4800)
		{
			dwCodeAddress &= 0x07FFFFFF ;
			secondOff = CountOffset(dwCodeAddress+2,*(WORD*)(dwCodeAddress+2+(BYTE*)pGame));
			secondLdr = *(DWORD*)(pGame+secondOff) ;
			ui16Replaced &= 0xFF00 ;
			ui16Replaced += 0x6 ;
			dwCodeAddress |= 0x08000000 ;
		}
		*(WORD*)(gamedata+MODIFYBASE+6) = ui16Replaced ;
		*((DWORD*)(gamedata+0x110)) = secondLdr ;
		//�޸�ldr rx1 , JUMPBACK ADDRESS
		Set_LDR_Reg((WORD*)(gamedata+MODIFYBASE+8),rx1);
		//�޸� BX RX1 
		Set_BX_Reg((WORD*)(gamedata+MODIFYBASE+0xa),rx1);

		*((DWORD*)(gamedata+0x118)) = 0x09FE0000+0x14400+iDataIndex*0x20 ;
		*((DWORD*)(gamedata+0x11C)) = pxcode->dataSize ;

		memcpy((pLoader+0x9000+0x120*(entryIndex+i)),gamedata,0x120) ;

	//4. �޸���Ϸ��
		ui16Replaced = 0x4700; // bx r0 ;
		//��0x04000130�޸�Ϊ��ת��ַ
		*((DWORD*)(pGame+dwDataOffset))=dwCheatDataAddress+1 ;
		//�޸� BX RX0 
		Set_BX_Reg((WORD*)(&ui16Replaced),rx0);
		dwCodeAddress &= 0x7FFFFFF ;
		*((WORD*)((UINT)pGame+dwCodeAddress+2)) = ui16Replaced ;
	}
	return TRUE ;
}

BOOL CGoldenCheat::IsXCodeValid(void* pXCode,BYTE* pGameData ,UINT size )
{
	//pXCode		���ݵĵ�ǰ����Ϸ��XCode�ͽ���ָ���ݴ���
	//pGameData		���ݵ�ǰ����Ϸ����
	PXCODE		pxcode = (PXCODE)pXCode ;
	PCODE		pcode = (PCODE)((BYTE*)pXCode+24) ;
	DWORD dwCodeAddress , dwDataOffset;
	if(!(pXCode&&pGameData))
		return FALSE;
	if(size <=0 )
		return FALSE ;

//1. �����޸�cheat code ���� ,׼������
	//�õ�ldr rx0 , =0x04000130 �ĵ�ַ
	for(UINT i=0 ; i<pxcode->CodeSize ; i++)
	{
		dwCodeAddress = pcode[i].m_dwAddress;
		//�õ�0x04000130 ���ڵ�ַ
		dwCodeAddress &= 0x07FFFFFF ;
		if((dwCodeAddress)>size)
			return FALSE ;
		dwDataOffset = CountOffset(dwCodeAddress,*(WORD*)(dwCodeAddress+pGameData));
		if(dwDataOffset+4 > size)
			return FALSE ;
		if(*((DWORD*)(dwDataOffset+pGameData)) != 0x04000130 )
			return FALSE ;
	}
	return TRUE ;
}

BOOL CGoldenCheat::CheatEditGame(BYTE *pLoader,/*��С1Mbit*/
					   BYTE *pXCode ,/*��xcode����*/
					   BYTE *pCheatList,/*����ָ�б�*/
					   int xcodeIndex,/*��Ϸ������*/
					   int cheatgame/*�н���ָ��Ϸ�ĸ���*/)
{
	PXCODE		pxcode = (PXCODE)pXCode ;
	PCODE		pcode = (PCODE)(pXCode+24) ;
	PGOLD_DATA	pgolddata = (PGOLD_DATA)pCheatList ;
	int ixcode = cheatgame , i = 0 , iMove=0 , j=0;
	DWORD uiCheatlist = 0 , uiCodeList = 0;
	WORD *pXCodeSize = new WORD[cheatgame] ;
	WORD *pCheatSize = new WORD[cheatgame] ;
	BYTE *pBuffer = NULL ,*pCheatData=NULL ,*pCodeList = NULL ;
	DWORD	backCheat = 0 , origSize = 0 ,origPos = 0 ;
	//1.�ж��н���ָ��Ϸ�ĸ����Ƿ���ȷ,ͬʱ������Ҫ������
	PXCODE pxtmp = (PXCODE)(pLoader+0x8000);
	PXCODE pxtmp2 = NULL ; //��Ҫ�޸���Ϸ��xcode
	while(ixcode)
	{
		if(pxtmp->sign != 'XCDE')
		{
			if(pXCodeSize)
				delete pXCodeSize ;
			if(pCheatSize)
				delete pCheatSize ;
			return FALSE ;
		}
		if( ixcode > (cheatgame - xcodeIndex))
		{//����ȷ��Ҫ�༭��Ϸ����ָxcode λ�ã��Լ�����ָ���ݵ�λ��
			uiCheatlist += pxtmp->dataSize ;
			uiCodeList += pxtmp->CodeSize ;
		}
		if(xcodeIndex == i)
			pxtmp2 = pxtmp ;
		pXCodeSize[i] = pxtmp->CodeSize ;
		pCheatSize[i] = pxtmp->dataSize ;
		i++;
		pxtmp = (PXCODE)((UINT)pxtmp+pxtmp->CodeSize*8+24);
		ixcode -- ;
	}
	//2. ׼��Ǩ������ , ȷ��xcode��һ����
	pCheatData = pLoader + 0x14400 ;
	if(memcmp(pxcode->gameName,pxtmp2->gameName,12))
	{
		if(pXCodeSize)
			delete pXCodeSize ;
		if(pCheatSize)
			delete pCheatSize ;
		return FALSE ;
	}
	for(i=xcodeIndex+1;i<cheatgame;i++)
		iMove += pCheatSize[i] ;
	pBuffer = new BYTE[iMove*32] ;////
	memcpy(pBuffer,pCheatData+(uiCheatlist+pxtmp2->dataSize)*32,iMove*32);
	memcpy(pCheatData+uiCheatlist*32,pCheatList,pxcode->dataSize*32);
	memcpy(pCheatData+(uiCheatlist+pxcode->dataSize)*32,pBuffer,iMove*32);
	backCheat = pxtmp2->dataSize ;
	pxtmp2->dataSize = pxcode->dataSize ;
	pCheatSize[xcodeIndex] = pxcode->dataSize ;

	//3.��ʼ�޸�ÿ����ڵ����ݵ�ַ�ʹ�С
	pCodeList=pLoader+0x9000+0x120*uiCodeList;
	for(i=xcodeIndex;i<cheatgame;i++)
	{
		//uiCodeList �ǵ�ǰXCOD����ʼ��ַ����
		for(j=0;j<pXCodeSize[i];j++)
		{
			origPos = *((DWORD*)(pCodeList+0x118)) ;
			origSize = *((DWORD*)(pCodeList+0x11C)) ;
			if(i!=xcodeIndex)
				*((DWORD*)(pCodeList+0x118)) = origPos + (pCheatSize[xcodeIndex]-backCheat)*0x20;
			*((DWORD*)(pCodeList+0x11C)) = pCheatSize[i];
			pCodeList+=0x120 ;
		}
	}
	if(pBuffer)
		delete pBuffer;
	if(pXCodeSize)
		delete pXCodeSize ;
	if(pCheatSize)
		delete pCheatSize ;
	return TRUE ;

}

DWORD CGoldenCheat::CountOffset(DWORD dwAddress,WORD uiNum)
{
//LDR Rd,[PC,#nn]      ;load 32bit    Rd = WORD[PC+nn]
	DWORD off = dwAddress + 4 ;
	off = (off&0xFFFFFFFC) + (uiNum&0xFF)*4 ;
	return off ;
}

BYTE CGoldenCheat::GetReturnRegisterFromGame(DWORD dwAddress,void *pGameData)
{
/* rx0
 Form|_15|_14|_13|_12|_11|_10|_9_|_8_|_7_|_6_|_5_|_4_|_3_|_2_|_1_|_0_|
 __5_|_0___1___0___0___0___1_|__Op___|Hd_|Hs_|____Rs_____|____Rd_____|HiReg/BX
 __6_|_0___1___0___0___1_|____Rd_____|_____________Word______________|LDR PC
 */
  
 	//DWORD dwAddress
	dwAddress &= 0x07FFFFFF ;
 	WORD i16Reg ;
 	WORD *pTemp = (WORD*)((DWORD)pGameData + dwAddress) ;
 	i16Reg = *pTemp ;
 	i16Reg  &= 0x7FF ;
 	i16Reg = i16Reg>>8 ;
 	return (BYTE)i16Reg ;
}

void CGoldenCheat::Set_BX_Reg(WORD *pBX , BYTE reg)
{
 /*
 Form|_15|_14|_13|_12|_11|_10|_9_|_8_|_7_|_6_|_5_|_4_|_3_|_2_|_1_|_0_|
 __5_|_0___1___0___0___0___1_|__Op___|Hd_|Hs_|____Rs_____|____Rd_____|HiReg/BX

:: BX  Rs      ;jump       PC = Rs     ;may switch THUMB/ARM
*/
	*pBX &= 0xFFC7 ;
	*pBX += (reg<<3) ;
}

void CGoldenCheat::Set_LDR_Reg(WORD *pBX , BYTE reg)
{
 /*
 Form|_15|_14|_13|_12|_11|_10|_9_|_8_|_7_|_6_|_5_|_4_|_3_|_2_|_1_|_0_|
 __6_|_0___1___0___0___1_|____Rd_____|_____________Word______________|LDR PC

:: 10-8   Rd - Destination Register   (R0..R7)
*/
	*pBX &= 0xF8FF ;
	*pBX += (reg<<8) ;
}

void CGoldenCheat::Set_POP_Reg(WORD *pBX , BYTE reg)
{
 /*
 Form|_15|_14|_13|_12|_11|_10|_9_|_8_|_7_|_6_|_5_|_4_|_3_|_2_|_1_|_0_|
 _14_|_1___0___1___1_|Op_|_1___0_|_R_|____________Rlist______________|PUSH/POP

  15-12  Must be 1011b for this type of instructions
  11     Opcode (0-1)
          0: PUSH {Rlist}{LR}   ;store in memory, decrements SP (R13)
          1: POP  {Rlist}{PC}   ;load from memory, increments SP (R13)
  10-9   Must be 10b for this type of instructions
  8      PC/LR Bit (0-1)
          0: No
          1: PUSH LR (R14), or POP PC (R15)
  7-0    Rlist - List of Registers (R7..R0)
*/
	*pBX &= 0xFF00 ;
	*pBX += 0x1<<reg ;
}

void CGoldenCheat::Set_MOV_Reg(WORD *pBX , BYTE reg)
{
 /*
 Form|_15|_14|_13|_12|_11|_10|_9_|_8_|_7_|_6_|_5_|_4_|_3_|_2_|_1_|_0_|
 __2_|_0___0___0___1___1_|_I,_Op_|___Rn/nn___|____Rs_____|____Rd_____|ADD/SUB

  15-11  Must be 00011b for 'add/subtract' instructions
  10-9   Opcode (0-3)
           0: ADD Rd,Rs,Rn   ;add register        Rd=Rs+Rn
           1: SUB Rd,Rs,Rn   ;subtract register   Rd=Rs-Rn
           2: ADD Rd,Rs,#nn  ;add immediate       Rd=Rs+nn
           3: SUB Rd,Rs,#nn  ;subtract immediate  Rd=Rs-nn
         Pseudo/alias opcode with Imm=0:
           2: MOV Rd,Rs      ;move (affects cpsr) Rd=Rs+0
 */
	*pBX &= 0xFFC7 ;
	*pBX += reg<<3 ;
}
