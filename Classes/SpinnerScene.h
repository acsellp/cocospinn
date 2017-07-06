#ifndef __SPINNER_SCENE_H__
#define __SPINNER_SCENE_H__

#include "cocos2d.h"
#define COCOS_DEBUG 1

class Spinner : public cocos2d::Scene
{
private:
    cocos2d::Sprite* sprite;
    float nrRot;
    float angleRot;
    int lastTouchID;
	char buf[300];
    int touchY;
    int touchX;
public:

    static cocos2d::Scene* createScene(HANDLE console);

    virtual bool init();
    
    // a selector callback
   // void menuCloseCallback(cocos2d::Ref* pSender);
	//void onMouseDown(Event *event);
	//void onMouseUp(Event *event);
    // implement the "static create()" method manually
    CREATE_FUNC(Spinner);
    
    bool TouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void TouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void TouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
