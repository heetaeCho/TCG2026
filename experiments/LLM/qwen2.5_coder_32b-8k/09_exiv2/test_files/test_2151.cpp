#include <gtest/gtest.h>

#include "exiv2/error.hpp"



namespace {



using namespace Exiv2;



// Test fixture for Error class tests

class ErrorTest_2151 : public ::testing::Test {

protected:

    // No setup or teardown required as the Error class is stateless and immutable

};



TEST_F(ErrorTest_2151, ConstructWithCodeOnly_2151) {

    ErrorCode code = 404;

    Error error(code);

    EXPECT_EQ(error.code(), code);

}



TEST_F(ErrorTest_2151, ConstructWithCodeAndOneArg_2151) {

    ErrorCode code = 404;

    std::string arg1 = "Not Found";

    Error error(code, arg1);

    EXPECT_EQ(error.code(), code);

    // Assuming what() includes the arguments

    EXPECT_TRUE(std::string(error.what()).find(arg1) != std::string::npos);

}



TEST_F(ErrorTest_2151, ConstructWithCodeAndTwoArgs_2151) {

    ErrorCode code = 404;

    std::string arg1 = "Not Found";

    std::string arg2 = "/path/to/resource";

    Error error(code, arg1, arg2);

    EXPECT_EQ(error.code(), code);

    // Assuming what() includes the arguments

    EXPECT_TRUE(std::string(error.what()).find(arg1) != std::string::npos);

    EXPECT_TRUE(std::string(error.what()).find(arg2) != std::string::npos);

}



TEST_F(ErrorTest_2151, ConstructWithCodeAndThreeArgs_2151) {

    ErrorCode code = 404;

    std::string arg1 = "Not Found";

    std::string arg2 = "/path/to/resource";

    std::string arg3 = "GET";

    Error error(code, arg1, arg2, arg3);

    EXPECT_EQ(error.code(), code);

    // Assuming what() includes the arguments

    EXPECT_TRUE(std::string(error.what()).find(arg1) != std::string::npos);

    EXPECT_TRUE(std::string(error.what()).find(arg2) != std::string::npos);

    EXPECT_TRUE(std::string(error.what()).find(arg3) != std::string::npos);

}



TEST_F(ErrorTest_2151, WhatMethodReturnsNonNullPointer_2151) {

    ErrorCode code = 404;

    Error error(code);

    EXPECT_NE(error.what(), nullptr);

}



// Boundary conditions

TEST_F(ErrorTest_2151, ConstructWithCodeAndEmptyStrings_2151) {

    ErrorCode code = 404;

    std::string arg1 = "";

    std::string arg2 = "";

    std::string arg3 = "";

    Error error(code, arg1, arg2, arg3);

    EXPECT_EQ(error.code(), code);

    // Assuming what() does not crash with empty strings

    EXPECT_TRUE(std::string(error.what()).empty() || std::string(error.what()) == "404");

}



// Exceptional or error cases

TEST_F(ErrorTest_2151, ConstructWithInvalidErrorCode_2151) {

    ErrorCode code = -1; // Assuming -1 is an invalid error code

    Error error(code);

    EXPECT_EQ(error.code(), code);

    // Assuming what() handles invalid codes gracefully

    EXPECT_NE(error.what(), nullptr);

}



}  // namespace
