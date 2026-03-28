#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class LevelDBOptionsTest_265 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_options_create();

    }



    void TearDown() override {

        leveldb_options_destroy(options);

    }



    leveldb_options_t* options;

};



TEST_F(LevelDBOptionsTest_265, DefaultMaxFileSize_265) {

    size_t max_file_size = options->rep.max_file_size;

    EXPECT_EQ(max_file_size, 2 * 1024 * 1024);

}



TEST_F(LevelDBOptionsTest_265, SetMaxFileSize_ValidValue_265) {

    size_t new_max_file_size = 10 * 1024 * 1024;

    leveldb_options_set_max_file_size(options, new_max_file_size);

    EXPECT_EQ(options->rep.max_file_size, new_max_file_size);

}



TEST_F(LevelDBOptionsTest_265, SetMaxFileSize_BoundaryValue_265) {

    size_t boundary_value = 0;

    leveldb_options_set_max_file_size(options, boundary_value);

    EXPECT_EQ(options->rep.max_file_size, boundary_value);

}
