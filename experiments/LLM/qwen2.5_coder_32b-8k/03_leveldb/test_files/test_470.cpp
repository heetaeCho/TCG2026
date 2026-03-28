#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"

#include "util/env.cc"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD3(DoWriteStringToFile, Status(const Slice& data, const std::string& fname, bool sync));

};



TEST_F(MockEnvTest_470, WriteStringToFileSync_Success_470) {

    MockEnv mock_env;

    Slice data("test_data");

    std::string fname = "test_file.txt";

    EXPECT_CALL(mock_env, DoWriteStringToFile(data, fname, true)).WillOnce(Return(Status::OK()));



    Status status = WriteStringToFileSync(&mock_env, data, fname);

    EXPECT_EQ(status.ok(), true);

}



TEST_F(MockEnvTest_470, WriteStringToFileSync_EmptyData_470) {

    MockEnv mock_env;

    Slice data("");

    std::string fname = "test_file.txt";

    EXPECT_CALL(mock_env, DoWriteStringToFile(data, fname, true)).WillOnce(Return(Status::OK()));



    Status status = WriteStringToFileSync(&mock_env, data, fname);

    EXPECT_EQ(status.ok(), true);

}



TEST_F(MockEnvTest_470, WriteStringToFileSync_EmptyFileName_470) {

    MockEnv mock_env;

    Slice data("test_data");

    std::string fname = "";

    EXPECT_CALL(mock_env, DoWriteStringToFile(data, fname, true)).WillOnce(Return(Status::IOError()));



    Status status = WriteStringToFileSync(&mock_env, data, fname);

    EXPECT_EQ(status.ok(), false);

}



TEST_F(MockEnvTest_470, WriteStringToFileSync_FileSystemFailure_470) {

    MockEnv mock_env;

    Slice data("test_data");

    std::string fname = "test_file.txt";

    EXPECT_CALL(mock_env, DoWriteStringToFile(data, fname, true)).WillOnce(Return(Status::IOError()));



    Status status = WriteStringToFileSync(&mock_env, data, fname);

    EXPECT_EQ(status.ok(), false);

}
