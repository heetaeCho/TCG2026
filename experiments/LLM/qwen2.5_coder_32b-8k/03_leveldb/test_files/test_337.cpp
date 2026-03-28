#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "leveldb/filename.h"

#include "leveldb/env.h"

#include "leveldb/status.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class EnvMock : public Env {

public:

    MOCK_METHOD(Status, WriteStringToFileSync, (const std::string&, const std::string&), (override));

    MOCK_METHOD(Status, RenameFile, (const std::string&, const std::string&), (override));

    MOCK_METHOD(Status, RemoveFile, (const std::string&), (override));

};



class SetCurrentFileTest_337 : public ::testing::Test {

protected:

    EnvMock env;

    const std::string dbname = "testdb";

    uint64_t descriptor_number = 123;

};



TEST_F(SetCurrentFileTest_337, NormalOperation_337) {

    EXPECT_CALL(env, WriteStringToFileSync("123\n", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(env, RenameFile(_, "testdb/CURRENT")).WillOnce(Return(Status::OK()));



    Status s = SetCurrentFile(&env, dbname, descriptor_number);

    EXPECT_TRUE(s.ok());

}



TEST_F(SetCurrentFileTest_337, WriteStringToFileFails_337) {

    EXPECT_CALL(env, WriteStringToFileSync("123\n", _)).WillOnce(Return(Status::IOError()));



    Status s = SetCurrentFile(&env, dbname, descriptor_number);

    EXPECT_TRUE(s.IsIOError());

}



TEST_F(SetCurrentFileTest_337, RenameFileFailsAndTmpFileRemoved_337) {

    EXPECT_CALL(env, WriteStringToFileSync("123\n", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(env, RenameFile(_, "testdb/CURRENT")).WillOnce(Return(Status::IOError()));

    EXPECT_CALL(env, RemoveFile(_));



    Status s = SetCurrentFile(&env, dbname, descriptor_number);

    EXPECT_TRUE(s.IsIOError());

}



TEST_F(SetCurrentFileTest_337, BoundaryConditionEmptyDbname_337) {

    const std::string empty_dbname = "";

    EXPECT_CALL(env, WriteStringToFileSync("123\n", _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(env, RenameFile(_, "CURRENT")).WillOnce(Return(Status::OK()));



    Status s = SetCurrentFile(&env, empty_dbname, descriptor_number);

    EXPECT_TRUE(s.ok());

}



TEST_F(SetCurrentFileTest_337, BoundaryConditionLargeDescriptorNumber_337) {

    uint64_t large_descriptor_number = UINT64_MAX;

    std::string expected_contents = std::to_string(large_descriptor_number) + "\n";

    EXPECT_CALL(env, WriteStringToFileSync(expected_contents, _)).WillOnce(Return(Status::OK()));

    EXPECT_CALL(env, RenameFile(_, "testdb/CURRENT")).WillOnce(Return(Status::OK()));



    Status s = SetCurrentFile(&env, dbname, large_descriptor_number);

    EXPECT_TRUE(s.ok());

}
