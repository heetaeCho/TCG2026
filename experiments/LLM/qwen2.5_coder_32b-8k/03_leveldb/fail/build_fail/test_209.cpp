#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "db/write_batch_internal.h"



namespace leveldb {



class WriteBatchTest_209 : public ::testing::Test {

protected:

    WriteBatch write_batch;

};



TEST_F(WriteBatchTest_209, SetContents_ValidSize_209) {

    const char data[] = "test_data";

    Slice contents(data, sizeof(data));

    ASSERT_NO_THROW(WriteBatchInternal::SetContents(&write_batch, contents));

}



TEST_F(WriteBatchTest_209, SetContents_SmallerThanHeader_209) {

    const char data[] = "tiny";

    Slice contents(data, 4);

    EXPECT_DEATH_IF_SUPPORTED({ WriteBatchInternal::SetContents(&write_batch, contents); }, "");

}



TEST_F(WriteBatchTest_209, ApproximateSize_DefaultConstructor_209) {

    EXPECT_EQ(write_batch.ApproximateSize(), 0u);

}



TEST_F(WriteBatchTest_209, Clear_NoOperations_209) {

    write_batch.Clear();

    EXPECT_EQ(write_batch.ApproximateSize(), 0u);

}



TEST_F(WriteBatchTest_209, Put_IncreasesApproximateSize_209) {

    size_t initial_size = write_batch.ApproximateSize();

    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);

    EXPECT_GT(write_batch.ApproximateSize(), initial_size);

}



TEST_F(WriteBatchTest_209, Delete_IncreasesApproximateSize_209) {

    size_t initial_size = write_batch.ApproximateSize();

    Slice key("key");

    write_batch.Delete(key);

    EXPECT_GT(write_batch.ApproximateSize(), initial_size);

}



TEST_F(WriteBatchTest_209, Append_MergesTwoBatches_209) {

    WriteBatch another_batch;

    Slice key1("key1"), value1("value1");

    Slice key2("key2"), value2("value2");

    write_batch.Put(key1, value1);

    another_batch.Put(key2, value2);



    size_t combined_size = write_batch.ApproximateSize() + another_batch.ApproximateSize();

    write_batch.Append(another_batch);



    EXPECT_EQ(write_batch.ApproximateSize(), combined_size);

}



TEST_F(WriteBatchTest_209, Iterate_ValidHandler_209) {

    class MockHandler : public Handler {

    public:

        MOCK_METHOD3(Put, void(const Slice& key, const Slice& value));

        MOCK_METHOD1(Delete, void(const Slice& key));

    };



    testing::StrictMock<MockHandler> handler;



    Slice key("key");

    Slice value("value");

    write_batch.Put(key, value);



    EXPECT_CALL(handler, Put(testing::Eq(key), testing::Eq(value)));

    EXPECT_EQ(write_batch.Iterate(&handler), Status::OK());

}



TEST_F(WriteBatchTest_209, Iterate_EmptyBatch_209) {

    class MockHandler : public Handler {

    public:

        MOCK_METHOD3(Put, void(const Slice& key, const Slice& value));

        MOCK_METHOD1(Delete, void(const Slice& key));

    };



    testing::StrictMock<MockHandler> handler;

    EXPECT_CALL(handler, Put).Times(0);

    EXPECT_CALL(handler, Delete).Times(0);



    EXPECT_EQ(write_batch.Iterate(&handler), Status::OK());

}



}  // namespace leveldb
