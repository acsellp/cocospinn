#ifndef _FILE_OPERATION_H_
# define _FILE_OPERATION_H_

#include <string>
#define MIN_SIZE 10
#define UNDEF 2147483647

namespace FileOperation 
{
	int		saveFile(std::string path, std::string data);
	char	*readFile(std::string path, size_t size);
	int		readFileValue(std::string path, size_t size);
	std::string getFilePath(std::string fileName);
};
#endif
