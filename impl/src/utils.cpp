
#include "utils.h"

#include "exceptions/ex_notreached.h"
#include "exceptions/ex_unsupported_platform.h"
#include "exceptions/ex_utils_error.h"

#include <sstream>

unsigned int strToUint(const std::string &src) {
    unsigned int ret;
    std::stringstream ss(src);
    ss >> ret;
    return ret;
}

std::string uintToStr(const unsigned int num){
    std::string ret {""};
    std::stringstream ss;
    ss << num;
    ret = ss.str();
    return ret;
}

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
