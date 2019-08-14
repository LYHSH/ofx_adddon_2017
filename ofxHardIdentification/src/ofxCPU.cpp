//--------------------------------------------------------------  
//                      CPU���к�  
//--------------------------------------------------------------  
#include "ofxCPU.h"
BOOL GetCpuByCmd(char *lpszCpu, int len/*=128*/)
{
	const long MAX_COMMAND_SIZE = 10000; // ��������������С     
#ifdef UNICODE
	WCHAR szFetCmd[] = L"wmic cpu get processorid"; // ��ȡCPU���к������� 
#else
	char szFetCmd[] = "wmic cpu get processorid"; // ��ȡCPU���к������� 
#endif // !UNICODE
	   
	const string strEnSearch = "ProcessorId"; // CPU���кŵ�ǰ����Ϣ  

	BOOL   bret = FALSE;
	HANDLE hReadPipe = NULL; //��ȡ�ܵ�  
	HANDLE hWritePipe = NULL; //д��ܵ�      
	PROCESS_INFORMATION pi;   //������Ϣ      
	STARTUPINFO         si;   //���������д�����Ϣ  
	SECURITY_ATTRIBUTES sa;   //��ȫ����  

	char            szBuffer[MAX_COMMAND_SIZE + 1] = { 0 }; // ���������н�������������  
	string          strBuffer;
	unsigned long   count = 0;
	long            ipos = 0;

	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));
	memset(&sa, 0, sizeof(sa));

	pi.hProcess = NULL;
	pi.hThread = NULL;
	si.cb = sizeof(STARTUPINFO);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//1.0 �����ܵ�  
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		goto END;
	}

	//2.0 ���������д��ڵ���ϢΪָ���Ķ�д�ܵ�  
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //���������д���  
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//3.0 ������ȡ�����еĽ���  
	bret = CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (!bret)
	{
		goto END;
	}

	//4.0 ��ȡ���ص�����  
	int rrr = WaitForSingleObject(pi.hProcess, 4000/*INFINITE*/); 
	if (WAIT_OBJECT_0 == rrr)
	{
		cout << "wait sucess" << endl;
	}
	else if (WAIT_ABANDONED == rrr)
	{
		cout << "wait mutex error" << endl;
	}
	else if (WAIT_TIMEOUT == rrr)
	{
		cout << "wait timeout" << endl;
	}
	else if (WAIT_FAILED == rrr)
	{
		cout << "wait failed" << endl;
	}
	
	bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
	if (!bret)
	{
		goto END;
	}

	//5.0 ����CPU���к�  
	bret = FALSE;
	strBuffer = szBuffer;
	ipos = strBuffer.find(strEnSearch);

	if (ipos < 0) // û���ҵ�  
	{
		goto END;
	}
	else
	{
		strBuffer = strBuffer.substr(ipos + strEnSearch.length());
	}

	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());

	//ȥ���м�Ŀո� \r \n  
	int j = 0;
	for (int i = 0; i < strlen(szBuffer); i++)
	{
		if (szBuffer[i] != ' ' && szBuffer[i] != '\n' && szBuffer[i] != '\r')
		{
			lpszCpu[j] = szBuffer[i];
			j++;
		}
	}
	lpszCpu[j] = '\0';

	bret = TRUE;

END:
	//�ر����еľ��  
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return(bret);
}