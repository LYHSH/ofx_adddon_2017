/************************************************************************/
/* project name:
/* file describe:��Ƶ����
/* author:hui
/* date:2016/8/17
/* date:2016/10/28(�Դ�������ع��Ż�)
/* date:2017.4.30(���²���������)
/* date:2017.9.15(������ָ�����md5����)
/* date:2018.11.6���Ӿ�Ĭ����ָ��
/* date:2019.01.29 �Ż���������ģ��
/************************************************************************/
#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxNetwork.h"
#include "videoControlCmd.h"
#include "cmdConverter.h"
#include "videoPlayerContants.h"
#ifdef OFX_HAP_VIDEO_PLAYER
#include "ofxHapPlayer.h"
#endif
#include "ofxPageBackFactory.h"
#ifdef OFX_AV_VIDEO_PLAYER
#include "frameSynAvServer.h"
#endif

#define VIDEO_EVENT_MESSAGE_NOTIFY			//��Ƶ�����¼���Ϣ֪ͨ
#define TIMELINE_MESSAGE_NOTIFY				//��Ƶ�����¼�����Ϣ֪ͨ

#ifdef TIMELINE_MESSAGE_NOTIFY
struct TIME_LINE_NODE
{
	float time;
	bool flag;
	int port;
	string ip;
	string msg;
};
#endif

typedef enum 
{
	VIDEO_PLAY,
	VIDEO_PAUSE,
	VIDEO_STOP,
	VIDEO_MUTE,
	VIDEO_UN_MUTE
}VIDEO_EVENT_TYPE;

class videoPlayer;
class videoPlayerEventArgs : public ofEventArgs {
public:
	videoPlayer * ptrSender;
	VIDEO_EVENT_TYPE eventType;
	int videoIndex;
};

class videoPlayer
{
public:
	videoPlayer(void);
	virtual ~videoPlayer(void);
	static float const STOP_POSITION;


	//��Ƶ����
	void setup(string _dir = "video/",string _settingFile = "setting.xml");
	//����ˢ��
	virtual void update();
	//������Ⱦ
	virtual void draw(float x, float y, float width, float height);
	void draw(float x,float y);
	void backImgDraw(float x, float y, float width, float height);
	void centerDraw(float _centerX, float _centerY, float _screenW, float _screenH);
	virtual void keyPressed(int key);

	//����
	void setplay();
	//��ͣ
	void setpause();
	//��λ
	void setstop();

	void setMute();
	void setUnMute();
	bool isMute();

	void setPosition(float _pos);
	float getPosition();
	int getCurFrame();
	int getTotalFrame();
	float getSeconds();

	bool isStoped();

	void reload();

	int getActiveIndex();

	static ofEvent<videoPlayerEventArgs> 		videoControlEvent;

	void clear();

	virtual void reloadVideo(int _index);
	void reloadVideoWithStop(int _index);

	int size();

	void playNextMoive();
	void playPrevMoive();

	void setSpeed(float _speed);
	void audioOut(float * output, int bufferSize, int nChannels);
protected:
	void init();
	void saveSetting(string _filename);
	void drawMessage();

	string convertStr(string _msg);

	string settingFileStr;
	string videoDirStr;
	string videoNameStr;

#ifdef OFX_MPH_VIDEO_PLAYER
	ofVideoPlayer video;
#endif
#ifdef OFX_HAP_VIDEO_PLAYER
	ofxHapPlayer video;
#endif
#ifdef OFX_AV_VIDEO_PLAYER
	frameSynAvServer video;
	ofSoundStream soundStream;
#endif
	
	vector<string> videoPaths;
	
	//UDP
	ofxUDPManager cmdRecvier;

	ofxPageBack * videoPageBack;		//����
	ofDirectory backDir;				//�����ļ�Ŀ¼
	ofFile curBackFile;					//��ǰ�����ļ�
	void loadPageBack(const ofFile & _file);

	
	ofxXmlSettings xml;
	static int const MAX_VOLUME = 255;
	static int const MIN_VOLUME = 0;
	int volume;
	void setVolume(int _volume);
	bool bIsLooping;
	void setLoop(bool _bLoop);
	bool bIsTesting;
	bool bUseBack;
	bool bRemoteControl;
	bool bMute;

	bool bGetBackimg;

	

#ifdef VIDEO_EVENT_MESSAGE_NOTIFY
#pragma region ��Ƶ�����¼���Ϣ֪ͨ

	ofxUDPManager cmdSender;
	int notifyPort;
	vector<string> notifyIps;
	void loadNotifySetting();
	void notityMessage(VIDEO_EVENT_TYPE _type);

	map<int, string> notifyMessages;

#pragma endregion ��Ƶ�����¼���Ϣ֪ͨ
#endif

#ifdef TIMELINE_MESSAGE_NOTIFY
	void sendUdpMsg(string _ip,int _port,string _msg);
	void loadTimeLineSetting();
	void timeLineReset();
	void timeLineUpdate();
	vector<TIME_LINE_NODE> timeLineNodes;
#endif

#pragma region ������˿���
	void videoFastForward();
	void videoRewind();
	int videoMoveStep;
	void loadVideoMoveSetting(string _filename = "videoMoveSetting.xml");
#pragma endregion ������˿���


	bool isStoping;


#pragma region �Ƿ�Ĭ
	bool isActive;
	void setActive(bool _state);
	bool isActiving();
#pragma endregion �Ƿ�Ĭ

#pragma region �����л�
	float lastKeyTouchTime;
#pragma endregion �����л�
};
#endif
