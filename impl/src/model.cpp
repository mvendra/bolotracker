
#include "model.h"
#include "utils/conversions.h"

#include "exceptions/ex_model_error.h"

#include <vector>

using strvec2 = std::vector<std::vector<std::string>>;

Model::Model():connection{}, db{}{
}

void Model::open_database(){
    db.db_path = connection;
    db.open_database();
}

void Model::close_database(){
    db.close_database();
}

Model::Model(const std::string &conn):connection{conn}, db{connection}{
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

    std::string sql {"INSERT INTO currencies(label, description, date_of_inclusion) VALUES(\""};
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
    sql += uintToStr(fk_investor) + ", " + uintToStr(fk_currency) + ", \"" + date.getDateString() + "\", \"" + short_name_local + "\", \"";
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

bool Model::get_investor_info(const std::string &name, Investor &inv){

    std::string name_local {name}; makeStrLower(name_local);

    std::string sql {"SELECT * FROM investors WHERE name = \""};
    sql += name_local + "\";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    } else if (res.size() > 1){
        EX_THROW(Ex_Model_Error, "While getting investor info for [" + name_local + "], more than one record was returned. This is likely a duplicate.");
    }

    if (res[0].size() != 5){
        EX_THROW(Ex_Model_Error, "While getting investor info for [" + name_local + "], less than 5 columns were returned. This is likely a faulty schema.");
    }

    inv.pk_investor = strToUint(res[0][0]);
    inv.name = name;
    inv.email = res[0][2];
    inv.description = res[0][3];
    inv.date_of_inclusion.setDate(res[0][4]);

    return true;

}

bool Model::get_investor_info(const unsigned int pk_investor, Investor &inv){

    std::string sql {"SELECT * FROM investors WHERE pk_investor = "};
    sql += uintToStr(pk_investor) + ";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    } else if (res.size() > 1){
        EX_THROW(Ex_Model_Error, "While getting investor info for [" + uintToStr(pk_investor) + "], more than one record was returned. This is likely a duplicate.");
    }

    if (res[0].size() != 5){
        EX_THROW(Ex_Model_Error, "While getting investor info for [" + uintToStr(pk_investor) + "], more or less than 5 columns were returned. This is likely a faulty schema.");
    }

    inv.pk_investor = pk_investor;
    inv.name = res[0][1];
    inv.email = res[0][2];
    inv.description = res[0][3];
    inv.date_of_inclusion.setDate(res[0][4]);

    return true;

}

bool Model::get_subject_info(const std::string &tag, Subject &subj){

    std::string tag_local {tag}; makeStrLower(tag_local);

    std::string sql {"SELECT * FROM subjects WHERE tag = \""};
    sql += tag_local + "\";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    } else if (res.size() > 1){
        EX_THROW(Ex_Model_Error, "While getting subject info for [" + tag_local + "], more than one record was returned. This is likely a duplicate.");
    }

    if (res[0].size() != 4){
        EX_THROW(Ex_Model_Error, "While getting subject info for [" + tag_local + "], more or less than 4 columns were returned. This is likely a faulty schema.");
    }

    subj.pk_subject = strToUint(res[0][0]);
    subj.tag = tag;
    subj.description = res[0][2];
    subj.date_of_inclusion.setDate(res[0][3]);

    return true;

}

bool Model::get_subject_info(const unsigned int pk_subject, Subject &subj){

    std::string sql {"SELECT * FROM subjects WHERE pk_subject = "};
    sql += uintToStr(pk_subject) + ";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    } else if (res.size() > 1){
        EX_THROW(Ex_Model_Error, "While getting subject info for [" + uintToStr(pk_subject) + "], more than one record was returned. This is likely a duplicate.");
    }

    if (res[0].size() != 4){
        EX_THROW(Ex_Model_Error, "While getting subject info for [" + uintToStr(pk_subject) + "], more or less than 4 columns were returned. This is likely a faulty schema.");
    }

    subj.pk_subject = pk_subject;
    subj.tag = res[0][1];
    subj.description = res[0][2];
    subj.date_of_inclusion.setDate(res[0][3]);

    return true;

}

bool Model::get_currency_info(const std::string &label, Currency &curr){

    std::string label_local {label}; makeStrLower(label_local);

    std::string sql {"SELECT * FROM currencies WHERE label = \""};
    sql += label_local + "\";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    } else if (res.size() > 1){
        EX_THROW(Ex_Model_Error, "While getting currency info for [" + label_local + "], more than one record was returned. This is likely a duplicate.");
    }

    if (res[0].size() != 4){
        EX_THROW(Ex_Model_Error, "While getting currency info for [" + label_local + "], more or less than 4 columns were returned. This is likely a faulty schema.");
    }

    curr.pk_currency = strToUint(res[0][0]);
    curr.label = label;
    curr.description = res[0][2];
    curr.date_of_inclusion.setDate(res[0][3]);

    return true;

}

bool Model::get_currency_info(const unsigned int pk_currency, Currency &curr){

    std::string sql {"SELECT * FROM currencies WHERE pk_currency = "};
    sql += uintToStr(pk_currency) + ";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    } else if (res.size() > 1){
        EX_THROW(Ex_Model_Error, "While getting currency info for [" + uintToStr(pk_currency) + "], more than one record was returned. This is likely a duplicate.");
    }

    if (res[0].size() != 4){
        EX_THROW(Ex_Model_Error, "While getting currency info for [" + uintToStr(pk_currency) + "], more or less than 4 columns were returned. This is likely a faulty schema.");
    }

    curr.pk_currency = pk_currency;
    curr.label = res[0][1];
    curr.description = res[0][2];
    curr.date_of_inclusion.setDate(res[0][3]);

    return true;

}

bool Model::has_any_helper(const std::string &column, const std::string &value, const std::string &pk_name, const std::string &table_name){

    std::string column_local {column}; makeStrLower(column_local);
    std::string value_local {value}; makeStrLower(value_local);
    std::string pk_name_local {pk_name}; makeStrLower(pk_name_local);
    std::string table_name_local {table_name}; makeStrLower(table_name_local);

    std::string sql {"SELECT "};
    sql += pk_name_local + " FROM " + table_name_local + " WHERE ";
    sql += column_local + " = \"" + value_local + "\";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }
    return true;

}

void Model::get_all_investors(std::vector<Investor> &invs){

    std::string sql {"SELECT * FROM investors;"};
    strvec2 res;
    db.exec(sql, res);

    for (auto x: res){
        Investor inv{strToUint(x[0]), x[1], x[2], x[3], x[4]};
        invs.push_back(inv);
    }

}

void Model::get_all_subjects(std::vector<Subject> &subjs){

    std::string sql {"SELECT * FROM subjects;"};
    strvec2 res;
    db.exec(sql, res);

    for (auto x: res){
        Subject subj{strToUint(x[0]), x[1], x[2], x[3]};
        subjs.push_back(subj);
    }

}

void Model::get_all_currencies(std::vector<Currency> &currs){

    std::string sql {"SELECT * FROM currencies;"};
    strvec2 res;
    db.exec(sql, res);

    for (auto x: res){
        Currency curr{strToUint(x[0]), x[1], x[2], x[3]};
        currs.push_back(curr);
    }

}

bool Model::get_invested_time_by_investor(const std::string &name, std::vector<InvestedTime> &vec_inv_time){

    std::string name_local {name}; makeStrLower(name_local);

    std::string sql {"SELECT * FROM invested_time WHERE fk_investor = (SELECT pk_investor FROM investors WHERE name = \""};
    sql += name_local + "\");";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        InvestedTime it{strToUint(x[0]), strToUint(x[1]), strToUint(x[2]), x[3], x[4], x[5], strToUint(x[6]), strToDouble(x[7])};
        vec_inv_time.push_back(it);
    }

    return true;

}

bool Model::get_invested_time_by_investor(const unsigned int pk_investor, std::vector<InvestedTime> &vec_inv_time){

    std::string sql {"SELECT * FROM invested_time WHERE fk_investor = "};
    sql += uintToStr(pk_investor);

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        InvestedTime it{strToUint(x[0]), strToUint(x[1]), strToUint(x[2]), x[3], x[4], x[5], strToUint(x[6]), strToDouble(x[7])};
        vec_inv_time.push_back(it);
    }

    return true;

}

bool Model::get_invested_time_subjects(const unsigned int pk_invested_time, std::vector<Subject> &subjs){

    std::string sql {"SELECT pk_subject, tag, description, date_of_inclusion FROM subjects INNER JOIN invested_time_subjects_link ON subjects.pk_subject = invested_time_subjects_link.fk_subject WHERE invested_time_subjects_link.fk_invested_time = "};
    sql += uintToStr(pk_invested_time) + ";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        Subject it{strToUint(x[0]), x[1], x[2], DateHelper{x[3]}};
        subjs.push_back(it);
    }

    return true;

}

bool Model::get_invested_assets_by_investor(const std::string &name, std::vector<InvestedAsset> &vec_inv_as){

    std::string name_local {name}; makeStrLower(name_local);

    std::string sql {"SELECT * FROM invested_assets WHERE fk_investor = (SELECT pk_investor FROM investors WHERE name = \""};
    sql += name_local + "\");";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        InvestedAsset it{strToUint(x[0]), strToUint(x[1]), strToUint(x[2]), x[3], x[4], x[5], x[6], strToDouble(x[7])};
        vec_inv_as.push_back(it);
    }

    return true;

}

bool Model::get_invested_assets_by_investor(const unsigned int pk_investor, std::vector<InvestedAsset> &vec_inv_as){

    std::string sql {"SELECT * FROM invested_assets WHERE fk_investor = "};
    sql += uintToStr(pk_investor);

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        InvestedAsset it{strToUint(x[0]), strToUint(x[1]), strToUint(x[2]), x[3], x[4], x[5], x[6], strToDouble(x[7])};
        vec_inv_as.push_back(it);
    }

    return true;

}

bool Model::get_invested_asset_subjects(const unsigned int pk_invested_asset, std::vector<Subject> &subjs){

    std::string sql {"SELECT pk_subject, tag, description, date_of_inclusion FROM subjects INNER JOIN invested_assets_subjects_link ON subjects.pk_subject = invested_assets_subjects_link.fk_subject WHERE invested_assets_subjects_link.fk_invested_asset = "};
    sql += uintToStr(pk_invested_asset) + ";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        Subject it{strToUint(x[0]), x[1], x[2], DateHelper{x[3]}};
        subjs.push_back(it);
    }

    return true;

}

bool Model::get_bonuses_by_investor(const std::string &name, std::vector<Bonus> &vec_bon){

    std::string name_local {name}; makeStrLower(name_local);

    std::string sql {"SELECT * FROM bonuses WHERE fk_investor = (SELECT pk_investor FROM investors WHERE name = \""};
    sql += name_local + "\");";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        Bonus it{strToUint(x[0]), strToUint(x[1]), x[2], x[3], x[4], x[5], x[6]};
        vec_bon.push_back(it);
    }

    return true;

}

bool Model::get_bonuses_by_investor(const unsigned int pk_investor, std::vector<Bonus> &vec_bon){

    std::string sql {"SELECT * FROM bonuses WHERE fk_investor = "};
    sql += uintToStr(pk_investor);

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        Bonus it{strToUint(x[0]), strToUint(x[1]), x[2], x[3], x[4], x[5], x[6]};
        vec_bon.push_back(it);
    }

    return true;

}

bool Model::get_bonus_subjects(const unsigned int pk_bonus, std::vector<Subject> &subjs){

    std::string sql {"SELECT pk_subject, tag, description, date_of_inclusion FROM subjects INNER JOIN bonuses_subjects_link ON subjects.pk_subject = bonuses_subjects_link.fk_subject WHERE bonuses_subjects_link.fk_bonus = "};
    sql += uintToStr(pk_bonus) + ";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        Subject it{strToUint(x[0]), x[1], x[2], DateHelper{x[3]}};
        subjs.push_back(it);
    }

    return true;

}

bool Model::get_invested_money_by_investor(const std::string &name, std::vector<InvestedMoney> &vec_mon){

    std::string name_local {name}; makeStrLower(name_local);

    std::string sql {"SELECT * FROM invested_money WHERE fk_investor = (SELECT pk_investor FROM investors WHERE name = \""};
    sql += name_local + "\");";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        InvestedMoney it{strToUint(x[0]), strToUint(x[1]), strToUint(x[2]), x[3], x[4], x[5], x[6], strToDouble(x[7])};
        vec_mon.push_back(it);
    }

    return true;

}

bool Model::get_invested_money_by_investor(const unsigned int pk_investor, std::vector<InvestedMoney> &vec_mon){

    std::string sql {"SELECT * FROM invested_money WHERE fk_investor = "};
    sql += uintToStr(pk_investor);

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        InvestedMoney it{strToUint(x[0]), strToUint(x[1]), strToUint(x[2]), x[3], x[4], x[5], x[6], strToDouble(x[7])};
        vec_mon.push_back(it);
    }

    return true;

}

bool Model::get_invested_money_subjects(const unsigned int pk_invested_money, std::vector<Subject> &subjs){

    std::string sql {"SELECT pk_subject, tag, description, date_of_inclusion FROM subjects INNER JOIN invested_money_subjects_link ON subjects.pk_subject = invested_money_subjects_link.fk_subject WHERE invested_money_subjects_link.fk_invested_money = "};
    sql += uintToStr(pk_invested_money) + ";";

    strvec2 res;
    db.exec(sql, res);
    if (res.size() == 0){
        return false;
    }

    for (auto x: res){
        Subject it{strToUint(x[0]), x[1], x[2], DateHelper{x[3]}};
        subjs.push_back(it);
    }

    return true;

}
