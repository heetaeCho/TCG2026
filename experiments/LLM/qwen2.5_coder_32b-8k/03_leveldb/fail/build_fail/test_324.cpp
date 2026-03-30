#include "gmock/gmock.h"

#include "gtest/gtest.h"

#include "db/log_reader.h"



using namespace leveldb;

using namespace leveldb::log;



class MockSequentialFile : public SequentialFile {

public:

    MOCK_METHOD(Status, Read(size_t n, Slice* result, char* scratch), (override));

    MOCK_METHOD(Status, Skip(uint64_t n), (override));

};



class MockReporter : public Reporter {

public:

    MOCK_METHOD(void, Corruption(size_t bytes, const Status& status), (override));

};



class LogReaderTest_324 : public ::testing::Test {

protected:

    void SetUp() override {

        file = new MockSequentialFile();

        reporter = new MockReporter();

        reader = new Reader(file, reporter, true, 0);

    }



    void TearDown() override {

        delete reader;

        delete reporter;

        delete file;

    }



    MockSequentialFile* file;

    MockReporter* reporter;

    Reader* reader;

};



TEST_F(LogReaderTest_324, ReadRecord_ReturnsTrueForFullType_324) {

    std::string scratch;

    Slice record;

    const char data[] = {1, 0, 0, 0, 0, 0, 'f', 'u', 'l', 'l'};

    EXPECT_CALL(*file, Read(7, testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data, 7)),

            testing::Return(Status::OK())));

    

    ASSERT_TRUE(reader->ReadRecord(&record, &scratch));

    ASSERT_EQ(record.ToString(), "full");

}



TEST_F(LogReaderTest_324, ReadRecord_ReturnsFalseForEofType_324) {

    std::string scratch;

    Slice record;

    const char data[] = {5, 0, 0, 0, 0, 0};

    EXPECT_CALL(*file, Read(6, testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data, 6)),

            testing::Return(Status::OK())));

    

    ASSERT_FALSE(reader->ReadRecord(&record, &scratch));

}



TEST_F(LogReaderTest_324, ReadRecord_HandlesFragmentedRecord_324) {

    std::string scratch;

    Slice record;

    const char firstData[] = {2, 0, 0, 0, 0, 0, 'f', 'i', 'r', 's', 't'};

    const char middleData[] = {3, 0, 0, 0, 0, 0, 'm', 'i', 'd'};

    const char lastData[] = {4, 0, 0, 0, 0, 0, 'l', 'a', 's', 't'};



    EXPECT_CALL(*file, Read(7, testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(firstData, 7)),

            testing::Return(Status::OK())))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(middleData, 6)),

            testing::Return(Status::OK())))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(lastData, 7)),

            testing::Return(Status::OK())));



    ASSERT_TRUE(reader->ReadRecord(&record, &scratch));

    ASSERT_EQ(record.ToString(), "firstmidlast");

}



TEST_F(LogReaderTest_324, ReadRecord_ReturnsFalseForBadRecordType_324) {

    std::string scratch;

    Slice record;

    const char data[] = {6, 0, 0, 0, 0, 0};

    EXPECT_CALL(*file, Read(6, testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data, 6)),

            testing::Return(Status::OK())));

    

    ASSERT_FALSE(reader->ReadRecord(&record, &scratch));

}



TEST_F(LogReaderTest_324, ReadRecord_ReportsCorruptionForInvalidMiddleType_324) {

    std::string scratch;

    Slice record;

    const char data[] = {3, 0, 0, 0, 0, 0, 'm', 'i', 'd'};

    

    EXPECT_CALL(*file, Read(7, testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data, 7)),

            testing::Return(Status::OK())));

    EXPECT_CALL(*reporter, Corruption(6, testing::_));

    

    ASSERT_FALSE(reader->ReadRecord(&record, &scratch));

}



TEST_F(LogReaderTest_324, ReadRecord_SkipsToInitialBlockIfOffsetSet_324) {

    std::string scratch;

    Slice record;

    const char data[] = {1, 0, 0, 0, 0, 0, 'f', 'u', 'l', 'l'};

    

    reader = new Reader(file, reporter, true, 10);

    EXPECT_CALL(*file, Skip(10)).WillOnce(testing::Return(Status::OK()));

    EXPECT_CALL(*file, Read(7, testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data, 7)),

            testing::Return(Status::OK())));

    

    ASSERT_TRUE(reader->ReadRecord(&record, &scratch));

    ASSERT_EQ(record.ToString(), "full");

}



TEST_F(LogReaderTest_324, ReadRecord_HandlesBoundaryConditionsWithSmallBuffers_324) {

    std::string scratch;

    Slice record;

    const char data1[] = {2, 0, 0, 0, 0, 0, 'f', 'i', 'r'};

    const char data2[] = {'s', 't'};

    const char data3[] = {4, 0, 0, 0, 0, 0, 'l', 'a', 's', 't'};



    EXPECT_CALL(*file, Read(7, testing::_, testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data1, 9)),

            testing::Return(Status::OK())))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data2, 2)),

            testing::Return(Status::OK())))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(Slice(data3, 7)),

            testing::Return(Status::OK())));



    ASSERT_TRUE(reader->ReadRecord(&record, &scratch));

    ASSERT_EQ(record.ToString(), "firstlast");

}
