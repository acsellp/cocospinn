#include "LuckyWheel.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1

HANDLE console2;
DWORD cw2;

Scene* LuckyWheel::createScene(HANDLE console)
{
	console2 = console;
	return LuckyWheel::create();
}

bool LuckyWheel::init()
{
	if (!Scene::init())
	{
		return false;
	}
	score = 0;
	speed = 0;
	serverData = 0;
	sequ = nullptr;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	centery = visibleSize.height / 2;
	centerx = visibleSize.width / 2;
	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	MenuItemFont* back = MenuItemFont::create("Back", CC_CALLBACK_1(LuckyWheel::menuCallBack, this));
	back->setPosition(40.0f, visibleSize.height - 20.0f);
	menu->addChild(back);
	this->addChild(menu);

	auto BG = Sprite::create("Background.jpg");
	BG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BG, -1);

	sprite = Sprite::create("Wheel.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size sz = sprite->getContentSize();
	
	auto pointer = Sprite::create("pointer.png");
	pointer->setRotation(180.0f);
	pointer->setScale(0.4f);
	pointer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + sz.height/1.8));
	this->addChild(pointer, 1);

	sprite->setScale(0.1f);

	auto scaleTo = ScaleTo::create(0.5f, 1.0f, 1.0f);
	sprite->runAction(scaleTo);
	this->addChild(sprite, 0);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(LuckyWheel::touchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LuckyWheel::touchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LuckyWheel::touchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(LuckyWheel::touchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sprite);
	auto rotateBy = RotateBy::create(0.4f, 720.0f);
	sprite->runAction(rotateBy);
	return true;
}

bool LuckyWheel::touchBegan(Touch* touch, Event* event)
{
	first = Director::getInstance()->convertToGL(touch->getLocationInView());
	return true;
}

void LuckyWheel::touchMoved(Touch* touch, Event* event)
{
	Point p = Director::getInstance()->convertToGL(touch->getLocationInView());
	//auto rotateTo = RotateTo::create(1.0f, 20);
	//EaseIn  *actionIn = EaseIn::create(rotateTo, 1.0f);
	//sprite->runAction(rotateTo);

}

void LuckyWheel::touchEnded(Touch* touch, Event* event)
{
	last = Director::getInstance()->convertToGL(touch->getLocationInView());
	setSpeedAndDir();
	if (forward)
	{
		if (speed > MAX_SPEED)
			speed = MAX_SPEED;
		else if (speed < MIN_SPEED)
			speed = MIN_SPEED;
		float nRot = MIN_SPEED / speed;
		float aRot = 300 * speed / MIN_SPEED;

		auto rotateBy = RotateBy::create(3, aRot/1.5);
		//rotateBy->setDuration(3.0f);
		//rotateBy->ActionInterval::initWithDuration(3.0f);
		EaseIn  *actionIn = EaseIn::create(rotateBy, 2.0f);
		//actionIn->ActionInterval::initWithDuration(1.0f);
		
		EaseOut *actionOut = EaseOut::create(rotateBy, 2.0f);
		//actionOut->ActionInterval::initWithDuration(1.0f);

		Vector<FiniteTimeAction *> actionVec;
		actionVec.insert(0, actionIn);
		actionVec.insert(1, actionOut);
		sequ = Sequence::create(actionVec);
		sprite->runAction(sequ);
		score += aRot;
#ifdef WIN32
		_snprintf_s(buf, 300, "\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\nServer value %ld\naRot,nRot  %lf,%lf\n\n", \
			first.x, first.y, last.x, last.y, centerx, centery, speed, score, serverData, aRot, nRot);
		size_t newsize = strlen(buf) + 1;
		size_t convertedChars = 0;
		wchar_t* wcstring = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
		WriteConsole(console2, wcstring, convertedChars, &(DWORD)cw2, NULL);
		delete[] wcstring;
#elif
		CCLOG("\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\n Server value %ld\nRot,nRot  %lf,%lf\n\n", \
			first.x, first.y, last.x, last.y, centerx, centery, speed, score, serverData, aRot, nRot);
#endif

	}
}

void LuckyWheel::touchCancelled(Touch* touch, Event* event)
{

}

void LuckyWheel::setSpeedAndDir()
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
	}
	else
		forward = false;
}

void LuckyWheel::menuCallBack(Ref* ref)
{
	Director::getInstance()->popScene();
}