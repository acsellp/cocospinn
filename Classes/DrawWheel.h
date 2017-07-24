#pragma once

#include "cocos2d.h"
class DrawWheel: public cocos2d::Layer
{
public:
	CREATE_FUNC(DrawWheel);
	virtual bool			init();
	void					drawSection(cocos2d::DrawNode* node, cocos2d::Vec2 origin, float radius, float degree, cocos2d::Color4F fillcol, int sects);
	static cocos2d::Layer*	createlayer();
	virtual void			update(float t);
	void					drawCircles();
	void					line(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	void					setSectionDelimiter(cocos2d::Vec2 p1, cocos2d::Vec2 p2, int sections);
	void					drawCircles(cocos2d::Vec2 center, float base_radius, cocos2d::Color4F color, uint8_t rep);

private:
	cocos2d::Vector<cocos2d::DrawNode* > secvector;
	cocos2d::Vector<cocos2d::LabelTTF* > textVector;
	cocos2d::Vector<cocos2d::DrawNode* > graySec;
	int		sectionNum;
	float	centerx;
	float	centery;
};