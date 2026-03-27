#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"

#include <string>

#include <vector>



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));

};



class EnvWrapperTest_121 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_env = new MockEnv();

        env_wrapper.reset(new EnvWrapper(mock_env));

    }



    void TearDown() override {

        env_wrapper.reset();

        delete mock_env;

    }



    MockEnv* mock_env;

    std::unique_ptr<EnvWrapper> env_wrapper;

};



TEST_F(EnvWrapperTest_121, GetTestDirectory_Successful_121) {

    std::string expected_path = "/test/directory";

    EXPECT_CALL(*mock_env, GetTestDirectory(_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(expected_path), Return(Status::OK())));



    std::string path;

    Status status = env_wrapper->GetTestDirectory(&path);

    

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(path, expected_path);

}



TEST_F(EnvWrapperTest_121, GetTestDirectory_Failure_121) {

    EXPECT_CALL(*mock_env, GetTestDirectory(_))

        .WillOnce(Return(Status::IOError()));



    std::string path;

    Status status = env_wrapper->GetTestDirectory(&path);



    ASSERT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_121, GetTestDirectory_NullPointer_121) {

    EXPECT_CALL(*mock_env, GetTestDirectory(_)).Times(0);

    

    Status status = env_wrapper->GetTestDirectory(nullptr);

    

    ASSERT_TRUE(status.IsInvalidArgument());

}
