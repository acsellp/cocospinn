#include "SpinnerScene.h"
#include "SimpleAudioEngine.h"
#include "Api.h"

USING_NS_CC;

Scene* Spinner::createScene()
{
	return Spinner::create();
}

bool Spinner::init()
{
    if (!Scene::init())
        return false;

	score = 0;
	speed = 0;
	serverData = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	centery = visibleSize.height / 2;
	centerx = visibleSize.width / 2;
	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	MenuItemFont* back = MenuItemFont::create("Back", CC_CALLBACK_1(Spinner::menuCallBack, this));
	back->setPosition(40.0f, visibleSize.height - 20.0f);
	menu->addChild(back);
	this->addChild(menu);

	auto bg = Sprite::create("Background.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, -1);

    sprite = Sprite::create("Spinner.png");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	
	//sprite->setScale(0.1f);
	//auto scaleTo = ScaleTo::create(0.5f, 1.0f, 1.0f);
	//sprite->runAction(scaleTo);
	this->addChild(sprite, 0);

	auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Spinner::TouchBegan, this);	
    touchListener->onTouchMoved = CC_CALLBACK_2(Spinner::TouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Spinner::TouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Spinner::TouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sprite);
	auto rotateBy = RotateBy::create(0.4f, 720.0f);
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

}

void Spinner::TouchEnded (Touch* touch, Event* event) 
{
	last = Director::getInstance()->convertToGL(touch->getLocationInView());
	setSpeedAndDir();
	if (forward)
	{
		if (speed > MAX_SPEED)
			speed = MAX_SPEED;
		else if (speed < MIN_SPEED)
			speed = MIN_SPEED;
		nRot = MIN_SPEED / speed;
		aRot = 360.0f * speed / MIN_SPEED;

		auto rotateBy = RotateBy::create(nRot/2, aRot/2);
		//rotateBy->setDuration(3.0f);
		//rotateBy->ActionInterval::initWithDuration(3.0f);

		EaseIn  *actionIn = EaseIn::create(rotateBy, 1.0f);
		//actionIn->ActionInterval::initWithDuration(1.0f);
		//sprite->runAction(actionIn);

		EaseOut *actionOut = EaseOut::create(rotateBy, 1.0f);
		//actionOut->ActionInterval::initWithDuration(1.0f);

		
		Vector<FiniteTimeAction *> actionVector;
		actionVector.insert(0, actionIn);
		actionVector.insert(1, actionOut);
		sequ = Sequence::create(actionVector);
		//sequ->ActionInterval::initWithDuration(5.0f);
		score += aRot;

		sprite->runAction(sequ);
#if (COCOS2D_DEBUG)
		char buf[300];
		_snprintf_s(buf, 300, "\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\nServer value %ld\naRot,nRot  %lf,%lf\n\n", \
			first.x, first.y, last.x, last.y, centerx, centery, speed, score, serverData, aRot, nRot);
		API::debug(buf);
#endif
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
	}
	else
		forward = false;
}

void Spinner::menuCallBack(Ref* ref)
{
	Director::getInstance()->popScene();
}

void Spinner::update(float dt)
{
	//API::updateSpinnerScore();
}