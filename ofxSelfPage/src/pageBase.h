#pragma once
#include "ofMain.h"
/************************************************************************/
/* project name: 
/* file describe:界面基类
/* author:Hui
/* date:2016/9/6
/************************************************************************/

enum PAGE_SWITCH_MODE
{
	NO_SWITCH_MODE,
	LEFT_LEAVE_SWITCH_MODE,
	RIGHT_LEAVE_SWITCH_MODE,
	UP_LEAVE_SWITCH_MODE,
	DOWN_LEAVE_SWITCH_MODE,
};


class pageBase
{
public:
	pageBase(void);
	virtual ~pageBase(void);

	static string name() { return "noName"; }

	void setParent(pageBase * _parent){parent = _parent;}
	pageBase * getParent(){return parent;}

	void setChild(pageBase * _child) { childer = _child; }
	pageBase * getChild() { return childer; }

	void setControlIndex(int _index) { controlIndex = _index; }
	int getControlIndex() { return controlIndex; }

	virtual void begin(){
		reset();
		setActive(true);
		beginTime = ofGetElapsedTimef();
	};
	virtual void end(){
		setActive(false);
	};

	virtual void reset() {};

	void cusupdate(){
		if (isActiving())
		{
			update();
		}
	};

	void cusdraw(int _alpha)
	{
		if (isActiving())
		{
			draw(_alpha);
		}
	}
	void cusdraw(){
		if (isActiving())
		{
			draw();
		}
	};

	void cuskeyPressed(int key){
		if (isActiving() && isBeginOk())
		{
			keyPressed(key);
		}
	};
	void cuskeyReleased(int key){
		if (isActiving() && isBeginOk())
		{
			keyReleased(key);
		}
	};
	void cusmouseMoved(int x, int y ){
		if (isActiving() && isBeginOk())
		{
			mouseMoved(x,y);
		}
	};
	void cusmouseDragged(int x, int y, int button){
		if (isActiving() && isBeginOk())
		{
			mouseDragged(x,y,button);
		}
	};
	void cusmousePressed(int x, int y, int button){
		if (isActiving() && isBeginOk())
		{
			mousePressed(x,y,button);
		}
	};
	void cusmouseReleased(int x, int y, int button){
		if (isActiving() && isBeginOk())
		{
			mouseReleased(x,y,button);
		}
	};

	void cusPlayAnimation()
	{
		if (isActiving() && isBeginOk())
		{
			playAnimation();
		}
	}

	bool isActiving(){return bActive;};

	void setDataDir(string _dir) { dataDir = _dir; };
	string getDataDir() { return dataDir; };
	void setStageRect(ofRectangle _rect) { stageRect = _rect; }
	ofRectangle getStageRect() { return stageRect; };
	virtual void backImgDraw(){};

	void setId(int _id);
	int getId()const;

	void addTouchId(int _id, PAGE_SWITCH_MODE _mode);
	void removeTouchId(int _id);

	bool pageTouch(int _id);
protected:
	bool isBeginOk(){
		return (ofGetElapsedTimef() - beginTime) > 0.2f;
	}
	void setActive(bool _bActive){bActive = _bActive;};
	virtual void update(){};
	virtual void draw(){};
	virtual void draw(int _alpha) {};

	virtual void keyPressed(int key){};
	virtual void keyReleased(int key){};
	virtual void mouseMoved(int x, int y ){};
	virtual void mouseDragged(int x, int y, int button){};
	virtual void mousePressed(int x, int y, int button){};
	virtual void mouseReleased(int x, int y, int button){};

	virtual void playAnimation() {};
private:
	bool bActive;
	string dataDir;
	float beginTime;

	ofRectangle stageRect;
	pageBase * parent;
	pageBase * childer;

	int controlIndex;
	int pageId;

	map<int, PAGE_SWITCH_MODE> touchIds;
};

