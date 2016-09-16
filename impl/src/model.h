
#ifndef __MODEL_H__
#define __MODEL_H__

// business rules class

#include "utils/datehelper.h"
#include "database.h"

#include <string>

class Model final {

public:

    Model(const std::string &dbpath);
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
    void add_invested_time(const unsigned int fk_investor, const unsigned int fk_currency,
                           const DateHelper &date, const std::string &description,
                           const std::string &comment, const unsigned int minutes,
                           const double price_per_unit);

    void attach_subject_to_invested_time(const unsigned int pk_invested_time, const unsigned int pk_subject);

    // invested assets
    void add_invested_asset(const unsigned int fk_investor, const unsigned int fk_currency,
                            const DateHelper &date, const std::string &short_name,
                            const std::string &description, const std::string &comment,
                            const double price);

    void attach_subject_to_invested_asset(const unsigned int pk_invested_asset, const unsigned int pk_subject);

    // bonuses
    void add_bonus(const unsigned int fk_investor, const DateHelper &date,
                   const std::string &short_name, const std::string &description,
                   const std::string &comment, const std::string &reward);

    void attach_subject_to_bonus(const unsigned int pk_bonus, const unsigned int pk_subject);

    // invested money
    void add_invested_money(const unsigned int fk_investor, const unsigned int fk_currency,
                            const DateHelper &date, const std::string &short_name,
                            const std::string &description, const std::string &comment,
                            const double amount);

    void attach_subject_to_invested_money(const unsigned int pk_invested_money, const unsigned int pk_subject);

    /////////////////////
    /* READ OPERATIONS */
    /////////////////////

    bool has_investor(const std::string& name);
    bool has_subject(const std::string& tag);
    bool has_currency(const std::string& label);

    bool get_investor_info(const std::string &name,
                           unsigned int &pk,
                           std::string &email,
                           std::string &description,
                           DateHelper &date_of_inclusion);

    bool get_investor_info(const unsigned int pk,
                           std::string &name,
                           std::string &email,
                           std::string &description,
                           DateHelper &date_of_inclusion);

    bool get_subject_info(const std::string &tag,
                          unsigned int &pk,
                          std::string &description,
                          DateHelper &date_of_inclusion);

    bool get_subject_info(const unsigned int pk,
                          std::string &tag,
                          std::string &description,
                          DateHelper &date_of_inclusion);

    bool get_currency_info(const std::string &label,
                           unsigned int &pk,
                           std::string &description,
                           DateHelper &date);

    bool get_currency_info(const unsigned int pk,
                           const std::string &label,
                           std::string &description,
                           DateHelper &date);

    ///////////////////////
    /* DELETE OPERATIONS */
    ///////////////////////

    // delete operations are still being considered.
    // they may not be needed at all. or rather, not wanted at all.
    // keeping history is important.

private:

    bool has_any_helper(const std::string &column, const std::string &value, const std::string &pk_name, const std::string &table_name);

    Database db;

};

#endif // __MODEL_H__
