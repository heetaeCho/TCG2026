#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "db/log_writer.h"

#include "leveldb/env.h"



using namespace leveldb;

using namespace leveldb::log;

using ::testing::_;



class MockWritableFile : public WritableFile {

public:

    MOCK_METHOD(Status, Append, (const Slice & data), (override));

    MOCK_METHOD(Status, Close, (), (override));

    MOCK_METHOD(Status, Flush, (), (override));

    MOCK_METHOD(Status, Sync, (), (override));

};



class WriterTest_345 : public ::testing::Test {

protected:

    std::unique_ptr<MockWritableFile> mock_file_;

    Writer* writer_;



    void SetUp() override {

        mock_file_ = std::make_unique<MockWritableFile>();

        writer_ = new Writer(mock_file_.get());

    }



    void TearDown() override {

        delete writer_;

    }

};



TEST_F(WriterTest_345, AddRecord_NormalOperation_345) {

    Slice record("test_record");

    EXPECT_CALL(*mock_file_, Append(_)).WillOnce(::testing::Return(Status::OK()));

    Status s = writer_->AddRecord(record);

    EXPECT_TRUE(s.ok());

}



TEST_F(WriterTest_345, AddRecord_BoundaryCondition_EmptyRecord_345) {

    Slice empty_record;

    EXPECT_CALL(*mock_file_, Append(_)).Times(0);

    Status s = writer_->AddRecord(empty_record);

    EXPECT_TRUE(s.ok());

}



TEST_F(WriterTest_345, AddRecord_BoundaryCondition_BlockSizeExactMatch_345) {

    std::string record_data(kBlockSize - kHeaderSize, 'a');

    Slice record(record_data);

    EXPECT_CALL(*mock_file_, Append(_)).WillOnce(::testing::Return(Status::OK()));

    Status s = writer_->AddRecord(record);

    EXPECT_TRUE(s.ok());

}



TEST_F(WriterTest_345, AddRecord_BoundaryCondition_MultipleBlocks_345) {

    std::string record_data(kBlockSize * 2 + kHeaderSize, 'a');

    Slice record(record_data);

    EXPECT_CALL(*mock_file_, Append(_)).Times(3).WillRepeatedly(::testing::Return(Status::OK()));

    Status s = writer_->AddRecord(record);

    EXPECT_TRUE(s.ok());

}



TEST_F(WriterTest_345, AddRecord_ErrorCase_AppendFails_345) {

    Slice record("test_record");

    EXPECT_CALL(*mock_file_, Append(_)).WillOnce(::testing::Return(Status::IOError()));

    Status s = writer_->AddRecord(record);

    EXPECT_TRUE(s.IsIOError());

}
