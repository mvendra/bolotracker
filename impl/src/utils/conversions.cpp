
#include "conversions.h"

#include <sstream>

unsigned int Conversions::strToUint(const std::string &src) {
    unsigned int ret;
    std::stringstream ss(src);
    ss >> ret;
    return ret;
}

std::string Conversions::uintToStr(const unsigned int num){
    std::string ret {""};
    std::stringstream ss;
    ss << num;
    ret = ss.str();
    return ret;
}
