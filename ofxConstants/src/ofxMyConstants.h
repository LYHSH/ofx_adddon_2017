#pragma once
/************************************************************************/
/* file describe:
/* author:hui
/* date:2018.1.29
/************************************************************************/
#include "ofMain.h"

#ifndef OF_FUNCTION_NAME
#define  OF_FUNCTION_NAME (__FUNCTION__)			//���ں�������
#endif

//void ofMyCmdSendSleep();							//ָ��ͼ���ȴ�

void ofScreenCrossTopmost(int _w,int _h);			//��������ö�
void ofScreenSize(int _w, int _h);					//���û����С

void ofNoWindow();									//����ʾ����
//#define LOCAL_DEBUG 0

