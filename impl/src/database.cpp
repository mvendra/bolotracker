
#include "database.h"

#include "sqlite3.h"

Database::Database(const std::string &connection){
    (void)connection; // mvdebug
}

Database::~Database(){
}
