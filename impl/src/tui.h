
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

    void print_happy_talk() const;
    void print_main_menu() const;
    void print_add_menu() const;

    template <typename T>
    T get_option() const;

    bool getSub(std::string &source, std::string &next, const char delim = ',');

    std::string get_input_line() const;

    std::string ltrim(const std::string &source);
    std::string rtrim(const std::string &source);
    std::string trim(const std::string &source);

    // submenus
    void menu_add_something();
    void menu_list_something() const;
    void menu_remove_something() const;

    void menu_add_investor();

};

#endif // __TUI_H__
