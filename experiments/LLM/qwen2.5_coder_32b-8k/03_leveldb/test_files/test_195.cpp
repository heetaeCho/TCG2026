#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



using namespace leveldb;

using ::testing::Return;



class WriteBatchTest_195 : public ::testing::Test {

protected:

    WriteBatch batch;

};



TEST_F(WriteBatchTest_195, PutIncreasesCount_195) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_195, DeleteIncreasesCount_195) {

    size_t initial_count = WriteBatchInternal::Count(&batch);

    batch.Delete(Slice("key"));

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_195, ClearResetsCount_195) {

    batch.Put(Slice("key"), Slice("value"));

    batch.Clear();

    EXPECT_EQ(WriteBatchInternal::Count(&batch), 0);

}



TEST_F(WriteBatchTest_195, ApproximateSizeNonZeroAfterPut_195) {

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_GT(batch.ApproximateSize(), 0);

}



TEST_F(WriteBatchTest_195, AppendIncreasesCount_195) {

    WriteBatch source;

    source.Put(Slice("key"), Slice("value"));

    size_t initial_count = WriteBatchInternal::Count(&batch);

    batch.Append(source);

    EXPECT_EQ(WriteBatchInternal::Count(&batch), initial_count + 1);

}



TEST_F(WriteBatchTest_195, ContentsReturnsValidSlice_195) {

    batch.Put(Slice("key"), Slice("value"));

    Slice contents = WriteBatchInternal::Contents(&batch);

    EXPECT_FALSE(contents.empty());

}



TEST_F(WriteBatchTest_195, ByteSizeMatchesApproximateSize_195) {

    batch.Put(Slice("key"), Slice("value"));

    EXPECT_EQ(WriteBatchInternal::ByteSize(&batch), batch.ApproximateSize());

}



// Assuming Handler is a class with a method Handle that returns Status

class MockHandler : public WriteBatch::Handler {

public:

    MOCK_METHOD3(Handle, Status(uint32_t, const Slice&, const Slice&));

};



TEST_F(WriteBatchTest_195, IterateCallsHandler_195) {

    MockHandler handler;

    EXPECT_CALL(handler, Handle(_, _, _)).WillOnce(Return(Status::OK()));

    batch.Put(Slice("key"), Slice("value"));

    Status status = batch.Iterate(&handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_195, IterateWithEmptyBatchDoesNotCallHandler_195) {

    MockHandler handler;

    EXPECT_CALL(handler, Handle(_, _, _)).Times(0);

    Status status = batch.Iterate(&handler);

    EXPECT_TRUE(status.ok());

}
