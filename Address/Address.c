#include"Address.h"
void TcharToChar(const TCHAR* tchar, char* _char)
{
	int iLength;
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//��tcharֵ����_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
char* SetFile()
{
	char szBuff[200];
	TCHAR szBuffer[MAX_PATH] = { 0 };   //���ѡ���ļ���·�� 
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("������ѡ���ļ����ļ���:");   //_T()����ͷ�ļ�tchar.h�µ�һ���궨�塣 
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);   //��ʼѡ���ļ����ļ���
	if (NULL == idl)
	{
		return 0;
	}
	SHGetPathFromIDList(idl, szBuffer);	//��ȡ����·��������szBufferֻ��洢��ǰѡ����ļ����ļ�������
	TcharToChar(szBuffer, szBuff);
	return szBuff;
}