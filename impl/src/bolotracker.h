
#ifndef __BOLOTRACKER_H__
#define __BOLOTRACKER_H__

#include <vector>
#include <string>

class BoloTracker final {

public:

    BoloTracker(const std::vector<std::string> &cmdline_params);
    ~BoloTracker();

    BoloTracker(const BoloTracker&) = delete;
    BoloTracker(BoloTracker&&) = delete;
    BoloTracker& operator=(const BoloTracker&) = delete;
    BoloTracker& operator=(BoloTracker&&) = delete;

    void run();

private:

    std::string get_db_path(const std::vector<std::string> &cmdline_params);

};

#endif // __BOLOTRACKER_H__
