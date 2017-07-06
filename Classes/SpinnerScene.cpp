#include "SpinnerScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1

HANDLE console;
DWORD cw;
const wchar_t* str;


Scene* Spinner::createScene(HANDLE cons)
{
	console = cons;
	return Spinner::create();
}

bool Spinner::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto BG = Sprite::create("Background.jpg");
	BG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BG, -1);
    sprite = Sprite::create("Spinner.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setScale(0.1f);
	
	auto scaleTo = ScaleTo::create(1.0f, 1.0f, 1.0f);
	sprite->runAction(scaleTo);
	this->addChild(sprite, 0);
#ifdef WIN32
	str = TEXT("Scene STARTED!!\n");
	WriteConsole(console, str, wcslen(str), &(DWORD)cw, NULL);
#endif
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, sprite);
	auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Spinner::TouchBegan, this);	
    touchListener->onTouchMoved = CC_CALLBACK_2(Spinner::TouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Spinner::TouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Spinner::TouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sprite);
	auto rotateBy = RotateBy::create(0.9f, 720.0f);
	sprite->runAction(rotateBy);
    return true;
}

bool Spinner::TouchBegan (Touch* touch, Event* event) 
{
	Point p = Director::getInstance()->convertToGL(touch->getLocationInView());
#ifdef WIN32
	_snprintf_s(buf , 300, "touch began ... x = %f y = %f\n\n", p.x, p.y);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t * wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
	free(wcstring);
#elif
	CCLOG("touch began  ... x = %f y = %f\n\n", p.x, p.y);
#endif
	return true; // if you are consuming it
}

void Spinner::TouchMoved (Touch* touch, Event* event) 
{
	auto rotateBy = RotateBy::create(2, 360.0f);
	sprite->runAction(rotateBy);
#ifdef WIN32
	_snprintf_s(buf, 300, "touch move  ... x = %f y = %f\n\n", touch->getLocationInView().x, touch->getLocationInView().y);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t * wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
	free(wcstring);
#elif
	CCLOG("touch moved  ... x = %f y = %f\n\n", touch->getLocationInView().x, touch->getLocationInView().y);
#endif

}

void Spinner::TouchEnded (Touch* touch, Event* event) 
{

#ifdef WIN32
	_snprintf_s(buf, 300, "touch ended  ... x = %f y = %f\n\n", touch->getLocationInView().x, touch->getLocationInView().y);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t * wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
	free(wcstring);
#elif
	CCLOG("touch ended  ... x = %f y = %f\n\n", touch->getLocationInView().x, touch->getLocationInView().y);
#endif

}

void Spinner::TouchCancelled(Touch* touch, Event* event)
{

#ifdef WIN32
	_snprintf_s(buf, 300, "touch cancelled  ... x = %f y = %f\n\n", touch->getDelta().x, touch->getDelta().y);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t * wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
	free(wcstring);
#elif
	CCLOG("touch canceled  ... x = %f y = %f\n\n", touch->getLocationInView().x, touch->getLocationInView().y);
#endif
}