
#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include "utils/conversions.h"

#include <string>
#include <iostream>
#include <sstream>

#define COLOR_WHITE  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"

void print_error(const std::string &msg){
    std::cout << COLOR_RED << msg << COLOR_WHITE << std::endl;
}

void print_success(const std::string &msg){
    std::cout << COLOR_GREEN << msg << COLOR_WHITE << std::endl;
}

void print_neutral(const std::string &msg){
    std::cout << COLOR_WHITE << msg << COLOR_WHITE << std::endl;
}

template <typename X, typename Y>
void test_eq(bool &total, const std::string &msg, X param1, Y param2){
    bool ret = (param1 == param2);
    total &= ret;
    std::string t1, t2;
    { std::stringstream ss; ss << param1; t1 = ss.str(); }
    { std::stringstream ss; ss << param2; t2 = ss.str(); }
    std::string msg_plus_params = msg + ". (" + t1 + ", " + t2 + ")";
    if (!ret){ print_error("FAILED: " + msg_plus_params); 
    } else { print_success("Passed: " + msg_plus_params); }
}

#endif // __UNIT_TEST_H__
