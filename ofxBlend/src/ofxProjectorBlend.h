#ifndef OFX_PROJECTOR_BLEND
#define OFX_PROJECTOR_BLEND

#include "ofMain.h"

enum ofxProjectorBlendLayout
{
	ofxProjectorBlend_Horizontal,
	ofxProjectorBlend_Vertical,
};

struct overLapData
{
	bool isLeftOverLap;
	bool isRightOverLap;
	bool isTopOverLap;
	bool isBottomOverLap;
};

class ofxProjectorBlend
{
  public:
	ofxProjectorBlend();
	
	void setup(int resolutionWidth, int resolutionHeight, int numProjectors, int pixelOverlap, 
			   ofxProjectorBlendLayout layout = ofxProjectorBlend_Horizontal);
	
	void begin();
	void end();
	void draw(float x = 0, float y = 0);
	
	
	float getCanvasWidth();
	float getCanvasHeight();
	ofFbo & getFullTexture() { return fullTexture; }
	void setShaderLocation(string shaderLocation);
	
	float getDisplayWidth();
	float getDisplayHeight();
	
	void setWindowToDisplaySize();
	void setPixelOverlap(float layoutlength);

	void setLeftOverLapFlag(int _index, bool _flag);
	void setRightOverLapFlag(int _index, bool _flag);
	void setTopOverLapFlag(int _index, bool _flag);
	void setBottomOverLapFlag(int _index, bool _flag);

	
	
	bool showBlend;
	
	float blendPower;
	float gammaR;
	float gammaG;
	float gammaB;
	float luminance;
	float blendPower2;
	float gammaR2;
	float gammaG2;
	float gammaB2;
	float luminance2;
	float threshold;
	
//protected:
	
	string shaderLocation;
	
	float fullTextureWidth;
	float fullTextureHeight;
	float singleChannelWidth;
	float singleChannelHeight;

	float displayWidth;
	float displayHeight;
	
	float pixelOverlap;
	int numProjectors;
	vector<overLapData> overLapFlags;

	ofxProjectorBlendLayout layout;
	ofShader blendShader;
	ofFbo fullTexture;
	void updateShaderUniforms();
};

#endif