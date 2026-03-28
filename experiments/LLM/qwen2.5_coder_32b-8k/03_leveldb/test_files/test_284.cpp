#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/env.h"



using namespace leveldb;



class EnvTest_284 : public ::testing::Test {

protected:

    Env* mock_env;

    leveldb_env_t env_struct;



    void SetUp() override {

        mock_env = new Env();

        env_struct.rep = mock_env;

        env_struct.is_default = false;

    }



    void TearDown() override {

        delete mock_env;

        if (env_struct.rep != nullptr) {

            free(env_struct.rep);

        }

    }

};



TEST_F(EnvTest_284, GetTestDirectory_Success_284) {

    std::string expected_path = "/test/directory";

    EXPECT_CALL(*mock_env, GetTestDirectory(::testing::_))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(expected_path),

            ::testing::Return(Status::OK())));



    char* result = leveldb_env_get_test_directory(&env_struct);

    ASSERT_STREQ(result, expected_path.c_str());

    free(result);

}



TEST_F(EnvTest_284, GetTestDirectory_NotFound_284) {

    EXPECT_CALL(*mock_env, GetTestDirectory(::testing::_))

        .WillOnce(::testing::Return(Status::NotFound()));



    char* result = leveldb_env_get_test_directory(&env_struct);

    ASSERT_EQ(result, nullptr);

}



TEST_F(EnvTest_284, GetTestDirectory_Corruption_284) {

    EXPECT_CALL(*mock_env, GetTestDirectory(::testing::_))

        .WillOnce(::testing::Return(Status::Corruption()));



    char* result = leveldb_env_get_test_directory(&env_struct);

    ASSERT_EQ(result, nullptr);

}



TEST_F(EnvTest_284, GetTestDirectory_IOError_284) {

    EXPECT_CALL(*mock_env, GetTestDirectory(::testing::_))

        .WillOnce(::testing::Return(Status::IOError()));



    char* result = leveldb_env_get_test_directory(&env_struct);

    ASSERT_EQ(result, nullptr);

}



TEST_F(EnvTest_284, GetTestDirectory_InvalidArgument_284) {

    EXPECT_CALL(*mock_env, GetTestDirectory(::testing::_))

        .WillOnce(::testing::Return(Status::InvalidArgument()));



    char* result = leveldb_env_get_test_directory(&env_struct);

    ASSERT_EQ(result, nullptr);

}



TEST_F(EnvTest_284, GetTestDirectory_NotSupportedError_284) {

    EXPECT_CALL(*mock_env, GetTestDirectory(::testing::_))

        .WillOnce(::testing::Return(Status::NotSupported()));



    char* result = leveldb_env_get_test_directory(&env_struct);

    ASSERT_EQ(result, nullptr);

}
