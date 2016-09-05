
#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

#ifdef __linux__
#include <unistd.h>
#endif // __linux__

unsigned int strToUint(const std::string &src);
std::string uintToStr(const unsigned int num);
std::string getAppWorkingDir();

#endif // __UTILS_H__
