#include "MainMenu.h"
#include "SpinnerScene.h"
#include "LuckyWheel.h"
#include "DrawWheel.h"
#include "Api.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{
	if (!Scene::init())
		return false;
	debug("MainMenu\n\n");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("Background.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, -1);
	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	MenuItemFont* spinner = MenuItemFont::create("Spinner", CC_CALLBACK_1(MainMenu::spinnerCallBack, this));
	spinner->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 20);
	MenuItemFont* wheel = MenuItemFont::create("Lucky Wheel", CC_CALLBACK_1(MainMenu::wheelCallBack, this));
	wheel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20);
	menu->addChild(spinner);
	menu->addChild(wheel);
	this->addChild(menu);
	
	return true;
}

void MainMenu::spinnerCallBack(Ref* ref)
{
	setSpinnerSpeed(1);
	auto spinner = Spinner::createScene();

	//Director::getInstance()->replaceScene(spinner);
	Director::getInstance()->pushScene(spinner);
}

void MainMenu::wheelCallBack(Ref* ref)
{
	setWheelSections(7);
	auto wheel = LuckyWheel::createScene();

	//Director::getInstance()->replaceScene(spinner);
	Director::getInstance()->pushScene(wheel);
}

void MainMenu::update(float tm)
{

}