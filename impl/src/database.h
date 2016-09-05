
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>

#include "sqlite3.h"

// this class is the system's Database Access Object

class Database final {

public:

    Database(const std::string &connection);
    ~Database();

    Database(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&) = delete;

private:

};

#endif // __DATABASE_H__
