
#ifndef __EX_UNSUPPORTED_PLATFORM_H__
#define __EX_UNSUPPORTED_PLATFORM_H__

#include "exceptions/ex_base.h"

class Ex_Unsupported_Platform final : public Ex_Base {
public:
    Ex_Unsupported_Platform(const std::string &msg, const std::string &func, const unsigned int line):Ex_Base(msg, func, line){}
};

#endif // __EX_UNSUPPORTED_PLATFORM_H__
