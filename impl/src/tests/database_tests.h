
#ifndef __DATABASE_TESTS_H__
#define __DATABASE_TESTS_H__

#include "database.h"

unsigned int test_database();

class DatabaseTestInternal final {

    // you are not supposed to reuse this object from test to test!
    // this is meant to be explicitly a fire-and-forget, stay-clean
    // wrapper

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
