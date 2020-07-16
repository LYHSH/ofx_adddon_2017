#pragma once
/************************************************************************/
/* file describe:
/* author:hui
/* date:2018.1.29
/************************************************************************/
#include "ofMain.h"

#ifndef OF_FUNCTION_NAME
#define  OF_FUNCTION_NAME (__FUNCTION__)			//所在函数名称
#endif

//void ofMyCmdSendSleep();							//指令发送间隔等待

void ofScreenCrossTopmost(int _w,int _h);			//画面跨屏置顶
void ofScreenSize(int _w, int _h);					//设置画面大小

void ofNoWindow();									//不显示界面
//#define LOCAL_DEBUG 0

