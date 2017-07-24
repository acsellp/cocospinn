#include "LuckyWheel.h"
#include "SimpleAudioEngine.h"
#include "DrawWheel.h"
#include "Api.h"

USING_NS_CC;

Scene*	LuckyWheel::createScene()
{
	return LuckyWheel::create();
}

bool	LuckyWheel::init()
{
	if (!Scene::init())
		return false;

	sections = API::getWheelSections();
	if (sections < 3)
		return false;
	score = 0;
	final_section = 65535;
	speed = 0;
	pos_per_rot = 0;
	sec = NULL;
	index_coef = 0.9f;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	centery = visibleSize.height / 2;
	centerx = visibleSize.width / 2;

	curr_pos_per_rot = 20; //speed dependent
	step = 2 * M_PI / curr_pos_per_rot;
	rot_coef = 1.2f; //speed dependdent
	moving_ball_radius = BALL_MOVE_RADIUS;
	
	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	MenuItemFont* back = MenuItemFont::create("Back", CC_CALLBACK_1(LuckyWheel::menuCallBack, this));
	back->setPosition(40.0f, visibleSize.height - 20.0f);
	menu->addChild(back);
	this->addChild(menu);

	Sprite* BG = Sprite::create("background.png");
	BG->setPosition(Vec2(visibleSize.width / 2 + visibleOrigin.x, visibleSize.height / 2 + visibleOrigin.y));
	this->addChild(BG, -1);
	
	Layer* layer = DrawWheel::createlayer();
	//layer->setPosition(Vec2(centerx ,  centery ));
	this->scheduleUpdate();
	layer->setTag(WHEEL_TAG);
	this->addChild(layer, 0);

	Sprite* ball = Sprite::create("white_ball.png");
	ball->setPosition(Vec2(centerx, centery + BALL_MOVE_RADIUS));
	ball->setScale(0.1f);
	ball->setTag(BALL_TAG);
	ball->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(ball, 2);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(LuckyWheel::touchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LuckyWheel::touchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LuckyWheel::touchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(LuckyWheel::touchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, layer);

	return true;
}

bool	LuckyWheel::touchBegan(Touch* touch, Event* event)
{
	first = Director::getInstance()->convertToGL(touch->getLocationInView());
	return true;
}

void	LuckyWheel::touchMoved(Touch* touch, Event* event)
{
	Point p = Director::getInstance()->convertToGL(touch->getLocationInView());
}

void	LuckyWheel::touchEnded(Touch* touch, Event* event)
{
	last = Director::getInstance()->convertToGL(touch->getLocationInView());
	setSpeedAndDir();

	if (forward && this->getChildByTag(WHEEL_TAG)->getActionByTag(WHEEL_SEQ_TAG) == nullptr)
	{
		if (speed > MAX_SPEED)
			speed = MAX_SPEED;
		else if (speed < MIN_SPEED)
			speed = MIN_SPEED;
		float nRot =  MAX_SPEED / speed;
		float aRot = 300 * speed / MAX_SPEED;

		float positionAfterRot;
		if (aRot <= 360.0)
			positionAfterRot = aRot;
		else
			positionAfterRot = (int)aRot % 360;

		// TODO update position

		auto rotateBy = RotateBy::create(2.0, 360);
		auto copy = rotateBy->clone();
		copy->setDuration(1.0f);

		//TODO animate
		EaseIn  *actionIn = EaseIn::create(rotateBy, 2.0f);
		EaseOut *actionOut = EaseOut::create(rotateBy, 2.0f);

		auto* remove = RemoveSelf::create(true);
		auto callbackUpdate = CallFunc::create(this, callfunc_selector(LuckyWheel::updateCallBack));
		auto delay = DelayTime::create(4);

		Vector<FiniteTimeAction *> actionVec;
		actionVec.insert(0, actionIn);
		// section number

		uint16_t i = 1;
		float	duration = 1.0f;
		float	angle = 100.0f;
		int		dur = 60;
		
		while (i < 40)
		{
			auto rot = RotateBy::create(duration, angle);
			actionVec.insert(i, rot);
			duration -= duration / 60;
			angle -= angle / 10;
			if (angle < 10)
				break;
			i++;
		}

		actionVec.insert(i++, delay);
		actionVec.insert(i++, remove);
		actionVec.insert(i++, callbackUpdate);
		Sequence *sequ = Sequence::create(actionVec);
		//actionIn->setTag(WHEEL_SEQ_TAG);
		sequ->setTag(WHEEL_SEQ_TAG);
		
		//return;
		if (this->getChildByTag(WHEEL_TAG) != nullptr)
			this->getChildByTag(WHEEL_TAG)->runAction(sequ);
		else
		{
#if (COCOS2D_DEBUG)
			API::debug("\n Wheel tag error\n");
#endif
			// todo node check
		}
		score += aRot;
#if (COCOS2D_DEBUG)
		char buf[300];
		_snprintf_s(buf, 300, "\n\n\n   Right bottom\nFirst: %f,%f\nLast: %f,%f\nOrigin: %f,%f\nSpeed: %f\nScore: %ld\naRot,nRot  %lf,%lf\n\n", \
			first.x, first.y, last.x, last.y, centerx, centery, speed, score, aRot, nRot);
		API::debug(buf);
#endif

	}
}

void	LuckyWheel::touchCancelled(Touch* touch, Event* event)
{

}

void	LuckyWheel::setSpeedAndDir()
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

void	LuckyWheel::menuCallBack(Ref* ref)
{
	Director::getInstance()->popScene();
}

uint8_t	LuckyWheel::getSectionIndex(float angle)
{
	uint8_t i = 0;
	while (i < LuckyWheel::sections)
	{
		if (sec[i].infAngle < angle && sec[i].supAngle > angle)
			return i;
		i++;
	}
	return 255;
}

void	LuckyWheel::update(float tm)
{
	if (this->getChildByTag(BALL_TAG) != nullptr && this->getChildByTag(WHEEL_TAG) != nullptr && \
		this->getChildByTag(WHEEL_TAG)->getActionByTag(WHEEL_SEQ_TAG) != nullptr)
	{
		Vec2 ball_pos = this->getChildByTag(BALL_TAG)->getPosition();
		int i = 1;
		float min_diff = 65535;
		int	closest_section = 0;
		Node* node = this->getChildByTag(WHEEL_TAG);
		if (node != nullptr)
		{
			while (i <= sections)
			{
				if (node->getChildByTag(i) != nullptr)
				{
					Vec2 sec_pos = node->getChildByTag(i)->getPosition();
					float diff = fabs(sec_pos.x - ball_pos.x) + fabs(sec_pos.y - ball_pos.y);
					if (diff < min_diff)
					{
						closest_section = i;
						min_diff = diff;
					}
				}
				i++;
			}
		}
		// intersection
		if (min_diff < 20)
		{
			Vec2 sec_pos_beg = node->getChildByTag(closest_section)->getPosition();
			Vec2 sec_pos_end;
			std::vector<Vec2> sec_begin;
			std::vector<Vec2> sec_end;
			int	sec_index_end;
		
			if (ball_pos.x < centerx && ball_pos.y < centery) // bottom left iii
			{
				if (sec_pos_beg.x - ball_pos.x <= -5 && sec_pos_beg.y - ball_pos.y <= -5)
				{
					sec_index_end = LuckyWheel::getSectionDelims(closest_section, ball_pos);
					if (sec_index_end == -1)
					{
						API::debug("\nsec_end_n  neg\n");
						return;
					}

					if (sec_index_end > closest_section)
					{
						prev_sec = closest_section;
						next_sec = sec_index_end;
					}
					else
					{
						prev_sec = sec_index_end;
						next_sec = closest_section;
					}
					API::debug("bottom left\n\n");
					char buf[30];
					_snprintf_s(buf, 30, "[%d-%d]  diff %lf\n", closest_section, sec_index_end, min_diff);
					API::debug(buf);
					final_section = closest_section;
					curr_touch_sec = prev_sec;

					LuckyWheel::move_node();
					Vec2 curr_pos = this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->getPosition();
					//LuckyWheel::bounce(Vec2(curr_pos.x - 10, curr_pos.y + 4));
				}
			}
			else if (ball_pos.x < centerx && ball_pos.y > centery) // top left ii
			{
				if (sec_pos_beg.x - ball_pos.x <= -5 && sec_pos_beg.y - ball_pos.y <= -5)
				{
					sec_index_end = LuckyWheel::getSectionDelims(closest_section, ball_pos);
					if (sec_index_end == -1)
					{
						API::debug("\nsec_end_n  neg\n");
						return;
					}

					if (sec_index_end > closest_section)
					{
						prev_sec = closest_section;
						next_sec = sec_index_end;
					}
					else
					{
						prev_sec = sec_index_end;
						next_sec = closest_section;
					}
					API::debug("top left\n");
					char buf[30];
					_snprintf_s(buf, 30, "[%d-%d]  diff %lf\n", closest_section, sec_index_end, min_diff);
					API::debug(buf);
					final_section = closest_section;
					curr_touch_sec = prev_sec;

					LuckyWheel::move_node();
					Vec2 curr_pos = this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->getPosition();
					//LuckyWheel::bounce(Vec2(curr_pos.x + 40, curr_pos.y + 20));
				}
			}
			else if (ball_pos.x > centerx && ball_pos.y < centery) // bottom right iv
			{
				if (ball_pos.x - sec_pos_beg.x <= -5 && sec_pos_beg.y - ball_pos.y <= -5)
				{
					sec_index_end = LuckyWheel::getSectionDelims(closest_section, ball_pos);
					if (sec_index_end == -1)
					{
						API::debug("\nsec_end_n  neg\n");
						return;
					}

					if (sec_index_end > closest_section)
					{
						prev_sec = closest_section;
						next_sec = sec_index_end;
					}
					else
					{
						prev_sec = sec_index_end;
						next_sec = closest_section;
					}
					API::debug("bottom right\n");
					char buf[30];
					_snprintf_s(buf, 30, "[%d-%d]  diff %lf\n", closest_section, sec_index_end, min_diff);
					API::debug(buf);

					final_section = closest_section;
					curr_touch_sec = prev_sec;

					LuckyWheel::move_node();
					Vec2 curr_pos = this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->getPosition();
					//LuckyWheel::bounce(Vec2(curr_pos.x + 10, curr_pos.y + 40));
				}
			}
			else if (ball_pos.x > centerx && ball_pos.y > centery) // top right i
			{
				if (ball_pos.x - sec_pos_beg.x <= -5 && ball_pos.y - sec_pos_beg.y <= -5)
				{
					sec_index_end = LuckyWheel::getSectionDelims(closest_section, ball_pos);
					if (sec_index_end == -1)
					{
						API::debug("\nsec_end_n  neg\n");
						return;
					}

					API::debug("top right\n\n");
					char buf[30];
					_snprintf_s(buf, 30, "[%d-%d]  diff %lf\n", closest_section, sec_index_end, min_diff);
					API::debug(buf);
					/*
					if (sec_index_end < closest_section)
					{
						if (sec_index_end < LuckyWheel::sections)
							sec_index_end = closest_section + 1;
						else
							sec_index_end = 1;
					}
					if (sec_index_end == closest_section)
						sec_index_end++;
					next_sec = sec_index_end;
					prev_sec = closest_section;
					*/
					if (sec_index_end > closest_section)
					{
						prev_sec = closest_section;
						next_sec = sec_index_end;
					}
					else
					{
						prev_sec = sec_index_end;
						next_sec = closest_section;
					}
					final_section = closest_section;
					curr_touch_sec = prev_sec;
					
					LuckyWheel::move_node();
					Vec2 curr_pos = this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->getPosition();
					//LuckyWheel::bounce(Vec2(curr_pos.x - 10, curr_pos.y - 15));
				}
			}
		}
		// update position
		if (pos_per_rot < curr_pos_per_rot)
			pos_per_rot++;
		else if (pos_per_rot == curr_pos_per_rot)
		{
			curr_pos_per_rot *= rot_coef;
			rot_coef += 0.2f;
			step = 2 * M_PI / curr_pos_per_rot;
			pos_per_rot = 1;
		}
		if (rot_coef > 2.2f)      // slow radius decrement
			moving_ball_radius -= moving_ball_radius / 8 / curr_pos_per_rot;
		float rad = step * pos_per_rot;
		float x = centerx + moving_ball_radius * sinf(rad);
		float y = centery + moving_ball_radius * cosf(rad);
		if (this->getChildByTag(BALL_TAG) != nullptr)
			this->getChildByTag(BALL_TAG)->setPosition(Vec2(x, y));
	}
	else if (this->getChildByTag(WHEEL_TAG) != nullptr && this->getChildByTag(WHEEL_TAG)->getActionByTag(WHEEL_SEQ_TAG) != nullptr)
	{
		if (this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG) == nullptr || \
			this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->getActionByTag(BOUNCE) != nullptr)
		{
			API::debug("__410 \n");
			return;
		}
		if (index_coef > 0.6f)
		{
			if (this->getChildByTag(WHEEL_TAG)->getChildByTag(curr_touch_sec * 1000) == nullptr)
			{
				this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->setTag(0);
				API::debug("\n __ endpoint error\n\n");
				return;
			}
			int index = 0;
			while (this->getChildByTag(WHEEL_TAG)->getChildByTag(curr_touch_sec * 1000 + index) != nullptr)
				index++;
			if (index < 3)
			{
				this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->setTag(0);
				API::debug("\nendpoint error\n\n");
				return;
			}
			Vec2 sec_pos_end = this->getChildByTag(WHEEL_TAG)->getChildByTag(curr_touch_sec * 1000 + (int)(index * index_coef))->getPosition();
			LuckyWheel::fixTouch(&sec_pos_end); // decrease ball radius
			auto move = MoveTo::create(0.9f + 1 - index_coef, sec_pos_end);
			move->setTag(BOUNCE);
			index_coef -= 0.1f;
			if (curr_touch_sec == next_sec)
				curr_touch_sec = prev_sec;
			else
				curr_touch_sec = next_sec;
			this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->runAction(move);


			char buf[100];
			_snprintf_s(buf, 40, "\n next %d  prev %d curr %d\n\n", next_sec, prev_sec, curr_touch_sec);
			API::debug(buf);		
		}
		else if (index_coef == 0.6f)
		{



		}
	}
}

LuckyWheel::~LuckyWheel()
{
	if (sec != NULL)
		delete[] sec;
}

void	LuckyWheel::updateCallBack()
{
	if (LuckyWheel::sections < 20)
	{
		LuckyWheel::sections += 2;
		API::updateWheelSections(LuckyWheel::sections);
	}
	else
	{
		LuckyWheel::sections = 5;
		API::updateWheelSections(5);
	}
	auto wheel = LuckyWheel::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5f, wheel));
}

void	LuckyWheel::move_node()
{
	if (this->getChildByTag(BALL_TAG) != nullptr && this->getChildByTag(WHEEL_TAG) != nullptr)
	{
		//this->unscheduleUpdate();
	 
		Node* wheel_node = this->getChildByTag(WHEEL_TAG);
		wheel_node->pauseSchedulerAndActions();
		this->pauseSchedulerAndActions();
		Vec2 current_position = this->getChildByTag(BALL_TAG)->getPosition();
		this->getChildByTag(BALL_TAG)->setScale(0.0f);
		this->getChildByTag(BALL_TAG)->setTag(0);
		Sprite* ball = Sprite::create("white_ball.png");
		ball->setPosition(current_position);
		ball->setScale(0.1f);
		ball->setTag(BALL_TAG);
		wheel_node->addChild(ball, BALL_TAG);
		this->resumeSchedulerAndActions();
		wheel_node->resumeSchedulerAndActions();
	}
}

void	LuckyWheel::bounce(Vec2 dest)
{	
	if (this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG) != nullptr)
	{
		EaseElasticOut *bn = EaseElasticOut::create(MoveTo::create(2.0f, dest));
		this->getChildByTag(WHEEL_TAG)->getChildByTag(BALL_TAG)->runAction(bn);
	}
}

std::vector<Vec2> LuckyWheel::getSectionDelimiterVector(Vec2 p1, Vec2 p2)
{
	std::vector<Vec2> line;
	
	float	dx = p1.x - p2.x;
	float	dy = p1.y - p2.y;
	float	dr = fabs(dy / dx); 
	float	error = dr - 0.5;
	float	y = p1.y;
	int		x = p1.x;

	while (x != (int)p2.x)
	{
		line.push_back(Vec2(x, y));
		DrawNode* drw = DrawNode::create();
		drw->drawDot(Vec2(x, y), 10, Color4F::WHITE);
		error += dr;
		if (error >= 0.5)
		{
			y++;
			error = error - 1.0;
		}
		if (p1.x < p2.x)
			x++;
		else
			x--;
		this->addChild(drw);
	}
	return line;
}

bool	LuckyWheel::checkIntersection_frwd(std::vector<Vec2> vect, Vec2 ball_pos, int cadran)
{
	if (vect.empty())
	{
#if (COCOS2D_DEBUG)
		API::debug("_checkIntersection_frwd -- nullptr params\n");
#endif
		return false;
	}
	switch (cadran)
	{
		case 1:
				for (Vec2 point : vect)
					if (ball_pos.x - point.x == 0 && ball_pos.y - point.y == 0)
						return true;
				return false;
		case 2:
				for (Vec2 point : vect)
					if (point.x - ball_pos.x == 0 && point.y - ball_pos.y == 0)
						return true;
				return false;
		case 3:
				for (Vec2 point : vect)
					if (point.x - ball_pos.x == 0 && point.y - ball_pos.y == 0)
						return true;
				return false;
		case 4:
				for (Vec2 point : vect)
					if (ball_pos.x - point.x == 0 && point.y - ball_pos.y == 0)
						return true;
				return false;
		default:
				return false;
	}
}

bool	LuckyWheel::checkIntersection_bkwd(std::vector<Vec2> vect, Vec2 ball_pos, int cadran)
{
	if (vect.empty())
	{
#if (COCOS2D_DEBUG)
		API::debug("_checkIntersection_bkwd -- nullptr params\n");
#endif
		return false;
	}
	switch (cadran)
	{
		case 1:
				for (Vec2 point : vect)
					if (point.x == ball_pos.x && point.y == ball_pos.y)
						return true;
				return false;
		case 2:
				for (Vec2 point : vect)
					if (point.x == ball_pos.x && point.y == ball_pos.y)
						return true;
				return false;
		case 3:
				for (Vec2 point : vect)
					if (point.x == ball_pos.x && point.y == ball_pos.y)
						return true;
				return false;
		case 4:
				for (Vec2 point : vect)
					if (point.x == ball_pos.x && point.y == ball_pos.y)
						return true;
				return false;
		default:
				return false;
	}
}

int		LuckyWheel::getSectionDelims(int closest_section, Vec2 ball_pos) // if closest > ret_sect closest = ret_sec - 1;
{
	float	diff_prev = 0.0f;
	float	diff_next = 0.0f;
	Vec2	prev_sec;
	Vec2	next_sec;
	Node*	node;
	Node*	child;

	node = this->getChildByTag(WHEEL_TAG);
	if (closest_section > LuckyWheel::sections || closest_section <= 0 || node == nullptr)
		return (-1);

	if (closest_section > 1)
		prev_sec = node->getChildByTag(closest_section - 1)->getPosition();
	else
		prev_sec = node->getChildByTag(LuckyWheel::sections)->getPosition();

	if (closest_section < LuckyWheel::sections)
		next_sec = node->getChildByTag(closest_section + 1)->getPosition();
	else
		next_sec = node->getChildByTag(1)->getPosition();

	diff_prev = fabs(prev_sec.x - ball_pos.x) + fabs(prev_sec.y - ball_pos.y);
	diff_next = fabs(next_sec.x - ball_pos.x) + fabs(next_sec.y - ball_pos.y);
	if (diff_next < diff_prev)
	{
		if (closest_section < LuckyWheel::sections)
			return (closest_section + 1);
		else
			return (1 + LuckyWheel::sections); // 1
	}
	else
	{
		if (closest_section > 1)
			return (closest_section - 1);
		else
			return (LuckyWheel::sections);
	}
}


void	LuckyWheel::fixTouch(Vec2* touch)
{
	if ()
}