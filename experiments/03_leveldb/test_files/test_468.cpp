#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"

#include "leveldb/status.h"

#include "leveldb/slice.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockWritableFile : public WritableFile {

public:

    MOCK_METHOD1(Append, Status(const Slice& data));

    MOCK_METHOD0(Close, Status());

    MOCK_METHOD0(Flush, Status());

    MOCK_METHOD0(Sync, Status());

};



class MockEnv : public Env {

public:

    MOCK_METHOD2(NewWritableFile, Status(const std::string& fname, WritableFile** result));

    MOCK_METHOD1(RemoveFile, Status(const std::string& fname));

};



class WriteStringToFileTest_468 : public ::testing::Test {

protected:

    NiceMock<MockEnv> mock_env;

    std::unique_ptr<WritableFile> writable_file;

    std::string test_data = "test data";

    Slice slice_data = Slice(test_data);

    std::string file_name = "testfile.txt";



    void SetUp() override {

        writable_file.reset(new MockWritableFile());

    }



    Status DoWriteStringToFile(Env* env, const Slice& data, const std::string& fname, bool should_sync) {

        return leveldb::DoWriteStringToFile(env, data, fname, should_sync);

    }

};



TEST_F(WriteStringToFileTest_468, NormalOperation_SuccessfulWriteAndSync_468) {

    EXPECT_CALL(mock_env, NewWritableFile(file_name, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(writable_file.release()), Return(Status::OK())));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Append(slice_data))

        .WillOnce(Return(Status::OK()));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Sync())

        .WillOnce(Return(Status::OK()));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Close())

        .WillOnce(Return(Status::OK()));



    Status status = DoWriteStringToFile(&mock_env, slice_data, file_name, true);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteStringToFileTest_468, NormalOperation_SuccessfulWriteWithoutSync_468) {

    EXPECT_CALL(mock_env, NewWritableFile(file_name, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(writable_file.release()), Return(Status::OK())));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Append(slice_data))

        .WillOnce(Return(Status::OK()));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Sync())

        .Times(0);

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Close())

        .WillOnce(Return(Status::OK()));



    Status status = DoWriteStringToFile(&mock_env, slice_data, file_name, false);

    EXPECT_TRUE(status.ok());

}



TEST_F(WriteStringToFileTest_468, NewWritableFileFailure_CleanupFileNotCalled_468) {

    EXPECT_CALL(mock_env, NewWritableFile(file_name, _))

        .WillOnce(Return(Status::IOError()));



    Status status = DoWriteStringToFile(&mock_env, slice_data, file_name, true);

    EXPECT_TRUE(!status.ok());

}



TEST_F(WriteStringToFileTest_468, AppendFailure_CleanupFileCalled_468) {

    EXPECT_CALL(mock_env, NewWritableFile(file_name, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(writable_file.release()), Return(Status::OK())));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Append(slice_data))

        .WillOnce(Return(Status::IOError()));

    EXPECT_CALL(mock_env, RemoveFile(file_name))

        .WillOnce(Return(Status::OK()));



    Status status = DoWriteStringToFile(&mock_env, slice_data, file_name, true);

    EXPECT_TRUE(!status.ok());

}



TEST_F(WriteStringToFileTest_468, SyncFailure_CleanupFileCalled_468) {

    EXPECT_CALL(mock_env, NewWritableFile(file_name, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(writable_file.release()), Return(Status::OK())));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Append(slice_data))

        .WillOnce(Return(Status::OK()));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Sync())

        .WillOnce(Return(Status::IOError()));

    EXPECT_CALL(mock_env, RemoveFile(file_name))

        .WillOnce(Return(Status::OK()));



    Status status = DoWriteStringToFile(&mock_env, slice_data, file_name, true);

    EXPECT_TRUE(!status.ok());

}



TEST_F(WriteStringToFileTest_468, CloseFailure_CleanupNotCalled_468) {

    EXPECT_CALL(mock_env, NewWritableFile(file_name, _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(writable_file.release()), Return(Status::OK())));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Append(slice_data))

        .WillOnce(Return(Status::OK()));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Sync())

        .WillOnce(Return(Status::OK()));

    EXPECT_CALL(*static_cast<MockWritableFile*>(writable_file.get()), Close())

        .WillOnce(Return(Status::IOError()));



    Status status = DoWriteStringToFile(&mock_env, slice_data, file_name, true);

    EXPECT_TRUE(!status.ok());

}
