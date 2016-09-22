
#include "controller_interface.h"

ControllerInterface::ControllerInterface(int _argc, char *_argv[], Model &md):argc{_argc}, argv{_argv}, model{md}{
}

ControllerInterface::~ControllerInterface(){
}
