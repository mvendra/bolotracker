
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
    int get_option() const;

};

#endif // __TUI_H__
