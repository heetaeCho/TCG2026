#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class LevelDBOptionsTest_263 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_options_create();

    }



    void TearDown() override {

        leveldb_options_destroy(options);

    }



    leveldb_options_t* options;

};



TEST_F(LevelDBOptionsTest_263, SetBlockSize_DefaultValue_263) {

    EXPECT_EQ(options->rep.block_size, 4 * 1024);

}



TEST_F(LevelDBOptionsTest_263, SetBlockSize_ValidSize_263) {

    size_t new_block_size = 8 * 1024;

    leveldb_options_set_block_size(options, new_block_size);

    EXPECT_EQ(options->rep.block_size, new_block_size);

}



TEST_F(LevelDBOptionsTest_263, SetBlockSize_BoundaryConditionMinimum_263) {

    size_t min_block_size = 1;

    leveldb_options_set_block_size(options, min_block_size);

    EXPECT_EQ(options->rep.block_size, min_block_size);

}



TEST_F(LevelDBOptionsTest_263, SetBlockSize_BoundaryConditionMaximum_263) {

    size_t max_block_size = std::numeric_limits<size_t>::max();

    leveldb_options_set_block_size(options, max_block_size);

    EXPECT_EQ(options->rep.block_size, max_block_size);

}
