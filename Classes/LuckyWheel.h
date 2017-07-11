#pragma once
#ifndef __LUCKY_WHEEL_H__
#define __LUCKY_WHEEL_H__
#include "cocos2d.h"
#define COCOS_DEBUG 1
#define MAX_SPEED 100
#define MIN_SPEED 5

class LuckyWheel : public cocos2d::Scene
{
public:
	CREATE_FUNC(LuckyWheel);
	static			cocos2d::Scene* createScene(HANDLE cons);
	virtual bool	init();
	void			setSpeedAndDir(void);
	bool			touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void			touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void			touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void			touchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void			menuCallBack(Ref* ref);
	void			updateSectionPosition(float newPosition);
	uint8_t			getSectionIndex(float angle);
	void			initSections();
private:
	cocos2d::Layer* sprite;
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

	typedef struct	wheelSections_s
	{
		float infAngle;
		float supAngle;
		char sectionParam[50];
	}wheelSection_t;
	wheelSection_t* sec;
	int sections;

	char buf[300];
};

#endif
