#include <gtest/gtest.h>

#include "leveldb/write_batch.h"

#include "leveldb/status.h"



using namespace leveldb;



class MockHandler : public Handler {

public:

    MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

    MOCK_METHOD(void, Delete, (const Slice& key), (override));

};



class WriteBatchTest_199 : public ::testing::Test {

protected:

    WriteBatch write_batch;

    MockHandler mock_handler;



    static const size_t kSmallValueSize = 10;

    static const size_t kLargeValueSize = 1024;

    static const Slice kKey1;

    static const Slice kKey2;

    static const Slice kValue1;

    static const Slice kValue2;

};



const Slice WriteBatchTest_199::kKey1("key1");

const Slice WriteBatchTest_199::kKey2("key2");

const Slice WriteBatchTest_199::kValue1(std::string(kSmallValueSize, 'a'));

const Slice WriteBatchTest_199::kValue2(std::string(kLargeValueSize, 'b'));



TEST_F(WriteBatchTest_199, ApproximateSizeIsZeroInitially_199) {

    EXPECT_EQ(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_199, PutIncreasesApproximateSize_199) {

    write_batch.Put(kKey1, kValue1);

    EXPECT_GT(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_199, DeleteIncreasesApproximateSize_199) {

    write_batch.Delete(kKey1);

    EXPECT_GT(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_199, ClearResetsApproximateSize_199) {

    write_batch.Put(kKey1, kValue1);

    write_batch.Clear();

    EXPECT_EQ(write_batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_199, AppendIncreasesApproximateSize_199) {

    WriteBatch another_batch;

    another_batch.Put(kKey2, kValue2);

    size_t original_size = write_batch.ApproximateSize();

    write_batch.Append(another_batch);

    EXPECT_GT(write_batch.ApproximateSize(), original_size);

}



TEST_F(WriteBatchTest_199, IterateCallsPutOnHandler_199) {

    write_batch.Put(kKey1, kValue1);

    EXPECT_CALL(mock_handler, Put(Eq(kKey1), Eq(kValue1)));

    write_batch.Iterate(&mock_handler);

}



TEST_F(WriteBatchTest_199, IterateCallsDeleteOnHandler_199) {

    write_batch.Delete(kKey2);

    EXPECT_CALL(mock_handler, Delete(Eq(kKey2)));

    write_batch.Iterate(&mock_handler);

}



TEST_F(WriteBatchTest_199, IterateWithMultipleOperations_199) {

    write_batch.Put(kKey1, kValue1);

    write_batch.Delete(kKey2);

    EXPECT_CALL(mock_handler, Put(Eq(kKey1), Eq(kValue1)));

    EXPECT_CALL(mock_handler, Delete(Eq(kKey2)));

    write_batch.Iterate(&mock_handler);

}



TEST_F(WriteBatchTest_199, IterateWithEmptyBatchDoesNothing_199) {

    EXPECT_CALL(mock_handler, Put(_, _)).Times(0);

    EXPECT_CALL(mock_handler, Delete(_)).Times(0);

    write_batch.Iterate(&mock_handler);

}
