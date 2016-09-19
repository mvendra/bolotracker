
#ifndef __MODEL_H__
#define __MODEL_H__

// business rules class

#include "utils/datehelper.h"
#include "database.h"
#include "dataobjects/dataobjects.h"

#include <string>
#include <vector>

class Model final {

public:

    Model(const std::string &conn);
    ~Model();

    Model(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) = delete;

    //////////////////////
    /* WRITE OPERATIONS */
    //////////////////////

    // basic, freestanding tables
    void add_investor(const std::string& name, const std::string &email,
                      const std::string& desc, const DateHelper &date_inclusion);

    void add_subject(const std::string& tag, const std::string &description,
                     const DateHelper &date_inclusion);

    void add_currency(const std::string& label, const std::string &description,
                      const DateHelper &date_inclusion);

    // invested time
    void add_invested_time(const std::string &investor_name, const std::string &currency_label,
                           const DateHelper &date, const std::string &description,
                           const std::string &comment, const unsigned int minutes,
                           const double price_per_unit);

    void add_invested_time(const unsigned int fk_investor, const unsigned int fk_currency,
                           const DateHelper &date, const std::string &description,
                           const std::string &comment, const unsigned int minutes,
                           const double price_per_unit);

    void attach_subject_to_invested_time(const unsigned int pk_invested_time, const std::string &subject_tag);

    void attach_subject_to_invested_time(const unsigned int pk_invested_time, const unsigned int pk_subject);

    // invested assets
    void add_invested_asset(const std::string &investor_name, const std::string &currency_label,
                            const DateHelper &date, const std::string &short_name,
                            const std::string &description, const std::string &comment,
                            const double price);

    void add_invested_asset(const unsigned int fk_investor, const unsigned int fk_currency,
                            const DateHelper &date, const std::string &short_name,
                            const std::string &description, const std::string &comment,
                            const double price);

    void attach_subject_to_invested_asset(const unsigned int pk_invested_asset, const std::string &subject_tag);

    void attach_subject_to_invested_asset(const unsigned int pk_invested_asset, const unsigned int pk_subject);

    // bonuses
    void add_bonus(const std::string &investor_name, const DateHelper &date,
                   const std::string &short_name, const std::string &description,
                   const std::string &comment, const std::string &reward);

    void add_bonus(const unsigned int fk_investor, const DateHelper &date,
                   const std::string &short_name, const std::string &description,
                   const std::string &comment, const std::string &reward);

    void attach_subject_to_bonus(const unsigned int pk_bonus, const std::string &subject_tag);

    void attach_subject_to_bonus(const unsigned int pk_bonus, const unsigned int pk_subject);

    // invested money
    void add_invested_money(const std::string &investor_name, const std::string &currency_label,
                            const DateHelper &date, const std::string &short_name,
                            const std::string &description, const std::string &comment,
                            const double amount);

    void add_invested_money(const unsigned int fk_investor, const unsigned int fk_currency,
                            const DateHelper &date, const std::string &short_name,
                            const std::string &description, const std::string &comment,
                            const double amount);

    void attach_subject_to_invested_money(const unsigned int pk_invested_money, const std::string &subject_tag);

    void attach_subject_to_invested_money(const unsigned int pk_invested_money, const unsigned int pk_subject);

    /////////////////////
    /* READ OPERATIONS */
    /////////////////////

    bool has_investor(const std::string& name);
    bool has_subject(const std::string& tag);
    bool has_currency(const std::string& label);

    // READ INDIVIDUAL ROWS
    // returns false is no error happens, but there is no such name

    // investors
    bool get_investor_info(const std::string &name, Investor &inv);
    bool get_investor_info(const unsigned int pk_investor, Investor &inv);

    // subjects
    bool get_subject_info(const std::string &tag, Subject &subj);
    bool get_subject_info(const unsigned int pk_subject, Subject &subj);

    // currencies
    bool get_currency_info(const std::string &label, Currency &curr);
    bool get_currency_info(const unsigned int pk_currency, Currency &curr);

    // invested time
    bool get_invested_time_by_investor(const std::string &name, std::vector<InvestedTime> &vec_inv_time);
    bool get_invested_time_by_investor(const unsigned int pk_investor, std::vector<InvestedTime> &vec_inv_time);
    bool get_invested_time_subjects(const unsigned int pk_invested_time, std::vector<Subject> &subjs);

    // invested assets
    bool get_invested_assets_by_investor(const std::string &name, std::vector<InvestedAsset> &vec_inv_as);
    bool get_invested_assets_by_investor(const unsigned int pk_investor, std::vector<InvestedAsset> &vec_inv_as);
    bool get_invested_asset_subjects(const unsigned int pk_invested_asset, std::vector<Subject> &subjs);

    // bonuses
    bool get_bonuses_by_investor(const std::string &name, std::vector<Bonus> &vec_bon);
    bool get_bonuses_by_investor(const unsigned int pk_investor, std::vector<Bonus> &vec_bon);
    bool get_bonus_subjects(const unsigned int pk_bonus, std::vector<Subject> &subjs);

    // invested money
    bool get_invested_money_by_investor(const std::string &name, std::vector<InvestedMoney> &vec_mon);
    bool get_invested_money_by_investor(const unsigned int pk_investor, std::vector<InvestedMoney> &vec_mon);
    bool get_invested_money_subjects(const unsigned int pk_invested_money, std::vector<Subject> &subjs);

    // READ LISTS OF ROWS
    void get_all_investors(std::vector<Investor> &invs);
    void get_all_subjects(std::vector<Subject> &subjs);
    void get_all_currencies(std::vector<Currency> &currs);

    ///////////////////////
    /* DELETE OPERATIONS */
    ///////////////////////

    // delete operations are still being considered.
    // they may not be needed at all. or rather, not wanted at all.
    // keeping history is important.

private:
    friend class ModelTestInternal;

    Model(); // deferred full construction only available to tester modules (friend classes)

    void open_database();
    void close_database();

    std::string connection;
    Database db;

    bool has_any_helper(const std::string &column, const std::string &value, const std::string &pk_name, const std::string &table_name);
    unsigned int get_pk_from_unique(const std::string &table, const std::string &pk_handle, const std::string &unique_handle, const std::string &unique_value);
    unsigned int get_pk_investor(const std::string &name);
    unsigned int get_pk_subject(const std::string &tag);
    unsigned int get_pk_currency(const std::string &label);

};

#endif // __MODEL_H__
