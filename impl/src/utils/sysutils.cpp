
#include "sysutils.h"

#include "managedbuffer.h"

#include "exceptions/ex_notreached.h"
#include "exceptions/ex_unsupported_platform.h"
#include "exceptions/ex_utils_error.h"

#include <sys/stat.h>

#include <fstream>
#include <cstdio>

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

bool getFileContents(const std::string &fn, std::string &contents){

    std::ifstream file;
    file.open(fn.c_str());
    if (!file.is_open()){
        return false;
    }

    file.seekg (0, file.end);
    unsigned int length = file.tellg();
    file.seekg (0, file.beg);

    ManagedBuffer mb { length+1 };
    file.read(mb.buffer, mb.length);
    contents = mb.buffer;

    return true;
}

bool fileExists(const std::string &fn){
    // thanks to http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
    struct stat buffer;   
    return (stat (fn.c_str(), &buffer) == 0);
}

void fileDelete(const std::string &fn){
    int r = std::remove(fn.c_str());
    (void)r;
}
