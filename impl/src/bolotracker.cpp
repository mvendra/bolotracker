
#include "bolotracker.h"
#include "model.h"
#include "tui.h"
#include "gui_fltk.h"
#include "utils/sysutils.h"

#include "exceptions/ex_base.h"
#include "exceptions/ex_invalid_file.h"

#include <memory>

//#define USE_TUI
#define USE_GUI_FLTK

BoloTracker::BoloTracker(const std::vector<std::string> &cmdline_params):dbpath{get_db_path(cmdline_params)}{
    // mvtodo: need to check if file exists, and is a file (and not a directory)?
}

BoloTracker::~BoloTracker(){
}

std::string BoloTracker::get_db_path(const std::vector<std::string> &cmdline_params){

    std::string db_path;

    // process the cmdline args
    for (unsigned int i=0; i<cmdline_params.size(); i++){

        // a working path has been specified
        if (i == 1){
            db_path = cmdline_params[i];
        }

    }

    // no db has been specified on the cmdline
    if (db_path.length() == 0){
        std::string working_dir {getAppWorkingDir()};
        db_path = working_dir + "/" + "bolo.db"; // default name
    }

    return db_path;

}

void BoloTracker::run(){

    Model md{dbpath};
#if defined(USE_TUI)
    std::unique_ptr<ControllerInterface> controller {std::make_unique<Tui>(md)};
#elif defined(USE_GUI_FLTK)
    std::unique_ptr<ControllerInterface> controller {std::make_unique<Gui_FLTK>(md)};
#endif
    while (controller->run()){}

}
