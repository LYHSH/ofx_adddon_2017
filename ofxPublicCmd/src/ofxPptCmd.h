#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name:pptԶ�̿�ݰ����������
/* file describe��pptԶ�̿���ָ�������
/* date:2017/4/7
/* author:hui
/************************************************************************/

static int const PPT_LISTEN_PORT = 35555;			//�����˿�

static string const CMD_PPT_NEXT_PAGE = "cmd_ppt_next_page";			//ִ����һ�������򻻵���һ�Żõ�Ƭ
static string const CMD_PPT_PREV_PAGE = "cmd_ppt_prev_page";			//ִ����һ�������򷵻���һ�Żõ�Ƭ
static string const CMD_PPT_SWITCH_PAGE = "cmd_ppt_switch_page";		//��ת����ָ����Żõ�Ƭ,ָ���ʽ�� CMD_PPT_SWITCH_PAGE:index;(ָ��ǰ׺+�õ�Ƭ��ţ��м���ð�Ÿ���)
static string const CMD_PPT_RESET_PAGE = "cmd_ppt_reset";				//��λ

static string const DELIMITER_PPT_CMD = ":";							//ָ��ָ���
static string const CMD_PPT_VIDEO_PLAY_OR_PAUSE = "cmd_ppt_video_play_or_pause";	//��ǰ�õ�Ƭ�������Ϊ��Ƶ���򲥷�/��ͣ��Ƶ������Ϊִ����һҳЧ����


