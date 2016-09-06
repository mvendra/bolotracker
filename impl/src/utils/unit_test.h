
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

// mvtodo: fully document this and release. this is pure GOLD
// mvtodo: and test the testing framework big time

// BASIC TESTING

// The basic testing function. Will use the passed |func| to
// compare |param1| with |param2|

template <typename X, typename Y>
bool test(const std::string &msg, X param1, Y param2, auto func){
    bool ret = func(param1, param2);
    // reporting
    std::string t1, t2;
    { std::stringstream ss; ss << param1; t1 = ss.str(); }
    { std::stringstream ss; ss << param2; t2 = ss.str(); }
    std::string msg_plus_params = msg + ". (" + t1 + ", " + t2 + ")";
    if (!ret){ print_error("FAILED: " + msg_plus_params); 
    } else { print_success("Passed: " + msg_plus_params); }
    return ret;
}

// EXCEPTION TESTING

// Will call |testcase|, and will treat as a success if it throws an
// exception of type |T|. If no exception is thrown, or
// an exception of another type is thrown, then will treat it as a failure.

template <typename T>
bool test_ex(const std::string &msg, auto testcase){
    try {
        testcase();
        print_error("FAILED: " + msg);
        return false;
    } catch (const T& ex){ 
        print_success("Passed: " + msg);
        return true;
    } catch (...){
        print_error("FAILED: " + msg);
        return false;
    }
}

// Will call |testcase|, and will treat as a failure if it throws an
// exception of type |T|. If no exception is thrown, or
// an exception of another type is thrown, then will treat it as a success.

template <typename T>
bool test_nex(const std::string &msg, auto testcase){
    try {
        testcase();
        print_success("Passed: " + msg);
        return true;
    } catch (const T& ex){
        print_error("FAILED: " + msg);
        return false;
    } catch (...){
        print_error("Passed: " + msg);
        return false;
    }
}

// Will call |testcase|, and will treat as a success
// if any exception is thrown, and as a failure otherwise.

bool test_anyex(const std::string &msg, auto testcase){
    try {
        testcase();
        print_error("FAILED: " + msg);
        return false;
    } catch (...){ 
        print_success("Passed: " + msg);
        return true;
    }
}

template <typename T>
bool test_anynex(const std::string &msg, auto testcase){
    try {
        testcase();
        print_success("Passed: " + msg);
        return true;
    } catch (...){
        print_error("FAILED: " + msg);
        return false;
    }
}

// HELPERS

template <typename X, typename Y>
bool test_eq(const std::string &msg, X param1, Y param2){
    auto comp_eq = [](auto p1, auto p2) { return (p1 == p2); };
    return test(msg, param1, param2, comp_eq);
}

template <typename X, typename Y>
bool test_gt(const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 > p2); };
    return test(msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
bool test_ge(const std::string &msg, X param1, Y param2){
    auto comp_ge = [](auto p1, auto p2) { return (p1 >= p2); };
    return test(msg, param1, param2, comp_ge);
}

template <typename X, typename Y>
bool test_lt(const std::string &msg, X param1, Y param2){
    auto comp_gt = [](auto p1, auto p2) { return (p1 < p2); };
    return test(msg, param1, param2, comp_gt);
}

template <typename X, typename Y>
bool test_le(const std::string &msg, X param1, Y param2){
    auto comp_le = [](auto p1, auto p2) { return (p1 <= p2); };
    return test(msg, param1, param2, comp_le);
}

template <typename X, typename Y>
bool test_ne(const std::string &msg, X param1, Y param2){
    auto comp_ne = [](auto p1, auto p2) { return (p1 != p2); };
    return test(msg, param1, param2, comp_ne);
}

// INTERFACE EXTENSIONS

template <typename X, typename Y>
void test(bool &total, const std::string &msg, X param1, Y param2, auto func){
    total &= test<X, Y>(msg, param1, param2, func);
}

template <typename T>
void test_ex(bool &total, const std::string &msg, auto testcase){
    total &= test_ex<T>(msg, testcase);
}

template <typename T>
void test_nex(bool &total, const std::string &msg, auto testcase){
    total &= test_nex<T>(msg, testcase);
}

void test_anyex(bool &total, const std::string &msg, auto testcase){
    total &= test_anyex(msg, testcase);
}

template <typename T>
void test_anynex(bool &total, const std::string &msg, auto testcase){
    total &= test_anynex<T>(msg, testcase);
}

template <typename X, typename Y>
void test_eq(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_eq<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_gt(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_gt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ge(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_ge<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_lt(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_lt<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_le(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_le<X, Y>(msg, param1, param2);
}

template <typename X, typename Y>
void test_ne(bool &total, const std::string &msg, X param1, Y param2){
    total &= test_ne<X, Y>(msg, param1, param2);
}

#endif // __UNIT_TEST_H__
