#include "DrawWheel.h"

USING_NS_CC;

HANDLE console4;
int sectionNum;

Layer* DrawWheel::createlayer(HANDLE cons, int sects)
{
	console4 = cons;
	sectionNum = sects;
	return DrawWheel::create();
}

bool DrawWheel::init()
{
	if (!Layer::init())
		return false;
#ifdef WIN32
	int i;
	char buf[300];
	_snprintf_s(buf, 300, "\n\n\n Draw  [%d] Sections  \n\n", sectionNum);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console4, wcstring, convertedChars, &(DWORD)DrawWheel::cw4, NULL);
	delete[] wcstring;
#else
	CCLOG("\n\n\n Draw [%d] Sections\n\n", sectionNum);
#endif
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	i = 0;
	sectionNum = 13;
	float dec = 360.0f / sectionNum;
	float angle = 360.0f;
	while (i < sectionNum)
	{
		secvector.insert(i, DrawNode::create());
		if (i % 3 == 0)
			drawSection(secvector.at(i), Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y), 120.0f, angle, Color4F::BLUE);
		else if (i % 2 == 0)
			drawSection(secvector.at(i), Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y), 120.0f, angle, Color4F::GREEN);
		else
			drawSection(secvector.at(i), Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y), 120.0f, angle, Color4F::RED);
		this->addChild(secvector.at(i));
		angle -= dec;
		i++;
	}

	//auto bg = Sprite::create("Background.jpg");
	//bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//this->addChild(bg, -1);

	return true;
}

void DrawWheel::drawSection(DrawNode* node, Vec2 center, float radius, float angle, Color4F fillcol)
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
	}
	node->drawPolygon(circle.data(), circle.size(), fillcol, 0, fillcol);
}
