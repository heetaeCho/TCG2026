#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



using namespace leveldb;

using ::testing::Return;



class WriteBatchTest_202 : public ::testing::Test {

protected:

    WriteBatch writeBatch;

};



TEST_F(WriteBatchTest_202, PutIncreasesCount_202) {

    int initialCount = WriteBatchInternal::Count(&writeBatch);

    Slice key("key");

    Slice value("value");

    writeBatch.Put(key, value);

    int finalCount = WriteBatchInternal::Count(&writeBatch);

    EXPECT_EQ(finalCount, initialCount + 1);

}



TEST_F(WriteBatchTest_202, DeleteIncreasesCount_202) {

    int initialCount = WriteBatchInternal::Count(&writeBatch);

    Slice key("key");

    writeBatch.Delete(key);

    int finalCount = WriteBatchInternal::Count(&writeBatch);

    EXPECT_EQ(finalCount, initialCount + 1);

}



TEST_F(WriteBatchTest_202, ClearResetsCount_202) {

    Slice key("key");

    Slice value("value");

    writeBatch.Put(key, value);

    writeBatch.Clear();

    int count = WriteBatchInternal::Count(&writeBatch);

    EXPECT_EQ(count, 0);

}



TEST_F(WriteBatchTest_202, ApproximateSizeNonZeroAfterPut_202) {

    Slice key("key");

    Slice value("value");

    writeBatch.Put(key, value);

    size_t size = writeBatch.ApproximateSize();

    EXPECT_GT(size, 0);

}



TEST_F(WriteBatchTest_202, AppendIncreasesCount_202) {

    WriteBatch source;

    Slice key("key");

    Slice value("value");

    source.Put(key, value);

    int initialCount = WriteBatchInternal::Count(&writeBatch);

    writeBatch.Append(source);

    int finalCount = WriteBatchInternal::Count(&writeBatch);

    EXPECT_EQ(finalCount, initialCount + 1);

}



TEST_F(WriteBatchTest_202, IterateWithEmptyBatch_202) {

    class MockHandler : public Handler {

    public:

        MOCK_METHOD(bool, Put, (const Slice& key, const Slice& value), (override));

        MOCK_METHOD(bool, Delete, (const Slice& key), (override));

    };



    MockHandler handler;

    EXPECT_CALL(handler, Put(_, _)).Times(0);

    EXPECT_CALL(handler, Delete(_)).Times(0);



    Status status = writeBatch.Iterate(&handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_202, IterateWithPutAndDelete_202) {

    class MockHandler : public Handler {

    public:

        MOCK_METHOD(bool, Put, (const Slice& key, const Slice& value), (override));

        MOCK_METHOD(bool, Delete, (const Slice& key), (override));

    };



    MockHandler handler;

    Slice putKey("putKey");

    Slice putValue("putValue");

    Slice deleteKey("deleteKey");



    writeBatch.Put(putKey, putValue);

    writeBatch.Delete(deleteKey);



    EXPECT_CALL(handler, Put(Eq(putKey), Eq(putValue))).Times(1).WillOnce(Return(true));

    EXPECT_CALL(handler, Delete(Eq(deleteKey))).Times(1).WillOnce(Return(true));



    Status status = writeBatch.Iterate(&handler);

    EXPECT_TRUE(status.ok());

}
