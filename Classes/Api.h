#ifndef __API_H__
# define __API_H__

# define COCOS2D_DEBUG		1
# define WHEEL_TAG			1000
# define WHEEL_SEQUENCE_TAG	2000
# define MAX_SPEED			100
# define MIN_SPEED			5

typedef void* HANDLE;


void	startDebug();
void	debug(char* output);
	
int		getWheelScore(void);
int		getWheelSections(void);
void	setWheelSections(int n);
int		getSpinnerScore(void);
void	setSpinnerSpeed(int coef);

#endif