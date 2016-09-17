
#ifndef __MODEL_TESTS_H__
#define __MODEL_TESTS_H__

#include "model.h"

bool test_model();

class ModelTestInternal final {

public:

    ModelTestInternal();
    ~ModelTestInternal();

    ModelTestInternal(const ModelTestInternal&) = delete;
    ModelTestInternal(ModelTestInternal&&) = delete;
    ModelTestInternal& operator=(const ModelTestInternal&) = delete;
    ModelTestInternal& operator=(ModelTestInternal&&) = delete;

    void load_test_data();

    std::string connection;
    Model model;

};

#endif // __MODEL_TESTS_H__
