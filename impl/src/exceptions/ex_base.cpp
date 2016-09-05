
#include "ex_base.h"

#include <sstream>

#include "utils.h"

Ex_Base::Ex_Base(const Ex_Base &other):
message{other.getMessage()}, function{other.getFunction()}, line{other.getLine()}{
}

Ex_Base::Ex_Base(const std::string &_msg, const std::string &_func, const unsigned int _line):
message{_msg}, function{_func}, line{_line}{
}

std::string Ex_Base::getMessage() const {
    return message;
}

std::string Ex_Base::getFunction() const {
    return function;
}

unsigned int Ex_Base::getLine() const {
    return line;
}

std::string Ex_Base::prettyPrint() const {
    return function + ":" + uintToStr(line) + " - " + message;
}
