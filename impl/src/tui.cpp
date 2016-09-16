
#include "tui.h"

#include <iostream>
#include "utils/conversions.h"

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

    //model.add_subject("dev", "test", dh);
    //model.add_currency("usd", "test", dh);
    //model.add_investor("bob", "bolo@tracker", "test", dh);
    //model.add_invested_time(1, 1, dh, "no desc", "no comment", 25, 1.25);
    //model.attach_subject_to_invested_time(1, 1);
    //model.add_invested_asset(1, 1, dh, "a little something", "desc", "no", 59.99);
    //model.attach_subject_to_invested_asset(1, 1);
    //model.add_bonus(1, dh, "little bono", "desc", "koment", "pizza");
    model.attach_subject_to_bonus(1, 2);
    // mvdebug end

}

void Tui::menu_list_something() const {

    // mvdebug begin
    unsigned int pk;
    std::string name;
    std::string email;
    std::string description;
    std::string comment;
    std::string label;
    std::string tag;
    double value;
    DateHelper dh {};

    (void)pk; (void)name; (void)label; (void)tag; (void)email; (void)description; (void)comment; (void)value; (void)dh;

    //model.get_investor_info("bob", pk, email, description, dh);
    //model.get_investor_info(1, name, email, description, dh);

    //model.get_subject_info("dev", pk, description, dh);
    //model.get_subject_info(2, tag, description, dh);

    //model.get_currency_info("usd", pk, description, dh);
    model.get_currency_info(2, label, description, dh);

    //std::cout << "pk: [" << uintToStr(pk) << "]" << std::endl;
    //std::cout << "name: [" << name << "]" << std::endl;
    //std::cout << "email: [" << email << "]" << std::endl;
    std::cout << "description: [" << description << "]" << std::endl;
    //std::cout << "comment: [" << comment << "]" << std::endl;
    std::cout << "label: [" << label << "]" << std::endl;
    //std::cout << "tag: [" << tag << "]" << std::endl;
    std::cout << "date: [" << dh.getDateString() << "]" << std::endl;

    int stop=1;
    (void)stop;
    // mvdebug end

}

void Tui::menu_remove_something() const {
}
