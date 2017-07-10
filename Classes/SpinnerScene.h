#pragma once
#ifndef __SPINNER_SCENE_H__
#define __SPINNER_SCENE_H__

#include "cocos2d.h"
#define COCOS_DEBUG 1
#define MAX_SPEED 100
#define MIN_SPEED 5

class Spinner : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(HANDLE cons);
    virtual bool init();
	void setSpeedAndDir(void);
    CREATE_FUNC(Spinner);
    bool TouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void TouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void TouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void menuCallBack(Ref* ref);
private:
	cocos2d::Sprite* sprite;
	cocos2d::Point first;
	cocos2d::Point last;
	cocos2d::Sequence *sequ;
	float centerx;
	float centery;
	float speed;
	float aRot;
	float nRot;
	bool forward;
	uint32_t score;
	uint32_t serverData;

	char buf[300];
};

#endif
