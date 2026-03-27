#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class LevelDBOptionsTest_261 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_options_create();

    }



    void TearDown() override {

        leveldb_options_destroy(options);

    }



    leveldb_options_t* options;

};



TEST_F(LevelDBOptionsTest_261, SetMaxOpenFiles_DefaultValue_261) {

    int default_value = 1000; // From the known dependencies

    EXPECT_EQ(options->rep.max_open_files, default_value);

}



TEST_F(LevelDBOptionsTest_261, SetMaxOpenFiles_NormalOperation_261) {

    int new_value = 500;

    leveldb_options_set_max_open_files(options, new_value);

    EXPECT_EQ(options->rep.max_open_files, new_value);

}



TEST_F(LevelDBOptionsTest_261, SetMaxOpenFiles_BoundaryCondition_Zero_261) {

    int boundary_value = 0;

    leveldb_options_set_max_open_files(options, boundary_value);

    EXPECT_EQ(options->rep.max_open_files, boundary_value);

}



TEST_F(LevelDBOptionsTest_261, SetMaxOpenFiles_BoundaryCondition_Negative_261) {

    int negative_value = -1;

    leveldb_options_set_max_open_files(options, negative_value);

    EXPECT_EQ(options->rep.max_open_files, negative_value);

}
