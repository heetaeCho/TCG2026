#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class LeveldbOptionsTest_264 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_options_create();

    }



    void TearDown() override {

        leveldb_options_destroy(options);

    }



    leveldb_options_t* options;

};



TEST_F(LeveldbOptionsTest_264, DefaultBlockRestartInterval_264) {

    EXPECT_EQ(options->rep.block_restart_interval, 16);

}



TEST_F(LeveldbOptionsTest_264, SetBlockRestartInterval_PositiveValue_264) {

    leveldb_options_set_block_restart_interval(options, 32);

    EXPECT_EQ(options->rep.block_restart_interval, 32);

}



TEST_F(LeveldbOptionsTest_264, SetBlockRestartInterval_ZeroValue_264) {

    leveldb_options_set_block_restart_interval(options, 0);

    EXPECT_EQ(options->rep.block_restart_interval, 0);

}



TEST_F(LeveldbOptionsTest_264, SetBlockRestartInterval_NegativeValue_264) {

    leveldb_options_set_block_restart_interval(options, -1);

    EXPECT_EQ(options->rep.block_restart_interval, -1);

}
