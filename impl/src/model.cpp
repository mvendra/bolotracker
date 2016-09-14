
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

    std::string name_local {name}; makeStrLower(name_local);
    std::string email_local {email}; //makeStrLower(email_local);
    std::string desc_local {desc}; //makeStrLower(desc_local);

    // prevent duplicates
    if (has_investor(name_local)){
        EX_THROW(Ex_Model_Error, "Investor named [" + name_local + "] already exists. Unable to add duplicate.");
    }

    std::string sql {"INSERT INTO investors(name, email, description, date_of_inclusion) VALUES(\""};
    sql += name_local + "\", \"" + email_local + "\", \"" + desc_local + "\", \"" + date_inclusion.getDateString() + "\");";
    db.exec(sql);

}

void Model::add_subject(const std::string& tag, const std::string &description,
                        const DateHelper &date_inclusion)
{

    std::string tag_local {tag}; makeStrLower(tag_local);
    std::string description_local {description}; //makeStrLower(description_local);

    if (has_subject(tag_local)){
        EX_THROW(Ex_Model_Error, "Subject named [" + tag_local + "] already exists. Unable to add duplicate.");
    }

    std::string sql {"INSERT INTO subjects(tag, description, date_of_inclusion) VALUES(\""};
    sql += tag_local + "\", \"" + description_local + "\", \"" + date_inclusion.getDateString() + "\");";
    db.exec(sql);

}

void Model::add_currency(const std::string& label, const std::string &description,
                         const DateHelper &date_inclusion)
{

    std::string label_local {label}; makeStrLower(label_local);
    std::string description_local {description}; //makeStrLower(description_local);

    if (has_currency(label_local)){
        EX_THROW(Ex_Model_Error, "Currency named [" + label_local + "] already exists. Unable to add duplicate.");
    }

    std::string sql {"INSERT INTO currency(label, description, date_of_inclusion) VALUES(\""};
    sql += label_local + "\", \"" + description_local + "\", \"" + date_inclusion.getDateString() + "\");";
    db.exec(sql);

}

void Model::add_invested_time(const unsigned int fk_investor, const unsigned int fk_currency,
                              const DateHelper &date, const std::string &description,
                              const std::string &comment, const unsigned int minutes,
                              const double price_per_unit)
{

    std::string description_local {description}; //makeStrLower(description_local);
    std::string comment_local {comment}; //makeStrLower(comment_local);

    std::string sql {"INSERT INTO invested_time(fk_investor, fk_currency, date, description, comment, minutes, price_per_unit) VALUES("};
    sql += uintToStr(fk_investor) + ", " + uintToStr(fk_currency) + ", \"" + date.getDateString() + "\", \"" + description_local + "\", \"";
    sql += comment_local + "\", " + uintToStr(minutes) + ", " + doubleToStr(price_per_unit) + ");";

    db.exec(sql);

}

void Model::attach_subject_to_invested_time(const unsigned int pk_invested_time, const unsigned int pk_subject){

    std::string sql {"INSERT INTO invested_time_subjects_link(fk_invested_time, fk_subject) VALUES("};
    sql += uintToStr(pk_invested_time) + ", " + uintToStr(pk_subject) + ");";

    db.exec(sql);

}

void Model::add_invested_asset(const unsigned int fk_investor, const unsigned int fk_currency,
                               const DateHelper &date, const std::string &short_name,
                               const std::string &description, const std::string &comment,
                               const double price)
{

    std::string short_name_local {short_name}; //makeStrLower(short_name_local);
    std::string description_local {description}; //makeStrLower(description_local);
    std::string comment_local {comment}; //makeStrLower(comment_local);

    std::string sql {"INSERT INTO invested_assets(fk_investor, fk_currency, date, short_name, description, comment, price) VALUES("};
    sql += uintToStr(fk_investor) + ", " + uintToStr(fk_currency) + ", \"" + date.getDateString() + "\", \"" + short_name_local + "\", \"";
    sql += description_local + "\", \"" + comment_local + "\", " + doubleToStr(price) + ");";

    db.exec(sql);

}

void Model::attach_subject_to_invested_asset(const unsigned int pk_invested_asset, const unsigned int pk_subject){

    std::string sql {"INSERT INTO invested_assets_subjects_link(fk_invested_asset, fk_subject) VALUES("};
    sql += uintToStr(pk_invested_asset) + ", " + uintToStr(pk_subject) + ");";

    db.exec(sql);

}

void Model::add_bonus(const unsigned int fk_investor, const DateHelper &date,
                      const std::string &short_name, const std::string &description,
                      const std::string &comment, const std::string &reward)
{

    std::string short_name_local {short_name}; //makeStrLower(short_name_local);
    std::string description_local {description}; //makeStrLower(description_local);
    std::string comment_local {comment}; //makeStrLower(comment_local);
    std::string reward_local {reward}; //makeStrLower(reward_local);

    std::string sql {"INSERT INTO bonuses(fk_investor, date, short_name, description, comment, reward) VALUES("};
    sql += uintToStr(fk_investor) + ", \"" + date.getDateString() + "\", \"" + short_name_local + "\", \"";
    sql += description_local + "\", \"" + comment_local + "\", \"" + reward_local + "\");";

    db.exec(sql);

}

void Model::attach_subject_to_bonus(const unsigned int pk_bonus, const unsigned int pk_subject){

    std::string sql {"INSERT INTO bonuses_subjects_link(fk_bonus, fk_subject) VALUES("};
    sql += uintToStr(pk_bonus) + ", " + uintToStr(pk_subject) + ");";

    db.exec(sql);

}

void Model::add_invested_money(const unsigned int fk_investor, const unsigned int fk_currency,
                               const DateHelper &date, const std::string &short_name,
                               const std::string &description, const std::string &comment,
                               const double amount)
{

    std::string short_name_local {short_name}; //makeStrLower(short_name_local);
    std::string description_local {description}; //makeStrLower(description_local);
    std::string comment_local {comment}; //makeStrLower(comment_local);

    std::string sql {"INSERT INTO invested_money(fk_investor, fk_currency, date, short_name, description, comment, amount) VALUES("};
    sql += uintToStr(fk_investor) + ", " + uintToStr(fk_currency) + ", \"" + date.getDateString() + "\", " + short_name_local + "\", \"";
    sql += description_local + "\", \"" + comment_local + "\", " + doubleToStr(amount) + ");";

    db.exec(sql);

}

void Model::attach_subject_to_invested_money(const unsigned int pk_invested_money, const unsigned int pk_subject){

    std::string sql {"INSERT INTO invested_money_subjects_link(fk_invested_money, fk_subject) VALUES("};
    sql += uintToStr(pk_invested_money) + ", " + uintToStr(pk_subject) + ");";

    db.exec(sql);

}

/////////////////////
/* READ OPERATIONS */
/////////////////////

bool Model::has_investor(const std::string& name){
    bool r {has_any_helper("name", name, "pk_investor", "investors")};
    return r;
}

bool Model::has_subject(const std::string& tag){
    bool r {has_any_helper("tag", tag, "pk_subject", "subjects")};
    return r;
}

bool Model::has_currency(const std::string& label){
    bool r {has_any_helper("label", label, "pk_currency", "currencies")};
    return r;
}

bool Model::has_any_helper(const std::string &column, const std::string &value, const std::string &pk_name, const std::string &table_name){

    std::string column_local {column}; makeStrLower(column_local);
    std::string value_local {value}; makeStrLower(value_local);
    std::string pk_name_local {pk_name}; makeStrLower(pk_name_local);
    std::string table_name_local {table_name}; makeStrLower(table_name_local);

    std::string sql {"SELECT "};
    sql += pk_name_local + " FROM " + table_name_local + " WHERE ";
    sql += column_local + " LIKE \"" + value_local + "\";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }
    return true;

}
