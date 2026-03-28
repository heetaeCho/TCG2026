#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, GetChildren, (const std::string& dir, std::vector<std::string>* r), (override));

};



class EnvWrapperTest_451 : public ::testing::Test {

protected:

    std::unique_ptr<MockEnv> mock_env_;

    std::unique_ptr<EnvWrapper> env_wrapper_;



    void SetUp() override {

        mock_env_ = std::make_unique<MockEnv>();

        env_wrapper_ = std::make_unique<EnvWrapper>(mock_env_.get());

    }

};



TEST_F(EnvWrapperTest_451, GetChildren_Successful_451) {

    std::vector<std::string> expected_children = {"file1", "file2"};

    EXPECT_CALL(*mock_env_, GetChildren("test_dir", _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(expected_children),

            Return(Status::OK())));



    std::vector<std::string> result;

    Status status = env_wrapper_->GetChildren("test_dir", &result);



    EXPECT_EQ(status, Status::OK());

    EXPECT_EQ(result, expected_children);

}



TEST_F(EnvWrapperTest_451, GetChildren_EmptyDirectory_451) {

    std::vector<std::string> expected_children;

    EXPECT_CALL(*mock_env_, GetChildren("empty_dir", _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(expected_children),

            Return(Status::OK())));



    std::vector<std::string> result;

    Status status = env_wrapper_->GetChildren("empty_dir", &result);



    EXPECT_EQ(status, Status::OK());

    EXPECT_TRUE(result.empty());

}



TEST_F(EnvWrapperTest_451, GetChildren_ErrorStatus_451) {

    EXPECT_CALL(*mock_env_, GetChildren("nonexistent_dir", _))

        .WillOnce(Return(Status::IOError()));



    std::vector<std::string> result;

    Status status = env_wrapper_->GetChildren("nonexistent_dir", &result);



    EXPECT_TRUE(status.IsIOError());

}



TEST_F(EnvWrapperTest_451, GetChildren_NullResultPointer_451) {

    EXPECT_CALL(*mock_env_, GetChildren(_, _)).Times(0);



    std::vector<std::string>* null_result = nullptr;

    Status status = env_wrapper_->GetChildren("test_dir", null_result);



    EXPECT_TRUE(status.IsInvalidArgument());

}
