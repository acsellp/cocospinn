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
	originy = visibleSize.height / 2;
	originx = visibleSize.width / 2;
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
	first = Director::getInstance()->convertToGL(touch->getLocationInView());
	return true; // if you are consuming it
}

void Spinner::TouchMoved (Touch* touch, Event* event) 
{
	Point p = Director::getInstance()->convertToGL(touch->getLocationInView());
#ifdef WIN32
	_snprintf_s(buf, 300, "Touch move  %f,%f\n", p.x, p.y);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t * wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
	free(wcstring);
#elif
	CCLOG("Touch move  %f,%f\n", touch->getLocationInView().x, touch->getLocationInView().y);
#endif
}

void Spinner::TouchEnded (Touch* touch, Event* event) 
{
	last = Director::getInstance()->convertToGL(touch->getLocationInView());
	setSpeed();
	if (speed > MAX_SPEED)
		speed = MAX_SPEED;
	else if (speed < MIN_SPEED)
		speed = MIN_SPEED;
	float nRot = MIN_SPEED / speed;
	float aRot = 580 * speed / MIN_SPEED;
	auto rotateBy = RotateBy::create(nRot, aRot);
	sprite->runAction(rotateBy);
}

void Spinner::TouchCancelled(Touch* touch, Event* event)
{
	
}

void Spinner::setSpeed()
{
	if ((first.y > last.y && last.x > originx) \
		|| (first.x > last.x && last.y < originy) \
		|| (first.y < last.y && last.x < originx) \
		|| (first.x < last.x && last.y > originy ))
	{
		speed = (first.y - last.y) + (first.x - last.x);
		if (speed < 0)
			speed *= -1;
#ifdef WIN32
		_snprintf_s(buf, 300, "\nBegin: %f,%f\nEnd: %f,%f\nOrigin: %f,%f\nSpeed: %f\n", first.x, first.y, last.x, last.y, originx, originy, speed);
		size_t newsize = strlen(buf) + 1;
		size_t convertedChars = 0;
		wchar_t* wcstring = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
		WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
		free(wcstring);
#elif
		CCLOG("Begin: %f,%f\nEnd: %f,%f\n\n", firstX, firstY, lastX, lastY);
#endif
	}
}