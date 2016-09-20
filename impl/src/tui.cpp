
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

    std::cout << std::endl << "Enter subject info, separated by comma" << std::endl;
    std::cout << "(tag, description)" << std::endl;

    std::string subj_info {get_input_line()};

    std::string tag;
    std::string desc;

    if (!getSub(subj_info, tag)){
        EX_THROW(Ex_Tui_Error, "Unable to parse subject's tag")
    }
    tag = trim(tag);

    getSub(subj_info, desc); // this should return false, as it is the last entry
    desc = trim(desc);

    // request confirmation
    std::cout << std::endl << "About to add subject: " << std::endl;
    std::cout << "tag: [" << tag << "]" << std::endl;
    std::cout << "description: [" << desc << "]" << std::endl;
    std::cout << "Type in \"confirm\" to proceed." << std::endl;

    std::string proceed {get_input_line()};
    if (proceed == "confirm"){
        model.add_subject(tag, desc, DateHelper{});
        print_success("Subject added");
    } else {
        std::cout << "Aborted" << std::endl;
    }

}

void Tui::menu_add_invested_time(){

    std::cout << std::endl << "Enter invested time info, separated by comma" << std::endl;
    std::cout << "(investor name, currency label, description, comment, minutes, price per unit)" << std::endl;

    std::string inv_time_info {get_input_line()};

    std::string inv_name;
    std::string curr_label;
    std::string desc;
    std::string comment;
    unsigned int minutes;
    double price_per_unit;

    // investor name
    if (!getSub(inv_time_info, inv_name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested time's investor name")
    }
    inv_name = trim(inv_name);

    // currency label
    if (!getSub(inv_time_info, curr_label)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested time's currency label")
    }
    curr_label = trim(curr_label);

    // description
    if (!getSub(inv_time_info, desc)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested time's description")
    }
    desc = trim(desc);

    // comment
    if (!getSub(inv_time_info, comment)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested time's comment")
    }
    comment = trim(comment);

    // minutes
    std::string minutes_str;
    if (!getSub(inv_time_info, minutes_str)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested time's minutes")
    }
    minutes_str = trim(minutes_str);
    minutes = strToUint(minutes_str);

    // price per unit
    std::string price_per_unit_str;
    getSub(inv_time_info, price_per_unit_str);
    price_per_unit_str = trim(price_per_unit_str);
    price_per_unit = strToUint(price_per_unit_str);

    // request confirmation
    std::cout << std::endl << "About to add invested time: " << std::endl;
    std::cout << "investor name: [" << inv_name << "]" << std::endl;
    std::cout << "currency label: [" << curr_label << "]" << std::endl;
    std::cout << "description: [" << desc << "]" << std::endl;
    std::cout << "comment: [" << comment << "]" << std::endl;
    std::cout << "minutes: [" << minutes_str << "]" << std::endl;
    std::cout << "price_per_unit: [" << price_per_unit_str << "]" << std::endl;
    std::cout << "Type in \"confirm\" to proceed." << std::endl;

    std::string proceed {get_input_line()};
    if (proceed == "confirm"){
        model.add_invested_time(inv_name, curr_label, DateHelper{}, desc, comment, minutes, price_per_unit);
        print_success("Invested time added");
    } else {
        std::cout << "Aborted" << std::endl;
    }

}

void Tui::menu_add_invested_asset(){

    std::cout << std::endl << "Enter invested asset info, separated by comma" << std::endl;
    std::cout << "(investor name, currency label, short name, description, comment, price)" << std::endl;

    std::string inv_asset_info {get_input_line()};

    std::string inv_name;
    std::string curr_label;
    std::string short_name;
    std::string desc;
    std::string comment;
    double price;

    // investor name
    if (!getSub(inv_asset_info, inv_name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested asset's investor name")
    }
    inv_name = trim(inv_name);

    // currency label
    if (!getSub(inv_asset_info, curr_label)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested asset's currency label")
    }
    curr_label = trim(curr_label);

    // short name
    if (!getSub(inv_asset_info, short_name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested asset's short name")
    }
    desc = trim(desc);

    // description
    if (!getSub(inv_asset_info, desc)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested asset's description")
    }
    desc = trim(desc);

    // comment
    if (!getSub(inv_asset_info, comment)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested asset's comment")
    }
    comment = trim(comment);

    // price
    std::string price_str;
    getSub(inv_asset_info, price_str);
    price_str = trim(price_str);
    price = strToUint(price_str);

    // request confirmation
    std::cout << std::endl << "About to add invested asset: " << std::endl;
    std::cout << "investor name: [" << inv_name << "]" << std::endl;
    std::cout << "currency label: [" << curr_label << "]" << std::endl;
    std::cout << "description: [" << desc << "]" << std::endl;
    std::cout << "comment: [" << comment << "]" << std::endl;
    std::cout << "price: [" << price_str << "]" << std::endl;
    std::cout << "Type in \"confirm\" to proceed." << std::endl;

    std::string proceed {get_input_line()};
    if (proceed == "confirm"){
        model.add_invested_asset(inv_name, curr_label, DateHelper{}, short_name, desc, comment, price);
        print_success("Invested asset added");
    } else {
        std::cout << "Aborted" << std::endl;
    }

}

void Tui::menu_add_bonus(){

    std::cout << std::endl << "Enter bonus info, separated by comma" << std::endl;
    std::cout << "(investor name, short name, description, comment, reward)" << std::endl;

    std::string bonus_info {get_input_line()};

    std::string inv_name;
    std::string short_name;
    std::string desc;
    std::string comment;
    std::string reward;

    // investor name
    if (!getSub(bonus_info, inv_name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse bonus's investor name")
    }
    inv_name = trim(inv_name);

    // short name
    if (!getSub(bonus_info, short_name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested bonus's short name")
    }
    short_name = trim(short_name);

    // description
    if (!getSub(bonus_info, desc)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested bonus's description")
    }
    desc = trim(desc);

    // comment
    if (!getSub(bonus_info, comment)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested bonus's comment")
    }
    comment = trim(comment);

    // reward
    getSub(bonus_info, reward);
    reward = trim(reward);

    // request confirmation
    std::cout << std::endl << "About to add bonus: " << std::endl;
    std::cout << "investor name: [" << inv_name << "]" << std::endl;
    std::cout << "short name: [" << short_name << "]" << std::endl;
    std::cout << "description: [" << desc << "]" << std::endl;
    std::cout << "comment: [" << comment << "]" << std::endl;
    std::cout << "reward: [" << reward << "]" << std::endl;
    std::cout << "Type in \"confirm\" to proceed." << std::endl;

    std::string proceed {get_input_line()};
    if (proceed == "confirm"){
        model.add_bonus(inv_name, DateHelper{}, short_name, desc, comment, reward);
        print_success("Bonus added");
    } else {
        std::cout << "Aborted" << std::endl;
    }

}

void Tui::menu_add_invested_money(){

    std::cout << std::endl << "Enter invested money info, separated by comma" << std::endl;
    std::cout << "(investor name, currency label, short name, description, comment, amount)" << std::endl;

    std::string inv_money_info {get_input_line()};

    std::string inv_name;
    std::string curr_label;
    std::string short_name;
    std::string desc;
    std::string comment;
    double amount;

    // investor name
    if (!getSub(inv_money_info, inv_name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested money's investor name")
    }
    inv_name = trim(inv_name);

    // currency label
    if (!getSub(inv_money_info, curr_label)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested money's currency label")
    }
    curr_label = trim(curr_label);

    // short name
    if (!getSub(inv_money_info, short_name)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested money's short name")
    }
    short_name = trim(short_name);

    // description
    if (!getSub(inv_money_info, desc)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested money's description")
    }
    desc = trim(desc);

    // comment
    if (!getSub(inv_money_info, comment)){
        EX_THROW(Ex_Tui_Error, "Unable to parse invested money's comment")
    }
    comment = trim(comment);

    // amount
    std::string amount_str;
    getSub(inv_money_info, amount_str);
    amount_str = trim(amount_str);
    amount = strToUint(amount_str);

    // request confirmation
    std::cout << std::endl << "About to add invested money: " << std::endl;
    std::cout << "investor name: [" << inv_name << "]" << std::endl;
    std::cout << "currency label: [" << curr_label << "]" << std::endl;
    std::cout << "short name: [" << short_name << "]" << std::endl;
    std::cout << "description: [" << desc << "]" << std::endl;
    std::cout << "comment: [" << comment << "]" << std::endl;
    std::cout << "amount: [" << amount_str << "]" << std::endl;
    std::cout << "Type in \"confirm\" to proceed." << std::endl;

    std::string proceed {get_input_line()};
    if (proceed == "confirm"){
        model.add_invested_money(inv_name, curr_label, DateHelper{}, short_name, desc, comment, amount);
        print_success("Invested money added");
    } else {
        std::cout << "Aborted" << std::endl;
    }

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
