#ifndef __API_H__
# define __API_H__

# define COCOS2D_DEBUG		1 // 0 - realease
# define WHEEL_TAG			1000
# define WHEEL_SEQUENCE_TAG	2000
# define MAX_SPEED			100
# define MIN_SPEED			5

typedef void* HANDLE;

namespace API
{
	void	startDebug();
	void	debug(char* output);

	int		getWheelScore(void);
	int		getWheelSections(void);
	void	updateWheelSections(int n);
	int		getSpinnerScore(void);
	void	updateSpinnerSpeed(int coef);
}

#endif