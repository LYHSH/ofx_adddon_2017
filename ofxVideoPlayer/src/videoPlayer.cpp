#include "videoPlayer.h"


float const videoPlayer::STOP_POSITION = 0.0f;
ofEvent <videoPlayerEventArgs> videoPlayer::videoControlEvent;
videoPlayer::videoPlayer(void)
{
	bGetBackimg = false;
	bMute = false;
	isActive = true;
	lastKeyTouchTime = 0.0f;

	videoPageBack = NULL;
}


videoPlayer::~videoPlayer(void)
{
	//video.closeMovie();
	video.close();

	if (videoPageBack)
	{
		delete videoPageBack;
		videoPageBack = NULL;
	}
}

void videoPlayer::setup(string _dir /* = "video/" */,string _settingFile /* = "setting.xml" */)
{
	videoDirStr = _dir;
	settingFileStr = _settingFile;

	init();

	loadNotifySetting();

#ifdef TIMELINE_MESSAGE_NOTIFY
	loadTimeLineSetting();
#endif

	loadVideoMoveSetting();

	isStoping = false;

#ifdef OFX_AV_VIDEO_PLAYER
	soundStream.setup(ofGetAppPtr(), 2, 0, 44100, 512, 4);
#endif
}

void videoPlayer::update()
{
	if (bRemoteControl)
	{
		//UDP
		char udpMessage[100];
		cmdRecvier.Receive(udpMessage, 100);
		string message = udpMessage;
		if (message != "") {
			ofLogNotice() << "receive:" << message<<endl;
			if (cmdConverter::getEncryCmd(CMD_ACTIVE_TRUE) == message)
			{
				ofLogNotice() << "set avtive true" << endl;
				setActive(true);
			}
			else if (cmdConverter::getEncryCmd(CMD_ACTIVE_FALSE) == message)
			{
				ofLogNotice() << "set avtive false" << endl;
				setActive(false);
				setstop();
			}
			
			if (isActiving())
			{
#pragma region 控制指令
				if (cmdConverter::getEncryCmd(CMD_MOVIE_PLAY) == message)
				{
					ofLogNotice() << "movie play" << endl;
					setplay();
				}
				else if (cmdConverter::getEncryCmd(CMD_MOVIE_PAUSE) == message)
				{
					ofLogNotice() << "movie pause" << endl;
					setpause();
				}
				else if (cmdConverter::getEncryCmd(CMD_MOVIE_STOP) == message)
				{
					ofLogNotice() << "movie stop" << endl;
					setstop();
				}
				else if (cmdConverter::getEncryCmd(CMD_MOVIE_REPLAY) == message)
				{
					ofLogNotice() << "movie replay" << endl;
					setstop();
					setplay();
				}
				else if (cmdConverter::getEncryCmd(CMD_MOVIE_LOOP) == message)
				{
					bIsLooping = true;
					bIsLooping ? video.setLoopState(OF_LOOP_NORMAL) : video.setLoopState(OF_LOOP_NONE);
					xml.setValue("loop", bIsLooping);
					xml.saveFile();
				}
				else if (cmdConverter::getEncryCmd(CMD_MOVIE_NOLOOP) == message)
				{
					bIsLooping = false;
					bIsLooping ? video.setLoopState(OF_LOOP_NORMAL) : video.setLoopState(OF_LOOP_NONE);
					xml.setValue("loop", bIsLooping);
					xml.saveFile();
				}
				else if (cmdConverter::getEncryCmd(CMD_VOLUME_ADD) == message)
				{
					volume += 5;
					if (volume > MAX_VOLUME)
					{
						volume = MAX_VOLUME;
					}
					setVolume(volume);
					xml.setValue("volume", int(volume));
					xml.saveFile();
				}
				else if (cmdConverter::getEncryCmd(CMD_VOLUME_SUB) == message)
				{
					volume -= 5;
					if (volume < MIN_VOLUME)
					{
						volume = MIN_VOLUME;
					}
					setVolume(volume);
					xml.setValue("volume", int(volume));
					xml.saveFile();
				}
				else if (cmdConverter::getEncryCmd(CMD_VOLUME_ON) == message)
				{
					setUnMute();
				}
				else if (cmdConverter::getEncryCmd(CMD_VOLUME_OFF) == message)
				{
					setMute();
				}
				else if (cmdConverter::getEncryCmd(CMD_NEXT_MOVIE) == message)
				{
					playNextMoive();
				}
				else if (cmdConverter::getEncryCmd(CMD_PRVE_MOVIE) == message)
				{
					playPrevMoive();
				}
				else if (cmdConverter::getEncryCmd(CMD_FAST_FORWARD) == message)
				{
					videoFastForward();
				}
				else if (cmdConverter::getEncryCmd(CMD_REWIND) == message)
				{
					videoRewind();
				}
				else
				{
					for (int movieIndex = MIN_MOVIE_INDEX; movieIndex <= MAX_MOVIE_INDEX; movieIndex++)
					{
						string movieIndexStr = FLAG_MOVIE_INDEX + SEPERATOR_MOVIE_INDEX + ofToString(movieIndex);
						if (message == convertStr(movieIndexStr))
						{
							reloadVideo(movieIndex);
							break;
						}
					}
				}
#pragma endregion
			}
		}
	}
	
	video.update();

	if (video.getIsMovieDone() || video.getCurrentFrame() > (video.getTotalNumFrames() - 5))
	{
		if (!bIsLooping)
		{
			setstop();
			ofLogNotice()<<"movie is done"<<endl;
		}
	}

#ifdef TIMELINE_MESSAGE_NOTIFY
	timeLineUpdate();
#endif

	if (videoPageBack)
	{
		videoPageBack->update();
	}
}

void videoPlayer::draw(float x, float y, float width, float height)
{
	video.draw(x, y, width, height);

	if (!bIsLooping || isStoping)
	{
		if (video.getPosition() == STOP_POSITION)
		{
			if (bUseBack)
			{
				if (videoPageBack)
				{
					videoPageBack->draw(x, y, width, height);
				}
				
			}
			else
			{
				ofPushStyle();
				ofSetColor(0);
				ofFill();
				ofRect(x - 5, y - 5, width + 10, height + 10);
				ofPopStyle();
			}
		}
	}
	

	if (bGetBackimg)
	{
		ofImage img;
		img.grabScreen(0, 0, width, height);
		img.saveImage(curBackFile.path());
		bGetBackimg = false;
	}

	drawMessage();
}

void videoPlayer::draw(float x, float y)
{
	draw(x, y, video.getWidth(), video.getHeight());
}

void videoPlayer::backImgDraw(float x, float y, float width, float height)
{
	if (videoPageBack)
	{
		videoPageBack->draw(x, y, width, height);
	}
}

void videoPlayer::centerDraw(float _centerX, float _centerY, float _screenW, float _screenH)
{
	float w = _screenW;
	float h = _screenH;

	if (video.getPosition() != STOP_POSITION)
	{
		if ((w/video.getWidth()) < (h/video.getHeight()))
		{
			w = _screenW;
			h = w * (video.getHeight()/video.getWidth());
		}
		else
		{
			h = _screenH;
			w = h * (video.getWidth()/video.getHeight());
		}
	}

	ofPushMatrix();
	ofTranslate(_centerX,_centerY);
	ofTranslate(-w/2,-h/2);

	if (video.getPosition() != STOP_POSITION)
	{
		video.draw(0,0,w,h);
	}
	else
	{
		if (bUseBack)
		{
			if (videoPageBack)
			{
				videoPageBack->draw(0, 0, w, h);
			}
		}
		else
		{
			ofPushStyle();
			ofSetColor(0);
			ofFill();
			ofRect(0-5, 0-5, w +10, h +10);
			ofPopStyle();
		}
	}
	
	ofPopMatrix();

	if (bGetBackimg)
	{
		ofImage img;
		img.grabScreen(0, 0, w, h);
		img.saveImage(curBackFile.path());
		bGetBackimg = false;
		Sleep(1000);
	}
	drawMessage();
}

void videoPlayer::keyPressed(int key)
{
	switch (key)
	{
	case 'p':
		setplay();
		break;
	case 's':
		setstop();
		break;
	case 32:				//空格键
		{
			static bool flag = false;
			flag = !flag;
			flag?setpause():setplay();
		}
		break;
	case 'd':
		bIsTesting = !bIsTesting;
		break;
	case 'l':
		bIsLooping = !bIsLooping;
		bIsLooping ? video.setLoopState(OF_LOOP_NORMAL) : video.setLoopState(OF_LOOP_NONE);
		xml.setValue("loop",bIsLooping);
		break;
	case 'b':
		{
			bUseBack = !bUseBack;
			xml.setValue("back",bUseBack);
		}
		break;
	case OF_KEY_UP:
		{
		volume += 5;
		if (volume > MAX_VOLUME)
		{
			volume = MAX_VOLUME;
		}
		xml.setValue("volume", int(volume));
		setVolume(volume);
		}
		break;
	case OF_KEY_DOWN:
		{
		volume -= 5;
		if (volume < MIN_VOLUME)
		{
			volume = MIN_VOLUME;
		}
		xml.setValue("volume", int(volume));
		setVolume(volume);
		}
		break;
	case OF_KEY_F12:
		{
			bMute = !bMute;
			bMute ? setMute() : setUnMute();
		}
		break;
	case OF_KEY_F1:
		{
			xml.saveFile();
		}
		break;
	case OF_KEY_F2:
	{
		saveSetting(settingFileStr);
	}
	break;
	case OF_KEY_LEFT:
	{
		videoRewind();
	}
		break;
	case OF_KEY_RIGHT:
	{
		videoFastForward();
	}
		break;
	case 'g':
		bGetBackimg = true;
		break;
	case 'n':
		playPrevMoive();
		break;
	case 'm':
		playNextMoive();
		break;
	default:
		break;
	}


	for (int i = 0; i < 10; i++)
	{
		static float const KeyTouchTimeLen = 3.0f;			//按键触发的最小间隔时间
		if (('0' + i) == key && (ofGetElapsedTimef() -  lastKeyTouchTime > KeyTouchTimeLen))
		{
			reloadVideo(i);
			lastKeyTouchTime = ofGetElapsedTimef();
		}
	}
}

float videoPlayer::getSeconds()
{
	return video.getPosition() * video.getDuration();
}


void videoPlayer::setplay()
{
	if (isStoped())
	{
		videoPlayerEventArgs args;
		args.ptrSender = this;
		args.eventType = VIDEO_PLAY;
		args.videoIndex = getActiveIndex();
		ofNotifyEvent(videoPlayer::videoControlEvent, args);

		notityMessage(VIDEO_PLAY);
#ifdef TIMELINE_MESSAGE_NOTIFY
		timeLineReset();
#endif
	}


	video.play();
	video.setPaused(false);

	isStoping = false;

	if (videoPageBack)
	{
		videoPageBack->stop();
	}

	ofLogNotice() << "movie set play" << endl;
	
}
void videoPlayer::setpause()
{
	if (video.isPlaying())
	{
		videoPlayerEventArgs args;
		args.ptrSender = this;
		args.eventType = VIDEO_PAUSE;
		args.videoIndex = getActiveIndex();
		ofNotifyEvent(videoPlayer::videoControlEvent, args);
		video.setPaused(true);

		notityMessage(VIDEO_PAUSE);
	}

	ofLogNotice() << "movie set pause" << endl;
}
void videoPlayer::setstop()
{
	if (!isStoped())
	{
		//video.setPaused(true);
		videoPlayerEventArgs args;
		args.ptrSender = this;
		args.eventType = VIDEO_STOP;
		args.videoIndex = getActiveIndex();
		ofNotifyEvent(videoPlayer::videoControlEvent, args);

		notityMessage(VIDEO_STOP);
#ifdef TIMELINE_MESSAGE_NOTIFY
		timeLineReset();
#endif
	}
		
// 	video.setPosition(0.0f);
// 	video.setFrame(0);
// 	Sleep(100);
	video.stop();

	isStoping = true;
	if (videoPageBack)
	{
		videoPageBack->play();
	}

	ofLogNotice() << "movie set stop" << endl;
}

void videoPlayer::setMute()
{
	setVolume(0);
	bMute = true;

	videoPlayerEventArgs args;
	args.ptrSender = this;
	args.eventType = VIDEO_MUTE;
	ofNotifyEvent(videoPlayer::videoControlEvent, args);

	notityMessage(VIDEO_MUTE);
}

void videoPlayer::setUnMute()
{
	setVolume(volume);
	bMute = false;

	videoPlayerEventArgs args;
	args.ptrSender = this;
	args.eventType = VIDEO_UN_MUTE;
	ofNotifyEvent(videoPlayer::videoControlEvent, args);

	notityMessage(VIDEO_UN_MUTE);
}

bool videoPlayer::isMute()
{
	return bMute;
}

void videoPlayer::setPosition(float _pos)
{
	_pos = ofClamp(_pos,0.0f,1.0f);
	video.setPosition(_pos);
}

float videoPlayer::getPosition()
{
	return video.getPosition();
}

int videoPlayer::getCurFrame()
{
	return video.getCurrentFrame();
}

int videoPlayer::getTotalFrame()
{
	return video.getTotalNumFrames();
}

bool videoPlayer::isStoped()
{
	return video.getPosition() == STOP_POSITION;
}

void videoPlayer::reload()
{
	//video.closeMovie();
	video.close();
	video.load(videoNameStr);
	setstop();
}

int videoPlayer::getActiveIndex()
{
	for (int i = 0; i< videoPaths.size(); i++)
	{
		if (videoNameStr == videoPaths[i])
		{
			return i;
		}
	}
	return 0;
}

void videoPlayer::init()
{
	clear();

	bIsTesting = false;

	{
		bool loadSucess = xml.loadFile(settingFileStr);

		bIsLooping = xml.getValue("loop", 1);
		volume = xml.getValue("volume", 255);
		bUseBack = xml.getValue("back", 0);
		bRemoteControl = xml.getValue("remoteControl", 1);
		bMute = xml.getValue("bMute", 0);
		isActive = xml.getValue("active", 1);

		if (!loadSucess)
		{
			saveSetting(settingFileStr);
		}
	}
	


	ofDirectory videoDIR;
	videoDIR.listDir(videoDirStr);
	videoDIR.sort();

	videoPaths.resize(videoDIR.size());
	for (int i = 0; i < videoPaths.size(); i++)
	{
		videoPaths[i] = videoDIR.getPath(i);
	}

	if (videoDIR.size() <= 0)
	{
		if (MessageBox(HWND_DESKTOP, "没有检索到视频文件，请将视频文件拷贝到data/video/文件中，名称不能含中文！", "Error", MB_OK | MB_ICONEXCLAMATION))
		{
			ofExit(-3);
		}
	}
	videoNameStr = videoDIR.getPath(0);
	
	if (!video.load(videoNameStr))
	{
		if (MessageBox(HWND_DESKTOP, "视频加载失败，请检查视频文件格式！", "Error", MB_OK | MB_ICONEXCLAMATION))
		{
			ofExit(-3);
		}
	}
	bIsLooping ? video.setLoopState(OF_LOOP_NORMAL) : video.setLoopState(OF_LOOP_NONE);

	bMute ? setMute() : setUnMute();

	backDir.listDir("static/");
	backDir.sort();

	if (backDir.size())
	{
		loadPageBack(backDir[0]);
	}

	bIsLooping ? setplay() : setstop();
	

	if (bRemoteControl)				//UDP
	{
		cmdRecvier.Create();
		cmdRecvier.Bind(PORT_MOVIE_CONTROL);
		cmdRecvier.SetNonBlocking(true);
	}

	setActive(isActive);
	if (!isActiving())
	{
		setstop();
	}


}

void videoPlayer::saveSetting(string _filename)
{
	ofxXmlSettings settingXml;

	settingXml.addValue("loop", bIsLooping);
	settingXml.addValue("volume", volume);
	settingXml.addValue("back", bUseBack);
	settingXml.save(_filename);
}

void videoPlayer::clear()
{
	xml.clear();
	cmdRecvier.Close();
	video.close();
}

void videoPlayer::drawMessage()
{
	if (bIsTesting)
	{
		stringstream sss;
		sss<<"position:"<<video.getPosition()<<endl;
		sss<<"frame:"<<video.getCurrentFrame()<<endl;
		sss << "total frame:" << video.getTotalNumFrames() << endl;
		sss<<"volume:"<<volume<<endl;
		sss<<"loop:"<<bIsLooping<<endl;
		sss<<"back:"<<bUseBack<<endl;
		sss << "mute:" << bMute << endl;
		sss << "fps:" << ofGetFrameRate() << endl;
#ifdef OFX_AV_VIDEO_PLAYER
		sss << "video fps:" << video.getFps() << endl;
#endif
		int seconds = getSeconds();
		float sec = seconds % 60;
		float min = seconds / 60;
		sss << min << "::" << sec << endl;
		ofPushStyle();
		ofSetColor(255,0,0);
		ofDrawBitmapString(sss.str(),20,20);
		ofPopStyle();
	}
}

string videoPlayer::convertStr(string _msg)
{
	return cmdConverter::getEncryCmd(_msg);
}

void videoPlayer::reloadVideo(int _index)
{
	ofLogNotice() << "reloadVideo:" << _index << endl;
	if (_index >= 0 && _index < videoPaths.size())
	{
		if (videoNameStr != videoPaths[_index])
		{
			float beginTime = ofGetElapsedTimef();
			video.close();


			videoNameStr = videoPaths[_index];
			video.load(videoNameStr);

			bIsLooping ? video.setLoopState(OF_LOOP_NORMAL) : video.setLoopState(OF_LOOP_NONE);

			bMute ? setMute() : setUnMute();
		}
		setplay();
	}

	if (_index >= 0 && _index < backDir.size() )
	{
		loadPageBack(backDir[_index]);
	}
}

void videoPlayer::reloadVideoWithStop(int _index)
{
	if (_index >= 0 && _index < videoPaths.size() && videoNameStr != videoPaths[_index])
	{
		video.close();


		videoNameStr = videoPaths[_index];
		video.load(videoPaths[_index]);

		bIsLooping ? video.setLoopState(OF_LOOP_NORMAL) : video.setLoopState(OF_LOOP_NONE);

		bMute ? setMute() : setUnMute();
	}
	else if (videoNameStr == videoPaths[_index])
	{
		setstop();
	}

	if (_index >= 0 && _index < backDir.size())
	{
		loadPageBack(backDir[_index]);
	}
}

int videoPlayer::size()
{
	return videoPaths.size();
}

void videoPlayer::playNextMoive()
{
	int index = getActiveIndex();

	index = (++index) % (size());
	reloadVideo(index);
}

void videoPlayer::playPrevMoive()
{
	int index = getActiveIndex();

	index = (--index + size()) % (size());
	reloadVideo(index);
}

void videoPlayer::audioOut(float * output, int bufferSize, int nChannels)
{
#ifdef OFX_AV_VIDEO_PLAYER
	video.audioOut(output, bufferSize, nChannels);
#endif
}

void videoPlayer::setSpeed(float _speed)
{
	video.setSpeed(_speed);
}

void videoPlayer::setVolume(int _volume)
{
	video.setVolume(ofMap(_volume, MIN_VOLUME, MAX_VOLUME, 0.0, 1.0f,true));
}

void videoPlayer::setLoop(bool _bLoop)
{
	bIsLooping = _bLoop;
	ofLogNotice("setLoop()") << "   " << bIsLooping << endl;
	bIsLooping ? video.setLoopState(OF_LOOP_NORMAL) : video.setLoopState(OF_LOOP_NONE);
}

void videoPlayer::loadNotifySetting()
{
	ofxXmlSettings xml;
	bool loadSucess = xml.load("message.xml");

	notifyPort = xml.getValue("MESSAGE_PORT", 15999);

	int ipNums = xml.getNumTags("MESSAGE_IP");
	notifyIps.resize(ipNums);
	for (int i = 0; i < notifyIps.size(); i++)
	{
		notifyIps[i] = xml.getValue("MESSAGE_IP", "127.0.0.1");
	}

	notifyMessages[VIDEO_PLAY] = xml.getValue("MESSAGE_VIDEO_PLAY","PLAY");
	notifyMessages[VIDEO_PAUSE] = xml.getValue("MESSAGE_VIDEO_PAUSE", "PAUSE");
	notifyMessages[VIDEO_STOP] = xml.getValue("MESSAGE_VIDEO_STOP", "STOP");
	notifyMessages[VIDEO_MUTE] = xml.getValue("MESSAGE_VIDEO_MUTE", "MUTE");
	notifyMessages[VIDEO_UN_MUTE] = xml.getValue("MESSAGE_VIDEO_UN_MUTE", "UNMUTE");

	if (!loadSucess)
	{
		xml.clear();
		xml.addValue("MESSAGE_PORT", 15999);

		xml.addValue("MESSAGE_IP", "127.0.0.1");

		xml.addValue("MESSAGE_VIDEO_PLAY", notifyMessages[VIDEO_PLAY]);
		xml.addValue("MESSAGE_VIDEO_PAUSE", notifyMessages[VIDEO_PAUSE]);
		xml.addValue("MESSAGE_VIDEO_STOP", notifyMessages[VIDEO_STOP]);
		xml.addValue("MESSAGE_VIDEO_MUTE", notifyMessages[VIDEO_MUTE]);
		xml.addValue("MESSAGE_VIDEO_UN_MUTE", notifyMessages[VIDEO_UN_MUTE]);

		xml.save("message.xml");
	}
}

#ifdef TIMELINE_MESSAGE_NOTIFY
void videoPlayer::notityMessage(VIDEO_EVENT_TYPE _type)
{
	static bool first = true;
	if (first)
	{
		cmdSender.Create();
		cmdSender.SetNonBlocking(true);
		first = false;
	}

//	string msg = convertStr(notifyMessages[_type]);
	string msg = notifyMessages[_type];

	for (int i = 0;i < notifyIps.size(); i++)
	{
		cmdSender.Connect(notifyIps[i].c_str(), notifyPort);
		cmdSender.Send(msg.c_str(), msg.size());

		ofLogNotice() <<"port:"<<notifyPort <<" send:" << msg << endl;
	}
	
}


void videoPlayer::sendUdpMsg(string _ip, int _port, string _msg)
{
	static bool first = true;
	static ofxUDPManager sender;
	if (first)
	{
		sender.Create();
		sender.SetNonBlocking(true);
		first = false;
	}
	sender.Connect(_ip.c_str(), _port);
	sender.Send(_msg.c_str(), _msg.size());

	ofLogNotice() << "send:" << _msg << endl;
}

void videoPlayer::loadTimeLineSetting()
{
	ofxXmlSettings xml;
	bool loadSucess = xml.load("timeline.xml");

	int nums = xml.getNumTags("NODE");

	for (int i = 0; i< nums; i++)
	{
		xml.pushTag("NODE", i);
		TIME_LINE_NODE node;
		node.flag = true;
		node.time = xml.getValue("TIME", 0.0f);
		node.ip = xml.getValue("IP", "127.0.0.1");
		node.port = xml.getValue("PORT", 8888);
		node.msg = xml.getValue("MESSAGE", "");
		xml.popTag();

		timeLineNodes.push_back(node);
	}

	if (!loadSucess)
	{
		xml.clear();
		xml.addTag("NODE");
		xml.pushTag("NODE");
		xml.addValue("TIME", 0.0f);
		xml.addValue("IP", "127.0.0.1");
		xml.addValue("PORT", 8888);
		xml.addValue("MESSAGE", "");
		xml.popTag();

		xml.save("timeline.xml");
	}
}

void videoPlayer::timeLineReset()
{
	for (int i = 0; i < timeLineNodes.size(); i++)
	{
		auto & var = timeLineNodes[i];
		var.flag = true;
	}
}

void videoPlayer::timeLineUpdate()
{
	if (!isStoped())
	{
		float curTime = video.getPosition() * video.getDuration();
		for (int i = 0;i < timeLineNodes.size(); i++)
		{
			auto & var = timeLineNodes[i];
			if (var.flag && curTime > var.time)
			{
				var.flag = false;
				sendUdpMsg(var.ip, var.port, var.msg);
			}
		}
	}
}
#endif

#pragma region 快进快退
void videoPlayer::videoFastForward()
{
	int frame = video.getCurrentFrame() + videoMoveStep;
	if (frame > video.getTotalNumFrames())
	{
		frame = video.getTotalNumFrames();
	}

	video.setFrame(frame);

}

void videoPlayer::videoRewind()
{
	int frame = video.getCurrentFrame() - videoMoveStep;
	if (frame < 0)
	{
		frame = 0;
	}

	video.setFrame(frame);
}

void videoPlayer::loadVideoMoveSetting(string _filename /* = "videoMoveSetting.xml" */)
{
	ofxXmlSettings xml;
	bool loadSucess = xml.load(_filename);

	videoMoveStep = xml.getValue("step", 5);

	if (!loadSucess)
	{
		xml.clear();
		xml.addValue("step", videoMoveStep);
		xml.save(_filename);
	}
}
#pragma endregion 快进快退

void videoPlayer::setActive(bool _state)
{
	isActive = _state;
}

bool videoPlayer::isActiving()
{
	return isActive;
}


void videoPlayer::loadPageBack(const ofFile & _file)
{
	if (curBackFile == _file)return;
	
	if (videoPageBack)
	{
		delete videoPageBack;
		videoPageBack = NULL;
	}

	curBackFile = _file;

	string fileExtension = curBackFile.getExtension();
	string filePath = curBackFile.path();
	if (fileExtension == "png" || fileExtension == "jpg")
	{
		videoPageBack = ofxPageBackFactory::createImagePageBack(filePath);
	}
	else if (fileExtension == "mp4" || fileExtension == "mov" || fileExtension == "avi" || fileExtension == "flv")
	{
		videoPageBack = ofxPageBackFactory::createVideoPageBack(filePath);
	}
	else
	{
		videoPageBack = ofxPageBackFactory::createNullPageBack(filePath);
	}
}