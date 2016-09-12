
#include "conversions.h"

#include <sstream>

unsigned int strToUint(const std::string &src) {
    unsigned int ret;
    std::stringstream ss(src);
    ss >> ret;
    return ret;
}

int strToInt(const std::string &src){
    int ret;
    std::stringstream ss(src);
    ss >> ret;
    return ret;
}

unsigned short strToUshort(const std::string &src){
    unsigned short ret;
    std::stringstream ss(src);
    ss >> ret;
    return ret;
}

std::string uintToStr(const unsigned int num){
    std::string ret {""};
    std::stringstream ss;
    ss << num;
    ret = ss.str();
    return ret;
}

std::string intToStr(const int num){
    std::string ret {""};
    std::stringstream ss;
    ss << num;
    ret = ss.str();
    return ret;
}

std::string ushortToStr(const unsigned short num){
    std::string ret {""};
    std::stringstream ss;
    ss << num;
    ret = ss.str();
    return ret;
}
