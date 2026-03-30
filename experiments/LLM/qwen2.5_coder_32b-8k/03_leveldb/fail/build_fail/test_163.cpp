#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "leveldb/status.h"

#include "port/port_stdcxx.h"

#include "db/version_edit.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD3(NewWritableFile, Status(const std::string&, WritableFile**, const Options&));

    MOCK_METHOD1(RemoveFile, Status(const std::string&));

};



class MockLogWriter : public log::Writer {

public:

    MOCK_METHOD1(AddRecord, Status(const Slice&));

};



class MockVersionEdit : public VersionEdit {

public:

    MOCK_CONST_METHOD0(has_log_number_, bool());

    MOCK_CONST_METHOD0(log_number_, uint64_t());

    MOCK_METHOD1(SetLogNumber, void(uint64_t));

    MOCK_METHOD1(SetPrevLogNumber, void(uint64_t));

    MOCK_METHOD1(SetNextFile, void(uint64_t));

    MOCK_METHOD1(SetLastSequence, void(SequenceNumber));

};



class VersionSetTest_163 : public ::testing::Test {

protected:

    MockEnv mock_env_;

    Options options_;

    TableCache table_cache_{nullptr};

    InternalKeyComparator icmp_{BytewiseComparator()};

    port::Mutex mu_;



    VersionSet* version_set_;

    MockVersionEdit* edit_;



    void SetUp() override {

        version_set_ = new VersionSet("test_db", &options_, &table_cache_, &icmp_);

        edit_ = new MockVersionEdit();

    }



    void TearDown() override {

        delete version_set_;

        delete edit_;

    }

};



TEST_F(VersionSetTest_163, LogAndApply_HasLogNumber_ValidRange_163) {

    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(true));

    EXPECT_CALL(*edit_, log_number_()).WillOnce(Return(5));



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_TRUE(status.ok());

}



TEST_F(VersionSetTest_163, LogAndApply_HasLogNumber_OutOfRange_163) {

    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(true));

    EXPECT_CALL(*edit_, log_number_()).WillOnce(Return(10));



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_TRUE(status.ok());

}



TEST_F(VersionSetTest_163, LogAndApply_NoLogNumber_SetsCurrentLogNumber_163) {

    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(false));



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_TRUE(status.ok());

}



TEST_F(VersionSetTest_163, LogAndApply_NewManifestFile_Success_163) {

    WritableFile* mock_file = new WritableFile();

    MockLogWriter* mock_log_writer = new MockLogWriter(mock_file);



    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(false));

    EXPECT_CALL(mock_env_, NewWritableFile(_, _, _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_file, Sync()).WillOnce(Return(Status::OK()));



    version_set_->env_ = &mock_env_;

    version_set_->descriptor_file_ = mock_file;

    version_set_->descriptor_log_ = mock_log_writer;



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_TRUE(status.ok());



    delete mock_file;

    delete mock_log_writer;

}



TEST_F(VersionSetTest_163, LogAndApply_NewManifestFile_Failure_163) {

    WritableFile* mock_file = new WritableFile();



    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(false));

    EXPECT_CALL(mock_env_, NewWritableFile(_, _, _)).WillOnce(Return(Status::IOError()));



    version_set_->env_ = &mock_env_;

    version_set_->descriptor_file_ = mock_file;



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_FALSE(status.ok());



    delete mock_file;

}



TEST_F(VersionSetTest_163, LogAndApply_AddRecord_Success_163) {

    WritableFile* mock_file = new WritableFile();

    MockLogWriter* mock_log_writer = new MockLogWriter(mock_file);



    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(false));

    EXPECT_CALL(mock_env_, NewWritableFile(_, _, _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_log_writer, AddRecord(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_file, Sync()).WillOnce(Return(Status::OK()));



    version_set_->env_ = &mock_env_;

    version_set_->descriptor_file_ = mock_file;

    version_set_->descriptor_log_ = mock_log_writer;



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_TRUE(status.ok());



    delete mock_file;

    delete mock_log_writer;

}



TEST_F(VersionSetTest_163, LogAndApply_AddRecord_Failure_163) {

    WritableFile* mock_file = new WritableFile();

    MockLogWriter* mock_log_writer = new MockLogWriter(mock_file);



    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(false));

    EXPECT_CALL(mock_env_, NewWritableFile(_, _, _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_log_writer, AddRecord(_)).WillOnce(Return(Status::IOError()));



    version_set_->env_ = &mock_env_;

    version_set_->descriptor_file_ = mock_file;

    version_set_->descriptor_log_ = mock_log_writer;



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_FALSE(status.ok());



    delete mock_file;

    delete mock_log_writer;

}



TEST_F(VersionSetTest_163, LogAndApply_SetCurrentFile_Success_163) {

    WritableFile* mock_file = new WritableFile();

    MockLogWriter* mock_log_writer = new MockLogWriter(mock_file);



    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(false));

    EXPECT_CALL(mock_env_, NewWritableFile(_, _, _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_log_writer, AddRecord(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_file, Sync()).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env_, RemoveFile(_)).Times(0);



    version_set_->env_ = &mock_env_;

    version_set_->descriptor_file_ = mock_file;

    version_set_->descriptor_log_ = mock_log_writer;



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_TRUE(status.ok());



    delete mock_file;

    delete mock_log_writer;

}



TEST_F(VersionSetTest_163, LogAndApply_SetCurrentFile_Failure_163) {

    WritableFile* mock_file = new WritableFile();

    MockLogWriter* mock_log_writer = new MockLogWriter(mock_file);



    EXPECT_CALL(*edit_, has_log_number_()).WillOnce(Return(false));

    EXPECT_CALL(mock_env_, NewWritableFile(_, _, _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_log_writer, AddRecord(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(*mock_file, Sync()).WillOnce(Return(Status::IOError()));

    EXPECT_CALL(mock_env_, RemoveFile(_)).Times(1);



    version_set_->env_ = &mock_env_;

    version_set_->descriptor_file_ = mock_file;

    version_set_->descriptor_log_ = mock_log_writer;



    Status status = version_set_->LogAndApply(edit_, &mu_);

    EXPECT_FALSE(status.ok());



    delete mock_file;

    delete mock_log_writer;

}
