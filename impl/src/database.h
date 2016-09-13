
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>

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

    void exec(const std::string &sql);
    void exec(const std::string &sql, std::vector<std::vector<std::string>> &result);

private:

    void bootstrap();
    bool read_row(sqlite3_stmt *statement, std::vector<std::string> &columns);

    sqlite3 *sqlite_con;

};

#endif // __DATABASE_H__
