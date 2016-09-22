
#include "gui_fltk.h"

#include "fltk_wrapper.h"

#include <stdlib.h>
#include <memory>

Gui_FLTK::Gui_FLTK(int _argc, char *_argv[], Model &md):ControllerInterface{_argc, _argv, md}{
}

Gui_FLTK::~Gui_FLTK(){
}

bool Gui_FLTK::run() {

    std::unique_ptr<Fl_Double_Window> window = std::make_unique<Fl_Double_Window>(400,320,argv[0]);
    std::unique_ptr<Fl_Box> box = std::make_unique<Fl_Box>(FL_ENGRAVED_FRAME,10,10,300,300,
        "MINIMUM UPDATE TEST\n"
        "\n"
        "The slider on the right purposely\n"
        "draws outside it's boundaries.\n"
        "Moving it should leave old copies\n"
        "of the label.  These copies should\n"
        "*not* be erased by any actions\n"
        "other than hiding and showing\n"
        "of that portion of the window\n"
        "or changing the button that\n"
        "intesects them.");


    window->resizable(box.get());

    std::unique_ptr<Fl_Slider> slider = std::make_unique<Fl_Slider>(320,10,20,300,"Too_Big_Label");
    slider->align(0);

    std::unique_ptr<Fl_Button> btn1 = std::make_unique<Fl_Button>(20,270,100,30,"Button");
    std::unique_ptr<Fl_Return_Button> btn2 = std::make_unique<Fl_Return_Button>(200,270,100,30,"Button");

    window->show(argc, argv);
    int finish = Fl::run();
    (void)finish;

    return false;

}
