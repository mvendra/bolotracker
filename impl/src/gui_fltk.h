
#ifndef __GUI_FLTK_H__
#define __GUI_FLTK_H__

#include "controller_interface.h"

class Gui_FLTK final: public ControllerInterface {

public:

    Gui_FLTK(Model &md);
    ~Gui_FLTK();

    Gui_FLTK(const Gui_FLTK&) = delete;
    Gui_FLTK(Gui_FLTK&&) = delete;
    Gui_FLTK& operator=(const Gui_FLTK&) = delete;
    Gui_FLTK& operator=(Gui_FLTK&&) = delete;

    virtual bool run() override;

private:

};

#endif // __GUI_FLTK_H__
