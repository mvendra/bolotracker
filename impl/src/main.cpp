
#include "bolotracker.h"

#include "utils/sysutils.h"
#include "exceptions/ex_base.h"

#include <iostream>

// choose only one...
//#define TEST_ONLY
//#define TEST_AND_RUN
#define RUN_ONLY

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

void bootstrap(){

    std::string working_dir = getAppWorkingDir();
    BoloTracker bt {working_dir};
    bt.run();

}

int main(int argc, char *argv[]){

    (void)argc; (void)argv; // silence warnings

#if defined(TEST_ONLY) || defined(TEST_AND_RUN)
#ifndef RUN_ONLY
    runtests();
#endif
#endif

#if defined(TEST_AND_RUN) || defined(RUN_ONLY)
#ifndef TEST_ONLY

    try {
        bootstrap();
    } catch (const Ex_Base &ex){
        std::cout << ex.getMessage() << std::endl;
    }

    return 0;

#endif
#endif

}
