#include "SplashBalloons.h"
#include "Api.h"

USING_NS_CC;

Scene*	SplashBalloons::createScene()
{
	return SplashBalloons::create();
}

bool	SplashBalloons::init()
{
	if (!Scene::init())
		return false;

	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float centery = visibleSize.height / 2;
	float centerx = visibleSize.width / 2;

	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	MenuItemFont* back = MenuItemFont::create("Back", CC_CALLBACK_1(SplashBalloons::menuCallBack, this));
	back->setPosition(40.0f, visibleSize.height - 20.0f);
	menu->addChild(back);
	this->addChild(menu, 2);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SplashBalloons::touchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SplashBalloons::touchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SplashBalloons::touchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

bool	SplashBalloons::touchBegan(Touch* touch, Event* event)
{
	first = Director::getInstance()->convertToGL(touch->getLocationInView());
	return true;
}

void	SplashBalloons::touchMoved(Touch* touch, Event* event)
{

}

void	SplashBalloons::touchEnded(Touch* touch, Event* event)
{
	last = Director::getInstance()->convertToGL(touch->getLocationInView());
}

void	SplashBalloons::menuCallBack(Ref* ref)
{
	Director::getInstance()->popScene();
}