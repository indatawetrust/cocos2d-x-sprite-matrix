#include "Box.h"

using namespace cocos2d;

Box::Box() {}

Box::~Box() {}

Box* Box::create()
{
    Box* box = new Box();
    
    if (box && box->init())
    {
        box->autorelease();
        return box;
    }
}
