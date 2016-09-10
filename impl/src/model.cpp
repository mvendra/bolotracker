
#include "model.h"

Model::Model(const std::string &dbpath):db{dbpath}{
    (void)dbpath; // mvdebug
}

Model::~Model(){
}

bool Model::add_new_investor(const std::string& name, const std::string &email,
                             const std::string& desc, const DateHelper &date_inclusion){

    (void)name; // mvdebug
    (void)email; // mvdebug
    (void)desc; // mvdebug
    (void)date_inclusion; // mvdebug

    // mvtodo: finish this
    return false; // mvdebug

}
