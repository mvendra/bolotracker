
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>

#include "sqlite3.h"

// this class is the system's Database Access Object
// this particular implementation is specific for
// sqlite 3. if it ever becomes desirable to support other
// database systems in this program, then you'd start by
// generalising this class, by creating another similar one,
// say, database_postgres, for example. also, have this class
// (and the soon-to-be-introduced postgres/mysql equivalent)
// to inherit from a common interface for the public operations
// exec(...) so it's possible to generalise/substitute
// easily the final data-access-object, for whatever
// database backend system that is intended.

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
