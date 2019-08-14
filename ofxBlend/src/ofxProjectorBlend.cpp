#include "ofxProjectorBlend.h"

string fragmentShader = "#extension GL_ARB_texture_rectangle : enable\n \
						\
						uniform sampler2DRect Tex0;\
						\
						uniform float width;\
						uniform float height;\
						\
						uniform float OverlapLeft;\
						uniform float OverlapRight; \
						uniform float OverlapTop;\
						uniform float OverlapBottom;\
						\
						uniform float BlackOutLeft;\
						uniform float BlackOutRight; \
						uniform float BlackOutTop;\
						uniform float BlackOutBottom;\
						\
						uniform float BlendPower;\
						uniform float SomeLuminanceControl;\
						uniform vec3  GammaCorrection;\
						\
						uniform float BlendPower2;\
						uniform float SomeLuminanceControl2;\
						uniform vec3  GammaCorrection2;\
						\
						uniform float SolidEdgeEnable;\
						uniform vec4  SolidEdgeColor;\
						uniform vec2  texCoordOffset;\
						\
						uniform float projectors;\
						uniform float threshold;\
						\
						vec4 drawSmoothEdge(float loc, float extend, float blePow, float lumCon, vec3 gamma)\
						{\
						vec4 edge;\
						float curve;\
						\
						curve = loc / extend;\
						curve = (curve < 0.5) ? \
						lumCon * pow(2.0 * curve, blePow) \
						: \
						1.0 - (1.0 - lumCon) * pow(2.0 * (1.0 - curve), blePow);\
						\
						edge = vec4(pow(curve, 1.0 / gamma.r), \
						pow(curve, 1.0 / gamma.g),\
						pow(curve, 1.0 / gamma.b),\
						1.0);\
						\
						return edge;\
						}\
						\
						vec4 drawSmoothEdges(in vec4 overlap, in vec4 blankout, in vec4 color)\
						{\
						vec2 xy = gl_TexCoord[0].xy;\
						vec2 xy_t = xy + texCoordOffset.xy;\
						vec4 blank = vec4(0.0,0.0,0.0,0.0);	\
						\
						float proj2 = 1.0;\
						float thresh = proj2 * width + overlap.x;\
						float blnPwr = (xy_t.x > thresh) ? BlendPower: BlendPower2;\
						float slc    = (xy_t.x > thresh) ? SomeLuminanceControl: SomeLuminanceControl2;\
						vec3 gamma   = (xy_t.x > thresh) ? GammaCorrection: GammaCorrection2;\
						slc += 0.5;\
						\
						vec4 sebImage = \
						(blankout.x + overlap.x > xy.x) ? \
						(blankout.x > xy.x) ? 	\
						blank\
						:	(blankout.z + overlap.z > xy.y) ?\
						(blankout.z > xy.y) ? \
						blank\
						: 	texture2DRect(Tex0, xy_t) 	*		\
						drawSmoothEdge(xy.x - blankout.x, overlap.x, blnPwr, slc, gamma) * \
						drawSmoothEdge(xy.y - blankout.z, overlap.z, blnPwr, slc, gamma)\
						: 	(height - blankout.w - overlap.w < xy.y) ?  \
						(height - blankout.w < xy.y) ? \
						blank\
						: 	texture2DRect(Tex0, xy_t) 	*\
						drawSmoothEdge(xy.x - blankout.x, overlap.x, blnPwr, slc, gamma) * \
						drawSmoothEdge(height - blankout.w - xy.y, overlap.w, blnPwr, slc, gamma)	\
						:	texture2DRect(Tex0, xy_t) *\
						drawSmoothEdge(xy.x - blankout.x, overlap.x, blnPwr, slc, gamma)\
						:	(width - blankout.y - overlap.y < xy.x) ? \
						(width - blankout.y < xy.x) ? \
						blank\
						:	(blankout.z + overlap.z > xy.y) ?\
						(blankout.z > xy.y) ? \
						blank\
						: 	texture2DRect(Tex0, xy_t) 	*\
						drawSmoothEdge(width - blankout.y - xy.x, overlap.y, blnPwr, slc, gamma) *\
						drawSmoothEdge(xy.y - blankout.z, overlap.z, blnPwr, slc, gamma)\
						:	(height - blankout.w - overlap.w < xy.y) ?\
						(height - blankout.w < xy.y) ? \
						blank\
						:	texture2DRect(Tex0, xy_t) *\
						drawSmoothEdge(width - blankout.y - xy.x, overlap.y, blnPwr, slc, gamma) * \
						drawSmoothEdge(height - blankout.w - xy.y, overlap.w, blnPwr, slc, gamma)\
						:	texture2DRect(Tex0, xy_t) *\
						drawSmoothEdge(width - blankout.y - xy.x, overlap.y, blnPwr, slc, gamma)\
						:	(blankout.z + overlap.z > xy.y) ?\
						(blankout.z > xy.y) ? \
						blank\
						: 	texture2DRect(Tex0, xy_t) *\
						drawSmoothEdge(xy.y - blankout.z, overlap.z, blnPwr, slc, gamma)\
						:	(height - blankout.w - overlap.w < xy.y) ?\
						(height - blankout.w < xy.y) ? \
						blank\
						:	texture2DRect(Tex0, xy_t) *\
						drawSmoothEdge(height - blankout.w - xy.y, overlap.w, blnPwr, slc, gamma)		\
						:	texture2DRect(Tex0, xy_t);\
						\
						return sebImage;\
						}\
						\
						vec4 drawSolidEdges(vec4 overlap, vec4 blankout, vec4 color)\
						{	\
						\
						vec2 xy = gl_TexCoord[0].xy;\
						vec2 xy_t = xy + texCoordOffset.xy;\
						vec4 blank = vec4(0.0,0.0,0.0,0.0);		\
						vec4 edgeImage =\
						(blankout.x + overlap.x > xy.x) ?\
						(blankout.x > xy.x) ?\
						blank\
						:	(blankout.z + overlap.z > xy.y) ?\
						(blankout.z > xy.y) ?\
						blank\
						: 	color\
						: 	(height - blankout.w - overlap.w < xy.y) ?\
						(height - blankout.w < xy.y) ?\
						blank\
						: 	color\
						:	color\
						:	(width - blankout.y - overlap.y < xy.x) ?\
						(width - blankout.y < xy.x) ?\
						blank\
						:	(blankout.z + overlap.z > xy.y) ?\
						(blankout.z > xy.y) ?\
						blank\
						: 	color\
						:	(height - blankout.w - overlap.w < xy.y) ?\
						(height - blankout.w < xy.y) ? \
						blank\
						:	color\
						:	color\
						:	(blankout.z + overlap.z > xy.y) ?\
						(blankout.z > xy.y) ? \
						blank\
						: 	color\
						:	(height - blankout.w - overlap.w < xy.y) ?\
						(height - blankout.w < xy.y) ? \
						blank\
						:	color\
						:	texture2DRect(Tex0, xy_t);		\
						return edgeImage;\
						}\
						\
						void main (void)\
						{\
						vec4 overlap = vec4 (OverlapLeft, OverlapRight, OverlapBottom, OverlapTop);\
						vec4 blankout = vec4 (BlackOutLeft, BlackOutRight, BlackOutBottom, BlackOutTop);\
						gl_FragData[0] = (SolidEdgeEnable == 1.0) ?\
						drawSolidEdges(overlap, blankout, SolidEdgeColor)\
						:	drawSmoothEdges(overlap, blankout, SolidEdgeColor);\
						}";

ofxProjectorBlend::ofxProjectorBlend()
{
	showBlend = true;

	gammaR = gammaR2 = 0.5;
	gammaG = gammaG2 = 0.5;
	gammaB = gammaB2 = 0.5;
	blendPower = blendPower2 = 1;
	luminance = luminance2 = 0;
	numProjectors = 0;
	threshold = 0;
	shaderLocation = "SmoothEdgeBlend";

}

void ofxProjectorBlend::setShaderLocation(string _shaderLocation){
	shaderLocation = _shaderLocation;
	//blendShader.load(shaderLocation);
	
	bool res = true;
	res &= blendShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
	res &= blendShader.linkProgram();

	if (!res)
	{
		ofLogError() << "shader setup failed" << endl;
	}
}

void ofxProjectorBlend::setup(int resolutionWidth, 
							  int resolutionHeight, 
							  int _numProjectors, 
							  int _pixelOverlap, 
							  ofxProjectorBlendLayout _layout)
{
	numProjectors = _numProjectors;
	layout = _layout;

	string l = "horizontal";
	if(layout==ofxProjectorBlend_Vertical)
		l = "vertical";
	ofLog(OF_LOG_NOTICE, "ofxProjectorBlend: res: %d x %d * %d, overlap: %d pixels, layout: %s\n", resolutionWidth, resolutionHeight, _numProjectors, _pixelOverlap, l.c_str());
	
	if(numProjectors <= 0)
	{
		ofLog(OF_LOG_ERROR, "Cannot initialize with " + ofToString(this->numProjectors) + " projectors.");
		return;
	}
	
	pixelOverlap = _pixelOverlap;
	
	singleChannelWidth = resolutionWidth;
	singleChannelHeight = resolutionHeight;

	if(layout == ofxProjectorBlend_Vertical)
	{
		fullTextureWidth = singleChannelWidth;
		fullTextureHeight = singleChannelHeight*numProjectors - (numProjectors-1)*pixelOverlap;

		displayWidth = resolutionWidth;
		displayHeight = resolutionHeight*numProjectors;
	}
	else if(layout == ofxProjectorBlend_Horizontal)
	{
		fullTextureWidth = singleChannelWidth*numProjectors - (numProjectors-1)*pixelOverlap;
		fullTextureHeight = singleChannelHeight;

		displayWidth = resolutionWidth*numProjectors;
		displayHeight = resolutionHeight;
	}
	else
	{
		ofLog(OF_LOG_ERROR, "ofxProjectorBlend: You have used an invalid ofxProjectorBlendLayout in ofxProjectorBlend::setup()");
		return;
	}

	ofLog(OF_LOG_NOTICE,"canvas res: %d  x  %d",fullTextureWidth,fullTextureHeight);

	overLapFlags.resize(numProjectors);
	for (int i = 0;i < overLapFlags.size();i++)
	{
		overLapFlags[i].isLeftOverLap = false;
		overLapFlags[i].isRightOverLap = false;
		overLapFlags[i].isTopOverLap = false;
		overLapFlags[i].isBottomOverLap = false;
	}
	
	fullTexture.allocate(fullTextureWidth, fullTextureHeight, GL_RGB, 4);
	//blendShader.load(shaderLocation);
	blendShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
	blendShader.linkProgram();
}

void ofxProjectorBlend::begin() {	
	fullTexture.begin();
	
	ofPushStyle();
	ofClear(0,0,0,0);
}

float ofxProjectorBlend::getDisplayWidth() {
	return displayWidth;
}

float ofxProjectorBlend::getDisplayHeight() {
	return displayHeight;
}

void ofxProjectorBlend::setWindowToDisplaySize() {
	ofSetWindowShape(getDisplayWidth(), getDisplayHeight());
}

void ofxProjectorBlend::setPixelOverlap(float layoutlength)
{
	pixelOverlap = layoutlength;

	if(layout == ofxProjectorBlend_Vertical)
	{
		fullTextureWidth = singleChannelWidth;
		fullTextureHeight = singleChannelHeight*numProjectors - (numProjectors-1)*pixelOverlap;
	}
	else if(layout == ofxProjectorBlend_Horizontal)
	{
		fullTextureWidth = singleChannelWidth*numProjectors - (numProjectors-1)*pixelOverlap;
		fullTextureHeight = singleChannelHeight;
	}

	fullTexture.allocate(fullTextureWidth, fullTextureHeight, GL_RGB, 4);
}

void ofxProjectorBlend::setLeftOverLapFlag(int _index, bool _flag)
{
	if (_index >= 0 && _index < numProjectors)
	{
		overLapFlags[_index].isLeftOverLap = _flag;
	}
}

void ofxProjectorBlend::setRightOverLapFlag(int _index, bool _flag)
{
	if (_index >= 0 && _index < numProjectors)
	{
		overLapFlags[_index].isRightOverLap = _flag;
	}
}

void ofxProjectorBlend::setTopOverLapFlag(int _index, bool _flag)
{
	if (_index >= 0 && _index < numProjectors)
	{
		overLapFlags[_index].isTopOverLap = _flag;
	}
}

void ofxProjectorBlend::setBottomOverLapFlag(int _index, bool _flag)
{
	if (_index >= 0 && _index < numProjectors)
	{
		overLapFlags[_index].isBottomOverLap = _flag;
	}
}

float ofxProjectorBlend::getCanvasWidth()
{
	return fullTextureWidth;
}

float ofxProjectorBlend::getCanvasHeight()
{
	return fullTextureHeight;
}

void ofxProjectorBlend::end() {
	fullTexture.end();
		
	ofPopStyle();
}

void ofxProjectorBlend::updateShaderUniforms() {
	
	blendShader.setUniform1f("OverlapTop", 0.0f);
	blendShader.setUniform1f("OverlapLeft", 0.0f);
	blendShader.setUniform1f("OverlapBottom", 0.0f);
	blendShader.setUniform1f("OverlapRight", 0.0f);
	
	blendShader.setUniform1f("BlendPower", blendPower);
	blendShader.setUniform1f("SomeLuminanceControl", luminance);
	blendShader.setUniform3f("GammaCorrection", gammaR, gammaG, gammaB);
	
	blendShader.setUniform1f("BlendPower2", blendPower2);
	blendShader.setUniform1f("SomeLuminanceControl2", luminance2);
	blendShader.setUniform3f("GammaCorrection2", gammaR2, gammaG2, gammaB2);
	
	blendShader.setUniform1f("projectors", this->numProjectors);
	blendShader.setUniform1f("threshold", threshold);
}

void ofxProjectorBlend::draw(float x, float y) {
	//ofSetHexColor(0xFFFFFF);
	glPushMatrix();
	glTranslatef(x, y, 0);
	if(showBlend)
	{
		//if(layout == ofxProjectorBlend_Horizontal)
		//{
		//	glScalef(1.0-(pixelOverlap*(numProjectors-1)/numProjectors)/singleChannelWidth, 1.0, 1.0);
		//}
		//else
		//{
		//	glScalef(1.0, 1.0-(pixelOverlap*(numProjectors-1)/numProjectors)/singleChannelHeight, 1.0);
		//}

		blendShader.begin();
		blendShader.setUniform1f("width", singleChannelWidth);
		blendShader.setUniform1f("height", singleChannelHeight);
		
		updateShaderUniforms();
		
// 		if(layout == ofxProjectorBlend_Horizontal)
// 			blendShader.setUniform1f("OverlapRight", pixelOverlap);
// 		else
// 			blendShader.setUniform1f("OverlapTop", 0);
// 
// 		if (layout == ofxProjectorBlend_Horizontal)
// 			blendShader.setUniform1f("OverlapLeft", pixelOverlap);
// 		else
// 			blendShader.setUniform1f("OverlapBottom", 0);
		
		blendShader.setUniformTexture("Tex0", fullTexture.getTexture(), 0);
		
		ofVec2f offset(0, 0);
		glPushMatrix();
		
		// loop through each projector and glTranslatef() to its position and draw.
		for(int i = 0; i < numProjectors; i++)
		{
			blendShader.setUniform2f("texCoordOffset", offset.x, offset.y);
			
			blendShader.setUniform1f("OverlapTop", overLapFlags[i].isBottomOverLap?pixelOverlap:0.0f);
			blendShader.setUniform1f("OverlapLeft", overLapFlags[i].isLeftOverLap ? pixelOverlap : 0.0f);
			blendShader.setUniform1f("OverlapBottom", overLapFlags[i].isTopOverLap ? pixelOverlap : 0.0f);
			blendShader.setUniform1f("OverlapRight", overLapFlags[i].isRightOverLap ? pixelOverlap : 0.0f);
//  			if(i == 1)
//  			{
//  				if(layout == ofxProjectorBlend_Horizontal)
//  					blendShader.setUniform1f("OverlapLeft", pixelOverlap);	
//  				else
//  					blendShader.setUniform1f("OverlapBottom", pixelOverlap);
//  			}
//  			
// 			if (i + 1 == numProjectors)
// 			{
// 				if (layout == ofxProjectorBlend_Horizontal)
// 					blendShader.setUniform1f("OverlapRight", 0);
// 				else
// 					blendShader.setUniform1f("OverlapTop", 0);
// 			}
			
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);                                    glVertex2f(0, 0);
			glTexCoord2f(singleChannelWidth, 0);                   glVertex2f(singleChannelWidth, 0);
			glTexCoord2f(singleChannelWidth, singleChannelHeight); glVertex2f(singleChannelWidth, singleChannelHeight);
			glTexCoord2f(0, singleChannelHeight);                  glVertex2f(0, singleChannelHeight);
			glEnd();
			
			// move the texture offset and where we're drawing to.
			if(layout == ofxProjectorBlend_Horizontal)
				offset.x += singleChannelWidth - pixelOverlap;
			else
				offset.y += singleChannelHeight - pixelOverlap;
			
			if(layout == ofxProjectorBlend_Horizontal)
				glTranslatef(singleChannelWidth, 0, 0);
			else
				glTranslatef(0, singleChannelHeight, 0);
		}
		glPopMatrix();
	
		blendShader.end();
	}
	else
	{
		fullTexture.draw(0, 0, displayWidth, displayHeight);
	}

	//Ïû³ý¾â³Ý
	ofNoFill();
	ofSetColor(0, 0, 0);
	ofDrawRectangle(1, 1, displayWidth-1, displayHeight-1);
	ofSetColor(255, 255, 255);

	glPopMatrix();
}