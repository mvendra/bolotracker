
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
    std::cout << "1. Add something" << std::endl;
    std::cout << "2. List something" << std::endl;
    std::cout << "3. Delete something" << std::endl;
    std::cout << "0. Exit" << std::endl;

}

template <typename T>
T Tui::get_option() const {
    T opt;
    std::cin >> opt;
    return opt;
}

bool Tui::run() {

    print_main_menu();
    int opt {get_option<int>()};

    switch (opt){

        case 1:
            menu_add_something();
            break;
        case 2:
            menu_list_something();
            break;
        case 3:
            menu_remove_something();
            break;
        case 0:
            return false;
            break;
        default:
            std::cout << "Invalid option." << std::endl;
            break;

    }

    return true;
}

void Tui::menu_add_something() const {
    // mvdebug begin
    DateHelper dh{};
    model.add_new_investor("bolo", "bolo@tracker", "test", dh);
    // mvdebug end
}

void Tui::menu_list_something() const {
}

void Tui::menu_remove_something() const {
}
