#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using ::testing::Return;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



namespace leveldb {



class MockEnv : public Env {

public:

    MOCK_METHOD(bool, FileExists, (const std::string& f), (override));

};



class EnvWrapperTest_110 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_env = new MockEnv();

        env_wrapper = new EnvWrapper(mock_env);

    }



    void TearDown() override {

        delete env_wrapper;

        delete mock_env;

    }



    MockEnv* mock_env;

    EnvWrapper* env_wrapper;

};



TEST_F(EnvWrapperTest_110, FileExists_ReturnsTrueWhenFileExists_110) {

    EXPECT_CALL(*mock_env, FileExists("testfile.txt")).WillOnce(Return(true));

    bool result = env_wrapper->FileExists("testfile.txt");

    EXPECT_TRUE(result);

}



TEST_F(EnvWrapperTest_110, FileExists_ReturnsFalseWhenFileDoesNotExist_110) {

    EXPECT_CALL(*mock_env, FileExists("nonexistentfile.txt")).WillOnce(Return(false));

    bool result = env_wrapper->FileExists("nonexistentfile.txt");

    EXPECT_FALSE(result);

}



TEST_F(EnvWrapperTest_110, FileExists_BoundaryConditionEmptyString_110) {

    EXPECT_CALL(*mock_env, FileExists("")).WillOnce(Return(false));

    bool result = env_wrapper->FileExists("");

    EXPECT_FALSE(result);

}



}  // namespace leveldb
