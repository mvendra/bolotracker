
#ifndef __EX_BASE_H__
#define __EX_BASE_H__

#ifdef _WIN32
#define EX_THROW(CLASS, MSG) throw CLASS(MSG, __FUNCSIG__, __LINE__);
#else
#define EX_THROW(CLASS, MSG) throw CLASS(MSG, __PRETTY_FUNCTION__, __LINE__);
#endif

#include <string>

class Ex_Base { 

public:

    Ex_Base(const Ex_Base &other);
    Ex_Base(const std::string &_msg, const std::string &_func, const unsigned int _line);
    std::string getMessage() const;
    std::string getFunction() const;
    unsigned int getLine() const;
    std::string prettyPrint() const;
    virtual ~Ex_Base() {}

    void operator=(const Ex_Base &other) = delete; // forbidden attrib op
    Ex_Base() = delete; // forbidding unparametrised constructor
    void *operator new(size_t size) = delete; // forbidding heap allocation

protected:

    std::string message;
    std::string function;
    unsigned int line;

};

#endif // __EX_BASE_H__
