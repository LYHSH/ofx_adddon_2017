/************************************************************************/
/* project name:ͨ��
/* file describe��VLC��Ƶ���ſ������ָ�������
/* date:2016/8/13
/* author:hui
/************************************************************************/
#ifndef VIDEO_CONTROL_CMD_H
#define VIDEO_CONTROL_CMD_H
#include "ofMain.h"
static string const CMD_MOVIE_PLAY = "guoguo_play";				//����
static string const CMD_MOVIE_PAUSE = "guoguo_pause";			//��ͣ
static string const CMD_MOVIE_STOP = "guoguo_stop";				//��λ

static string const CMD_MOVIE_REPLAY = "guoguo_replay";			//���²���
static string const CMD_MOVIE_LOOP = "guoguo_loop";				//����Ϊѭ������
static string const CMD_MOVIE_NOLOOP = "guoguo_noloop";			//����Ϊ���β���

static string const CMD_VOLUME_ADD = "volume_add";				//����+
static string const CMD_VOLUME_SUB = "volume_sub";				//����-

static string const CMD_VOLUME_ON = "volume_on";				//������
static string const CMD_VOLUME_OFF = "volume_off";				//������


static string const FLAG_MOVIE_INDEX = "flagMovieIndex";		//ӰƬ��ű�־
static string const SEPERATOR_MOVIE_INDEX = ":";				//�ָ���
static int const MAX_MOVIE_INDEX = 50;							//ӰƬ������ֵ
static int const MIN_MOVIE_INDEX = 0;							//ӰƬ�����Сֵ
//msg:FLAG_MOVIE_INDEX+SEPERATOR_MOVIE_INDEX+INDEX

static string const CMD_PRVE_MOVIE = "prev_movie";				//��һ��
static string const CMD_NEXT_MOVIE = "next_movie";				//��һ��

static string const CMD_FAST_FORWARD = "fast_froward";				//���
static string const CMD_REWIND = "rewind";						//����

static unsigned int const PORT_MOVIE_CONTROL = 13666;			//���ؿ��Ƽ����˿�
//static unsigned int const PORT_MOVIE_CONTROL = 5051;			//���ؿ��Ƽ����˿�

static string const CMD_ACTIVE_TRUE = "set_active_true";				//����
static string const CMD_ACTIVE_FALSE = "set_active_false";				//��Ĭ
#endif