#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/log_reader.h"



namespace leveldb {

namespace log {



using ::testing::_;

using ::testing::Invoke;

using ::testing::NiceMock;



class MockSequentialFile : public SequentialFile {

public:

    MOCK_METHOD(Status, Read(size_t n, Slice* result, char* scratch), (override));

    MOCK_METHOD(Status, Skip(uint64_t n), (override));

};



class MockReporter : public Reporter {

public:

    MOCK_METHOD(void, Corruption(size_t bytes, const Status& status), (override));

};



class LogReaderTest_323 : public ::testing::Test {

protected:

    MockSequentialFile mock_file_;

    NiceMock<MockReporter> mock_reporter_;

    Reader reader_{&mock_file_, &mock_reporter_, true, 0};



    void SetUp() override {

        // Setup any common state before each test

    }



    void TearDown() override {

        // Cleanup any state after each test

    }

};



TEST_F(LogReaderTest_323, ReadRecord_ReturnsFalseWhenEOF_323) {

    EXPECT_CALL(mock_file_, Read(_, _, _))

        .WillOnce(Invoke([](size_t n, Slice* result, char* scratch) -> Status {

            *result = Slice();

            return Status::OK();

        }));



    Slice record;

    std::string scratch;

    bool success = reader_.ReadRecord(&record, &scratch);

    EXPECT_FALSE(success);

}



TEST_F(LogReaderTest_323, ReadRecord_CallsReportCorruptionOnCorruptedData_323) {

    EXPECT_CALL(mock_file_, Read(_, _, _))

        .WillOnce(Invoke([](size_t n, Slice* result, char* scratch) -> Status {

            *result = Slice("corrupted_data", 14);

            return Status::OK();

        }));



    EXPECT_CALL(mock_reporter_, Corruption(_, _));



    Slice record;

    std::string scratch;

    bool success = reader_.ReadRecord(&record, &scratch);

    EXPECT_FALSE(success);

}



TEST_F(LogReaderTest_323, LastRecordOffset_ReturnsInitialOffsetWhenNoRecordsRead_323) {

    uint64_t offset = reader_.LastRecordOffset();

    EXPECT_EQ(offset, 0);

}



TEST_F(LogReaderTest_323, ReadRecord_SkipsToInitialBlockIfResyncing_323) {

    Reader resync_reader{&mock_file_, &mock_reporter_, true, 1};



    EXPECT_CALL(resync_reader, SkipToInitialBlock())

        .WillOnce(Invoke([]() -> bool { return true; }));



    Slice record;

    std::string scratch;

    bool success = resync_reader.ReadRecord(&record, &scratch);

    EXPECT_TRUE(success);

}



} // namespace log

} // namespace leveldb
