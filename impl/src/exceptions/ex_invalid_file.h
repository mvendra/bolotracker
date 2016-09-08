
#ifndef __EX_INVALID_FILE_H__
#define __EX_INVALID_FILE_H__

#include "exceptions/ex_base.h"

class Ex_InvalidFile final : public Ex_Base {
public:
    Ex_InvalidFile(const std::string &msg, const std::string &func, const unsigned int line):Ex_Base(msg, func, line){}
};

#endif // __EX_INVALID_FILE_H__
