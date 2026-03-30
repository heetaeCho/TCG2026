#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/options.h"



class LeveldbOptionsTest_260 : public ::testing::Test {

protected:

    leveldb_options_t* options;



    void SetUp() override {

        options = new leveldb_options_t();

    }



    void TearDown() override {

        delete options;

    }

};



TEST_F(LeveldbOptionsTest_260, SetWriteBufferSize_ValidSize_260) {

    size_t newSize = 8 * 1024 * 1024;

    leveldb_options_set_write_buffer_size(options, newSize);

    EXPECT_EQ(options->rep.write_buffer_size, newSize);

}



TEST_F(LeveldbOptionsTest_260, SetWriteBufferSize_ZeroSize_260) {

    size_t newSize = 0;

    leveldb_options_set_write_buffer_size(options, newSize);

    EXPECT_EQ(options->rep.write_buffer_size, newSize);

}



TEST_F(LeveldbOptionsTest_260, SetWriteBufferSize_MaxSize_260) {

    size_t newSize = std::numeric_limits<size_t>::max();

    leveldb_options_set_write_buffer_size(options, newSize);

    EXPECT_EQ(options->rep.write_buffer_size, newSize);

}
