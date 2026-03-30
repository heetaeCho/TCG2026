#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class WriteBatchTest_203 : public ::testing::Test {

protected:

    WriteBatch writeBatch;

};



TEST_F(WriteBatchTest_203, PutIncreasesCount_203) {

    int initialCount = WriteBatchInternal::Count(&writeBatch);

    writeBatch.Put(Slice("key"), Slice("value"));

    EXPECT_EQ(WriteBatchInternal::Count(&writeBatch), initialCount + 1);

}



TEST_F(WriteBatchTest_203, DeleteIncreasesCount_203) {

    int initialCount = WriteBatchInternal::Count(&writeBatch);

    writeBatch.Delete(Slice("key"));

    EXPECT_EQ(WriteBatchInternal::Count(&writeBatch), initialCount + 1);

}



TEST_F(WriteBatchTest_203, ClearResetsCount_203) {

    writeBatch.Put(Slice("key"), Slice("value"));

    writeBatch.Clear();

    EXPECT_EQ(WriteBatchInternal::Count(&writeBatch), 0);

}



TEST_F(WriteBatchTest_203, ApproximateSizeNonZeroAfterPut_203) {

    writeBatch.Put(Slice("key"), Slice("value"));

    EXPECT_GT(writeBatch.ApproximateSize(), 0U);

}



TEST_F(WriteBatchTest_203, AppendIncreasesCount_203) {

    WriteBatch anotherBatch;

    anotherBatch.Put(Slice("key"), Slice("value"));

    int initialCount = WriteBatchInternal::Count(&writeBatch);

    writeBatch.Append(anotherBatch);

    EXPECT_EQ(WriteBatchInternal::Count(&writeBatch), initialCount + 1);

}



TEST_F(WriteBatchTest_203, IterateWithHandlerCallsHandler_203) {

    class MockHandler : public WriteBatch::Handler {

    public:

        MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

        MOCK_METHOD(void, Delete, (const Slice& key), (override));

    };



    MockHandler mockHandler;

    writeBatch.Put(Slice("key"), Slice("value"));

    EXPECT_CALL(mockHandler, Put(Slice("key"), Slice("value")));

    writeBatch.Iterate(&mockHandler);

}



TEST_F(WriteBatchTest_203, IterateWithEmptyBatchDoesNotCallHandler_203) {

    class MockHandler : public WriteBatch::Handler {

    public:

        MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

        MOCK_METHOD(void, Delete, (const Slice& key), (override));

    };



    MockHandler mockHandler;

    EXPECT_CALL(mockHandler, Put(_, _)).Times(0);

    EXPECT_CALL(mockHandler, Delete(_)).Times(0);

    writeBatch.Iterate(&mockHandler);

}



TEST_F(WriteBatchTest_203, SequenceNumberInitiallyZero_203) {

    EXPECT_EQ(WriteBatchInternal::Sequence(&writeBatch), 0U);

}



TEST_F(WriteBatchTest_203, SetAndRetrieveSequenceNumber_203) {

    WriteBatchInternal::SetSequence(&writeBatch, 12345U);

    EXPECT_EQ(WriteBatchInternal::Sequence(&writeBatch), 12345U);

}
