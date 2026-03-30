#include <gtest/gtest.h>

#include "re2/parse.cc"

#include "absl/strings/string_view.h"



using namespace re2;



// Fixture class for IsValidCaptureName tests

class IsValidCaptureNameTest_532 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



// Test normal operation with valid capture names

TEST_F(IsValidCaptureNameTest_532, ValidCaptureNames_532) {

    EXPECT_TRUE(IsValidCaptureName("Valid1"));

    EXPECT_TRUE(IsValidCaptureName("valid_name"));

    EXPECT_TRUE(IsValidCaptureName("_validName9"));

}



// Test boundary conditions with single character valid capture names

TEST_F(IsValidCaptureNameTest_532, SingleCharValidNames_532) {

    EXPECT_TRUE(IsValidCaptureName("A"));

    EXPECT_TRUE(IsValidCaptureName("a"));

    EXPECT_TRUE(IsValidCaptureName("_"));

}



// Test boundary conditions with empty string

TEST_F(IsValidCaptureNameTest_532, EmptyString_532) {

    EXPECT_FALSE(IsValidCaptureName(""));

}



// Test exceptional cases with invalid characters

TEST_F(IsValidCaptureNameTest_532, InvalidCharacters_532) {

    EXPECT_FALSE(IsValidCaptureName("1Invalid"));

    EXPECT_FALSE(IsValidCaptureName("invalid-name"));

    EXPECT_FALSE(IsValidCaptureName("invalid name"));

    EXPECT_FALSE(IsValidCaptureName("invalid@name"));

}



// Test exceptional cases with only invalid characters

TEST_F(IsValidCaptureNameTest_532, OnlyInvalidCharacters_532) {

    EXPECT_FALSE(IsValidCaptureName("12345"));

    EXPECT_FALSE(IsValidCaptureName("!@#$%"));

    EXPECT_FALSE(IsValidCaptureName(" "));

}



// Test boundary conditions with very long valid capture names

TEST_F(IsValidCaptureNameTest_532, VeryLongValidNames_532) {

    std::string long_name(1000, 'a');

    EXPECT_TRUE(IsValidCaptureName(long_name));

}
