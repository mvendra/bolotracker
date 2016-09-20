
#ifndef __TUI_H__
#define __TUI_H__

#include "controller_interface.h"

class Tui final: public ControllerInterface {

public:

    Tui(Model &md);
    ~Tui();

    Tui(const Tui&) = delete;
    Tui(Tui&&) = delete;
    Tui& operator=(const Tui&) = delete;
    Tui& operator=(Tui&&) = delete;

    virtual bool run() override;

private:

    void print_success(const std::string &msg) const;

    void print_happy_talk() const;
    void print_main_menu() const;
    void print_add_menu() const;
    void print_list_menu() const;

    template <typename T>
    T get_option() const;

    bool getSub(std::string &source, std::string &next, const char delim = ',');

    std::string get_input_line() const;

    std::string ltrim(const std::string &source);
    std::string rtrim(const std::string &source);
    std::string trim(const std::string &source);

    // submenus
    void menu_add_something();
    void menu_list_something();
    void menu_remove_something();

    void menu_add_investor();
    void menu_add_currency();
    void menu_add_subject();
    void menu_add_invested_time();
    void menu_add_invested_asset();
    void menu_add_bonus();
    void menu_add_invested_money();

    void menu_list_investors();
    void menu_list_currencies();
    void menu_list_subjects();
    void menu_list_invested_time();
    void menu_list_invested_assets();
    void menu_list_bonuses();
    void menu_list_invested_money();

};

#endif // __TUI_H__
