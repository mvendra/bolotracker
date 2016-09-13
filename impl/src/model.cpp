
#include "model.h"
#include "utils/conversions.h"

#include "exceptions/ex_model_error.h"

#include <vector>

using strvec2 = std::vector<std::vector<std::string>>;

Model::Model(const std::string &dbpath):db{dbpath}{
}

Model::~Model(){
}

//////////////////////
/* WRITE OPERATIONS */
//////////////////////

void Model::add_investor(const std::string& name, const std::string &email,
                         const std::string& desc, const DateHelper &date_inclusion)
{

    // make all lowercase
    std::string name_local = name; makeStrLower(name_local);
    std::string email_local = email; makeStrLower(email_local);
    std::string desc_local = desc; makeStrLower(desc_local);

    // prevent duplicates
    if (has_investor(name_local)){
        EX_THROW(Ex_Model_Error, "Investor named [" + name_local + "] already exists. Unable to add duplicate.");
    }

    std::string sql {"INSERT INTO investors(name, email, description, date_of_inclusion) VALUES(\""};
    sql += name_local + "\" , \"" + email_local + "\", \"" + desc_local + "\", \"" + date_inclusion.getDateString() + "\");";
    db.exec(sql);

}

void Model::add_subject(const std::string& tag, const std::string &description,
                        const DateHelper &date_inclusion)
{

    std::string tag_local = tag; makeStrLower(tag_local);
    std::string description_local = description; makeStrLower(description_local);

    if (has_subject(tag_local)){
        EX_THROW(Ex_Model_Error, "Subject named [" + tag_local + "] already exists. Unable to add duplicate.");
    }

    // mvtodo: implement

    (void)tag; // mvdebug
    (void)description; // mvdebug
    (void)date_inclusion; // mvdebug

}

void Model::add_currency(const std::string& label, const std::string &description,
                         const DateHelper &date_inclusion)
{

    std::string label_local = label; makeStrLower(label_local);
    std::string description_local = description; makeStrLower(description_local);

    if (has_currency(label_local)){
        EX_THROW(Ex_Model_Error, "Currency named [" + label_local + "] already exists. Unable to add duplicate.");
    }

    // mvtodo: implement

    (void)label; // mvdebug
    (void)description; // mvdebug
    (void)date_inclusion; // mvdebug

}

void Model::add_invested_time(const unsigned int fk_investor, const unsigned int fk_currency,
                              const DateHelper &date, const std::string &description,
                              const std::string &comment, const unsigned int minutes,
                              const double price_per_unit)
{

    // mvtodo: implement

    (void)fk_investor; // mvdebug
    (void)fk_currency; // mvdebug
    (void)date; // mvdebug
    (void)description; // mvdebug
    (void)comment; // mvdebug
    (void)minutes; // mvdebug
    (void)price_per_unit; // mvdebug

}

void Model::attach_subject_to_invested_time(const unsigned int pk_invested_time, const unsigned int pk_subject){

    // mvtodo: implement

    (void)pk_invested_time; // mvdebug
    (void)pk_subject; // mvdebug

}

void Model::add_invested_asset(const unsigned int fk_investor, const unsigned int fk_currency,
                               const DateHelper &date, const std::string &short_name,
                               const std::string &description, const std::string &comment,
                               const double price)
{

    // mvtodo: implement

    (void)fk_investor; // mvdebug
    (void)fk_currency; // mvdebug
    (void)date; // mvdebug
    (void)short_name; // mvdebug
    (void)description; // mvdebug
    (void)comment; // mvdebug
    (void)price; // mvdebug

}

void Model::attach_subject_to_invested_asset(const unsigned int pk_invested_asset, const unsigned int pk_subject){

    // mvtodo: implement

    (void)pk_invested_asset; // mvdebug
    (void)pk_subject; // mvdebug

}

void Model::add_bonus(const unsigned int fk_investor, const DateHelper &date,
                      const std::string &short_name, const std::string &description,
                      const std::string &comment, const std::string &reward)
{

    // mvtodo: implement

    (void)fk_investor; // mvdebug
    (void)date; // mvdebug
    (void)short_name; // mvdebug
    (void)description; // mvdebug
    (void)comment; // mvdebug
    (void)reward; // mvdebug

}

void Model::attach_subject_to_bonus(const unsigned int pk_bonus, const unsigned int pk_subject){

    // mvtodo: implement

    (void)pk_bonus; // mvdebug
    (void)pk_subject; // mvdebug

}

void Model::add_invested_money(const unsigned int fk_investor, const unsigned int fk_currency,
                               const DateHelper &date, const std::string &short_name,
                               const std::string &description, const std::string &comment,
                               const double amount)
{

    // mvtodo: implement

    (void)fk_investor; // mvdebug
    (void)fk_currency; // mvdebug
    (void)date; // mvdebug
    (void)short_name; // mvdebug
    (void)description; // mvdebug
    (void)comment; // mvdebug
    (void)amount; // mvdebug

}

void Model::attach_subject_to_invested_money(const unsigned int pk_invested_money, const unsigned int pk_subject){

    // mvtodo: implement

    (void)pk_invested_money; // mvdebug
    (void)pk_subject; // mvdebug

}

/////////////////////
/* READ OPERATIONS */
/////////////////////

bool Model::has_investor(const std::string& name){
    bool r = has_any_helper("name", name, "pk_investor", "investors");
    return r;
}

bool Model::has_subject(const std::string& tag){
    bool r = has_any_helper("tag", tag, "pk_subject", "subjects");
    return r;
}

bool Model::has_currency(const std::string& label){
    bool r = has_any_helper("label", label, "pk_currency", "currencies");
    return r;
}

bool Model::has_any_helper(const std::string &column, const std::string &value, const std::string &pk_name, const std::string &table_name){

    std::string column_local = column; makeStrLower(column_local);
    std::string value_local = value; makeStrLower(value_local);
    std::string pk_name_local = pk_name; makeStrLower(pk_name_local);
    std::string table_name_local = table_name; makeStrLower(table_name_local);

    std::string sql = {"SELECT "};
    sql += pk_name_local + " FROM " + table_name_local + " WHERE ";
    sql += column_local + " LIKE \"" + value_local + "\";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }
    return true;

}
