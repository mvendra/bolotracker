
#include "bolotracker.h"

#include "utils.h"
#include "exceptions/ex_base.h"

#include <iostream>

void bootstrap(){

    std::string working_dir = getAppWorkingDir();
    BoloTracker bt {working_dir};
    bt.run();

}

int main(int argc, char *argv[]){

    (void)argc; (void)argv; // silence warnings

    try {
        bootstrap();
    } catch (const Ex_Base &ex){
        std::cout << ex.getMessage() << std::endl;
    }

    return 0;

}
