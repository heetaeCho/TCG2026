#include <gtest/gtest.h>

#include "exiv2/error.hpp"



using namespace Exiv2;



// Test fixture for Error class tests

class ErrorTest_2162 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any, goes here.

    }



    void TearDown() override {

        // Teardown code, if any, goes here.

    }

};



// Test normal operation with no arguments

TEST_F(ErrorTest_2162, ConstructorWithErrorCodeOnly_2162) {

    Error error(ErrorCode::kerGeneralError);

    EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);

}



// Test construction with one argument

TEST_F(ErrorTest_2162, ConstructorWithOneArgument_2162) {

    Error error(ErrorCode::kerGeneralError, "arg1");

    EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);

}



// Test construction with two arguments

TEST_F(ErrorTest_2162, ConstructorWithTwoArguments_2162) {

    Error error(ErrorCode::kerGeneralError, "arg1", "arg2");

    EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);

}



// Test construction with three arguments

TEST_F(ErrorTest_2162, ConstructorWithThreeArguments_2162) {

    Error error(ErrorCode::kerGeneralError, "arg1", "arg2", "arg3");

    EXPECT_EQ(error.code(), ErrorCode::kerGeneralError);

}



// Test what() method returns non-null pointer

TEST_F(ErrorTest_2162, WhatMethodReturnsNonNull_2162) {

    Error error(ErrorCode::kerGeneralError);

    EXPECT_NE(error.what(), nullptr);

}



// Test boundary condition with minimum enum value for ErrorCode

TEST_F(ErrorTest_2162, ConstructorWithMinErrorCode_2162) {

    Error error(static_cast<ErrorCode>(0));

    EXPECT_EQ(error.code(), static_cast<ErrorCode>(0));

}



// Test boundary condition with maximum enum value for ErrorCode (assuming a reasonable max value)

TEST_F(ErrorTest_2162, ConstructorWithMaxErrorCode_2162) {

    Error error(ErrorCode::kerLastErrorCode); // Assuming kerLastErrorCode is the last valid ErrorCode

    EXPECT_EQ(error.code(), ErrorCode::kerLastErrorCode);

}



// Test exceptional case with invalid ErrorCode (if observable)

TEST_F(ErrorTest_2162, ConstructorWithInvalidErrorCode_2162) {

    Error error(static_cast<ErrorCode>(-1)); // Assuming -1 is an invalid ErrorCode

    EXPECT_EQ(error.code(), static_cast<ErrorCode>(-1));

}
