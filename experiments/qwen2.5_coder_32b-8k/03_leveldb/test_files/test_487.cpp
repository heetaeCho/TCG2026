#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "db/log_writer.h"

#include "leveldb/env.h"



using namespace leveldb;

using namespace leveldb::log;

using ::testing::_;

using ::testing::InvokeWithoutArgs;

using ::testing::Return;



class MockWritableFile : public WritableFile {

public:

    MOCK_METHOD(Status, Append, (const Slice& data), (override));

    MOCK_METHOD(Status, Close, (), (override));

    MOCK_METHOD(Status, Flush, (), (override));

    MOCK_METHOD(Status, Sync, (), (override));

};



class WriterTest_487 : public ::testing::Test {

protected:

    std::unique_ptr<MockWritableFile> mock_dest_;

    std::unique_ptr<Writer> writer_;



    void SetUp() override {

        mock_dest_ = std::make_unique<MockWritableFile>();

        writer_ = std::make_unique<Writer>(mock_dest_.get());

    }

};



TEST_F(WriterTest_487, ConstructorWithDestOnly_487) {

    EXPECT_EQ(writer_->block_offset_, 0);

}



TEST_F(WriterTest_487, ConstructorWithDestAndLength_487) {

    uint64_t dest_length = kBlockSize * 2 + 5;

    writer_ = std::make_unique<Writer>(mock_dest_.get(), dest_length);

    EXPECT_EQ(writer_->block_offset_, 5);

}



TEST_F(WriterTest_487, AddRecord_Success_487) {

    Slice slice("test_data");

    EXPECT_CALL(*mock_dest_, Append(_)).WillOnce(Return(Status::OK()));

    Status status = writer_->AddRecord(slice);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriterTest_487, AddRecord_Failure_487) {

    Slice slice("test_data");

    EXPECT_CALL(*mock_dest_, Append(_)).WillOnce(Return(Status::IOError("error")));

    Status status = writer_->AddRecord(slice);

    EXPECT_FALSE(status.ok());

}
