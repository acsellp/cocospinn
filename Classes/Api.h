#pragma once

# define COCOS2D_DEBUG		1 // 0 - realease
# define WHEEL_TAG			100
# define WHEEL_SEQ_TAG		200
# define BALL_TAG			300
# define BALL_SEQ_TAG		400
# define SPINNER_SEQ_TAG	500
# define SPINNER_TAG		600
# define BOUNCE				700

# define MAX_SPEED			100
# define MIN_SPEED			5


# define WHEEL_RADIUS		150 // 97
# define BALL_MOVE_RADIUS	WHEEL_RADIUS  * 1.1

typedef void* HANDLE;

namespace API
{
	void	startDebug();
	void	debug(char* output);

	void	init(void);
	int		getWheelScore(void);
	int		getWheelSections(void);
	void	updateWheelSections(int n);
	int		getSpinnerScore(void);
	void	updateSpinnerSpeed(int coef);
}