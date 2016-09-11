
#ifndef __EX_FAILED_OPENING_DATABASE_H__
#define __EX_FAILED_OPENING_DATABASE_H__

#include "exceptions/ex_base.h"

class Ex_FailedOpeningDatabase final : public Ex_Base {
public:
    Ex_FailedOpeningDatabase(const std::string &msg, const std::string &func, const unsigned int line):Ex_Base(msg, func, line){}
};

#endif // __EX_FAILED_OPENING_DATABASE_H__
