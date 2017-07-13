#include "LuckyWheel.h"
#include "SimpleAudioEngine.h"
#include "DrawWheel.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1

HANDLE console2;
DWORD cw2;
int sections;

Scene* LuckyWheel::createScene(HANDLE console, int sec)
{
	console2 = console;
	sections = sec;
	return LuckyWheel::create();
}

bool LuckyWheel::init()
{
	if (!Scene::init())
		return false;

	score = 0;
	speed = 0;
	serverData = 0;
	sec = NULL;

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
	

	//sprite = Sprite::create("Wheel.png");
	//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Layer* layer = DrawWheel::createlayer(console2, sections);
	Size sz = layer->getContentSize();

	auto pointer = Sprite::create("pointer.png");
	pointer->setRotation(180.0f);
	pointer->setScale(0.4f);
	pointer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + sz.height/2.35));
	this->addChild(pointer, 1);

	//layer->setScale(0.1f);
	//auto scaleTo = ScaleTo::create(0.5f, 1.0f, 1.0f);
	//layer->runAction(scaleTo);
	layer->setTag(666);
	this->addChild(layer, 0);

	//layer->scheduleUpdate(); // UPDATE

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(LuckyWheel::touchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LuckyWheel::touchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LuckyWheel::touchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(LuckyWheel::touchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, layer);
	//auto rotateBy = RotateBy::create(0.4f, 720.0f);
	//layer->runAction(rotateBy);
	
	LuckyWheel::initSections();
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

		float positionAfterRot;
		if (aRot <= 360.0)
			positionAfterRot = aRot;
		else
			positionAfterRot = (int)aRot % 360;

		//TODO update position
		uint8_t index = 6;// LuckyWheel::getSectionIndex(positionAfterRot);
		//LuckyWheel::updateSectionPosition(positionAfterRot);
		auto rotateBy = RotateBy::create(2, aRot / 2);
		//TODO animate
		
		EaseIn  *actionIn = EaseIn::create(rotateBy, 2.0f);
		EaseOut *actionOut = EaseOut::create(rotateBy, 2.0f);
		auto* remove = RemoveSelf::create(true);
		auto callback = CallFunc::create(this, callfunc_selector(LuckyWheel::updateCallBack));
		auto delay = DelayTime::create(4);

		Vector<FiniteTimeAction *> actionVec;
		actionVec.insert(0, actionIn);
		actionVec.insert(1, actionOut);
		actionVec.insert(2, delay);
		actionVec.insert(3, remove);
		actionVec.insert(4, callback);

		Sequence *sequ = Sequence::create(actionVec);
		sequ->setTag(6);

		if (this->getChildByTag(666) != nullptr)
			this->getChildByTag(666)->runAction(sequ);
		else
		{
			// todo node check
		}
		score += aRot;

		if (sections < 20)
			sections += 2;
		else
			sections = 5;

#ifdef WIN32
		char buf[300];
		_snprintf_s(buf, 300, "\n\n\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\nServer value %ld\naRot,nRot  %lf,%lf\nSection index %d\n\n", \
			first.x, first.y, last.x, last.y, centerx, centery, speed, score, serverData, aRot, nRot, index);
		size_t newsize = strlen(buf) + 1;
		size_t convertedChars = 0;
		wchar_t* wcstring = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
		WriteConsole(console2, wcstring, convertedChars, &(DWORD)cw2, NULL);
		delete[] wcstring;
#else
		CCLOG("\n\n\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\n Server value %ld\nRot,nRot  %lf,%lf\n\n", \
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

void LuckyWheel::updateSectionPosition(float newPositin)
{
	int i = 0;

	while (i < sections)
	{
		float bef1 = sec[i].infAngle, bef2 = sec[i].supAngle;
		sec[i].infAngle -= newPositin;
		if (sec[i].infAngle < 0)
			sec[i].infAngle *= -1;
		sec[i].supAngle -= newPositin;
		if (sec[i].supAngle < 0)
			sec[i].supAngle *= -1;
/*
#ifdef WIN32
		_snprintf_s(buf, 300, "\n   %s  before %lf,%lf after %lf,%lf\n", sec[i].sectionParam, bef1, bef2, sec[i].infAngle, sec[i].supAngle);
		size_t newsize = strlen(buf) + 1;
		size_t convertedChars = 0;
		wchar_t* wcstring = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
		WriteConsole(console2, wcstring, convertedChars, &(DWORD)cw2, NULL);
		delete[] wcstring;
#else
		CCLOG("\n   %s  before %lf,%lf after %lf,%lf\n", sec[i].sectionParam, bef1, bef2, sec[i].infAngle, sec[i].supAngle);
#endif
*/
		i++;
	}

}

uint8_t LuckyWheel::getSectionIndex(float angle)
{
	uint8_t i = 0;
	while (i < sections)
	{
		if (sec[i].infAngle < angle && sec[i].supAngle > angle)
			return i;
		i++;
	}
	return 255;
}

void LuckyWheel::initSections()
{
	//todo vectors push pop...
	if (sec != NULL)
		delete[] sec;
	sec = new wheelSection_t[sections];

	sec[0].infAngle = 0.0f;
	sec[0].supAngle = 360.0f / sections;
	strcpy(sec[0].sectionParam, "Mr.Wong");

	sec[1].infAngle = 360.0f / sections;
	sec[1].supAngle = 360.0f / sections * 2;
	strcpy(sec[1].sectionParam, "Mr.Chan");

	sec[2].infAngle = 360.0f / sections * 2;
	sec[2].supAngle = 360.0f / sections * 3;
	strcpy(sec[2].sectionParam, "Miss Li");

	sec[3].infAngle = 360.0f / sections * 3;
	sec[3].supAngle = 360.0f / sections * 4;
	strcpy(sec[3].sectionParam, "Mr.Lee");

	sec[4].infAngle = 360.0f / sections * 4;
	sec[4].supAngle = 360.0f;
	strcpy(sec[4].sectionParam, "Mr.Kwok");
}

void  LuckyWheel::update(float tm)
{
	if (this->getChildByTag(666) != nullptr)
	{

	}
}

LuckyWheel::~LuckyWheel()
{
	if (sec != NULL)
		delete[] sec;
}

void LuckyWheel::updateCallBack()
{
	auto wheel = LuckyWheel::createScene(console2, sections);
	Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5f, wheel));
}