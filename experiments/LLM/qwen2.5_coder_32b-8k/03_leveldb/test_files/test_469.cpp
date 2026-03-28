#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"

#include "util/env.cc"



using namespace leveldb;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD3(DoWriteStringToFile, Status(const Slice& data, const std::string& fname, bool should_sync));

};



TEST_F(MockEnv, WriteStringToFile_Success_469) {

    MockEnv mock_env;

    Slice data("test_data");

    std::string filename("test_file.txt");



    EXPECT_CALL(mock_env, DoWriteStringToFile(data, filename, false))

        .WillOnce(Return(OK()));



    Status status = WriteStringToFile(&mock_env, data, filename);

    EXPECT_EQ(status.ok(), true);

}



TEST_F(MockEnv, WriteStringToFile_EmptyData_469) {

    MockEnv mock_env;

    Slice empty_data("");

    std::string filename("test_file.txt");



    EXPECT_CALL(mock_env, DoWriteStringToFile(empty_data, filename, false))

        .WillOnce(Return(OK()));



    Status status = WriteStringToFile(&mock_env, empty_data, filename);

    EXPECT_EQ(status.ok(), true);

}



TEST_F(MockEnv, WriteStringToFile_Failure_469) {

    MockEnv mock_env;

    Slice data("test_data");

    std::string filename("test_file.txt");



    EXPECT_CALL(mock_env, DoWriteStringToFile(data, filename, false))

        .WillOnce(Return(Status::IOError()));



    Status status = WriteStringToFile(&mock_env, data, filename);

    EXPECT_EQ(status.ok(), false);

}
