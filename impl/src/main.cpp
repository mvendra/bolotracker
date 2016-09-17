
#include "bolotracker.h"

#include "exceptions/ex_base.h"

#include <string>
#include <vector>
#include <iostream>

// choose only one...
#define TEST_ONLY
//#define TEST_AND_RUN
//#define RUN_ONLY

#if defined(TEST_ONLY) || defined(TEST_AND_RUN)
#include "tests/bolotracker_tests.h"

void runtests(){
    if (test_all()){
        std::cout << "Result: Success." << std::endl; 
    } else {
        std::cout << "Result: Fail." << std::endl; 
    }
}
#endif

using vstr = std::vector<std::string>;

void bootstrap(const vstr& cmdline_params){
    BoloTracker bt {cmdline_params};
    bt.run();
}

vstr parse_cmdline_args(const int argc, char * const argv[]){

    vstr ret;
    std::string cmdp;
    for (int i=0; i<argc; i++){
        cmdp = argv[i];
        ret.push_back(cmdp);
    }
    return ret;

}

int main_delegate(int argc, char *argv[]){

    vstr r {parse_cmdline_args(argc, argv)};

#if defined(TEST_ONLY) || defined(TEST_AND_RUN)
#ifndef RUN_ONLY
    runtests();
#ifdef TEST_ONLY
    return 0;
#endif
#endif
#endif

#if defined(TEST_AND_RUN) || defined(RUN_ONLY)
#ifndef TEST_ONLY

    bootstrap(r);
    return 0;

#endif
#endif

}

int main(int argc, char *argv[]){

    try {
        return main_delegate(argc, argv);
    } catch (const Ex_Base &ex){
        std::cout << "Exception caught: " << ex.getMessage() << std::endl;
        return 1;
    } catch (...){
        std::cout << "Unexpected exception has been raised." << std::endl;
        return 2;
    }

}
