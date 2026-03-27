#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/c.cc"  // Assuming this file contains the function to be tested



namespace {



class CopyStringTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if necessary

    }



    void TearDown() override {

        // Cleanup code, if necessary

    }

};



TEST_F(CopyStringTest_219, NormalOperation_219) {

    const std::string input = "Hello, World!";

    char* result = CopyString(input);

    EXPECT_STREQ(result, input.c_str());

    free(result);  // Clean up the allocated memory

}



TEST_F(CopyStringTest_219, EmptyString_219) {

    const std::string input = "";

    char* result = CopyString(input);

    EXPECT_STREQ(result, input.c_str());

    free(result);  // Clean up the allocated memory

}



TEST_F(CopyStringTest_219, SingleCharacter_219) {

    const std::string input = "A";

    char* result = CopyString(input);

    EXPECT_STREQ(result, input.c_str());

    free(result);  // Clean up the allocated memory

}



TEST_F(CopyStringTest_219, LargeString_219) {

    const std::string input(1024, 'A');  // Large string of 'A's

    char* result = CopyString(input);

    EXPECT_STREQ(result, input.c_str());

    free(result);  // Clean up the allocated memory

}



}  // namespace
