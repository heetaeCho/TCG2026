#include <gtest/gtest.h>

#include "leveldb/write_batch.h"



using namespace leveldb;



class WriteBatchTest_198 : public ::testing::Test {

protected:

    WriteBatch write_batch;

};



TEST_F(WriteBatchTest_198, ClearEmptiesBatch_198) {

    // Assuming Put adds data to the batch

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);

    

    size_t size_before = write_batch.ApproximateSize();

    EXPECT_GT(size_before, 0);



    write_batch.Clear();

    size_t size_after = write_batch.ApproximateSize();

    EXPECT_EQ(size_after, kHeader);

}



TEST_F(WriteBatchTest_198, ApproximateSizeReturnsCorrectSizeAfterClear_198) {

    write_batch.Clear();

    size_t size = write_batch.ApproximateSize();

    EXPECT_EQ(size, kHeader);

}



TEST_F(WriteBatchTest_198, AppendIncreasesApproximateSize_198) {

    WriteBatch another_batch;

    Slice key("key");

    Slice value("value");

    another_batch.Put(key, value);



    size_t initial_size = write_batch.ApproximateSize();

    write_batch.Append(another_batch);

    size_t final_size = write_batch.ApproximateSize();



    EXPECT_GT(final_size, initial_size);

}



TEST_F(WriteBatchTest_198, IterateCallsHandlerWithCorrectArguments_198) {

    class MockHandler : public WriteBatch::Handler {

    public:

        MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

        MOCK_METHOD(void, Delete, (const Slice& key), (override));

    };



    ::testing::StrictMock<MockHandler> handler;

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);



    EXPECT_CALL(handler, Put(key, value)).Times(1);

    write_batch.Iterate(&handler);

}



TEST_F(WriteBatchTest_198, IterateDoesNotCallHandlerOnEmptyBatch_198) {

    class MockHandler : public WriteBatch::Handler {

    public:

        MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

        MOCK_METHOD(void, Delete, (const Slice& key), (override));

    };



    ::testing::StrictMock<MockHandler> handler;



    EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

    EXPECT_CALL(handler, Delete(::testing::_)).Times(0);



    write_batch.Iterate(&handler);

}



TEST_F(WriteBatchTest_198, DeleteAddsEntryToBatch_198) {

    Slice key("key");

    write_batch.Delete(key);



    size_t size = write_batch.ApproximateSize();

    EXPECT_GT(size, kHeader);

}
