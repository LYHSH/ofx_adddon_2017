#include "loopVideoplayer.h"



loopVideoplayer::loopVideoplayer()
{
	lastTime = 0.0f;
	synTimeLen = 900.0f;
}


loopVideoplayer::~loopVideoplayer()
{
}

void loopVideoplayer::update()
{
	if (bRemoteControl)
	{
		//UDP
		char udpMessage[100];
		cmdRecvier.Receive(udpMessage, 100);
		string message = udpMessage;
		if (message != "") {
			ofLogNotice() << "receive:" << message << endl;
			if (cmdConverter::getEncryCmd(CMD_ACTIVE_TRUE) == message)
			{
				ofLogNotice() << "set avtive true" << endl;
				setActive(true);
				//恢复原始状态
				reloadVideo(0);
				setLoop(true);
			}
			else if (cmdConverter::getEncryCmd(CMD_ACTIVE_FALSE) == message)
			{
				ofLogNotice() << "set avtive false" << endl;
				setActive(false);
				setstop();
			}

			if (isActiving())
			{
#pragma region 指令控制
				if (cmdConverter::getEncryCmd(CMD_MOVIE_PLAY) == message)
				{
					ofLogNotice() << "movie play" << endl;
					reloadVideo(1);
					setLoop(false);
				}
				else if (cmdConverter::getEncryCmd(CMD_MOVIE_PAUSE) == message)
				{
					ofLogNotice() << "movie pause" << endl;
					setpause();
				}
				else if (cmdConverter::getEncryCmd(CMD_MOVIE_STOP) == message)
				{
					ofLogNotice() << "movie stop" << endl;
					reloadVideo(0);
					setLoop(true);
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
#pragma endregion 指令控制
			}

			
		}
	}

	video.update();

	if (video.getIsMovieDone() || video.getCurrentFrame() > (video.getTotalNumFrames() - 5))
	{
		if (0 != getActiveIndex())
		{
			reloadVideo(0);
			setLoop(true);
		}
	}
}
