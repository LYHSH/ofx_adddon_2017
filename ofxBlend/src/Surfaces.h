/**
 * @file Surfaces.h
 * @author GeistYp
 * @date 2009/12/01
 *
 * @brief �ɿ�Ť����ͷ�ļ�
 */

#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"

#define SingleScreenWidth 1440
#define SingleScreenHeigth 900
/**
 * @class Surfaces Surfaces.h
 * @brief �ɿ�Ť������
 *
 * ʹ�����ӣ�
 * @code
 		// ��ʼ�������ַ�ʽ
		Surfaces sf;

		sf.initSurfacePara(8, 8, 0, 0, 1280, 1024);		// ʹ�ò�����ʼ����Ĭ���������꣨0��0��-��1��1����ϸ�ڳ̶�20
		sf.readFromXML("surfaces.xml");					// ʹ�������ļ���ʼ��
		...
		// ��������
		sf.updateSurface();
		...
		// ��������
		sf.drawSurface();
		...
		// ������
		sf.mouseRelease(x, y);
		sf.mouseDragged(x, y);
		sf.mouseClicked(x, y);
		// ���̿���
		sf.keyPressed(key);
		// ����
		sf.resetControlPts();			// ���ÿ��Ƶ�
		sf.saveToXML("surfaces.xml");	// ��������
		sf.displayControlPoint(!sf.bOpenCtrlPts);	// �Ƿ����ÿ��Ƶ�ģʽ
 * @endcode
 */
class Surfaces
{
public:
	Surfaces(void);
	~Surfaces(void);

	/**
	 * @brief ��ʼ�����Ƶ��ڴ棬�������õ���������ȼ�����п��Ƶ�
	 * @return void
	 * @see resetControlPts
	 * @see ctrlpoints
	 */
	void initCtrlPtsArray();


	/**
	 * @brief ��ʼ�������ڴ棬�������õ��������������ȼ������
	 * @return void
	 * @see texpts
	 */
	void initTexPtsArray();


	/**
	 * @brief ʹ�ò�����ʼ������
	 * @param  iNumPointX X�������
	 * @param  iNumPointY Y�������
	 * @param  iXL �������Ͻ�X����
	 * @param  iYL �������Ͻ�Y����
	 * @param  iXR �������½�X����
	 * @param  iYR �������½�Y����
	 * @param  fTexXL �������Ͻ�X����
	 * @param  fTexYL �������Ͻ�Y����
	 * @param  fTexXR �������½�X����
	 * @param  fTexYR �������½�Y����
	 * @param  iDets ����ϸ�ڳ̶�
	 * @return void
	 * @see initCtrlPtsArray
	 * @see initTexPtsArray
	 * @see setSurfaces
	 */
	void initSurfacePara(string _fileName, int iNumPointX, int iNumPointY, int iXL, int iYL, int iXR, int iYR,
					 float fTexXL = 0.0, float fTexYL = 0.0, float fTexXR = 1.0, float fTexYR = 1.0,
					 int iDets = 20);

	/**
	 * @brief ��ȡxml�ļ�����ʼ�����棬Ĭ����dataĿ¼��
	 * @param  fileName ��Ҫ��ȡ��xml�ļ���
	 * @return void
	 */
	void readFromXML(string _fileName);
	string fileName;


	/**
	 * @brief �������������xml�ļ���Ĭ����dataĿ¼��
	 * @param  fileName �����ļ���
	 * @return void
	 */
	void saveToXML();
	void saveToXML(ofVec2f _offset);

	/**
	 * @brief �������棬��ʼ��GL_MAP2_VERTEX_3��GL_MAP2_TEXTURE_COORD_2����ֵ����
	 * @return void
	 */
	void setSurfaces();

	/**
	 * @brief �������棬ʹ����䷽ʽ���ƣ���ʹ��ǰ��Ҫ�ƶ���ɫ������ID�����ÿ��Ƶ�ģʽ������ƿ��Ƶ㣬���Ƶ��ɫ�������
	 * @return void
	 */
	void drawSurface();

	/**
	 * @brief �������棬�������Ƶ㷢���仯�����³�ʼ��GL_MAP2_VERTEX_3����ֵ����
	 * @return void
	 */
	void updateSurface();

	/**
	 * @brief ���ÿ��Ƶ�λ�ã����ȼ������
	 * @return void
	 * @see ctrlpoints
	 */
	void resetControlPts();

	/**
	 * @brief ���ÿ��Ƶ�ģʽ
	 * @param  disCtrl �Ƿ����ÿ��Ƶ�ģʽ
	 * @return void
	 * @see bOpenCtrlPts
	 */
	void displayControlPoint(bool disCtrl) { 
		bOpenCtrlPts = disCtrl;
	}

	/**
	 * @brief ��������ƣ��ڿ��Ƶ�ģʽ�¼�鵱ǰ���λ���Ƿ��п��Ƶ�
	 * @param  x ���λ��x
	 * @param  y ���λ��y
	 * @return void
	 * @see bOpenCtrlPts
	 * @see iChoosedPts
	 */
	void mouseClicked(int x, int y);

	/**
	 * @brief ����϶����ƣ���ѡ�п��Ƶ������£����¿��Ƶ�λ��
	 * @param  x ���λ��x
	 * @param  y ���λ��y
	 * @return void
	 * @see bChanged
	 * @see iChoosedPts
	 */
	void mouseDragged(int x, int y);

	/**
	 * @brief ����ͷţ��ָ���ѡ��״̬
	 * @param  x ���λ��x
	 * @param  y ���λ��y
	 * @return void
	 */
	void mouseRelease(int x, int y);

	/**
	* @brief ���̿���
	* @param  key ���λ��key
	* @return void
	*/
	void keyPressed(int key);
	void setactive(bool _active);

	void addXnum();
	void addYnum();
	void subXnum();
	void subYnum();

	bool active;

	GLfloat *ctrlpoints;	///< ���Ƶ����� N*N*3
	GLfloat *texpts;		///< �������� N*N*2

	int iChoosedPts;	///< ѡ�еĿ��Ƶ�ID��δѡ����ֵΪ-1
	bool bChanged;		///< ���Ƶ��Ƿ��б仯

	bool bOpenCtrlPts;	///< �Ƿ����ÿ��Ƶ�ģʽ

	ofxXmlSettings xml;	///< xml�ĵ��������ڶ�ȡ��д���ļ�

private:
	int iNumX, iNumY;		///< ���Ƶ�XY������
	int iDetails;			///< ��ֵ����ϸ�ڳ̶�
	int iScrLeftX, iScrLeftY, iScrRightX, iScrRightY;	///< ��Ļ��������λ��

	float fTexLeftX, fTexLeftY, fTexRightX, fTexRightY; ///< ������������λ��

	// �ĵ����
	string strBasicTag;
	string strNumX, strNumY, strDetails;
	string strScrLeftX, strScrLeftY, strScrRightX, strScrRightY;
	string strTexLeftX, strTexLeftY, strTexRightX, strTexRightY;
	string strCtrlPtsTag, strTexPtsTag, strSubCtrlPtsTag, strSubTexPtsTag;

/*	int screenID;*/

};
