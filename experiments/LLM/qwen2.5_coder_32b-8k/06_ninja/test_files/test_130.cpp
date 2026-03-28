#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    void Warning(const char* msg, ...);

}



class WarningTest : public ::testing::Test {};



TEST_F(WarningTest_130, NormalOperationWithSimpleMessage_130) {

    // This test case checks if the function can handle a simple message without any additional parameters.

    EXPECT_NO_THROW(Warning("This is a simple warning message."));

}



TEST_F(WarningTest_130, BoundaryConditionEmptyString_130) {

    // This test case checks if the function can handle an empty string as a message.

    EXPECT_NO_THROW(Warning(""));

}



TEST_F(WarningTest_130, NormalOperationWithFormatSpecifiers_130) {

    // This test case checks if the function can correctly handle format specifiers in the message.

    EXPECT_NO_THROW(Warning("This is a warning with an integer: %d", 42));

    EXPECT_NO_THROW(Warning("This is a warning with a float: %f", 3.14f));

}



TEST_F(WarningTest_130, ExceptionalCaseWithNullPointer_130) {

    // This test case checks if the function can handle a null pointer as a message.

    EXPECT_NO_THROW(Warning(nullptr)); // Assuming it does not crash and handles gracefully

}
