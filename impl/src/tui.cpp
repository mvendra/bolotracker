
#include "tui.h"

#include "utils/conversions.h"
#include "dataobjects/investor.h"

#include "utils/datehelper.h"

#include "exceptions/ex_tui_error.h"

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

void Tui::print_add_menu() const {

    std::cout << std::endl << "Choose what to add" << std::endl;
    std::cout << "1. Investor" << std::endl;
    std::cout << "2. Currency" << std::endl;
    std::cout << "3. Subject" << std::endl;
    std::cout << "4. Invested time" << std::endl;
    std::cout << "5. Invested asset" << std::endl;
    std::cout << "6. Bonus" << std::endl;
    std::cout << "7. Invested money" << std::endl;
    std::cout << "0. Return to main menu" << std::endl;

}

template <typename T>
T Tui::get_option() const {
    T opt;
    std::cin >> opt;
    return opt;
}

std::string Tui::get_input_line() const {
    std::string ret;
    std::getline(std::cin, ret);
    if (ret == ""){
        std::getline(std::cin, ret);
    }
    return ret;
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



void Tui::menu_add_something(){

    print_add_menu();
    int opt {get_option<int>()};

    switch (opt){
        case 1:
            menu_add_investor();
            break;
        case 2:
            menu_add_currency();
            break;
        case 3:
            menu_add_subject();
            break;
        case 4:
            menu_add_invested_time();
            break;
        case 5:
            menu_add_invested_asset();
            break;
        case 6:
            menu_add_bonus();
            break;
        case 7:
            menu_add_invested_money();
            break;
        case 0:
            // returns to main menu
            break;
        default:
            std::cout << "Invalid option." << std::endl;
            break;

    }

}

void Tui::menu_list_something() const {
}

void Tui::menu_remove_something() const {
    std::cout << "Removal is currently not implemented" << std::endl;
}

void Tui::menu_add_investor() {

    std::cout << std::endl << "Enter investor info, separated by comma" << std::endl;
    std::cout << "(name, email, description)" << std::endl;

    std::string inv_info {get_input_line()};

    std::string name;
    std::string email;
    std::string desc;

    if (!getSub(inv_info, name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse investor's name")
    }
    name = trim(name);

    if (!getSub(inv_info, email)){
        EX_THROW(Ex_Tui_Error, "Unable to parse investor's email")
    }
    email = trim(email);

    getSub(inv_info, desc); // this should return false, as it is the last entry
    desc = trim(desc);

    // request confirmation
    std::cout << std::endl << "About to add investor: " << std::endl;
    std::cout << "name: [" << name << "]" << std::endl;
    std::cout << "email: [" << email << "]" << std::endl;
    std::cout << "description: [" << desc << "]" << std::endl;
    std::cout << "Type in \"confirm\" to proceed." << std::endl;

    std::string proceed {get_input_line()};
    if (proceed == "confirm"){
        model.add_investor(name, email, desc, DateHelper{});
        print_success("Investor added");
    } else {
        std::cout << "Aborted" << std::endl;
    }

}

void Tui::menu_add_currency(){

    std::cout << std::endl << "Enter currency info, separated by comma" << std::endl;
    std::cout << "(label, description)" << std::endl;

    std::string curr_info {get_input_line()};

    std::string label;
    std::string desc;

    if (!getSub(curr_info, label)){
        EX_THROW(Ex_Tui_Error, "Unable to parse currency's label")
    }
    label = trim(label);

    getSub(curr_info, desc); // this should return false, as it is the last entry
    desc = trim(desc);

    // request confirmation
    std::cout << std::endl << "About to add currency: " << std::endl;
    std::cout << "label: [" << label << "]" << std::endl;
    std::cout << "description: [" << desc << "]" << std::endl;
    std::cout << "Type in \"confirm\" to proceed." << std::endl;

    std::string proceed {get_input_line()};
    if (proceed == "confirm"){
        model.add_currency(label, desc, DateHelper{});
        print_success("Currency added");
    } else {
        std::cout << "Aborted" << std::endl;
    }

}

void Tui::menu_add_subject(){
}

void Tui::menu_add_invested_time(){
}

void Tui::menu_add_invested_asset(){
}

void Tui::menu_add_bonus(){
}

void Tui::menu_add_invested_money(){
}

bool Tui::getSub(std::string &source, std::string &next, const char delim){

    size_t n = source.find_first_of(delim);
    if (n == std::string::npos){
        next = source;
        source = "";
        return false;
    }

    next = source.substr(0, n);
    source = source.substr(n+1);

    return true;

}

std::string Tui::ltrim(const std::string &source){
    size_t n = source.find_first_not_of(' ');
    if (n == std::string::npos){
        return source;
    }
    return source.substr(n);
}

std::string Tui::rtrim(const std::string &source){
    if (source == ""){
        return "";
    }
    if (source[source.size()-1] != ' '){
        return source;
    }
    int n = -1;
    for (int i = source.size()-1; i!=-1; i--){
        if (source[i] != ' '){
            n = i;
            break;
        }
    }
    if (n == -1){
        return source;
    }
    return source.substr(0, n+1);
}

std::string Tui::trim(const std::string &source){
    return ltrim(rtrim(source));
}

void Tui::print_success(const std::string &msg) const {

    std::string white {"\033[0m"};
    std::string green {"\033[32m"};
    std::cout << green << msg << white << std::endl;

}
