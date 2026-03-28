#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "msvc_helper_main-win32.cc"

#include "clparser.h"

#include "msvc_helper.h"



using ::testing::_;

using ::testing::Return;

using ::testing::SetArgReferee;

using ::testing::StrEq;



class CLWrapperMock : public CLWrapper {

public:

    MOCK_METHOD2(Run, int(const std::string&, std::string*));

};



class CLParserMock : public CLParser {

public:

    MOCK_METHOD4(Parse, bool(const std::string&, const std::string&, std::string*, std::string*));

};



class MSVCHelperMainTest_109 : public ::testing::Test {

protected:

    void SetUp() override {

        // Mock objects

        cl_wrapper_mock = new CLWrapperMock();

        cl_parser_mock = new CLParserMock();



        // Save original pointers and replace with mocks

        original_cl_wrapper = new CLWrapper;

        *reinterpret_cast<CLWrapper**>(&cl) = cl_wrapper_mock;



        original_cl_parser = new CLParser;

        *reinterpret_cast<CLParser**>(&parser) = cl_parser_mock;

    }



    void TearDown() override {

        // Restore original pointers

        *reinterpret_cast<CLWrapper**>(&cl) = original_cl_wrapper;

        delete cl_wrapper_mock;



        *reinterpret_cast<CLParser**>(&parser) = original_cl_parser;

        delete cl_parser_mock;

    }



    CLWrapper* original_cl_wrapper;

    CLParser* original_cl_parser;

    CLWrapperMock* cl_wrapper_mock;

    CLParserMock* cl_parser_mock;

};



TEST_F(MSVCHelperMainTest_109, NormalOperation_NoOutputFile_109) {

    char* argv[] = { "msvc_helper", "-- command args" };

    int argc = 3;



    EXPECT_CALL(*cl_wrapper_mock, Run(StrEq("command args"), _)).WillOnce(DoAll(SetArgReferee<1>("output"), Return(0)));



    int result = MSVCHelperMain(argc, argv);

    EXPECT_EQ(result, 0);

}



TEST_F(MSVCHelperMainTest_109, NormalOperation_WithOutputFile_109) {

    char* argv[] = { "msvc_helper", "-o", "output.txt", "-- command args" };

    int argc = 5;



    EXPECT_CALL(*cl_wrapper_mock, Run(StrEq("command args"), _)).WillOnce(DoAll(SetArgReferee<1>("output"), Return(0)));

    EXPECT_CALL(*cl_parser_mock, Parse(StrEq("output"), "", _, _)).WillOnce(Return(true));



    int result = MSVCHelperMain(argc, argv);

    EXPECT_EQ(result, 0);

}



TEST_F(MSVCHelperMainTest_109, MissingCommandArgs_109) {

    char* argv[] = { "msvc_helper", "-o", "output.txt" };

    int argc = 3;



    int result = MSVCHelperMain(argc, argv);

    EXPECT_EQ(result, 0); // Should print usage and return 0

}



TEST_F(MSVCHelperMainTest_109, EnvFileReadSuccess_109) {

    char* argv[] = { "msvc_helper", "-e", "env.txt", "-- command args" };

    int argc = 5;



    EXPECT_CALL(*cl_wrapper_mock, Run(StrEq("command args"), _)).WillOnce(DoAll(SetArgReferee<1>("output"), Return(0)));



    int result = MSVCHelperMain(argc, argv);

    EXPECT_EQ(result, 0); // Assuming the env file is read successfully

}



TEST_F(MSVCHelperMainTest_109, EnvFileReadFailure_109) {

    char* argv[] = { "msvc_helper", "-e", "nonexistent.txt", "-- command args" };

    int argc = 5;



    EXPECT_CALL(*cl_wrapper_mock, Run(_, _)).Times(0); // Should not proceed to run



    int result = MSVCHelperMain(argc, argv);

    EXPECT_EQ(result, 1); // Assuming the env file read fails and returns a non-zero exit code

}



TEST_F(MSVCHelperMainTest_109, ParseFailure_109) {

    char* argv[] = { "msvc_helper", "-o", "output.txt", "-- command args" };

    int argc = 5;



    EXPECT_CALL(*cl_wrapper_mock, Run(StrEq("command args"), _)).WillOnce(DoAll(SetArgReferee<1>("output"), Return(0)));

    EXPECT_CALL(*cl_parser_mock, Parse(_, _, _, _)).WillOnce(Return(false));



    int result = MSVCHelperMain(argc, argv);

    EXPECT_EQ(result, 1); // Assuming parse failure results in a non-zero exit code

}
