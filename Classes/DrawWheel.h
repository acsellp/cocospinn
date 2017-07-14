#ifndef __DRAWWHEEL_H__
#define __DRAWWHEEL_H__

#include "cocos2d.h"
class DrawWheel: public cocos2d::Layer
{
public:
	CREATE_FUNC(DrawWheel);
	virtual bool			init();
	void					drawSection(cocos2d::DrawNode* node, cocos2d::Vec2 origin, float radius, float degree, cocos2d::Color4F fillcol);
	static cocos2d::Layer*	createlayer();
private:
	cocos2d::Vector<cocos2d::DrawNode*> secvector;
	cocos2d::Vector<cocos2d::LabelTTF*> textVector;
	int sectionNum;
};
#endif