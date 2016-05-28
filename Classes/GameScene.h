#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <vector>

using namespace std;

#include "cocos2d.h"
#include "Box.h"

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	
    vector<Box*> rectMatrix;

    vector<Box*> selectBox;

    vector<cocos2d::Label*> text;

    CREATE_FUNC(Game);
};

#endif // __GAME_SCENE_H__
