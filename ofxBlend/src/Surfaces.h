/**
 * @file Surfaces.h
 * @author GeistYp
 * @date 2009/12/01
 *
 * @brief 可控扭曲面头文件
 */

#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"

#define SingleScreenWidth 1440
#define SingleScreenHeigth 900
/**
 * @class Surfaces Surfaces.h
 * @brief 可控扭曲面类
 *
 * 使用例子：
 * @code
 		// 初始化，两种方式
		Surfaces sf;

		sf.initSurfacePara(8, 8, 0, 0, 1280, 1024);		// 使用参数初始化，默认纹理坐标（0，0）-（1，1），细节程度20
		sf.readFromXML("surfaces.xml");					// 使用设置文件初始化
		...
		// 更新曲面
		sf.updateSurface();
		...
		// 绘制曲面
		sf.drawSurface();
		...
		// 鼠标控制
		sf.mouseRelease(x, y);
		sf.mouseDragged(x, y);
		sf.mouseClicked(x, y);
		// 键盘控制
		sf.keyPressed(key);
		// 设置
		sf.resetControlPts();			// 重置控制点
		sf.saveToXML("surfaces.xml");	// 保存设置
		sf.displayControlPoint(!sf.bOpenCtrlPts);	// 是否启用控制点模式
 * @endcode
 */
class Surfaces
{
public:
	Surfaces(void);
	~Surfaces(void);

	/**
	 * @brief 初始化控制点内存，按照设置的左右两点等间隔排列控制点
	 * @return void
	 * @see resetControlPts
	 * @see ctrlpoints
	 */
	void initCtrlPtsArray();


	/**
	 * @brief 初始化纹理内存，按照设置的左右纹理点坐标等间隔计算
	 * @return void
	 * @see texpts
	 */
	void initTexPtsArray();


	/**
	 * @brief 使用参数初始化曲面
	 * @param  iNumPointX X轴点数量
	 * @param  iNumPointY Y轴点数量
	 * @param  iXL 曲面左上角X坐标
	 * @param  iYL 曲面左上角Y坐标
	 * @param  iXR 曲面右下角X坐标
	 * @param  iYR 曲面右下角Y坐标
	 * @param  fTexXL 纹理左上角X坐标
	 * @param  fTexYL 纹理左上角Y坐标
	 * @param  fTexXR 纹理右下角X坐标
	 * @param  fTexYR 纹理右下角Y坐标
	 * @param  iDets 纹理细节程度
	 * @return void
	 * @see initCtrlPtsArray
	 * @see initTexPtsArray
	 * @see setSurfaces
	 */
	void initSurfacePara(string _fileName, int iNumPointX, int iNumPointY, int iXL, int iYL, int iXR, int iYR,
					 float fTexXL = 0.0, float fTexYL = 0.0, float fTexXR = 1.0, float fTexYR = 1.0,
					 int iDets = 20);

	/**
	 * @brief 读取xml文件并初始化曲面，默认在data目录下
	 * @param  fileName 需要读取的xml文件名
	 * @return void
	 */
	void readFromXML(string _fileName);
	string fileName;


	/**
	 * @brief 保存曲面参数到xml文件，默认在data目录下
	 * @param  fileName 保存文件名
	 * @return void
	 */
	void saveToXML();
	void saveToXML(ofVec2f _offset);

	/**
	 * @brief 设置曲面，初始化GL_MAP2_VERTEX_3和GL_MAP2_TEXTURE_COORD_2的求值程序
	 * @return void
	 */
	void setSurfaces();

	/**
	 * @brief 绘制曲面，使用填充方式绘制，在使用前需要制定颜色或纹理ID，启用控制点模式还会绘制控制点，控制点红色，标号蓝
	 * @return void
	 */
	void drawSurface();

	/**
	 * @brief 更新曲面，仅当控制点发生变化才重新初始化GL_MAP2_VERTEX_3的求值程序
	 * @return void
	 */
	void updateSurface();

	/**
	 * @brief 重置控制点位置，按等间隔排列
	 * @return void
	 * @see ctrlpoints
	 */
	void resetControlPts();

	/**
	 * @brief 启用控制点模式
	 * @param  disCtrl 是否启用控制点模式
	 * @return void
	 * @see bOpenCtrlPts
	 */
	void displayControlPoint(bool disCtrl) { 
		bOpenCtrlPts = disCtrl;
	}

	/**
	 * @brief 鼠标点击控制，在控制点模式下检查当前点击位置是否有控制点
	 * @param  x 鼠标位置x
	 * @param  y 鼠标位置y
	 * @return void
	 * @see bOpenCtrlPts
	 * @see iChoosedPts
	 */
	void mouseClicked(int x, int y);

	/**
	 * @brief 鼠标拖动控制，在选中控制点的情况下，更新控制点位置
	 * @param  x 鼠标位置x
	 * @param  y 鼠标位置y
	 * @return void
	 * @see bChanged
	 * @see iChoosedPts
	 */
	void mouseDragged(int x, int y);

	/**
	 * @brief 鼠标释放，恢复无选中状态
	 * @param  x 鼠标位置x
	 * @param  y 鼠标位置y
	 * @return void
	 */
	void mouseRelease(int x, int y);

	/**
	* @brief 键盘控制
	* @param  key 鼠标位置key
	* @return void
	*/
	void keyPressed(int key);
	void setactive(bool _active);

	void addXnum();
	void addYnum();
	void subXnum();
	void subYnum();

	bool active;

	GLfloat *ctrlpoints;	///< 控制点数组 N*N*3
	GLfloat *texpts;		///< 纹理数组 N*N*2

	int iChoosedPts;	///< 选中的控制点ID，未选中其值为-1
	bool bChanged;		///< 控制点是否有变化

	bool bOpenCtrlPts;	///< 是否启用控制点模式

	ofxXmlSettings xml;	///< xml文档对象用于读取和写入文件

private:
	int iNumX, iNumY;		///< 控制点XY轴数量
	int iDetails;			///< 求值程序细节程度
	int iScrLeftX, iScrLeftY, iScrRightX, iScrRightY;	///< 屏幕左上右下位置

	float fTexLeftX, fTexLeftY, fTexRightX, fTexRightY; ///< 纹理左上右下位置

	// 文档标记
	string strBasicTag;
	string strNumX, strNumY, strDetails;
	string strScrLeftX, strScrLeftY, strScrRightX, strScrRightY;
	string strTexLeftX, strTexLeftY, strTexRightX, strTexRightY;
	string strCtrlPtsTag, strTexPtsTag, strSubCtrlPtsTag, strSubTexPtsTag;

/*	int screenID;*/

};
