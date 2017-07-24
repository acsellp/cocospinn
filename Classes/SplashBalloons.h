#pragma once

#include "cocos2d.h"

class SplashBalloons: public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene(void);
	virtual bool			init(void);
	void					menuCallBack(cocos2d::Ref* ref);
	bool					touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void					touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void					touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(SplashBalloons);

private:
	cocos2d::Size			visibleSize;
	cocos2d::Vec2			visibleOrigin;
	cocos2d::Point			first;
	cocos2d::Point			last;
};