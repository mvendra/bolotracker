
#ifndef __SYSUTILS_H__
#define __SYSUTILS_H__

#include <string>

std::string getAppWorkingDir();
std::string getSysTmpDir();
bool getFileContents(const std::string &, std::string&);
bool fileExists(const std::string &);
bool fileDelete(const std::string &);

#endif // __SYSUTILS_H__
