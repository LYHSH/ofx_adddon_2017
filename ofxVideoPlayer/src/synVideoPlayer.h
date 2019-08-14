#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxXmlSettings.h"
#include "videoPlayer.h"

typedef struct
{
	string ip;
	int port;
}Connection;

class synVideoPlayer : public videoPlayer
{
public:
	synVideoPlayer();
	~synVideoPlayer();

	void setup();
	void update();

	bool readSettingsFromXml(string file);
	ofxUDPManager udp;
	vector<Connection> connections;
	int listenPort;

	bool isClient;

	int lastframe;

	void clientSyn();
	void serverSyn();

};

