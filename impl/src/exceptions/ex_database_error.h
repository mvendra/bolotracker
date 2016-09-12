
#ifndef __EX_DATABASE_ERROR_H__
#define __EX_DATABASE_ERROR_H__

#include "exceptions/ex_base.h"

class Ex_Database_Error final : public Ex_Base {
public:
    Ex_Database_Error(const std::string &msg, const std::string &func, const unsigned int line):Ex_Base(msg, func, line){}
};

#endif // __EX_DATABASE_ERROR_H__
