
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

// THE PRAGMA BELOW IS TO ALLOW THE USE OF AUTO AS A FUNCTION PARAMETER
#ifdef __GNUC__
#pragma GCC system_header // disabling error-triggering warnings
#endif

// mvtodo: provide both, a parameterised bool and a returned bool version of each function

// mvtodo: fully document this and release. this is pure GOLD

// mvtodo: consider adding optional msg decorator to report original function (test, test_eq, etc)
template <typename X, typename Y>
void test(bool &total, const std::string &msg, X param1, Y param2, auto func){
    bool ret = func(param1, param2);
    total &= ret;
    std::string t1, t2;
    { std::stringstream ss; ss << param1; t1 = ss.str(); }
    { std::stringstream ss; ss << param2; t2 = ss.str(); }
    std::string msg_plus_params = msg + ". (" + t1 + ", " + t2 + ")";
    if (!ret){ print_error("FAILED: " + msg_plus_params); 
    } else { print_success("Passed: " + msg_plus_params); }
}

template <typename X, typename Y>
void test_eq(bool &total, const std::string &msg, X param1, Y param2){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    test(total, msg, param1, param2, comp_eq);
}

template <typename X, typename Y>
void test_gt(bool &total, const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 > p2); };
    test(total, msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
void test_ge(bool &total, const std::string &msg, X param1, Y param2){
    auto comp_ge = [](auto p1, auto p2) { return (p1 >= p2); };
    test(total, msg, param1, param2, comp_ge);
}

template <typename X, typename Y>
void test_lt(bool &total, const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 < p2); };
    test(total, msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
void test_le(bool &total, const std::string &msg, X param1, Y param2){
    auto comp_le = [](auto p1, auto p2) { return (p1 <= p2); };
    test(total, msg, param1, param2, comp_le);
}

template <typename T>
void test_ex(bool &total, const std::string &msg, auto testcase){
    try {
        testcase();
        total &= false;
        print_error("FAILED (exception expected): " + msg);
    } catch (const T& ex){ 
        print_success("Passed (exception thrown): " + msg);
    } catch (...){
        print_error("FAILED (wrong type of exception): " + msg);
        total &= false;
    }
}

template <typename T>
void test_nex(bool &total, const std::string &msg, auto testcase){
    try {
        testcase();
        print_success("Passed (no exception thrown): " + msg);
    } catch (const T& ex){
        total &= false;
        print_error("FAILED (exception expected): " + msg);
    } catch (...){
        print_error("FAILED (wrong type of exception): " + msg);
        total &= false;
    }
}

void test_anyex(bool &total, const std::string &msg, auto testcase){
    try {
        testcase();
        total &= false;
        print_error("FAILED (exception expected): " + msg);
    } catch (...){ 
        print_success("Passed (exception thrown): " + msg);
    }
}

template <typename T>
void test_anynex(bool &total, const std::string &msg, auto testcase){
    try {
        testcase();
        print_success("Passed (no exception thrown): " + msg);
    } catch (...){
        print_error("FAILED (wrong type of exception): " + msg);
        total &= false;
    }
}

#endif // __UNIT_TEST_H__
