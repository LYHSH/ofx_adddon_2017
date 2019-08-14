/************************************************************************/
/* Ò¡Í·µÆ¿ØÖÆ                                                                     */
/************************************************************************/
#ifndef WAVE_LIGHT_CONTROL_H
#define WAVE_LIGHT_CONTROL_H
#include "ofxSerial.h"
#include "ofMain.h"

class waveLightControl : public ofThread
{
public:
	waveLightControl(void);
	~waveLightControl(void);

	void setup(int comNum);

	void addOrder(int _loopIndex);


	void setOrder(int _id);
	void threadedFunction();

	void exit(ofEventArgs &e);

	queue<int> orders;
	ofxSerial serial;
};
#endif


