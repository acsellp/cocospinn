#include "WheelOfFortune.h"
#include "DrawWheel.h"
#include "Api.h"

USING_NS_CC;

Scene*	WheelOfFortune::createScene()
{
	return WheelOfFortune::create();
}

bool	WheelOfFortune::init()
{
	if (!Scene::init())
		return false;

	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float centery = visibleSize.height / 2;
	float centerx = visibleSize.width / 2;

	Sprite* bk = Sprite::create("background.png");
	bk->setPosition(Vec2(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y));
	this->addChild(bk);

	//Sprite* hide_half = Sprite::create("background.png");
	//hide_half->setAnchorPoint(Vec2(0.5, 0));
	//hide_half->setPosition(Vec2(centerx, centery));
	//this->addChild(hide_half, 1);

	//Layer* layer = DrawWheel::create();
	//this->addChild(layer);
	WheelOfFortune::initSections();


	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	MenuItemFont* back = MenuItemFont::create("Back", CC_CALLBACK_1(WheelOfFortune::menuCallBack, this));
	back->setPosition(40.0f, visibleSize.height - 20.0f);
	menu->addChild(back);
	this->addChild(menu, 2);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WheelOfFortune::touchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WheelOfFortune::touchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WheelOfFortune::touchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	return true;
}

bool	WheelOfFortune::touchBegan(Touch* touch, Event* event)
{
	API::debug("touch began\n\n");
	first = Director::getInstance()->convertToGL(touch->getLocationInView());
	return true;
}

void	WheelOfFortune::touchMoved(Touch* touch, Event* event)
{

}


void	WheelOfFortune::touchEnded(Touch* touch, Event* event)
{
	last = Director::getInstance()->convertToGL(touch->getLocationInView());

	API::debug("touch eneded\n\n");
}

void	WheelOfFortune::initSections()
{
	Vector<DrawNode*> secvector;
	Vector<LabelTTF*> textVector;
	uint8_t i = 0;
	float radius = 120;
	float dec = 360.0f / 12;
	float angle = 0;
	float textPos = angle / 12 * 2;
	float centerx = visibleSize.width / 2;
	float centery = visibleSize.height / 2;
	float textRotationAngle = 90 + textPos;

	while (i < 12)
	{
		secvector.insert(i, DrawNode::create());
		if (i % 2 == 0)
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F(198, 198, 198, 1.0f), i + 1);
		else
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F(60, 175, 181, 1.0f), i + 1);
		this->addChild(secvector.at(i), 0);
		textVector.insert(i, LabelTTF::create(std::to_string(i + 1), "Arial", 22));
		textVector.at(i)->setPosition(Vec2(centerx + (radius - radius / 12) * cosf(6.28 * (angle - textPos) / 360.0f),
			centery + (radius - radius / 12) * sinf(6.28 * (angle - textPos) / 360.0f)));
		textVector.at(i)->setRotation(textRotationAngle);
		this->addChild(textVector.at(i), 1);
		angle -= 15;
		textRotationAngle += textPos * 2;
		i++;
	}
}

void	WheelOfFortune::drawSection(DrawNode* node, Vec2 center, float radius, float angle, Color4F fillcol, int sections)
{
	std::vector<Point> circle;

	if (!node)
		return;
	auto step = 2 * M_PI * angle / 360.0f / 100;
	circle.emplace_back(center);
	for (int i = 0; i <= 100; i++)
	{
		auto radians = step * i;
		auto x = center.y + radius * cosf(radians);
		auto y = center.y + radius * sinf(radians);
		circle.emplace_back(x, y);
		if (i == 100)
		{
			Sprite* mark_point = Sprite::create("white_ball.png");
			mark_point->setPosition(x, y);
			mark_point->setTag(sections);
			mark_point->setScale(0.0f);
			this->addChild(mark_point, 1000);
		}
	}
	node->drawPolygon(circle.data(), circle.size(), fillcol, 0, fillcol);
}

void	WheelOfFortune::menuCallBack(Ref* ref)
{
	Director::getInstance()->popScene();
}