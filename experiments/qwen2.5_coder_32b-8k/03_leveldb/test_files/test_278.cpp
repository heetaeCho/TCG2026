#include <gtest/gtest.h>

#include "db/c.cc"



// Test fixture for leveldb_writeoptions_destroy function.

class WriteOptionsDestroyTest_278 : public ::testing::Test {

protected:

    void SetUp() override {

        write_options = new leveldb_writeoptions_t();

    }



    void TearDown() override {

        // Do not delete here as it will be tested in the test case.

    }



    leveldb_writeoptions_t* write_options;

};



// Test normal operation of leveldb_writeoptions_destroy

TEST_F(WriteOptionsDestroyTest_278, NormalOperation_278) {

    EXPECT_NE(write_options, nullptr);

    leveldb_writeoptions_destroy(write_options);

    // No assertion can be made directly on the pointer after deletion.

}



// Test boundary condition with null pointer

TEST_F(WriteOptionsDestroyTest_278, NullPointer_278) {

    leveldb_writeoptions_t* null_opt = nullptr;

    EXPECT_NO_THROW(leveldb_writeoptions_destroy(null_opt));

}
