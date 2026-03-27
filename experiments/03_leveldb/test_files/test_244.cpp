#include <gtest/gtest.h>

#include "db/c.h"  // Assuming the header file where leveldb_writebatch_t and its functions are declared



// Test fixture class for leveldb_writebatch_t tests

class WriteBatchTest_244 : public ::testing::Test {

protected:

    void SetUp() override {

        write_batch = leveldb_writebatch_create();

    }



    void TearDown() override {

        delete write_batch;

    }



    leveldb_writebatch_t* write_batch;

};



// Test case to verify that a write batch can be created successfully

TEST_F(WriteBatchTest_244, CreateReturnsNonNullPointer_244) {

    ASSERT_NE(write_batch, nullptr);

}
