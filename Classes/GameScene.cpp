#include "GameScene.h"
#include "Box.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()

USING_NS_CC;

Scene* Game::createScene()
{
    auto scene = Scene::create();
    
    auto layer = Game::create();

    scene->addChild(layer);

    return scene;
}

bool Game::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    int rect_width = visibleSize.width/7;

    for(int i=0;i<5;i++){

        for(int j=0;j<5;j++){

            auto sprite = Box::create();

            sprite->setTextureRect(Rect(0,0,rect_width,rect_width));
            sprite->setAnchorPoint(Vec2(0.5,0.5));
            sprite->setPosition(Vec2( origin.x + visibleSize.width/2 - i*rect_width + rect_width*2 ,
                                    origin.y + visibleSize.height/2 - j*rect_width + rect_width*2 ));
            sprite->setColor(Color3B(52, 152, 219));
		
	    sprite->setPos(j,i);

            this->rectMatrix.push_back(sprite);

            this->addChild(sprite);

        }

    }

    auto label = Label::createWithTTF("name","fonts/Marker Felt.ttf",12);

    auto listener = EventListenerTouchOneByOne::create();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch,Event* event) {
        
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        
        Point pt = touch->getLocation();

        for(auto rect: this->rectMatrix)
        {
                
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		
	    Point location = touch->getLocationInView();

	    location = Director::getInstance()->convertToGL(location);

	    Node *ptr = dynamic_cast<Node*>(rect);

	    Rect pTextureRect = ptr->boundingBox();

	    if(pTextureRect.containsPoint(location)){
		this->selectBox.push_back(rect);

		rect->runAction(TintTo::create(0.5f,255.0f,255.0f,255.0f));

		return true;
	    }

        }
        
        return false;
    };

    listener->onTouchMoved = [&](Touch* touch,Event* event) {
	auto target = static_cast<Sprite *>(event->getCurrentTarget());
        
        Point pt = touch->getLocation();

        for(auto rect: this->rectMatrix)
        {
                
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		
	    Point location = touch->getLocationInView();

	    location = Director::getInstance()->convertToGL(location);

	    Node *ptr = dynamic_cast<Node*>(rect);

	    Rect pTextureRect = ptr->boundingBox();

	    if(pTextureRect.containsPoint(location)){
		
		bool is = false;

		for(auto sRect: this->selectBox){
		
			if(sRect->getI() == rect->getI() 
			&& sRect->getJ() == rect->getJ()){	
				is = true;
				break;
			}
		
		}
		
		if(!is){
			rect->runAction(TintTo::create(0.5f,255.0f,255.0f,255.0f));
			this->selectBox.push_back(rect);
		}
	
		break;
	    }
	}
    };

    listener->onTouchEnded = [=](Touch* touch,Event* event) {
	
	for(auto rect: this->selectBox){
		rect->runAction(TintTo::create(0.5f,52.0f, 152.0f, 219.0f));
	}

	this->selectBox.clear();

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}
