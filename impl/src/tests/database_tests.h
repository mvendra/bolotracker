
#ifndef __DATABASE_TESTS_H__
#define __DATABASE_TESTS_H__

#include "database.h"

void setup_mock_db();
bool test_database();

class DatabaseTestInternal final {

public:

    DatabaseTestInternal();
    ~DatabaseTestInternal();

    DatabaseTestInternal(const DatabaseTestInternal&) = delete;
    DatabaseTestInternal(DatabaseTestInternal&&) = delete;
    DatabaseTestInternal& operator=(const DatabaseTestInternal&) = delete;
    DatabaseTestInternal& operator=(DatabaseTestInternal&&) = delete;

    void load_test_data();

    std::string db_path;
    Database db;

};

#endif // __DATABASE_TESTS_H__
