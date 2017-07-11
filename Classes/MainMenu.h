#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene(HANDLE cons);
	virtual bool			init();
	void					spinnerCallBack(cocos2d::Ref* ref);
	void					wheelCallBack(cocos2d::Ref* ref);
	CREATE_FUNC(MainMenu);
};
#endif