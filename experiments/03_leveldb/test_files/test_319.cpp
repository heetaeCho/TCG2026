#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/db_impl.cc"

#include "leveldb/status.h"

#include "leveldb/options.h"

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD2(GetChildren, Status(const std::string&, std::vector<std::string>*));

    MOCK_METHOD2(LockFile, Status(const std::string&, FileLock**));

    MOCK_METHOD1(UnlockFile, Status(FileLock*));

    MOCK_METHOD1(RemoveFile, Status(const std::string&));

    MOCK_METHOD1(RemoveDir, Status(const std::string&));

};



class DestroyDBTest_319 : public ::testing::Test {

protected:

    MockEnv mock_env;

    Options options;



    void SetUp() override {

        options.env = &mock_env;

    }

};



TEST_F(DestroyDBTest_319, NormalOperation_319) {

    std::vector<std::string> filenames = {"0.log", "CURRENT"};

    EXPECT_CALL(mock_env, GetChildren("dbname", _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(filenames), Return(Status::OK())));

    EXPECT_CALL(mock_env, LockFile("dbname/LOCK", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/0.log")).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/CURRENT")).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, UnlockFile(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/LOCK")).Times(1);

    EXPECT_CALL(mock_env, RemoveDir("dbname")).WillOnce(Return(Status::OK()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.ok());

}



TEST_F(DestroyDBTest_319, NoFilesToRemove_319) {

    std::vector<std::string> filenames;

    EXPECT_CALL(mock_env, GetChildren("dbname", _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(filenames), Return(Status::OK())));

    EXPECT_CALL(mock_env, LockFile("dbname/LOCK", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, UnlockFile(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/LOCK")).Times(1);

    EXPECT_CALL(mock_env, RemoveDir("dbname")).WillOnce(Return(Status::OK()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.ok());

}



TEST_F(DestroyDBTest_319, GetChildrenFails_319) {

    EXPECT_CALL(mock_env, GetChildren("dbname", _)).WillOnce(Return(Status::IOError()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(DestroyDBTest_319, LockFileFails_319) {

    std::vector<std::string> filenames = {"0.log"};

    EXPECT_CALL(mock_env, GetChildren("dbname", _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(filenames), Return(Status::OK())));

    EXPECT_CALL(mock_env, LockFile("dbname/LOCK", _)).WillOnce(Return(Status::IOError()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(DestroyDBTest_319, RemoveFileFails_319) {

    std::vector<std::string> filenames = {"0.log"};

    EXPECT_CALL(mock_env, GetChildren("dbname", _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(filenames), Return(Status::OK())));

    EXPECT_CALL(mock_env, LockFile("dbname/LOCK", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/0.log")).WillOnce(Return(Status::IOError()));

    EXPECT_CALL(mock_env, UnlockFile(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/LOCK")).Times(1);

    EXPECT_CALL(mock_env, RemoveDir("dbname")).WillOnce(Return(Status::OK()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(DestroyDBTest_319, UnlockFileFails_319) {

    std::vector<std::string> filenames = {"0.log"};

    EXPECT_CALL(mock_env, GetChildren("dbname", _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(filenames), Return(Status::OK())));

    EXPECT_CALL(mock_env, LockFile("dbname/LOCK", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/0.log")).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, UnlockFile(_)).WillOnce(Return(Status::IOError()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/LOCK")).Times(1);

    EXPECT_CALL(mock_env, RemoveDir("dbname")).WillOnce(Return(Status::OK()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(DestroyDBTest_319, RemoveLockFileFails_319) {

    std::vector<std::string> filenames = {"0.log"};

    EXPECT_CALL(mock_env, GetChildren("dbname", _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(filenames), Return(Status::OK())));

    EXPECT_CALL(mock_env, LockFile("dbname/LOCK", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/0.log")).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, UnlockFile(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/LOCK")).WillOnce(Return(Status::IOError()));

    EXPECT_CALL(mock_env, RemoveDir("dbname")).WillOnce(Return(Status::OK()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(DestroyDBTest_319, RemoveDirFails_319) {

    std::vector<std::string> filenames = {"0.log"};

    EXPECT_CALL(mock_env, GetChildren("dbname", _))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(filenames), Return(Status::OK())));

    EXPECT_CALL(mock_env, LockFile("dbname/LOCK", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/0.log")).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, UnlockFile(_)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(mock_env, RemoveFile("dbname/LOCK")).Times(1);

    EXPECT_CALL(mock_env, RemoveDir("dbname")).WillOnce(Return(Status::IOError()));



    Status status = DestroyDB("dbname", options);

    EXPECT_TRUE(status.IsIOError());

}
