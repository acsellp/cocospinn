#include "Api.h"
#include "cocos2d.h"
#include <windows.h>
#include <iostream>

USING_NS_CC;


HANDLE			console;
int				wheelSections;
int				spinnerSpeed;
int				spinnerScore;
Scene*			runningScene;
Node*			currentNode;


void	API::init()
{
	currentNode = nullptr;
	console = NULL;
	wheelSections = 7;
	spinnerSpeed = 1;
	spinnerScore = 0;
	runningScene = nullptr;
}

void	API::startDebug()
{
	AllocConsole();
	console = GetStdHandle(STD_OUTPUT_HANDLE);
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
	// ..
	return wheelSections;
}

void	API::updateWheelSections(int n)
{
	wheelSections = n;
}

void	API::updateSpinnerSpeed(int speed)
{
	//if scene != done ->return
	spinnerSpeed = speed;
}

int		API::getSpinnerScore(void)
{
	// .. 
	return spinnerScore;
}
