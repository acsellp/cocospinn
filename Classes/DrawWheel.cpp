#include "DrawWheel.h"
#include "Api.h"

USING_NS_CC;

Layer* DrawWheel::createlayer()
{
	return DrawWheel::create();
}

bool DrawWheel::init()
{
	if (!Layer::init())
		return false;
	int i;
	DrawWheel::sectionNum = API::getWheelSections();
	
#if (COCOS2D_DEBUG)
	char buf[300];
	_snprintf_s(buf, 300, "\n\n Draw  [%d] Sections  \n\n", DrawWheel::sectionNum);
	API::debug(buf);
#endif
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
	Sprite* coin = Sprite::create("coin.png");
	coin->setPosition(Vec2(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y));
	coin->setScale(0.4f);
	coin->setRotation(-45.0f);
	this->addChild(coin, 10);

	i = 0;
	Vec2 pos;
	float radius = WHEEL_RADIUS;
	float grayRad = WHEEL_RADIUS * 0.6;
	float dec = 360.0f / DrawWheel::sectionNum;
	float angle = 360.0f;
	float textPos = angle / (DrawWheel::sectionNum * 2);
	centerx = visibleSize.width / 2 + visibleOrigin.x;
	centery = visibleSize.height / 2 + visibleOrigin.y;
	float textRotationAngle = 90 + textPos;
	float x, y, rad;

	while (i < DrawWheel::sectionNum)
	{
		DrawNode*  segm = DrawNode::create();
		rad = 2 * M_PI * angle / 360.0f;
		x = (visibleSize.width / 2) + WHEEL_RADIUS * cosf(rad);
		y = (visibleSize.height / 2) + WHEEL_RADIUS * sinf(rad);
		segm->drawSegment(Vec2(centerx, centery), Vec2(x, y), 2.0f, Color4F::WHITE);
		this->addChild(segm, 3);

		secvector.insert(i, DrawNode::create());
		graySec.insert(i, DrawNode::create());
		if (i == 0)
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F(182, 83, 162, 1.0f), i + 1); // green
		else if (i % 2 == 0)
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F(198, 198, 198, 1.0f), i + 1); // black
		else
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F(60, 175, 181, 1.0f), i + 1); // red
		drawSection(graySec.at(i), Vec2(centerx, centery), grayRad, angle, Color4F(157, 134, 136, 1.0f), i + 10000); // gray
		this->addChild(secvector.at(i), 0);
		this->addChild(graySec.at(i), 1);
		textVector.insert(i, LabelTTF::create(std::to_string(i + 1), "Arial", 22));
		textVector.at(i)->setPosition(Vec2(centerx + (radius - radius / 12) * cosf(6.28 * (angle - textPos) / 360.0f),
			centery + (radius - radius / 12) * sinf(6.28 * (angle - textPos) / 360.0f)));
		textVector.at(i)->setRotation(textRotationAngle);
		this->addChild(textVector.at(i), 1);
		angle -= dec;
		textRotationAngle += textPos * 2;
		pos = this->getChildByTag(i + 1)->getPosition();
		setSectionDelimiter(Vec2(centerx, centery), pos, i + 1);
		i++;
	}
	DrawWheel::drawCircles();
	return true;
}

void	DrawWheel::setSectionDelimiter(Vec2 p1, Vec2 p2, int section)
{
	float len = 0;
	if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y))
		len = fabs(p2.x - p1.x);
	else
		len = fabs(p2.y - p1.y);
	float dx = (p2.x - p1.x) / len;
	float dy = (p2.y - p1.y) / len;
	float x = p1.x + 0.5;
	float y = p1.y + 0.5;
	int i = 0;
	int tag_inc = 0;
	while (i < (int)len)
	{
		if (i % 4 == 0)
		{
			Sprite* sp = Sprite::create("1px.png");
			sp->setScale(0.0f);
			sp->setPosition(x, y);
			sp->setTag(section * 1000 + tag_inc++);
			this->addChild(sp);
		}
		x += dx;
		y += dy;
		i++;
	}
}

void DrawWheel::drawSection(DrawNode* node, Vec2 center, float radius, float angle, Color4F fillcol, int sections)
{
	std::vector<Point> circle;

	if (!node)
		return;
	auto step = 2 * M_PI * angle / 360.0f / 100;
	circle.emplace_back(center);
	for (int i = 0; i <= 100; i++)
	{
		auto radians = step * i;// +sectionAngle;
		auto x = center.x + radius * cosf(radians);
		auto y = center.y + radius * sinf(radians);
		circle.emplace_back(x, y);
		if (i == 100)
		{
			//DrawNode* mark_point = DrawNode::create();
			Sprite* mark_point = Sprite::create("1px.png");
			mark_point->setPosition(x, y);
			mark_point->setTag(sections);
			mark_point->setScale(0.0f);
			this->addChild(mark_point, 100);
		}
	}
	node->drawPolygon(circle.data(), circle.size(), fillcol, 0, fillcol);
}

void	DrawWheel::drawCircles()
{
	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS, Color4F::WHITE, 3);

	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS * 0.6, Color4F::WHITE, 2);

	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS * 0.6 + 15, Color4F::WHITE, 2);
	
	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS + 3, Color4F(114, 93, 94, 1), 10);
	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS + 13, Color4F(98, 75, 76, 1), 8);

	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS + 21, Color4F::WHITE, 3);
	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS + 24, Color4F(143, 127, 129, 1), 8);

	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS + 32, Color4F(157, 134, 136, 1), 5);
	DrawWheel::drawCircles(Vec2(centerx, centery), WHEEL_RADIUS + 37, Color4F(98, 75, 76, 1), 8);
}


void	DrawWheel::drawCircles(Vec2 center, float base_radius, Color4F color, uint8_t rep)
{
	uint8_t i = 0;

	while (i < rep)
	{
		DrawNode* circle = DrawNode::create();
		circle->drawCircle(center, base_radius + i, 360.0f, 200, false, color);
		this->addChild(circle, 20);
		i++;
	}
}

void	DrawWheel::update(float t)
{

}