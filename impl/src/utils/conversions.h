
#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include <string>

class Conversions final {
public:
    Conversions() = delete;
    ~Conversions() = delete;
    Conversions(const Conversions&) = delete;
    Conversions(Conversions**) = delete;
    Conversions& operator=(const Conversions&) = delete;
    Conversions& operator=(Conversions&&) = delete;

    static unsigned int strToUint(const std::string &src);
    static std::string uintToStr(const unsigned int num);

};

#endif // __CONVERSIONS_H__
