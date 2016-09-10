
#include "database.h"

Database::Database(const std::string &connection):sqlite_con{0}{
    (void)connection; // mvdebug
}

Database::~Database(){
}
