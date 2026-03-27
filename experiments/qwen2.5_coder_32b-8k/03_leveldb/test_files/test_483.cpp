#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Invoke;



class MockHandler : public Handler {

public:

    MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

    MOCK_METHOD(void, Delete, (const Slice& key), (override));

};



class WriteBatchTest_483 : public ::testing::Test {

protected:

    WriteBatch write_batch;

};



TEST_F(WriteBatchTest_483, ClearEmptiesBatch_483) {

    write_batch.Put(Slice("key"), Slice("value"));

    write_batch.Clear();

    EXPECT_EQ(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_483, PutIncreasesApproximateSize_483) {

    size_t initial_size = write_batch.ApproximateSize();

    write_batch.Put(Slice("key"), Slice("value"));

    EXPECT_GT(write_batch.ApproximateSize(), initial_size);

}



TEST_F(WriteBatchTest_483, DeleteIncreasesApproximateSize_483) {

    size_t initial_size = write_batch.ApproximateSize();

    write_batch.Delete(Slice("key"));

    EXPECT_GT(write_batch.ApproximateSize(), initial_size);

}



TEST_F(WriteBatchTest_483, AppendMergesBatches_483) {

    WriteBatch other_batch;

    other_batch.Put(Slice("key"), Slice("value"));

    size_t initial_size = write_batch.ApproximateSize();

    write_batch.Append(other_batch);

    EXPECT_GT(write_batch.ApproximateSize(), initial_size);

}



TEST_F(WriteBatchTest_483, IterateCallsHandlerPut_483) {

    MockHandler handler;

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);



    EXPECT_CALL(handler, Put(key, value)).Times(1);

    write_batch.Iterate(&handler);

}



TEST_F(WriteBatchTest_483, IterateCallsHandlerDelete_483) {

    MockHandler handler;

    Slice key("key");

    write_batch.Delete(key);



    EXPECT_CALL(handler, Delete(key)).Times(1);

    write_batch.Iterate(&handler);

}



TEST_F(WriteBatchTest_483, ClearAfterAppendDoesNotCrash_483) {

    WriteBatch other_batch;

    other_batch.Put(Slice("key"), Slice("value"));

    write_batch.Append(other_batch);

    write_batch.Clear();

    EXPECT_NO_THROW(write_batch.Iterate(nullptr));

}
