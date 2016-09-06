
#include "bolotracker.h"

#include "utils/utils.h"
#include "exceptions/ex_base.h"

#include <iostream>

#ifndef NDEBUG
#define TESTS_ONLY
#include "tests/bt_tests.h"
#endif // NDEBUG

void bootstrap(){

    std::string working_dir = getAppWorkingDir();
    BoloTracker bt {working_dir};
    bt.run();

}

int main(int argc, char *argv[]){

    (void)argc; (void)argv; // silence warnings

#ifdef TESTS_ONLY

    if (test_all()){
        std::cout << "Result: Success." << std::endl; 
    } else {
        std::cout << "Result: Fail." << std::endl; 
    }

#else

    try {
        bootstrap();
    } catch (const Ex_Base &ex){
        std::cout << ex.getMessage() << std::endl;
    }

    return 0;

#endif // TESTS_ONLY

}
