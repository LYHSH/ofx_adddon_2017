#pragma once
/************************************************************************/
/* project name:ͨ��
/* file describe����Ƶ�ļ����ſ������ָ�������
/* date:2016/11/20
/* author:hui
/************************************************************************/
#ifndef OFX_SOUND_PLAY_CONTROL_H
#define OFX_SOUND_PLAY_CONTROL_H
#include "ofMain.h"

static string const CMD_SOUND_PLAY = "CMD_SOUND_PLAY";				//����
static string const CMD_SOUND_PAUSE = "CMD_SOUND_PAUSE";			//��ͣ
static string const CMD_SOUND_STOP = "CMD_SOUND_STOP";				//��λ
static string const CMD_SOUND_REPLAY = "CMD_SOUND_REPLAY";			//���²���

static string const CMD_SOUND_ADD = "CMD_SOUND_ADD";				//����+
static string const CMD_SOUND_SUB = "CMD_SOUND_SUB";				//����-

static string const CMD_SOUND_MUTE = "CMD_SOUND_MUTE";				//����
static string const CMD_SOUND_UNMUTE = "CMD_SOUND_UNMUTE";			//ȡ������

static unsigned int const PORT_SOUND_CONTROL = 13777;			//���ؿ��Ƽ����˿�
#endif
