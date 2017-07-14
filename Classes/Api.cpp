#include "Api.h"
#include "cocos2d.h"
#include <windows.h>
#include <iostream>

USING_NS_CC;

static HANDLE	console;
int				wheelSections;
int				spinnerSpeed;
int				spinnerScore;
Scene*			runningScene;

void	startDebug()
{
	AllocConsole();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	debug("Start debugging\n");
}

void	debug(char* output)
{
#ifdef WIN32
		DWORD cw;
		size_t newsize = strlen(output) + 1;
		size_t convertedChars = 0;
		wchar_t* wcstring = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring, newsize, output, _TRUNCATE);
		WriteConsole(console, wcstring, convertedChars, &cw, NULL);
		delete[] wcstring;
#else
		cout << output;
#endif
}

int		getWheelSections(void)
{
	return wheelSections;
}

void	setWheelSections(int n)
{
	wheelSections = n;
}

void	setSpinnerSpeed(int speed)
{
	spinnerSpeed = speed;
}

int		getSpinnerScore(void);
{
	return spinnerScore;
}