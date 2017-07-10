#include "MainMenu.h"
#include "SpinnerScene.h"
#include "LuckyWheel.h"


USING_NS_CC;

HANDLE console;
DWORD cw;

Scene* MainMenu::createScene(HANDLE cons)
{
	console = cons;
	return MainMenu::create();
}

bool MainMenu::init()
{
	if (!Scene::init())
		return false;

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
#ifdef WIN32
	auto spinner = Spinner::createScene(console);
#elif
	auto spinner = Spinner::createScene(nullptr);
#endif
	//Director::getInstance()->replaceScene(spinner);
	Director::getInstance()->pushScene(spinner);
}

void MainMenu::wheelCallBack(Ref* ref)
{
#ifdef WIN32
	auto wheel = LuckyWheel::createScene(console);
#elif
	auto wheel = LuckyWheel::createScene(nullptr);
#endif
	//Director::getInstance()->replaceScene(spinner);
	Director::getInstance()->pushScene(wheel);
}