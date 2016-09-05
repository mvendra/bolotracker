
#ifndef __EX_NOTREACHED_H__
#define __EX_NOTREACHED_H__

#include "exceptions/ex_base.h"

#define NOTREACHED(MSG) EX_THROW(Ex_NotReached, MSG)

class Ex_NotReached final : public Ex_Base {
public:
    Ex_NotReached(const std::string &msg, const std::string &func, const unsigned int line):Ex_Base(msg, func, line){}
};

#endif // __EX_NOTREACHED_H__
