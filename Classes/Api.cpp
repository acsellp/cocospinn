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

void	API::startDebug()
{
	AllocConsole();
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	debug("Start debugging\n");
}

void	API::debug(char* output)
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

int		API::getWheelSections(void)
{
	return wheelSections;
}

void	API::updateWheelSections(int n)
{
	wheelSections = n;
}

void	API::updateSpinnerSpeed(int speed)
{
	spinnerSpeed = speed;
}

int		API::getSpinnerScore(void)
{
	return spinnerScore;
}