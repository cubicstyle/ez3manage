//ini�ļ���д��
//����3����������.�ֱ���
//iniopen(char FileName,int Itemcount)  �򿪻���INI�ļ�
//FileName:�ļ���     Itemcount:�����(�ø�����������ļ�����Ŀ����)
//char *iniread(char* Items)            ���ֶ�ֵ
//Items:�ֶ���  ����ֵ:�ֶ�ֵ
//iniwrite(char *Items,char *ItemValute)   д�ֶ������ֶ�ֵ 
//Items:�ֶ���  ItemValute:�ֶ�ֵ
//inimodify(char *Items,char *ItemValute)   �޸��ֶ������ֶ�ֵ 
//Items:�ֶ���  ItemValute:�ֶ�ֵ
//������  ���


class  CFileini
{

public:
	 
     int  iniopen(char  *FileName,int It);
	 char* iniread(char *Item);
	 iniwrite(char *Item,  char *ItemValue);
	 char*  inimodify(char *Item,char *ItemValue);
	 CFileini();
	 ~CFileini();

protected:
	char inifilename[512];
	 char **Items;
	 char **ItemValues;
	 int Itemcount;
	 int newcount;
	 FILE *fp; 
 

};