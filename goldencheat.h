// GoldenCheat.h: interface for the CGoldenCheat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOLDENCHEAT_H__A7598603_1881_4CD3_A416_80DE900A4211__INCLUDED_)
#define AFX_GOLDENCHEAT_H__A7598603_1881_4CD3_A416_80DE900A4211__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGoldenCheat    
{
public:
	BOOL CheatEditGame(BYTE *pLoader,/*��С1Mbit*/
					   BYTE *pXCode ,/*��xcode����*/
					   BYTE *pCheatList,/*����ָ�б�*/
					   int xcodeIndex/*��Ϸ������*/,
					   int cheatgame/*�н���ָ��Ϸ�ĸ���*/);
						
	BOOL CheatAddNewGame(BYTE *pLoader ,/*��С1Mbit*/
						   BYTE	*pGame , /*��Ϸ����*/
						   BYTE *pXCode ,/*��xcode����*/
						   BYTE *pCheatList,/*����ָ�б�*/
						   BYTE	entryIndex, /*�������*/
						   int xcodeIndex/*��Ϸ������*/);
	BOOL IsXCodeValid(void* pXCode,BYTE* pGameData,UINT size );
	CGoldenCheat();
	virtual ~CGoldenCheat();

protected:
	DWORD	CountOffset(DWORD dwAddress,WORD uiNum);
	BYTE	GetResetFromXCode(void *pXCode);
	BYTE	GetReturnRegisterFromGame(DWORD dwAddress,void *pGameData);
	void	Set_BX_Reg(WORD *pBX , BYTE reg);
	void	Set_LDR_Reg(WORD *pBX , BYTE reg);
	void	Set_POP_Reg(WORD *pBX , BYTE reg);
	void	Set_MOV_Reg(WORD *pBX , BYTE reg);
};

#endif // !defined(AFX_GOLDENCHEAT_H__A7598603_1881_4CD3_A416_80DE900A4211__INCLUDED_)
