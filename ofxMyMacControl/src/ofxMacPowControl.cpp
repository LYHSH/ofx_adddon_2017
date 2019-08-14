#include "ofxMacPowControl.h"


static bool m_bWinsockInit = false;
ofxMacPowControl::ofxMacPowControl()
{
	if (m_bWinsockInit) {
		unsigned short vr;
		WSADATA	wsaData;
		vr = MAKEWORD(2, 2);
		WSAStartup(vr, &wsaData);
		m_bWinsockInit = true;
	}
}


ofxMacPowControl::~ofxMacPowControl()
{
}

void ofxMacPowControl::setup()
{
	udpConnection.Create();
	udpConnection.SetNonBlocking(true);


	m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_hSocket != INVALID_SOCKET)
	{		
		int unused = true;
		setsockopt(m_hSocket, SOL_SOCKET, SO_BROADCAST, (char*)&unused, sizeof(unused));
	}

	memset((void*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);
//	addr.sin_addr.s_addr = inet_addr("255.255.255.255");//π„≤•µÿ÷∑
	addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);

	bool nonBlocking = true;

#ifdef TARGET_WIN32
	unsigned long arg = nonBlocking;
	int retVal = ioctlsocket(m_hSocket, FIONBIO, &arg);
#else
	int arg = nonBlocking;
	int retVal = ioctl(m_hSocket, FIONBIO, &arg);
#endif
}

void ofxMacPowControl::powOn(string macStr)
{
	ofLogNotice(OF_FUNCTION_NAME) << macStr << endl;
	//Buffer for packet
	char magicP[102];

	for (int i = 0; i < 6; i++)
         magicP[i] = 0xff;

	vector <string> sss = ofSplitString(macStr, "-");
	for (int i = 0; i < 6; i++)
		magicP[i + 6] = ofHexToInt(sss[i].c_str());

	//fill remaining 90 bytes (15 time repeat)
	//Warning : It is higly recommended not to use functions like
	//memcpy, read MSDN for more details.
	for (int i = 0; i < 15; i++)
		memcpy(&magicP[(i + 2) * 6], &magicP[6], 6);

	int res = sendto(m_hSocket, magicP, 102, 0, (struct sockaddr *)&addr, sizeof(addr));
}
void ofxMacPowControl::powOff(string ip)
{
	ofLogNotice(OF_FUNCTION_NAME) << ip << endl;

	static const string msg = "shutdown";

	udpConnection.Connect(ip.c_str(), 1000);
	udpConnection.Send(msg.c_str(), msg.length());

	Sleep(100);

	udpConnection.Connect(ip.c_str(), 30801);
	udpConnection.Send(msg.c_str(), msg.length());
}