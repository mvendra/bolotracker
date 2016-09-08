
#include "tui.h"

#include <iostream>

Tui::Tui(Model &md):ControllerInterface{md}{
    print_happy_talk();
}

Tui::~Tui(){
}

void Tui::print_happy_talk() const {
    std::cout << "BoloTracker TUI." << std::endl;
}

void Tui::print_main_menu() const {

    std::cout << std::endl << "Choose an option" << std::endl;
    // mvtodo: add rest before zero - exit
    std::cout << "0. Exit" << std::endl;

}

int Tui::get_option() const {
    int opt;
    std::cin >> opt;
    return opt;
}

bool Tui::run() {

    print_main_menu();
    int opt = get_option();
    if (opt == 0){
        return false;
    }

    return true;
}
