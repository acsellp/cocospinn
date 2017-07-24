#pragma once

#include "cocos2d.h"
class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	void					spinnerCallBack(cocos2d::Ref* ref);
	void					wheelCallBack(cocos2d::Ref* ref);
	void					wheelOfFOrutneCallBack(cocos2d::Ref* ref);
	void					sbCallBack(cocos2d::Ref* ref);
	virtual void			update(float dt);
	CREATE_FUNC(MainMenu);
};