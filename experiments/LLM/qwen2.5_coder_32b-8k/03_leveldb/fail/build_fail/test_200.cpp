#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/write_batch.h"

#include "leveldb/slice.h"

#include "leveldb/status.h"



using namespace leveldb;

using ::testing::_;

using ::testing::InSequence;

using ::testing::InvokeWithoutArgs;



class MockHandler : public WriteBatch::Handler {

public:

    MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));

    MOCK_METHOD(void, Delete, (const Slice& key), (override));

};



class WriteBatchTest_200 : public ::testing::Test {

protected:

    WriteBatch write_batch;

    MockHandler mock_handler;

};



TEST_F(WriteBatchTest_200, IterateWithEmptyBatch_200) {

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_200, IterateWithSinglePut_200) {

    Slice key("key1");

    Slice value("value1");

    write_batch.Put(key, value);



    EXPECT_CALL(mock_handler, Put(key, value)).Times(1);

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_200, IterateWithMultiplePuts_200) {

    Slice key1("key1");

    Slice value1("value1");

    Slice key2("key2");

    Slice value2("value2");



    write_batch.Put(key1, value1);

    write_batch.Put(key2, value2);



    InSequence seq;

    EXPECT_CALL(mock_handler, Put(key1, value1)).Times(1);

    EXPECT_CALL(mock_handler, Put(key2, value2)).Times(1);



    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_200, IterateWithSingleDelete_200) {

    Slice key("key1");

    write_batch.Delete(key);



    EXPECT_CALL(mock_handler, Delete(key)).Times(1);

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_200, IterateWithMultipleDeletes_200) {

    Slice key1("key1");

    Slice key2("key2");



    write_batch.Delete(key1);

    write_batch.Delete(key2);



    InSequence seq;

    EXPECT_CALL(mock_handler, Delete(key1)).Times(1);

    EXPECT_CALL(mock_handler, Delete(key2)).Times(1);



    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_200, IterateWithMixedOperations_200) {

    Slice key1("key1");

    Slice value1("value1");

    Slice key2("key2");



    write_batch.Put(key1, value1);

    write_batch.Delete(key2);



    InSequence seq;

    EXPECT_CALL(mock_handler, Put(key1, value1)).Times(1);

    EXPECT_CALL(mock_handler, Delete(key2)).Times(1);



    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteBatchTest_200, IterateWithCorruptedHeader_200) {

    WriteBatchInternal::SetContents(&write_batch, Slice("short"));

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(WriteBatchTest_200, IterateWithInvalidPutOperation_200) {

    std::string malformed_put_data("\x01\x03key\0"); // kTypeValue with invalid length

    WriteBatchInternal::SetContents(&write_batch, Slice(malformed_put_data));

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(WriteBatchTest_200, IterateWithInvalidDeleteOperation_200) {

    std::string malformed_delete_data("\x00\x03key\0"); // kTypeDeletion with invalid length

    WriteBatchInternal::SetContents(&write_batch, Slice(malformed_delete_data));

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(WriteBatchTest_200, IterateWithUnknownTag_200) {

    std::string unknown_tag_data("\x02"); // unknown tag

    WriteBatchInternal::SetContents(&write_batch, Slice(unknown_tag_data));

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(WriteBatchTest_200, IterateWithWrongCount_200) {

    std::string valid_put_data("\x01\x03key\0\x04value\0");

    WriteBatchInternal::SetContents(&write_batch, Slice(valid_put_data));

    WriteBatchInternal::SetCount(&write_batch, 0); // setting wrong count

    Status status = write_batch.Iterate(&mock_handler);

    EXPECT_TRUE(status.IsCorruption());

}
