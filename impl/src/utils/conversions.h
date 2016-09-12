
#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include <string>


unsigned int strToUint(const std::string &src);
int strToInt(const std::string &src);
unsigned short strToUshort(const std::string &src);
std::string uintToStr(const unsigned int num);
std::string intToStr(const int num);
std::string ushortToStr(const unsigned int num);

#endif // __CONVERSIONS_H__
