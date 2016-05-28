#ifndef _BOX_H_
#define _BOX_H_

#include "cocos2d.h"

class Box : public cocos2d::Sprite
{
int i;
int j;

    public:
        Box();
        ~Box();
        static Box* create();
	void setPos(int i,int j){
		this->i = i;
		this->j = j;
	}
	int getI(){
		return this->i;
	}
	int getJ(){
		return this->j;
	}
};

#endif // _BOX_H__
