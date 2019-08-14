/************************************************************************/
/* project name:通用
/* file describe：VLC视频播放控制相关指令定义声明
/* date:2016/8/13
/* author:hui
/************************************************************************/
#ifndef VIDEO_CONTROL_CMD_H
#define VIDEO_CONTROL_CMD_H
#include "ofMain.h"
static string const CMD_MOVIE_PLAY = "guoguo_play";				//播放
static string const CMD_MOVIE_PAUSE = "guoguo_pause";			//暂停
static string const CMD_MOVIE_STOP = "guoguo_stop";				//复位

static string const CMD_MOVIE_REPLAY = "guoguo_replay";			//重新播放
static string const CMD_MOVIE_LOOP = "guoguo_loop";				//设置为循环播放
static string const CMD_MOVIE_NOLOOP = "guoguo_noloop";			//设置为单次播放

static string const CMD_VOLUME_ADD = "volume_add";				//声音+
static string const CMD_VOLUME_SUB = "volume_sub";				//声音-

static string const CMD_VOLUME_ON = "volume_on";				//声音开
static string const CMD_VOLUME_OFF = "volume_off";				//声音关


static string const FLAG_MOVIE_INDEX = "flagMovieIndex";		//影片序号标志
static string const SEPERATOR_MOVIE_INDEX = ":";				//分隔符
static int const MAX_MOVIE_INDEX = 50;							//影片序号最大值
static int const MIN_MOVIE_INDEX = 0;							//影片序号最小值
//msg:FLAG_MOVIE_INDEX+SEPERATOR_MOVIE_INDEX+INDEX

static string const CMD_PRVE_MOVIE = "prev_movie";				//上一首
static string const CMD_NEXT_MOVIE = "next_movie";				//上一首

static string const CMD_FAST_FORWARD = "fast_froward";				//快进
static string const CMD_REWIND = "rewind";						//快退

static unsigned int const PORT_MOVIE_CONTROL = 13666;			//本地控制监听端口
//static unsigned int const PORT_MOVIE_CONTROL = 5051;			//本地控制监听端口

static string const CMD_ACTIVE_TRUE = "set_active_true";				//激活
static string const CMD_ACTIVE_FALSE = "set_active_false";				//静默
#endif