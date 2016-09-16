
#include "tests/database_tests.h"

#include "testforecho.h"

bool test_database(){

    bool total {true};

    // mvtodo: use databasetestinternal class to manage sqlite access, and physical
    // file lifetime (i.e. delete it from the filesystem after we are done testing)
    // mvtodo: consider using /tmp for testing

    

    return total;

}

DatabaseTestInternal::DatabaseTestInternal():
db_path{"/tmp/test.db"},
db{db_path}
{
// mvtodo: chicken or egg problem here. need to remove db_path if it already exists, so
// that db will re-create itself with bootstrap(). or make bootstrap callable, and let
// Database allow external calls for resetting. (sounds better. its the equivalent
// of a DROP ALL, and its specific to sqlite.
}

DatabaseTestInternal::~DatabaseTestInternal(){
    // mvtodo: remove db_path if it exists
}

DatabaseTestInternal::load_test_data(){
}
