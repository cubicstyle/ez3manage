#pragma once
class CEfaCheat
{
public:
	CEfaCheat(void);
	~CEfaCheat(void);
	BOOL	IsXCodeValid(void* pXCode,BYTE* pGameData ,UINT size );
	BOOL	CheatAddNewGame(BYTE *pGame,/*��Ϸָ�룬����ΪLoader����ʵ��������Ϸ*/
							BYTE *pPosition,/*�÷ŵ�λ�ã�Ӧ����pGame֮��*/
							BYTE *pXCode ,/*��xcode����*/
							BYTE *pCheatList,/*����ָ�б�*/
							int  cheatsize);
	BOOL	InstanceAddNewGame(BYTE *pGame,/*��Ϸָ�룬����ΪLoader����ʵ��������Ϸ*/
							BYTE *pPosition,/*�÷ŵ�λ�ã�Ӧ����pGame֮��*/
							BYTE *pXCode ,/*��xcode����*/
							BYTE *pCheatList,/*����ָ�б�*/
							int  cheatsize,
							DWORD	dwNandAddress /*nand Flash �浵λ�õ���ʼ��ַ*/
							);

	//bool	CheatEditGame(BYTE *pXCode ,/*��xcode����*/
	//						  BYTE *pCheatList,/*����ָ�б�*/
	//						  BYTE *pPostion/*��Ϸ����ָ��λ��*/);
private:
	DWORD	CountOffset(DWORD dwAddress,WORD uiNum);
	BYTE	GetResetFromXCode(void *pXCode);
	BYTE	GetReturnRegisterFromGame(DWORD dwAddress,void *pGameData);
	void	Set_BX_Reg(WORD *pBX , BYTE reg);
	void	Set_LDR_Reg(WORD *pBX , BYTE reg);
	void	Set_POP_Reg(WORD *pBX , BYTE reg);
	void	Set_MOV_Reg(WORD *pBX , BYTE reg);

};
