

#ifndef __LUCKY_WHEEL_H__
#define __LUCKY_WHEEL_H__
#pragma once
#include "cocos2d.h"
#define COCOS_DEBUG 1
#define MAX_SPEED 100
#define MIN_SPEED 5

class LuckyWheel : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(HANDLE cons);
	virtual bool init();
	void setSpeedAndDir(void);
	CREATE_FUNC(LuckyWheel);
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
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
