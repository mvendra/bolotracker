
#include <iostream>

#include "bolotracker.h"

int main(int argc, char *argv[]){

    (void)argc; (void)argv; // silence warnings

    BoloTracker bt {"/home/mateus/nuke/"}; // mvtodo: get the pwd and pass it here
    bt.run();

	return 0;

}
