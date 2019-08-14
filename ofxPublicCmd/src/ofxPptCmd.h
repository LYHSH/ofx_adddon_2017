#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:ppt远程快捷按键控制软件
/* file describe：ppt远程控制指令常量定义
/* date:2017/4/7
/* author:hui
/************************************************************************/

static int const PPT_LISTEN_PORT = 35555;			//监听端口

static string const CMD_PPT_NEXT_PAGE = "cmd_ppt_next_page";			//执行下一个动画或换到下一张幻灯片
static string const CMD_PPT_PREV_PAGE = "cmd_ppt_prev_page";			//执行上一个动画或返回上一张幻灯片
static string const CMD_PPT_SWITCH_PAGE = "cmd_ppt_switch_page";		//跳转到到指定编号幻灯片,指令格式： CMD_PPT_SWITCH_PAGE:index;(指令前缀+幻灯片编号，中间以冒号隔开)
static string const CMD_PPT_RESET_PAGE = "cmd_ppt_reset";				//复位

static string const DELIMITER_PPT_CMD = ":";							//指令分隔符
static string const CMD_PPT_VIDEO_PLAY_OR_PAUSE = "cmd_ppt_video_play_or_pause";	//当前幻灯片画面如果为视频，则播放/暂停视频；否则为执行下一页效果。


