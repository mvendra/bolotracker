
#ifndef __BOLOTRACKER_H__
#define __BOLOTRACKER_H__

#include "database.h"

class BoloTracker final {

public:

    BoloTracker(const std::string &db_params);
    ~BoloTracker();

    BoloTracker(const BoloTracker&) = delete;
    BoloTracker(BoloTracker&&) = delete;
    BoloTracker& operator=(const BoloTracker&) = delete;
    BoloTracker& operator=(BoloTracker&&) = delete;

    void run();

private:

    Database db;

};

#endif // __BOLOTRACKER_H__
