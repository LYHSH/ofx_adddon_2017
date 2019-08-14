#pragma once
/************************************************************************/
/* project name:通用
/* file describe：音频文件播放控制相关指令定义声明
/* date:2016/11/20
/* author:hui
/************************************************************************/
#ifndef OFX_SOUND_PLAY_CONTROL_H
#define OFX_SOUND_PLAY_CONTROL_H
#include "ofMain.h"

static string const CMD_SOUND_PLAY = "CMD_SOUND_PLAY";				//播放
static string const CMD_SOUND_PAUSE = "CMD_SOUND_PAUSE";			//暂停
static string const CMD_SOUND_STOP = "CMD_SOUND_STOP";				//复位
static string const CMD_SOUND_REPLAY = "CMD_SOUND_REPLAY";			//重新播放

static string const CMD_SOUND_ADD = "CMD_SOUND_ADD";				//音量+
static string const CMD_SOUND_SUB = "CMD_SOUND_SUB";				//音量-

static string const CMD_SOUND_MUTE = "CMD_SOUND_MUTE";				//静音
static string const CMD_SOUND_UNMUTE = "CMD_SOUND_UNMUTE";			//取消静音

static unsigned int const PORT_SOUND_CONTROL = 13777;			//本地控制监听端口
#endif
