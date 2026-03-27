#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/log_writer.h"

#include "leveldb/env.h"



using namespace leveldb;

using namespace leveldb::log;

using ::testing::_;

using ::testing::Return;



class MockWritableFile : public WritableFile {

public:

    MOCK_METHOD(Status, Append, (const Slice& data), (override));

    MOCK_METHOD(Status, Close, (), (override));

    MOCK_METHOD(Status, Flush, (), (override));

    MOCK_METHOD(Status, Sync, (), (override));

};



class WriterTest_486 : public ::testing::Test {

protected:

    MockWritableFile* mock_file;

    Writer* writer;



    void SetUp() override {

        mock_file = new MockWritableFile();

        writer = new Writer(mock_file);

    }



    void TearDown() override {

        delete writer;

        delete mock_file;

    }

};



TEST_F(WriterTest_486, AddRecord_SuccessfulWrite_486) {

    Slice data("test_data");

    EXPECT_CALL(*mock_file, Append(_)).WillOnce(Return(Status::OK()));

    Status status = writer->AddRecord(data);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriterTest_486, AddRecord_FailureInAppend_486) {

    Slice data("test_data");

    EXPECT_CALL(*mock_file, Append(_)).WillOnce(Return(Status::IOError("Simulated error")));

    Status status = writer->AddRecord(data);

    EXPECT_TRUE(!status.ok());

}



TEST_F(WriterTest_486, AddEmptyRecord_SuccessfulWrite_486) {

    Slice data("");

    EXPECT_CALL(*mock_file, Append(_)).WillOnce(Return(Status::OK()));

    Status status = writer->AddRecord(data);

    EXPECT_TRUE(status.ok());

}
