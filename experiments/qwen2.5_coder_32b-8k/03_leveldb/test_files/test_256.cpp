#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/options.h"



class LevelDBOptionsTest_256 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_options_create();

    }



    void TearDown() override {

        leveldb_options_destroy(options);

    }



    leveldb_options_t* options;

};



TEST_F(LevelDBOptionsTest_256, SetErrorIfExists_DefaultValue_256) {

    EXPECT_EQ(options->rep.error_if_exists, false);

}



TEST_F(LevelDBOptionsTest_256, SetErrorIfExists_SetTrue_256) {

    leveldb_options_set_error_if_exists(options, 1);

    EXPECT_EQ(options->rep.error_if_exists, true);

}



TEST_F(LevelDBOptionsTest_256, SetErrorIfExists_SetFalse_256) {

    leveldb_options_set_error_if_exists(options, 0);

    EXPECT_EQ(options->rep.error_if_exists, false);

}



TEST_F(LevelDBOptionsTest_256, SetErrorIfExists_BoundaryValue1_256) {

    leveldb_options_set_error_if_exists(options, 1);

    EXPECT_EQ(options->rep.error_if_exists, true);

}



TEST_F(LevelDBOptionsTest_256, SetErrorIfExists_BoundaryValue0_256) {

    leveldb_options_set_error_if_exists(options, 0);

    EXPECT_EQ(options->rep.error_if_exists, false);

}
