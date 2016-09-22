
#ifndef __BOLOTRACKER_H__
#define __BOLOTRACKER_H__

#include <vector>
#include <string>

class BoloTracker final {

public:

    BoloTracker(int argc, char *argv[]);
    ~BoloTracker();

    BoloTracker(const BoloTracker&) = delete;
    BoloTracker(BoloTracker&&) = delete;
    BoloTracker& operator=(const BoloTracker&) = delete;
    BoloTracker& operator=(BoloTracker&&) = delete;

    void run();

private:

    std::vector<std::string> parse_cmdline_args(const int argc, char *const argv[]);
    std::string get_db_path(const std::vector<std::string> &cmdline_params);

    int argc;
    char **argv;
    std::string dbpath;


};

#endif // __BOLOTRACKER_H__
