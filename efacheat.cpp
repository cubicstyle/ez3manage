#include "StdAfx.h"
#include "cheatcode.h"
#include ".\efacheat.h"
#include "instance.h"
#include "New_EZManageDlg.h"
CEfaCheat::CEfaCheat(void)
{
}

CEfaCheat::~CEfaCheat(void)
{
}


DWORD CEfaCheat::CountOffset(DWORD dwAddress,WORD uiNum)
{
//LDR Rd,[PC,#nn]      ;load 32bit    Rd = WORD[PC+nn]
	DWORD off = dwAddress + 4 ;
	off = (off&0xFFFFFFFC) + (uiNum&0xFF)*4 ;
	return off ;
}

BYTE CEfaCheat::GetReturnRegisterFromGame(DWORD dwAddress,void *pGameData)
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

void CEfaCheat::Set_BX_Reg(WORD *pBX , BYTE reg)
{
 /*
 Form|_15|_14|_13|_12|_11|_10|_9_|_8_|_7_|_6_|_5_|_4_|_3_|_2_|_1_|_0_|
 __5_|_0___1___0___0___0___1_|__Op___|Hd_|Hs_|____Rs_____|____Rd_____|HiReg/BX

:: BX  Rs      ;jump       PC = Rs     ;may switch THUMB/ARM
*/
	*pBX &= 0xFFC7 ;
	*pBX += (reg<<3) ;
}

void CEfaCheat::Set_LDR_Reg(WORD *pBX , BYTE reg)
{
 /*
 Form|_15|_14|_13|_12|_11|_10|_9_|_8_|_7_|_6_|_5_|_4_|_3_|_2_|_1_|_0_|
 __6_|_0___1___0___0___1_|____Rd_____|_____________Word______________|LDR PC

:: 10-8   Rd - Destination Register   (R0..R7)
*/
	*pBX &= 0xF8FF ;
	*pBX += (reg<<8) ;
}

void CEfaCheat::Set_POP_Reg(WORD *pBX , BYTE reg)
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

void CEfaCheat::Set_MOV_Reg(WORD *pBX , BYTE reg)
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

BOOL CEfaCheat::IsXCodeValid(void* pXCode,BYTE* pGameData ,UINT size )
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

BOOL CEfaCheat::CheatAddNewGame(BYTE *pGame,/*��Ϸָ�룬����ΪLoader����ʵ��������Ϸ*/
								BYTE *pPosition,/*�÷ŵ�λ�ã�Ӧ����pGame֮��*/
								BYTE *pXCode ,/*��xcode����*/
							    	BYTE *pCheatList,/*����ָ�б�*/
							    	int  cheatsize)
{

#define BINSIZE 0x1E0
#define CODESIZE 448 //0x1C0
#define MODIFYBASE 0x150
	PXCODE		pxcode = (PXCODE)pXCode ;
	PCODE		pcode = (PCODE)(pXCode+24) ;
	PGOLD_DATA	pgolddata = (PGOLD_DATA)pCheatList ;
	BYTE		gamedata[BINSIZE] ;
	BYTE		*pPos = NULL;
	int			iPos = 0 ;
	int 		iDataIndex = 0 , iSize = 0 ;
	BYTE rx0 , rx1 ;
	WORD  ui16Replaced;
	DWORD dwCheatDataAddress , dwCodeAddress , dwDataOffset , secondOff, secondLdr = 0;

	//1���ȷ���XCODE
	memcpy(pPosition,pxcode,(pxcode->CodeSize*8+24));
	iPos += (pxcode->CodeSize*8+24);
	pPos = pPosition + iPos ;
	//2.׼����Ϸ���ݵ��޸�
	for(int i=0 ; i<pxcode->CodeSize ; i++)
	{
		//����cheat ����
		memset(gamedata,0,BINSIZE);
		memcpy(gamedata,cheatcode,CODESIZE);
		//�˵�ַΪ0x04000130��ַ
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
		//������ת�ĵ�ַ
		dwCheatDataAddress = 0x8000000+(pPosition-pGame)+(pxcode->CodeSize*8+24)+i*BINSIZE;
		//�޸ĳ�������Ҫ�Ķ������ݣ��Լ��Ĵ���
		*((DWORD*)(gamedata+0x1AC)) = dwCheatDataAddress + BINSIZE - 8 ; //���ص�����ָ��λ��
		dwCodeAddress |= 0x08000000 ;
		*((DWORD*)(gamedata+0x1B8)) = dwCodeAddress + 5 ;     //�����Ƿ��ص�ַ
		//�޸�pop {rx0}
		Set_POP_Reg((WORD*)(gamedata+MODIFYBASE),rx0);
		//�޸� mov lr ,rx0
		Set_MOV_Reg((WORD*)(gamedata+MODIFYBASE+2),rx0);
		//�޸�ldr rx0 , =0x04000130
		Set_LDR_Reg((WORD*)(gamedata+MODIFYBASE+4),rx0);
		//��ԭ�������ݿ��������ڵ�����
		if((ui16Replaced&0x4800) == 0x4800)//�����Loader
		{
			dwCodeAddress &= 0x07FFFFFF ;
			secondOff = CountOffset(dwCodeAddress+2,*(WORD*)(dwCodeAddress+2+(BYTE*)pGame));
			secondLdr = *(DWORD*)(pGame+secondOff) ;
			ui16Replaced &= 0xFF00 ;
			ui16Replaced += 0x17 ;
			dwCodeAddress |= 0x08000000 ;
		}
		*(WORD*)(gamedata+MODIFYBASE+6) = ui16Replaced ;
		*((DWORD*)(gamedata+0x1B4)) = secondLdr ;
		//�޸�ldr rx1 , JUMPBACK ADDRESS
		Set_LDR_Reg((WORD*)(gamedata+MODIFYBASE+8),rx1);
		//�޸� BX RX1 
		Set_BX_Reg((WORD*)(gamedata+MODIFYBASE+0xa),rx1);

		*((DWORD*)(gamedata+BINSIZE-8)) = 0x8000000+(pPosition-pGame)+(pxcode->CodeSize*8+24) + BINSIZE*pxcode->CodeSize ;
		*((DWORD*)(gamedata+BINSIZE-4)) = pxcode->dataSize ;

		memcpy(pPosition+iPos,gamedata,BINSIZE) ;
		iPos += BINSIZE ;
	//3. �޸���Ϸ��
		ui16Replaced = 0x4700; // bx r0 ;
		//��0x04000130�޸�Ϊ��ת��ַ
		*((DWORD*)(pGame+dwDataOffset))=dwCheatDataAddress+1 ;
		//�޸� BX RX0 
		Set_BX_Reg((WORD*)(&ui16Replaced),rx0);
		dwCodeAddress &= 0x7FFFFFF ;
		*((WORD*)((UINT)pGame+dwCodeAddress+2)) = ui16Replaced ;
	}

	//4.����Ϸ����ָ���ݷ��ں���λ��
	iSize = pxcode->dataSize ;
	if(iSize>0)
	{
		PGOLD_DATA pgoldtmp =(PGOLD_DATA) (pPosition+(pxcode->CodeSize*8+24) + BINSIZE*pxcode->CodeSize);
		memcpy(pgoldtmp,pgolddata,cheatsize);
	}
	
	return TRUE ;
}

BOOL CEfaCheat::InstanceAddNewGame(BYTE *pGame,/*��Ϸָ�룬����ΪLoader����ʵ��������Ϸ*/
								BYTE *pPosition,/*�÷ŵ�λ�ã�Ӧ����pGame֮��*/
								BYTE *pXCode ,/*��xcode����*/
							    BYTE *pCheatList,/*����ָ�б�*/
							    int  cheatsize,
								DWORD	dwNandAddress /*nand Flash �浵λ�õ���ʼ��ַ*/
									)
{
#define INC_BINSIZE 0x6C0
#define INC_CODESIZE 0x69c //0x1C0
#define INC_MODIFYBASE 0x16c
	PXCODE		pxcode = (PXCODE)pXCode ;
	PCODE		pcode = (PCODE)(pXCode+24) ;
	PGOLD_DATA	pgolddata = (PGOLD_DATA)pCheatList ;
	BYTE		gamedata[INC_BINSIZE] ;
	BYTE		*pPos = NULL;
	int			iPos = 0 ;
	int 		iDataIndex = 0 , iSize = 0 ;
	BYTE rx0 , rx1 ;
	WORD  ui16Replaced;
	DWORD dwCheatDataAddress , dwCodeAddress , dwDataOffset , secondOff, secondLdr = 0;

	//1���ȷ���XCODE
	memcpy(pPosition,pxcode,(pxcode->CodeSize*8+24));
	iPos += (pxcode->CodeSize*8+24);
	pPos = pPosition + iPos ;
	//2.׼����Ϸ���ݵ��޸�
	for(int i=0 ; i<pxcode->CodeSize ; i++)
	{
		//����cheat ����
		memset(gamedata,0,INC_BINSIZE);
		memcpy(gamedata,instance,INC_CODESIZE);
		//�˵�ַΪ0x04000130��ַ
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
		//������ת�ĵ�ַ
		dwCheatDataAddress = 0x8000000+(pPosition-pGame)+(pxcode->CodeSize*8+24)+i*INC_BINSIZE;
		//�޸ĳ�������Ҫ�Ķ������ݣ��Լ��Ĵ���
		*((DWORD*)(gamedata+0x1CC)) = dwCheatDataAddress + INC_BINSIZE - 8 ; //���ص�����ָ��λ��
		dwCodeAddress |= 0x08000000 ;
		*((DWORD*)(gamedata+0x1D8)) = dwCodeAddress + 5 ;     //�����Ƿ��ص�ַ
		//�޸�pop {rx0}
		Set_POP_Reg((WORD*)(gamedata+INC_MODIFYBASE),rx0);
		//�޸� mov lr ,rx0
		Set_MOV_Reg((WORD*)(gamedata+INC_MODIFYBASE+2),rx0);
		//�޸�ldr rx0 , =0x04000130
		Set_LDR_Reg((WORD*)(gamedata+INC_MODIFYBASE+4),rx0);
		//��ԭ�������ݿ��������ڵ�����
		if((ui16Replaced&0x4800) == 0x4800)//�����Loader
		{
			dwCodeAddress &= 0x07FFFFFF ;
			secondOff = CountOffset(dwCodeAddress+2,*(WORD*)(dwCodeAddress+2+(BYTE*)pGame));
			secondLdr = *(DWORD*)(pGame+secondOff) ;
			ui16Replaced &= 0xFF00 ;
			ui16Replaced += 0x17 ;
			dwCodeAddress |= 0x08000000 ;
		}
		*(WORD*)(gamedata+INC_MODIFYBASE+6) = ui16Replaced ;
		*((DWORD*)(gamedata+0x1D4)) = secondLdr ;
		//�޸�ldr rx1 , JUMPBACK ADDRESS
		Set_LDR_Reg((WORD*)(gamedata+INC_MODIFYBASE+8),rx1);
		//�޸� BX RX1 
		Set_BX_Reg((WORD*)(gamedata+INC_MODIFYBASE+0xa),rx1);
	
		DWORD k = INC_BINSIZE*pxcode->CodeSize ;
		*((DWORD*)(gamedata+INC_BINSIZE-8)) = 0x8000000+(pPosition-pGame)+(pxcode->CodeSize*8+24) + k ;
		*((DWORD*)(gamedata+INC_BINSIZE-4)) = pxcode->dataSize ;

		//.�޸�nand�ı����ַ
		*(DWORD*)(gamedata+0x668) = dwNandAddress ;
		memcpy(pPosition+iPos,gamedata,INC_BINSIZE) ;
		iPos += INC_BINSIZE ;
	//3. �޸���Ϸ��
		ui16Replaced = 0x4700; // bx r0 ;
		//��0x04000130�޸�Ϊ��ת��ַ
		*((DWORD*)(pGame+dwDataOffset))=dwCheatDataAddress+1 ;
		//�޸� BX RX0 
		Set_BX_Reg((WORD*)(&ui16Replaced),rx0);
		dwCodeAddress &= 0x7FFFFFF ;
		*((WORD*)((UINT)pGame+dwCodeAddress+2)) = ui16Replaced ;
	}

	//4.����Ϸ����ָ���ݷ��ں���λ��
	iSize = pxcode->dataSize ;
	if(iSize>0)
	{
		PGOLD_DATA pgoldtmp =(PGOLD_DATA) (pPosition+(pxcode->CodeSize*8+24) + INC_BINSIZE*pxcode->CodeSize);
		memcpy(pgoldtmp,pgolddata,cheatsize);
	}

	return TRUE ;
}



/*
BOOL CEfaCheat::CheatEditGame(BYTE *pXCode ,
							  BYTE *pCheatList,
							  BYTE *pPostion)
{
	PXCODE		pxcode = (PXCODE)pXCode ;
	PCODE		pcode = (PCODE)(pXCode+24) ;
	PGOLD_DATA	pgolddata = (PGOLD_DATA)pCheatList ;
	PXCODE pxtmp = (PXCODE)(pPostion);
	int iPos = 0,iSize=0,i=0;
	//1.�Ƚ�xcode��һ����
	if(memcmp(pxcode->gameName,pxtmp->gameName,12))
	{
		return FALSE ;
	}
	iPos += ( pxcode->CodeSize*8+24);
	//2.��ʼ�޸�ÿ����ڵ����ݵ�ַ�ʹ�С
	for(i=0;i<pxcode->CodeSize;i++)
	{
		*((DWORD*)(pPostion+iPos+0x14C)) = pxcode->dataSize;
		iPos += 0x150 ;
	}
	//2. copy ����ָ����
	iSize = pxcode->dataSize ;
	if(iSize>0)
	{
		PGOLD_DATA pgoldtmp =(PGOLD_DATA) (pPostion +(pxcode->CodeSize*8+24) + 0x150*pxcode->CodeSize);
		memcpy(pgoldtmp,pgolddata,iSize*0x20);
	}

	return TRUE ;
}
*/
