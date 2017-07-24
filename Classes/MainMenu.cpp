#include "MainMenu.h"
#include "SpinnerScene.h"
#include "LuckyWheel.h"
#include "DrawWheel.h"
#include "Api.h"
#include "SplashBalloons.h"
#include "WheelOfFortune.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{
	if (!Scene::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("background.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y));
	this->addChild(bg, -1);
	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	MenuItemFont* spinner = MenuItemFont::create("Spinner", CC_CALLBACK_1(MainMenu::spinnerCallBack, this));
	spinner->setPosition(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y - 20);
	MenuItemFont* wheel = MenuItemFont::create("Lucky Wheel", CC_CALLBACK_1(MainMenu::wheelCallBack, this));
	wheel->setPosition(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y + 20);
	MenuItemFont* wof = MenuItemFont::create("Wheel Of Fortune", CC_CALLBACK_1(MainMenu::wheelOfFOrutneCallBack, this));
	wof->setPosition(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y + 60);
	MenuItemFont* sb = MenuItemFont::create("Splash Balloons", CC_CALLBACK_1(MainMenu::sbCallBack, this));
	sb->setPosition(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y + 100);
	menu->addChild(spinner);
	menu->addChild(wheel);
	menu->addChild(wof);
	menu->addChild(sb);
	this->addChild(menu);
	
	return true;
}

void MainMenu::spinnerCallBack(Ref* ref)
{
	//API::updateSpinnerSpeed(1);
	auto spinner = Spinner::createScene();

	//Director::getInstance()->replaceScene(spinner);
	Director::getInstance()->pushScene(spinner);
}

void MainMenu::wheelCallBack(Ref* ref)
{
	//API::updateWheelSections(7);
	auto wheel = LuckyWheel::createScene();

	//Director::getInstance()->replaceScene(spinner);
	Director::getInstance()->pushScene(wheel);
}

void MainMenu::wheelOfFOrutneCallBack(Ref* ref)
{
	auto wof = WheelOfFortune::createScene();
	Director::getInstance()->pushScene(wof);
}

void MainMenu::sbCallBack(Ref* ref)
{
	auto sb = SplashBalloons::createScene();
	Director::getInstance()->pushScene(sb);
}

void MainMenu::update(float tm)
{

}