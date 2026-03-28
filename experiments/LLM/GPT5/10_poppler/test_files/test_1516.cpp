#include <gtest/gtest.h>

// Forward declaration of the function to be tested
static const char *_getButtonType(FormButtonType type);

class GetButtonTypeTest_1516 : public ::testing::Test {
protected:
    // Any setup or tear down code can go here if necessary
};

// Test normal operation: formButtonPush
TEST_F(GetButtonTypeTest_1516, GetButtonTypePush_1516) {
    // Test for formButtonPush
    EXPECT_STREQ(_getButtonType(formButtonPush), "push");
}

// Test normal operation: formButtonCheck
TEST_F(GetButtonTypeTest_1516, GetButtonTypeCheck_1516) {
    // Test for formButtonCheck
    EXPECT_STREQ(_getButtonType(formButtonCheck), "check");
}

// Test normal operation: formButtonRadio
TEST_F(GetButtonTypeTest_1516, GetButtonTypeRadio_1516) {
    // Test for formButtonRadio
    EXPECT_STREQ(_getButtonType(formButtonRadio), "radio");
}

// Test boundary condition: Invalid FormButtonType (not recognized)
TEST_F(GetButtonTypeTest_1516, GetButtonTypeUnknown_1516) {
    // Test for an invalid FormButtonType, expecting "unknown"
    EXPECT_STREQ(_getButtonType(static_cast<FormButtonType>(-1)), "unknown");
}