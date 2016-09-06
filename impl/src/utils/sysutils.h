
#ifndef __SYSUTILS_H__
#define __SYSUTILS_H__

#include <string>

#ifdef __linux__
#include <unistd.h>
#endif // __linux__

std::string getAppWorkingDir();

#endif // __SYSUTILS_H__
