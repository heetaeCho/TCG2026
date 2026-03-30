#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util.cc"  // Assuming util.cc contains the StringNeedsShellEscaping function



using namespace testing;



// Test fixture for StringNeedsShellEscaping tests

class StringNeedsShellEscapingTest_138 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(StringNeedsShellEscapingTest_138, NormalOperation_SafeString_138) {

    EXPECT_FALSE(StringNeedsShellEscaping("safe_string"));

}



TEST_F(StringNeedsShellEscapingTest_138, NormalOperation_UnsafeString_138) {

    EXPECT_TRUE(StringNeedsShellEscaping("unsafe;string"));

}



TEST_F(StringNeedsShellEscapingTest_138, BoundaryCondition_EmptyString_138) {

    EXPECT_FALSE(StringNeedsShellEscaping(""));

}



TEST_F(StringNeedsShellEscapingTest_138, BoundaryCondition_SingleSafeChar_138) {

    EXPECT_FALSE(StringNeedsShellEscaping("a"));

}



TEST_F(StringNeedsShellEscapingTest_138, BoundaryCondition_SingleUnsafeChar_138) {

    EXPECT_TRUE(StringNeedsShellEscaping(";"));

}



TEST_F(StringNeedsShellEscapingTest_138, ExceptionalCase_AllSafeChars_138) {

    EXPECT_FALSE(StringNeedsShellEscaping("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_./"));

}



TEST_F(StringNeedsShellEscapingTest_138, ExceptionalCase_AllUnsafeChars_138) {

    EXPECT_TRUE(StringNeedsShellEscaping("!@#$%^&*()+=[]{}|\\:;',.<>?/~`\""));

}
