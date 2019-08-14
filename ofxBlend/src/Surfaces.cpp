/**
 * @file Surfaces.cpp
 * @author GeistYp
 * @date 2009/12/01
 *
 * @brief 可控曲面类cpp文件
 * @see Surfaces.h
 */

#include "Surfaces.h"

Surfaces::Surfaces(void)
{
	strBasicTag = "Basic_Info";

	strNumX = "NumX"; strNumY = "NumY";

	strDetails = "Details";

	strScrLeftX  = "Screen_Left_X";  strScrLeftY  = "Screen_Left_Y";
	strScrRightX = "Screen_Right_X"; strScrRightY = "Screen_Right_Y";

	strTexLeftX  = "Texture_Left_X";  strTexLeftY  = "Texture_Left_Y";
	strTexRightX = "Texture_Right_X"; strTexRightY = "Texture_Right_Y";

	strCtrlPtsTag	 = "Control_Point";
	strTexPtsTag	 = "Texture_Point";
	strSubCtrlPtsTag = "CPT";
	strSubTexPtsTag  = "TPT";

}

Surfaces::~Surfaces(void)
{
	delete[] ctrlpoints;
	delete[] texpts;
}

void Surfaces::initSurfacePara(string _fileName, int iNumPointX, int iNumPointY, int iXL, int iYL, int iXR, int iYR,
						   float fTexXL, float fTexYL, float fTexXR, float fTexYR,
						   int iDets)
{
	iNumX = iNumPointX; iNumY = iNumPointY; iDetails = iDets;

	iScrLeftX = iXL; iScrLeftY = iYL; iScrRightX = iXR; iScrRightY = iYR;

	stringstream sss;
	sss<<"left up   "<<"x:"<<iScrLeftX<<"  y:"<<iScrLeftY<<endl;
	sss<<"right down   "<<"x:"<<iScrRightX<<"  y:"<<iScrRightY<<endl;
	ofLogNotice("Surfaces::initSurfacePara()")<<sss.str()<<endl;
	fTexLeftX = fTexXL; fTexLeftY = fTexYL; fTexRightX = fTexXR; fTexRightY = fTexYR;

	iChoosedPts = -1;
	active = false;

	initCtrlPtsArray();

	initTexPtsArray();

	setSurfaces();

	fileName = _fileName;
/*	screenID = _screenID;*/
}

void Surfaces::setSurfaces()
{
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, iNumX, 0, 1, 3*iNumY, iNumY, &ctrlpoints[0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0]);

	glMapGrid2f(iDetails, 0.0, 1.0, iDetails, 0.0, 1.0);
}

void Surfaces::drawSurface()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_MAP2_VERTEX_3);

	glEvalMesh2(GL_FILL, 0, iDetails, 0, iDetails);

	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_TEXTURE_2D);

	if ( bOpenCtrlPts )
	{
		ofPushStyle();
		//glPointSize(5);
		/*glBegin(GL_POINTS);
		for ( int i = 0; i < iNumX*iNumY*3; i+=3 )
		{
			glColor3f(0.5, 0.3, 0.4);
			glVertex3f(ctrlpoints[i], ctrlpoints[i+1], ctrlpoints[i+2]);
		}
		glEnd();*/
		//ofNoFill();
		for ( int i = 0; i < iNumX*iNumY*3; i+=3 )
		{
			if ( i == iChoosedPts)
			{
				ofSetColor(0, 0, 255);
				ofFill();
				ofDrawCircle(ctrlpoints[i], ctrlpoints[i+1], 10);
				ofNoFill();
				ofDrawCircle(ctrlpoints[i], ctrlpoints[i+1], 14);
				ofFill();
				ofSetColor(255, 0, 0);
				ofDrawBitmapString(ofToString(i/3), ctrlpoints[i]-4, ctrlpoints[i+1]+4);
			}
			else
			{
				ofSetColor(255, 0, 0);
				ofFill();
				ofDrawCircle(ctrlpoints[i], ctrlpoints[i+1], 10);
				ofNoFill();
				ofDrawCircle(ctrlpoints[i], ctrlpoints[i+1], 14);
				ofFill();
				ofSetColor(255, 255, 255);
				ofDrawBitmapString(ofToString(i/3), ctrlpoints[i]-4, ctrlpoints[i+1]+4);
			}
		}
		ofPopStyle();
	}
}

void Surfaces::updateSurface()
{
	//if ( bChanged )
	//{
		//for ( int i = 0; i < iNumX; i++ )
		//{
		//	for ( int j = 0; j < iNumY; j++ )
		//	{
		//		if(ctrlpoints[i*iNumY*3+j*3+0] <= 0+SingleScreenWidth*screenID)
		//			ctrlpoints[i*iNumY*3+j*3+0] = 0+SingleScreenWidth*screenID;
		//		if(ctrlpoints[i*iNumY*3+j*3+0] >= SingleScreenWidth+SingleScreenWidth*screenID)
		//			ctrlpoints[i*iNumY*3+j*3+0] = SingleScreenWidth+SingleScreenWidth*screenID;
		//		if(ctrlpoints[i*iNumY*3+j*3+1] <= 0)
		//			ctrlpoints[i*iNumY*3+j*3+1] = 0;
		//		if(ctrlpoints[i*iNumY*3+j*3+1] >= SingleScreenHeigth)
		//			ctrlpoints[i*iNumY*3+j*3+1] = SingleScreenHeigth;
		//	}
		//}

		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, iNumX, 0, 1, 3*iNumY, iNumY, &ctrlpoints[0]);

	//	bChanged = false;
	//}
}

void Surfaces::resetControlPts()
{
	float fPerDistX = (iScrRightX - iScrLeftX)/(float)(iNumX-1);//N 点 N-1 个格子
	float fPerDistY = (iScrRightY - iScrLeftY)/(float)(iNumY-1);

	for ( int i = 0; i < iNumX; i++ )
	{
		for ( int j = 0; j < iNumY; j++ )
		{
			ctrlpoints[i*iNumY*3+j*3+0] = iScrLeftX + (float)i*fPerDistX;
			ctrlpoints[i*iNumY*3+j*3+1] = iScrLeftY + (float)j*fPerDistY;
			ctrlpoints[i*iNumY*3+j*3+2] = 0;
		}
	}

	bChanged = true;
}

void Surfaces::mouseClicked(int x, int y)
{
	if ( bOpenCtrlPts )
	{
		iChoosedPts = -1;

		for ( int i = 0; i < iNumX*iNumY*3; i+=3 )
		{
			//暂时定为4像素的点击区域
			if ( fabs(ctrlpoints[i] - x) < 16 && fabs(ctrlpoints[i+1] - y) < 16 )
			{
				iChoosedPts = i;
				break;
			}
		}
	}
}

void Surfaces::mouseDragged(int x, int y)
{
	if ( bOpenCtrlPts )
	{
		if ( iChoosedPts == -1 ) return;

		ctrlpoints[iChoosedPts] = x;
		ctrlpoints[iChoosedPts+1] = y;

		bChanged = true;
	}
}

void Surfaces::mouseRelease(int x, int y)
{
	if ( bOpenCtrlPts )
	{
		iChoosedPts = -1;
		bChanged = false;
		active = false;
	}
}

void Surfaces::keyPressed(int key)
{
	if (key ==' ')
	{
		active = !active;
		iChoosedPts = 0;
		bChanged = true;
		bOpenCtrlPts = !bOpenCtrlPts;		
	}
	else if (key == 's' || key == 'S')
	{
		active = true;
		iChoosedPts = 0;
		bChanged = true;
	}
	else if (key == 'r' || key == 'R')
	{
		resetControlPts();
	}
	if (active)
	{
		if (key == 'N' || key == 'n')
		{
			iChoosedPts -= 3;
			if (iChoosedPts < 0)
				iChoosedPts = 0;
		}
		else if (key == 'M' || key == 'm')
		{
			iChoosedPts += 3;
			if (iChoosedPts > iNumY*iNumX*3-3)
				iChoosedPts = iNumY*iNumX*3-3;
		}
		else if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL)
		{
			iChoosedPts = -1;
			active = false;
			bChanged = false;
		}
		else if (key == OF_KEY_UP)
		{
			ctrlpoints[iChoosedPts+1]--;
			bChanged = true;
		}
		else if (key == OF_KEY_DOWN)
		{
			ctrlpoints[iChoosedPts+1]++;
			bChanged = true;
		}
		else if (key == OF_KEY_LEFT)
		{
			ctrlpoints[iChoosedPts]--;
			bChanged = true;
		}
		else if (key == OF_KEY_RIGHT)
		{
			ctrlpoints[iChoosedPts]++;
			bChanged = true;
		}

		if (key == '+' || key == '=')
		{
			addXnum();
			addYnum();
		}
		else if (key == '-' || key == '_')
		{
			subXnum();
			subYnum();
		}
	}
}

void Surfaces::setactive(bool _active)
{
	active = _active;
	bOpenCtrlPts = active;
}

void Surfaces::initCtrlPtsArray()
{
	ctrlpoints = new GLfloat[20*20*3];

	resetControlPts();
}

void Surfaces::initTexPtsArray()
{
	texpts = new GLfloat[2*2*2];

	float fPerDistX = fTexRightX - fTexLeftX;
	float fPerDistY = fTexRightY - fTexLeftY;

	for ( int i = 0; i < 2; i++ )
	{
		for ( int j = 0; j < 2; j++ )
		{
			texpts[i*4+j*2+0] = fTexLeftX + (float)i*fPerDistX;
			texpts[i*4+j*2+1] = fTexLeftY + (float)j*fPerDistY;
		}

	}
}

void Surfaces::saveToXML()
{
	xml.clear();

	xml.addTag("Surfaces");
	xml.pushTag("Surfaces");

	//保存基本信息
	xml.addTag(strBasicTag);
	xml.pushTag(strBasicTag);
		xml.addValue(strNumX, iNumX); xml.addValue(strNumY, iNumY);

		xml.addValue(strDetails, iDetails);

		xml.addValue(strScrLeftX, iScrLeftX);   xml.addValue(strScrLeftY, iScrLeftY);
		xml.addValue(strScrRightX, iScrRightX); xml.addValue(strScrRightY, iScrRightY);

		xml.addValue(strTexLeftX, fTexLeftX);   xml.addValue(strTexLeftY, fTexLeftY);
		xml.addValue(strTexRightX, fTexRightX); xml.addValue(strTexRightY, fTexRightY);
	xml.popTag();

	// 保存控制点
	xml.addTag(strCtrlPtsTag);
	xml.pushTag(strCtrlPtsTag);
	for ( int i = 0; i < iNumX*iNumY*3; i+=3 )
	{
		xml.addTag(strSubCtrlPtsTag);
		xml.pushTag(strSubCtrlPtsTag, i/3);
			xml.addValue("x", ctrlpoints[i]);
			xml.addValue("y", ctrlpoints[i+1]);
			xml.addValue("z", ctrlpoints[i+2]);
		xml.popTag();
	}
	xml.popTag();

	// 保存纹理坐标
	xml.addTag(strTexPtsTag);
	xml.pushTag(strTexPtsTag);
	for ( int j = 0; j < 8; j+=2 )
	{
		xml.addTag(strSubTexPtsTag);
		xml.pushTag(strSubTexPtsTag, j/2);
			xml.addValue("tX", texpts[j]);
			xml.addValue("tY", texpts[j+1]);
		xml.popTag();
	}
	xml.popTag();

	xml.popTag();

	xml.saveFile(ofToDataPath(fileName));
}

void Surfaces::saveToXML(ofVec2f _offset)
{
	xml.clear();

	xml.addTag("Surfaces");
	xml.pushTag("Surfaces");

	//保存基本信息
	xml.addTag(strBasicTag);
	xml.pushTag(strBasicTag);
	xml.addValue(strNumX, iNumX); xml.addValue(strNumY, iNumY);

	xml.addValue(strDetails, iDetails);

	xml.addValue(strScrLeftX, iScrLeftX + _offset.x);   xml.addValue(strScrLeftY, iScrLeftY + _offset.y);
	xml.addValue(strScrRightX, iScrRightX + _offset.x); xml.addValue(strScrRightY, iScrRightY + _offset.y);

	xml.addValue(strTexLeftX, fTexLeftX);   xml.addValue(strTexLeftY, fTexLeftY);
	xml.addValue(strTexRightX, fTexRightX); xml.addValue(strTexRightY, fTexRightY);
	xml.popTag();

	// 保存控制点
	xml.addTag(strCtrlPtsTag);
	xml.pushTag(strCtrlPtsTag);
	for (int i = 0; i < iNumX*iNumY * 3; i += 3)
	{
		xml.addTag(strSubCtrlPtsTag);
		xml.pushTag(strSubCtrlPtsTag, i / 3);
		xml.addValue("x", ctrlpoints[i] + _offset.x);
		xml.addValue("y", ctrlpoints[i + 1] + _offset.y);
		xml.addValue("z", ctrlpoints[i + 2]);
		xml.popTag();
	}
	xml.popTag();

	// 保存纹理坐标
	xml.addTag(strTexPtsTag);
	xml.pushTag(strTexPtsTag);
	for (int j = 0; j < 8; j += 2)
	{
		xml.addTag(strSubTexPtsTag);
		xml.pushTag(strSubTexPtsTag, j / 2);
		xml.addValue("tX", texpts[j]);
		xml.addValue("tY", texpts[j + 1]);
		xml.popTag();
	}
	xml.popTag();

	xml.popTag();

	xml.saveFile(ofToDataPath(fileName));
}

void Surfaces::readFromXML(string _fileName)
{
	fileName = _fileName;
/*	screenID = _screenID;*/

	xml.loadFile(ofToDataPath(fileName));

	xml.pushTag("Surfaces");

	// 读取基本信息
	xml.pushTag(strBasicTag);
		iNumX = xml.getValue(strNumX, 0); iNumY = xml.getValue(strNumY, 0);

		iDetails = xml.getValue(strDetails, 0);

		iScrLeftX  = xml.getValue(strScrLeftX, 0);  iScrLeftY  = xml.getValue(strScrLeftY, 0);
		iScrRightX = xml.getValue(strScrRightX, 0); iScrRightY = xml.getValue(strScrRightY, 0);

		fTexLeftX  = xml.getValue(strTexLeftX, 0.0);  fTexLeftY  = xml.getValue(strTexLeftY, 0.0);
		fTexRightX = xml.getValue(strTexRightX, 0.0); fTexRightY = xml.getValue(strTexRightY, 0.0);
	xml.popTag();

	// 读取控制点
	xml.pushTag(strCtrlPtsTag);
	int iNumControlPts = xml.getNumTags(strSubCtrlPtsTag);
	ctrlpoints = new GLfloat[400*3];
	
	for ( int i = 0; i < iNumControlPts; i++ )
	{
		ctrlpoints[i*3]   = xml.getValue(strSubCtrlPtsTag + ":x", 0.0, i);
		ctrlpoints[i*3+1] = xml.getValue(strSubCtrlPtsTag + ":y", 0.0, i);
		ctrlpoints[i*3+2] = xml.getValue(strSubCtrlPtsTag + ":z", 0.0, i);
	}
	xml.popTag();

	// 读取纹理坐标
	xml.pushTag(strTexPtsTag);
	int iNumTexPts = xml.getNumTags(strSubTexPtsTag);
	texpts = new GLfloat[2*2*2];
	for ( int i = 0; i < iNumTexPts; i++ )
	{
		texpts[i*2]   = xml.getValue(strSubTexPtsTag + ":tX", 0.0, i);
		texpts[i*2+1] = xml.getValue(strSubTexPtsTag + ":tY", 0.0, i);
	}
	xml.popTag();

	xml.popTag();

	iChoosedPts = -1;
	active = false;

	setSurfaces();
}

void Surfaces::addXnum()
{
	if (iNumX >= 8)
		return;

	GLfloat *tempctrlpoints;
	tempctrlpoints = new GLfloat[iNumX*iNumY*3];
	//临时数据存储
	for ( int i = 0; i < iNumX; i++ )
	{
		for ( int j = 0; j < iNumY; j++ )
		{
			tempctrlpoints[i*iNumY*3+j*3+0] = ctrlpoints[i*iNumY*3+j*3+0];
			tempctrlpoints[i*iNumY*3+j*3+1] = ctrlpoints[i*iNumY*3+j*3+1];
			tempctrlpoints[i*iNumY*3+j*3+2] = ctrlpoints[i*iNumY*3+j*3+2];
		}
	}
	//ctrlpoints = new GLfloat[(iNumX+1)*iNumY*3];
	for (int i = 0; i < iNumX+1; i++)
	{
		for (int j = 0; j < iNumY; j++)
		{
			if (i != iNumX && i != 0)
			{
				ctrlpoints[i*iNumY*3+j*3+0] = tempctrlpoints[(i-1)*iNumY*3+j*3+0]+((float)(iNumX-i)/(float)iNumX)*(tempctrlpoints[i*iNumY*3+j*3+0]-tempctrlpoints[(i-1)*iNumY*3+j*3+0]);
				ctrlpoints[i*iNumY*3+j*3+1] = tempctrlpoints[(i-1)*iNumY*3+j*3+1]+((float)(iNumX-i)/(float)iNumX)*(tempctrlpoints[i*iNumY*3+j*3+1]-tempctrlpoints[(i-1)*iNumY*3+j*3+1]);
				ctrlpoints[i*iNumY*3+j*3+2] = tempctrlpoints[(i-1)*iNumY*3+j*3+2]+((float)(iNumX-i)/(float)iNumX)*(tempctrlpoints[i*iNumY*3+j*3+2]-tempctrlpoints[(i-1)*iNumY*3+j*3+2]);
			}
			else if(i == iNumX)
			{
				ctrlpoints[i*iNumY*3+j*3+0] = tempctrlpoints[(i-1)*iNumY*3+j*3+0];
				ctrlpoints[i*iNumY*3+j*3+1] = tempctrlpoints[(i-1)*iNumY*3+j*3+1];
				ctrlpoints[i*iNumY*3+j*3+2] = tempctrlpoints[(i-1)*iNumY*3+j*3+2];
			}
			else if(i == 0)
			{
				ctrlpoints[i*iNumY*3+j*3+0] = tempctrlpoints[i*iNumY*3+j*3+0];
				ctrlpoints[i*iNumY*3+j*3+1] = tempctrlpoints[i*iNumY*3+j*3+1];
				ctrlpoints[i*iNumY*3+j*3+2] = tempctrlpoints[i*iNumY*3+j*3+2];
			}
		}
	}
	iNumX++;
}
void Surfaces::addYnum()
{
	if (iNumY >= 8)
		return;

	GLfloat *tempctrlpoints;
	tempctrlpoints = new GLfloat[iNumX*iNumY*3];
	//临时数据存储
	for ( int i = 0; i < iNumX; i++ )
	{
		for ( int j = 0; j < iNumY; j++ )
		{
			tempctrlpoints[i*iNumY*3+j*3+0] = ctrlpoints[i*iNumY*3+j*3+0];
			tempctrlpoints[i*iNumY*3+j*3+1] = ctrlpoints[i*iNumY*3+j*3+1];
			tempctrlpoints[i*iNumY*3+j*3+2] = ctrlpoints[i*iNumY*3+j*3+2];
		}
	}
	//ctrlpoints = new GLfloat[iNumX*(iNumY+1)*3];
	for (int i = 0; i < iNumX; i++)
	{
		for (int j = 0; j < iNumY+1; j++)
		{
			if (j != iNumY && j != 0)
			{
				ctrlpoints[i*(iNumY+1)*3+j*3+0] = tempctrlpoints[i*iNumY*3+(j-1)*3+0]+((float)(iNumY-j)/(float)iNumY)*(tempctrlpoints[i*iNumY*3+j*3+0]-tempctrlpoints[i*iNumY*3+(j-1)*3+0]);
				ctrlpoints[i*(iNumY+1)*3+j*3+1] = tempctrlpoints[i*iNumY*3+(j-1)*3+1]+((float)(iNumY-j)/(float)iNumY)*(tempctrlpoints[i*iNumY*3+j*3+1]-tempctrlpoints[i*iNumY*3+(j-1)*3+1]);
				ctrlpoints[i*(iNumY+1)*3+j*3+2] = tempctrlpoints[i*iNumY*3+(j-1)*3+2]+((float)(iNumY-j)/(float)iNumY)*(tempctrlpoints[i*iNumY*3+j*3+2]-tempctrlpoints[i*iNumY*3+(j-1)*3+2]);
			}
			else if(j == iNumY)
			{
				ctrlpoints[i*(iNumY+1)*3+j*3+0] = tempctrlpoints[i*iNumY*3+(j-1)*3+0];
				ctrlpoints[i*(iNumY+1)*3+j*3+1] = tempctrlpoints[i*iNumY*3+(j-1)*3+1];
				ctrlpoints[i*(iNumY+1)*3+j*3+2] = tempctrlpoints[i*iNumY*3+(j-1)*3+2];
			}
			else if(j == 0)
			{
				ctrlpoints[i*(iNumY+1)*3+j*3+0] = tempctrlpoints[i*iNumY*3+j*3+0];
				ctrlpoints[i*(iNumY+1)*3+j*3+1] = tempctrlpoints[i*iNumY*3+j*3+1];
				ctrlpoints[i*(iNumY+1)*3+j*3+2] = tempctrlpoints[i*iNumY*3+j*3+2];
			}
		}
	}
	iNumY++;
}
void Surfaces::subXnum()
{
	if (iNumX <= 2)
		return;

	GLfloat *tempctrlpoints;
	tempctrlpoints = new GLfloat[iNumX*iNumY*3];
	//临时数据存储
	for ( int i = 0; i < iNumX; i++ )
	{
		for ( int j = 0; j < iNumY; j++ )
		{
			tempctrlpoints[i*iNumY*3+j*3+0] = ctrlpoints[i*iNumY*3+j*3+0];
			tempctrlpoints[i*iNumY*3+j*3+1] = ctrlpoints[i*iNumY*3+j*3+1];
			tempctrlpoints[i*iNumY*3+j*3+2] = ctrlpoints[i*iNumY*3+j*3+2];
		}
	}
	//ctrlpoints = new GLfloat[(iNumX-1)*iNumY*3];
	for (int i = 0; i < iNumX-1; i++)
	{
		for (int j = 0; j < iNumY; j++)
		{
			if (i != iNumX-2 && i != 0)
			{
				ctrlpoints[i*iNumY*3+j*3+0] = tempctrlpoints[i*iNumY*3+j*3+0]+((float)i/(float)(iNumX-2))*(tempctrlpoints[(i+1)*iNumY*3+j*3+0]-tempctrlpoints[i*iNumY*3+j*3+0]);
				ctrlpoints[i*iNumY*3+j*3+1] = tempctrlpoints[i*iNumY*3+j*3+1]+((float)i/(float)(iNumX-2))*(tempctrlpoints[(i+1)*iNumY*3+j*3+1]-tempctrlpoints[i*iNumY*3+j*3+1]);
				ctrlpoints[i*iNumY*3+j*3+2] = tempctrlpoints[i*iNumY*3+j*3+2]+((float)i/(float)(iNumX-2))*(tempctrlpoints[(i+1)*iNumY*3+j*3+2]-tempctrlpoints[i*iNumY*3+j*3+2]);
			}
			else if(i == iNumX-2)
			{
				ctrlpoints[i*iNumY*3+j*3+0] = tempctrlpoints[(i+1)*iNumY*3+j*3+0];
				ctrlpoints[i*iNumY*3+j*3+1] = tempctrlpoints[(i+1)*iNumY*3+j*3+1];
				ctrlpoints[i*iNumY*3+j*3+2] = tempctrlpoints[(i+1)*iNumY*3+j*3+2];
			}
			else if(i == 0)
			{
				ctrlpoints[i*iNumY*3+j*3+0] = tempctrlpoints[i*iNumY*3+j*3+0];
				ctrlpoints[i*iNumY*3+j*3+1] = tempctrlpoints[i*iNumY*3+j*3+1];
				ctrlpoints[i*iNumY*3+j*3+2] = tempctrlpoints[i*iNumY*3+j*3+2];
			}
		}
	}
	iNumX--;
}
void Surfaces::subYnum()
{
	if (iNumY <= 2)
		return;

	GLfloat *tempctrlpoints;
	tempctrlpoints = new GLfloat[iNumX*iNumY*3];
	//临时数据存储
	for ( int i = 0; i < iNumX; i++ )
	{
		for ( int j = 0; j < iNumY; j++ )
		{
			tempctrlpoints[i*iNumY*3+j*3+0] = ctrlpoints[i*iNumY*3+j*3+0];
			tempctrlpoints[i*iNumY*3+j*3+1] = ctrlpoints[i*iNumY*3+j*3+1];
			tempctrlpoints[i*iNumY*3+j*3+2] = ctrlpoints[i*iNumY*3+j*3+2];
		}
	}
	//ctrlpoints = new GLfloat[iNumX*(iNumY-1)*3];
	for (int i = 0; i < iNumX; i++)
	{
		for (int j = 0; j < iNumY-1; j++)
		{
			if (j != iNumY-2 && j != 0)
			{
				ctrlpoints[i*(iNumY-1)*3+j*3+0] = tempctrlpoints[i*iNumY*3+j*3+0]+((float)j/(float)(iNumY-2))*(tempctrlpoints[i*iNumY*3+(j+1)*3+0]-tempctrlpoints[i*iNumY*3+j*3+0]);
				ctrlpoints[i*(iNumY-1)*3+j*3+1] = tempctrlpoints[i*iNumY*3+j*3+1]+((float)j/(float)(iNumY-2))*(tempctrlpoints[i*iNumY*3+(j+1)*3+1]-tempctrlpoints[i*iNumY*3+j*3+1]);
				ctrlpoints[i*(iNumY-1)*3+j*3+2] = 0;
			}
			else if(j == iNumY-2)
			{
				ctrlpoints[i*(iNumY-1)*3+j*3+0] = tempctrlpoints[i*iNumY*3+(j+1)*3+0];
				ctrlpoints[i*(iNumY-1)*3+j*3+1] = tempctrlpoints[i*iNumY*3+(j+1)*3+1];
				ctrlpoints[i*(iNumY-1)*3+j*3+2] = 0;
			}
			else if(j == 0)
			{
				ctrlpoints[i*(iNumY-1)*3+j*3+0] = tempctrlpoints[i*iNumY*3+j*3+0];
				ctrlpoints[i*(iNumY-1)*3+j*3+1] = tempctrlpoints[i*iNumY*3+j*3+1];
				ctrlpoints[i*(iNumY-1)*3+j*3+2] = 0;
			}
		}
	}
	iNumY--;
}