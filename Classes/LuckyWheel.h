#pragma once
#ifndef __LUCKY_WHEEL_H__
#define __LUCKY_WHEEL_H__
#include "cocos2d.h"
#define COCOS_DEBUG 1
#define MAX_SPEED 100
#define MIN_SPEED 5

#define WHEEL_TAG 1000
#define SEQUENCE_TAG 2000

typedef struct	wheelSections_s
{
	float		infAngle;
	float		supAngle;
	char		sectionParam[50];
}				wheelSection_t;

class LuckyWheel : public cocos2d::Scene
{
public:
	CREATE_FUNC(LuckyWheel);
	static			cocos2d::Scene* createScene(HANDLE cons, int sec);
	virtual bool	init(void);
	void			setSpeedAndDir(void);
	bool			touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void			touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void			touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void			touchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void			menuCallBack(Ref* ref);
	void			updateSectionPosition(float newPosition);
	uint8_t			getSectionIndex(float angle);
	void			initSections(void);
	virtual void	update(float dt);
	void			updateCallBack(void);
	~LuckyWheel();
private:
	cocos2d::Point	first;
	cocos2d::Point	last;
	float			centerx;
	float			centery;
	float			speed;
	float			aRot;
	float			nRot;
	bool			forward;
	uint32_t		score;
	uint32_t		serverData;
	wheelSection_t*	sec;
};

#endif
