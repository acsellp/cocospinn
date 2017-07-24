#pragma once

#include "cocos2d.h"

typedef struct	wheelSections_s
{
	float		infAngle;
	float		supAngle;
	char		sectionParam[50];
}				wheelSection_t;

class LuckyWheel : public cocos2d::Scene
{
public:
	CREATE_FUNC(LuckyWheel);
	static				cocos2d::Scene* createScene(void);
	virtual bool		init(void);
	void				setSpeedAndDir(void);
	bool				touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void				touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void				touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void				touchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void				menuCallBack(Ref* ref);
	uint8_t				getSectionIndex(float angle);
	virtual void		update(float dt);
	void				updateCallBack(void);
	void				move_node();
	void				bounce(cocos2d::Vec2 dest);
	std::vector<cocos2d::Vec2>	getSectionDelimiterVector(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	bool				checkIntersection(std::vector<cocos2d::Vec2> vect, cocos2d::Vec2 ball_pos, int cadran);
	int					getSectionDelims(int closest_section, cocos2d::Vec2 ball_pos);
	bool				checkIntersection_frwd(std::vector<cocos2d::Vec2> vect, cocos2d::Vec2 ball_pos, int cadran);
	bool				checkIntersection_bkwd(std::vector<cocos2d::Vec2> vect, cocos2d::Vec2 ball_pos, int cadran);
	void				putpos(void);
	~LuckyWheel();

private:
	cocos2d::Point		first;
	cocos2d::Point		last;
	float				centerx;
	float				centery;
	float				speed;
	float				aRot;
	float				nRot;
	float				step;
	int					curr_pos_per_rot;
	float				index_coef;
	float				rot_coef;
	float				moving_ball_radius;
	bool				forward;
	int					sections;
	int					pos_per_rot;
	int					final_section;
	int					prev_sec;
	int					next_sec;
	int					curr_touch_sec;
	uint32_t			score;
	wheelSection_t*		sec;



	char buf[300];
};
