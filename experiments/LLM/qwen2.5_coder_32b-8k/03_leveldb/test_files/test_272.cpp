#include <gtest/gtest.h>

#include "db/c.h"



class ReadOptionsTest_272 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_readoptions_create();

    }



    void TearDown() override {

        delete options;

    }



    leveldb_readoptions_t* options;

};



TEST_F(ReadOptionsTest_272, CreateReturnsNonNullPointer_272) {

    EXPECT_NE(options, nullptr);

}



TEST_F(ReadOptionsTest_272, CreateAllocatesNewObjectEachTime_272) {

    leveldb_readoptions_t* another_options = leveldb_readoptions_create();

    EXPECT_NE(options, another_options);

    delete another_options;

}
