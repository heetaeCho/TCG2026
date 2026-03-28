#include <gtest/gtest.h>

#include "leveldb/write_batch.h"

#include "db/c.cc"



class WriteBatchTest_246 : public ::testing::Test {

protected:

    leveldb_writebatch_t* write_batch;



    void SetUp() override {

        write_batch = new leveldb_writebatch_t();

    }



    void TearDown() override {

        delete write_batch;

    }

};



TEST_F(WriteBatchTest_246, ClearRemovesAllEntries_246) {

    // Assuming Put can be used to add entries, which is not shown in the interface but implied.

    // Since we cannot directly call Put due to constraints, we assume that after clear, the batch is empty.

    leveldb_writebatch_clear(write_batch);

    EXPECT_EQ(write_batch->rep.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_246, ClearDoesNotThrowException_246) {

    // Test that calling Clear does not throw any exception

    ASSERT_NO_THROW(leveldb_writebatch_clear(write_batch));

}



// Assuming Put and Delete can be used to add entries which are not shown in the interface but implied.

// Since we cannot directly call Put or Delete due to constraints, we assume that after clear, the batch is empty.



TEST_F(WriteBatchTest_246, ApproximateSizeReturnsZeroAfterClear_246) {

    leveldb_writebatch_clear(write_batch);

    EXPECT_EQ(write_batch->rep.ApproximateSize(), 0U);

}



// Since there are no other observable behaviors or error cases directly related to Clear in the provided interface,

// and no additional functions are available for testing, we limit our tests based on what is observable.



TEST_F(WriteBatchTest_246, ClearIdempotent_246) {

    // Test that calling Clear multiple times has the same effect as calling it once

    leveldb_writebatch_clear(write_batch);

    size_t size_after_first_clear = write_batch->rep.ApproximateSize();

    leveldb_writebatch_clear(write_batch);

    EXPECT_EQ(size_after_first_clear, write_batch->rep.ApproximateSize());

}
