
#ifndef __SYSUTILS_H__
#define __SYSUTILS_H__

#include <string>

#ifdef __linux__
#include <unistd.h>
#endif // __linux__

std::string getAppWorkingDir();
bool getFileContents(const std::string &, std::string&);
bool fileExists(const std::string &);
void fileDelete(const std::string &);

#endif // __SYSUTILS_H__
