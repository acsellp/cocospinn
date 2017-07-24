#pragma once

#include "cocos2d.h"

class WheelOfFortune : public cocos2d::Scene
{
public :
	static cocos2d::Scene*	createScene(void);
	virtual bool			init(void);
	void					menuCallBack(cocos2d::Ref* ref);
	void					drawSection(cocos2d::DrawNode* node, cocos2d::Vec2 center, float radius, float angle, cocos2d::Color4F fillcol, int sections);
	void					initSections(void);
	bool					touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void					touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void					touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(WheelOfFortune);

private:
	//float					centery;
	//float					centerx;
	cocos2d::Size			visibleSize;
	cocos2d::Vec2			visibleOrigin;
	cocos2d::Point			first;
	cocos2d::Point			last;
};