#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/env.h"

#include "util/env.cc"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockEnv : public Env {

public:

    MOCK_METHOD2(NewSequentialFile, Status(const std::string&, SequentialFile**));

};



class MockSequentialFile : public SequentialFile {

public:

    MOCK_METHOD3(Read, Status(size_t, Slice*, char*));

};



class ReadFileToStringTest_471 : public ::testing::Test {

protected:

    NiceMock<MockEnv> mock_env;

    std::string result_data;



    void SetUp() override {

        result_data.clear();

    }

};



TEST_F(ReadFileToStringTest_471, NormalOperation_471) {

    const std::string file_name = "test_file";

    const char* buffer = "Hello, World!";

    Slice fragment(buffer, strlen(buffer));



    auto mock_seq_file = std::make_unique<NiceMock<MockSequentialFile>>();

    EXPECT_CALL(mock_env, NewSequentialFile(file_name, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(mock_seq_file.get()),

            Return(Status::OK())));



    EXPECT_CALL(*mock_seq_file, Read(strlen(buffer), _, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(fragment),

            Return(Status::OK())))

        .WillOnce(Return(Status::IOError()));



    Status s = ReadFileToString(&mock_env, file_name, &result_data);



    EXPECT_TRUE(s.ok());

    EXPECT_EQ(result_data, "Hello, World!");

}



TEST_F(ReadFileToStringTest_471, BoundaryCondition_EmptyFile_471) {

    const std::string file_name = "empty_file";



    auto mock_seq_file = std::make_unique<NiceMock<MockSequentialFile>>();

    EXPECT_CALL(mock_env, NewSequentialFile(file_name, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(mock_seq_file.get()),

            Return(Status::OK())));



    Slice empty_fragment;

    EXPECT_CALL(*mock_seq_file, Read(_, _, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(empty_fragment),

            Return(Status::OK())))

        .WillOnce(Return(Status::IOError()));



    Status s = ReadFileToString(&mock_env, file_name, &result_data);



    EXPECT_TRUE(s.ok());

    EXPECT_EQ(result_data.empty(), true);

}



TEST_F(ReadFileToStringTest_471, ErrorCase_FileNotFound_471) {

    const std::string file_name = "nonexistent_file";



    EXPECT_CALL(mock_env, NewSequentialFile(file_name, _))

        .WillOnce(Return(Status::NotFound()));



    Status s = ReadFileToString(&mock_env, file_name, &result_data);



    EXPECT_TRUE(s.IsNotFound());

    EXPECT_EQ(result_data.empty(), true);

}



TEST_F(ReadFileToStringTest_471, ErrorCase_ReadError_471) {

    const std::string file_name = "error_file";



    auto mock_seq_file = std::make_unique<NiceMock<MockSequentialFile>>();

    EXPECT_CALL(mock_env, NewSequentialFile(file_name, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(mock_seq_file.get()),

            Return(Status::OK())));



    EXPECT_CALL(*mock_seq_file, Read(_, _, _))

        .WillOnce(Return(Status::IOError()));



    Status s = ReadFileToString(&mock_env, file_name, &result_data);



    EXPECT_TRUE(s.IsIOError());

    EXPECT_EQ(result_data.empty(), true);

}



TEST_F(ReadFileToStringTest_471, MultipleReads_471) {

    const std::string file_name = "multi_read_file";

    const char* buffer1 = "Hello, ";

    const char* buffer2 = "World!";

    Slice fragment1(buffer1, strlen(buffer1));

    Slice fragment2(buffer2, strlen(buffer2));



    auto mock_seq_file = std::make_unique<NiceMock<MockSequentialFile>>();

    EXPECT_CALL(mock_env, NewSequentialFile(file_name, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(mock_seq_file.get()),

            Return(Status::OK())));



    EXPECT_CALL(*mock_seq_file, Read(strlen(buffer1), _, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(fragment1),

            Return(Status::OK())))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(fragment2),

            Return(Status::OK())))

        .WillOnce(Return(Status::IOError()));



    Status s = ReadFileToString(&mock_env, file_name, &result_data);



    EXPECT_TRUE(s.ok());

    EXPECT_EQ(result_data, "Hello, World!");

}
