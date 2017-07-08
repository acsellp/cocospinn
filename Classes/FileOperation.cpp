#include "cocos2d.h"
#include "FileOperation.h"
#include <stdio.h>

using namespace std;

int FileOperation::saveFile(string path, string data)
{
	if (path.empty() || data.empty())
		return (-1);
	FILE* fp = fopen(path.c_str() , "w");
	if (!fp)
		return (-1);
	fputs(data.c_str(), fp);
	fclose(fp);
	return (0);
}

char*  FileOperation::readFile(string path, size_t size)
{
	if (path.empty() || size <= 0)
		return NULL;
	FILE* fp = fopen(path.c_str(), "r");
	char* buf = new char[size + 1];
	if (!fp || !buf)
		return NULL;
	fgets(buf, size, fp);
	fclose(fp);
	return buf;
}

int  FileOperation::readFileValue(string path, size_t size)
{
	int ret = 0;
	if (path.empty() || size <= 0)
		return UNDEF;
	FILE* fp = fopen(path.c_str(), "r");
	char* buf = new char[size + 1];
	if (!fp || !buf)
		return UNDEF;
	fgets(buf, size, fp);
	fclose(fp);
	ret = atoi(buf);
	delete[] buf;
	return ret;
}

string  FileOperation::getFilePath(string fileName)
{
	string path("");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	path.append("/data/data/org.cocos2dx.application/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//GetFullPathName("");
	path.append("D:/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
	path = cocos2d::CCApplication::sharedApplication().getAppDataPath();
#endif

#if (CC_TAGET_PLATFORM == CC_PLATFORM_IOS)
	path = IOS .. path
#endif
#ifdef _TRANZDA_VM_
	path = "D:/Work7" + path;
	path.append("tmpfile");
#endif
	return path;
}
