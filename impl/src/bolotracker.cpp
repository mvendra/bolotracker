
#include "bolotracker.h"
#include "model.h"
#include "tui.h"
#include "gui_fltk.h"
#include "utils/sysutils.h"

#include "exceptions/ex_base.h"
#include "exceptions/ex_invalid_file.h"

#include <memory>

#define USE_TUI
//#define USE_GUI_FLTK

BoloTracker::BoloTracker(int _argc, char *_argv[]):argc{_argc}, argv{_argv}, dbpath{get_db_path(parse_cmdline_args(_argc, _argv))}{
    // mvtodo: need to check if file exists, and is a file (and not a directory)?
}

BoloTracker::~BoloTracker(){
}

std::vector<std::string> BoloTracker::parse_cmdline_args(const int argc, char *const argv[]){

    std::vector<std::string> ret;
    std::string cmdp;
    for (int i=0; i<argc; i++){
        cmdp = argv[i];
        ret.push_back(cmdp);
    }
    return ret;

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

// micro ad-hoc inline factory
#if defined(USE_TUI)
    std::unique_ptr<ControllerInterface> controller {std::make_unique<Tui>(argc, argv, md)};
#elif defined(USE_GUI_FLTK)
    std::unique_ptr<ControllerInterface> controller {std::make_unique<Gui_FLTK>(argc, argv, md)};
#endif

    while (controller->run()){}

}
