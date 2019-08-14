#pragma once
/************************************************************************/
/* file describe:∞¥≈•≥ÈœÛ¿‡
/* author:hui
/* date:2016/12/8
/************************************************************************/
#include "ofMain.h"
class button
{
public:
	button(void);
	virtual ~button(void);

	virtual bool touch(int _x,int _y){
		return false;
	}
	virtual bool release(int _x,int _y){
		return false;
	}

	virtual void update(){};
	virtual void draw(){};

	void setName(const string & _name);
	string getName()const;

	void setId(const int & _id);
	int getId()const;

	void enable();
	void disable();
	bool isEnable();
protected:
	void setTouch(bool _touch){
		bTouched = _touch;
	}
	bool getTouch()const{
		return bTouched;
	}
private:
	string name;
	int id;
	bool bTouched;

	bool bEnable;

};

