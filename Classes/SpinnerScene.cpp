#include "SpinnerScene.h"
#include "SimpleAudioEngine.h"
#include "FileOperation.h"

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
	score = 0;
	speed = 0;
	serverData = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	centery = visibleSize.height / 2;
	centerx = visibleSize.width / 2;
	auto BG = Sprite::create("Background.jpg");
	BG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BG, -1);
    sprite = Sprite::create("Spinner.png");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(0.1f);
	
	auto scaleTo = ScaleTo::create(1.0f, 1.0f, 1.0f);
	sprite->runAction(scaleTo);
	this->addChild(sprite, 0);
#ifdef WIN32
	str = TEXT("Scene Started\n");
	WriteConsole(console, str, wcslen(str), &(DWORD)cw, NULL);
#elif
	CCLOG("Scene Started\n");
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
	return true;
}

void Spinner::TouchMoved (Touch* touch, Event* event) 
{
	Point p = Director::getInstance()->convertToGL(touch->getLocationInView());
	//auto rotateTo = RotateTo::create(1.0f, 20);
	//EaseIn  *actionIn = EaseIn::create(rotateTo, 1.0f);
	//sprite->runAction(rotateTo);
#ifdef WIN32
	_snprintf_s(buf, 300, "Touch move  %f,%f\n", p.x, p.y);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t * wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
	free(wcstring);
#elif
	CCLOG("Touch move  %f,%f\n", p.x, p.y);
#endif
}

void Spinner::TouchEnded (Touch* touch, Event* event) 
{
	last = Director::getInstance()->convertToGL(touch->getLocationInView());
	setSpeedAndDir();
	if (forward)
	{
		int ret = FileOperation::readFileValue("./serverData.dt", 10);
		if (ret != UNDEF)
		{
			speed += ret;
			serverData = ret;
		}
		//else err();
		if (speed > MAX_SPEED)
			speed = MAX_SPEED;
		else if (speed < MIN_SPEED)
			speed = MIN_SPEED;
		float nRot = MIN_SPEED / speed;
		float aRot = 580 * speed / MIN_SPEED;

		auto rotateBy = RotateBy::create(nRot, aRot);
		//rotateBy->setDuration(3.0f);
		//rotateBy->ActionInterval::initWithDuration(3.0f);
		EaseIn  *actionIn = EaseIn::create(rotateBy, 2.0f);
		actionIn->ActionInterval::initWithDuration(1.0f);
		//sprite->runAction(actionIn);
		EaseOut *actionOut = EaseOut::create(rotateBy, 2.0f);
		actionOut->ActionInterval::initWithDuration(1.0f);

		sequ = Sequence::create(actionIn, actionOut, NULL);
		sequ->ActionInterval::initWithDuration(5.0f);
		score += aRot;
		//if (score > LVL1)
		//	Spinner::runlvl2();
		sprite->runAction(sequ);
	}
}

void Spinner::TouchCancelled(Touch* touch, Event* event)
{
	
}

void Spinner::setSpeedAndDir()
{
	if ((first.x < centerx && first.y < centery && abs(first.x - last.x) < centerx / 3 && last.y - first.y > 0 && last.x < centerx) || // left botton
		(first.x < centerx && first.y > centery && abs(first.y - last.y) < centery / 3 && first.x - last.x < 0) || // left top
		(first.x > centerx && first.y > centery && abs(first.x - last.x) < centerx / 3 && first.y - last.y > 0) || // right top
		(first.x > centerx && first.y < centery && abs(first.y - last.y) < centery / 3 && first.x - last.x > 0)) // right bottom
	{
		speed = (first.y - last.y) + (first.x - last.x);
		if (speed < 0)
			speed *= -1;
		forward = true;
#ifdef WIN32
		_snprintf_s(buf, 300, "\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\nServer value %ld\n\n", \
			first.x, first.y, last.x, last.y, centerx, centery, speed, score, serverData);
		size_t newsize = strlen(buf) + 1;
		size_t convertedChars = 0;
		wchar_t* wcstring = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
		WriteConsole(console, wcstring, convertedChars, &(DWORD)cw, NULL);
		delete[] wcstring;
#elif
		CCLOG("\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\n Server value %ld\n\n", \
			first.x, first.y, last.x, last.y, centerx, centery, speed, score, serverData);
#endif
	}
	else
		forward = false;
}