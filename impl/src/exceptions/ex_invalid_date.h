
#ifndef __EX_INVALID_DATE_H__
#define __EX_INVALID_DATE_H__

#include "exceptions/ex_base.h"

class Ex_Invalid_Date final : public Ex_Base {
public:
    Ex_Invalid_Date(const std::string &msg, const std::string &func, const unsigned int line):Ex_Base(msg, func, line){}
};

#endif // __EX_INVALID_DATE_H__
