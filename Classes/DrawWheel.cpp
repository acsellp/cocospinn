#include "DrawWheel.h"

USING_NS_CC;

HANDLE	console4;
int		sectionNum;
DWORD	cw4;

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
	int i;
#ifdef WIN32
	char buf[300];
	_snprintf_s(buf, 300, "\n\n\n Draw  [%d] Sections  \n\n", sectionNum);
	size_t newsize = strlen(buf) + 1;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring, newsize, buf, _TRUNCATE);
	WriteConsole(console4, wcstring, convertedChars, &(DWORD)cw4, NULL);
	delete[] wcstring;
#else
	CCLOG("\n\n\n Draw [%d] Sections\n\n", sectionNum);
#endif
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	i = 0;
	//sectionNum = 12;

	float radius = 120.0f;
	float dec = 360.0f / sectionNum;
	float angle = 360.0f;
	float textPos = angle / (sectionNum * 2);
	float centerx = visibleSize.width / 2 + origin.x;
	float centery = visibleSize.height / 2 + origin.y;
	float textRotationAngle = 90 + textPos;
	// TODO update color
	while (i < sectionNum)
	{
		secvector.insert(i, DrawNode::create());
		if (i == 0)
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F::GREEN);
		else if (i % 2 == 0)
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F::BLACK);
		else
			drawSection(secvector.at(i), Vec2(centerx, centery), radius, angle, Color4F::RED);
		this->addChild(secvector.at(i), 0);

		textVector.insert(i, LabelTTF::create(std::to_string(i + 1), "Arial", 22));
		textVector.at(i)->setPosition(Vec2(centerx + (radius - radius / 12) * cosf(6.28 * (angle - textPos) / 360.0f) ,
			centery + (radius - radius / 12) * sinf(6.28 * (angle - textPos) / 360.0f)));
		textVector.at(i)->setRotation(textRotationAngle);
		this->addChild(textVector.at(i), 1);
		
		angle -= dec;
		textRotationAngle += textPos * 2;
		i++;
	}
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
