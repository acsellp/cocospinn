#pragma once

#include "cocos2d.h"

class Spinner : public cocos2d::Scene
{
public:
    static cocos2d::Scene*	createScene();
    virtual bool			init();
	void					setSpeedAndDir(void);
    bool					TouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void					TouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void					TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void					TouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void					menuCallBack(Ref* ref);
	void					update(float dt);
	CREATE_FUNC(Spinner);
private:
	cocos2d::Point			first;
	cocos2d::Point			last;
	std::vector<uint16_t>	touch_stack;
	float					centerx;
	float					centery;
	uint16_t				speed;
	float					aRot;
	float					nRot;
	bool					forward;
	uint32_t				score;
	uint32_t				serverData;
};
