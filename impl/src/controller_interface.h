
#ifndef __CONTROLLER_INTERFACE_H__
#define __CONTROLLER_INTERFACE_H__

#include "model.h"

#ifdef __GNUC__
#pragma GCC system_header // disabling error-triggering warnings
#endif

class ControllerInterface {

public:

    ControllerInterface(int _argc, char *_argv[], Model &md);
    virtual ~ControllerInterface();

    virtual bool run() = 0;

protected:

    int argc;
    char **argv;
    Model &model;

};

#endif // __CONTROLLER_INTERFACE_H__
