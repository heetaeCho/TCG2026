#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockHandler : public Handler {

public:

    MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

    MOCK_METHOD(void, Delete, (const Slice& key), (override));

};



TEST_F(WriteBatchTest_207, AppendEmptyBatchDoesNothing_207) {

    WriteBatch batch1;

    WriteBatch batch2;

    batch1.Append(batch2);

}



TEST_F(WriteBatchTest_207, AppendNonEmptyBatchMergesOperations_207) {

    WriteBatch batch1;

    WriteBatch batch2;



    Slice key1("key1");

    Slice value1("value1");



    Slice key2("key2");

    Slice value2("value2");



    batch2.Put(key1, value1);

    batch2.Delete(key2);



    batch1.Append(batch2);



    MockHandler handler;

    EXPECT_CALL(handler, Put(key1, value1)).Times(1);

    EXPECT_CALL(handler, Delete(key2)).Times(1);



    batch1.Iterate(&handler);

}



TEST_F(WriteBatchTest_207, AppendMultipleBatches_207) {

    WriteBatch batch1;

    WriteBatch batch2;

    WriteBatch batch3;



    Slice key1("key1");

    Slice value1("value1");



    Slice key2("key2");

    Slice value2("value2");



    Slice key3("key3");

    Slice value3("value3");



    batch2.Put(key1, value1);

    batch3.Delete(key2);

    batch3.Put(key3, value3);



    batch1.Append(batch2);

    batch1.Append(batch3);



    MockHandler handler;

    EXPECT_CALL(handler, Put(key1, value1)).Times(1);

    EXPECT_CALL(handler, Delete(key2)).Times(1);

    EXPECT_CALL(handler, Put(key3, value3)).Times(1);



    batch1.Iterate(&handler);

}



TEST_F(WriteBatchTest_207, ClearEmptiesBatch_207) {

    WriteBatch batch;

    Slice key("key");

    Slice value("value");



    batch.Put(key, value);

    batch.Clear();



    MockHandler handler;

    EXPECT_CALL(handler, Put(_, _)).Times(0);

    EXPECT_CALL(handler, Delete(_)).Times(0);



    batch.Iterate(&handler);

}



TEST_F(WriteBatchTest_207, ApproximateSizeReturnsNonZeroForNonEmptyBatch_207) {

    WriteBatch batch;

    Slice key("key");

    Slice value("value");



    batch.Put(key, value);

    EXPECT_GT(batch.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_207, ApproximateSizeReturnsZeroForEmptyBatch_207) {

    WriteBatch batch;

    EXPECT_EQ(batch.ApproximateSize(), 0U);

}
