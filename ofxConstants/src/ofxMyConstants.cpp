#include "ofxMyConstants.h"

// void ofMyCmdSendSleep()
// {
// 	Sleep(50);
// }

void ofScreenCrossTopmost(int _w, int _h)
{
	//窗口设置
	HWND thiswnd;
	thiswnd = ofGetWin32Window();
	SetWindowLong(thiswnd, -16, 0x800000);
	SetWindowPos(thiswnd, HWND_TOPMOST, -1, -1, _w + 2, _h + 2, 0x40);
}

void ofScreenSize(int _w, int _h)
{
	//窗口设置
	HWND thiswnd;
	thiswnd = ofGetWin32Window();
	SetWindowLong(thiswnd, -16, 0x800000);
	SetWindowPos(thiswnd, HWND_NOTOPMOST, -1, -1, _w + 2, _h + 2, 0x40);
}

void ofNoWindow()
{
	//窗口设置
// 	HWND thiswnd;
// 	thiswnd = ofGetWin32Window();
// 	SetWindowLong(thiswnd, -16, 0x800000);
// 	SetWindowPos(thiswnd, HWND_BOTTOM, -10000, -10000, 1,1, 0x40);
// 	ShowWindow(thiswnd, SW_HIDE);
// 	FreeConsole();

 	HWND thiswnd;
 	thiswnd = ofGetWin32Window();
 	ShowWindow(thiswnd, SW_HIDE);
 	UpdateWindow(thiswnd);

	FreeConsole();
}