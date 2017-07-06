#ifndef __SPINNER_SCENE_H__
#define __SPINNER_SCENE_H__

#include "cocos2d.h"
#define COCOS_DEBUG 1
#define MAX_SPEED 100
#define MIN_SPEED 10

class Spinner : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(HANDLE console);
    virtual bool init();
	void setSpeed(void);
    CREATE_FUNC(Spinner);
    bool TouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void TouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void TouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	cocos2d::Sprite* sprite;
	cocos2d::Point first;
	cocos2d::Point last;
	float originx;
	float originy;
	float speed;
	char buf[300];
};

#endif // __HELLOWORLD_SCENE_H__
