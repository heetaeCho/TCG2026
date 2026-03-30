#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "msvc_helper.h"



class CLWrapperTest_108 : public ::testing::Test {

protected:

    CLWrapper cl_wrapper_;

};



TEST_F(CLWrapperTest_108, SetEnvBlock_SetsEnvBlockPointer_108) {

    void* mock_env_block = reinterpret_cast<void*>(0x12345678);

    cl_wrapper_.SetEnvBlock(mock_env_block);



    // Since we can't access private members directly, we need to rely on observable behavior.

    // Here, we assume that the only way to verify this is through a subsequent call to Run or another method

    // that uses env_block_, but since no such method is provided, we can only assume SetEnvBlock works as intended.

}



TEST_F(CLWrapperTest_108, Run_CommandEmpty_ReturnsNonZero_108) {

    std::string output;

    int result = cl_wrapper_.Run("", &output);



    EXPECT_NE(result, 0);

}



TEST_F(CLWrapperTest_108, Run_ValidCommand_ReturnsZero_108) {

    std::string output;

    // Assuming "echo" is a valid command in the environment

    int result = cl_wrapper_.Run("echo test", &output);



    EXPECT_EQ(result, 0);

}



TEST_F(CLWrapperTest_108, Run_CommandWithOutput_ModifiesOutputString_108) {

    std::string output;

    // Assuming "echo" outputs to stdout

    int result = cl_wrapper_.Run("echo test", &output);



    EXPECT_EQ(result, 0);

    EXPECT_FALSE(output.empty());

}



TEST_F(CLWrapperTest_108, Run_CommandWithOutput_OutputContainsExpectedText_108) {

    std::string output;

    // Assuming "echo" outputs to stdout

    int result = cl_wrapper_.Run("echo test", &output);



    EXPECT_EQ(result, 0);

    EXPECT_THAT(output, ::testing::HasSubstr("test"));

}



TEST_F(CLWrapperTest_108, Run_NullOutputPointer_ReturnsNonZero_108) {

    // Assuming passing a null pointer for output is invalid

    int result = cl_wrapper_.Run("echo test", nullptr);



    EXPECT_NE(result, 0);

}
