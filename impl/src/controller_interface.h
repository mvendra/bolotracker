
#ifndef __CONTROLLER_INTERFACE_H__
#define __CONTROLLER_INTERFACE_H__

#include "model.h"

class ControllerInterface {

public:

    ControllerInterface(Model &md);
    virtual ~ControllerInterface();

    virtual bool run() = 0;

protected:


private:

    Model &model;

};

#endif // __CONTROLLER_INTERFACE_H__
