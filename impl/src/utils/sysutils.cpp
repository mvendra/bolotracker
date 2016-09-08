
#include "sysutils.h"

#include "exceptions/ex_notreached.h"
#include "exceptions/ex_unsupported_platform.h"
#include "exceptions/ex_utils_error.h"

#include <sys/stat.h>

std::string getAppWorkingDir(){

#ifdef __linux__
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        std::string r = cwd;
        return r;
    } else {
        EX_THROW(Ex_Utils_Error, "Unable to get app working dir")
    }
#else
    EX_THROW(Ex_Unsupported_Platform, "Working directory detection not implemented on this platform")
#endif

    NOTREACHED("Could not detect current working directory")

}

bool fileExists(const std::string &fn){
    // thanks to http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
    struct stat buffer;   
    return (stat (fn.c_str(), &buffer) == 0);
}
