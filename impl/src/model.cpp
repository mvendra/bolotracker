
#include "model.h"

#include "exceptions/ex_model_error.h"

Model::Model(const std::string &dbpath):db{dbpath}{
}

Model::~Model(){
}

void Model::add_new_investor(const std::string& name, const std::string &email,
                             const std::string& desc, const DateHelper &date_inclusion){

    if (has_investor(name)){
        EX_THROW(Ex_Model_Error, "Investor named [" + name + "] already exists. Unable to add duplicate.");
    }

    std::string sql {"INSERT INTO investors(name, email, description, date_of_inclusion) VALUES(\""};
    sql += name + "\" , \"" + email + "\", \"" + desc + "\", \"" + date_inclusion.getDateString() + "\");";
    //db.exec(sql); // mvdebug

}

bool Model::has_investor(const std::string& name){
(void)name; // mvdebug
/* mvdebug begin
    std::string errmsg;
    db.exec()
mvdebug end*/

return false; // mvdebug
}
