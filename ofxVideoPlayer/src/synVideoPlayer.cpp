#include "synVideoPlayer.h"



synVideoPlayer::synVideoPlayer()
{
}


synVideoPlayer::~synVideoPlayer()
{
}

void synVideoPlayer::setup()
{
	videoPlayer::setup();
	readSettingsFromXml("synConfig.xml");

	udp.Create();
	udp.SetNonBlocking(true);
	if (isClient)
	{
		udp.Bind(listenPort);
	}

	lastframe = 0;
}
void synVideoPlayer::update()
{
	videoPlayer::update();

	if (isClient)
	{
		clientSyn();
	}
	else
	{
		serverSyn();
	}
}

bool synVideoPlayer::readSettingsFromXml(string file)
{
	ofxXmlSettings xml;
	xml.load(file);
	
	int value = xml.getValue("isClient", 1);
	isClient = value;
	if (!isClient)
	{
		int nums = xml.getNumTags("client");
		for (int i = 0; i < nums; i++)
		{
			xml.pushTag("client", i);
			string ip = xml.getValue("ip", "");
			int port = xml.getValue("port", 9001);
			Connection c;
			c.ip = ip;
			c.port = port;
			connections.push_back(c);
			xml.popTag();
		}
	}
	else
	{
		listenPort = xml.getValue("listen_port", 15999);
	}
	return isClient;
}

void synVideoPlayer::clientSyn()
{
	char data[1000] = "0";
	udp.Receive(data, 1000);
	string msg = data;

	if (msg != "")
	{
		float pos = ofToFloat(msg);

		video.setPosition(pos);
	}
}

void synVideoPlayer::serverSyn()
{
	if (video.isPlaying() && (ofGetFrameNum() - lastframe > 4000))
	{
		float pos = video.getPosition();

		string msg = ofToString(pos);

		for (int i = 0; i < connections.size(); i++)
		{
			udp.Connect(connections[i].ip.c_str(), connections[i].port);
			udp.Send(msg.c_str(), msg.size());
		}

		lastframe = ofGetFrameNum();
	}
}