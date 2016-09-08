
#ifndef __MODEL_H__
#define __MODEL_H__

// business rules class

#include "utils/datehelper.h"

#include <string>

class Model final {

public:

    Model(const std::string &dbpath);
    ~Model();

    Model(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) = delete;

    // INVESTORS
    bool add_new_investor(const std::string& name, const std::string &email,
                          const std::string& desc, const DateHelper &date_inclusion);

    // SUBJECTS

    // CURRENCIES

private:

};

#endif // __MODEL_H__
