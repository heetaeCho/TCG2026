#include <gtest/gtest.h>

// Include necessary headers
#include "Form.h"

// Since _getButtonType is a static function in Form.cc, we need to access it.
// We'll include the source file or declare the function.
// Since it's static, we need to include the .cc file directly to access it in tests.
// Alternatively, we can re-declare it as extern for testing purposes.
// The most practical approach for testing a static function is to include the source.

// We need to access the static function. One approach is to include the .cc file.
// This is a common testing pattern for static functions.
#include "Form.cc"

class GetButtonTypeTest_1516 : public ::testing::Test {
protected:
};

TEST_F(GetButtonTypeTest_1516, ReturnsCheckForFormButtonCheck_1516) {
    const char *result = _getButtonType(formButtonCheck);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "check");
}

TEST_F(GetButtonTypeTest_1516, ReturnsPushForFormButtonPush_1516) {
    const char *result = _getButtonType(formButtonPush);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "push");
}

TEST_F(GetButtonTypeTest_1516, ReturnsRadioForFormButtonRadio_1516) {
    const char *result = _getButtonType(formButtonRadio);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "radio");
}

TEST_F(GetButtonTypeTest_1516, ReturnsUnknownForInvalidType_1516) {
    // Cast an invalid integer value to FormButtonType to test the default case
    const char *result = _getButtonType(static_cast<FormButtonType>(99));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "unknown");
}

TEST_F(GetButtonTypeTest_1516, ReturnsUnknownForNegativeValue_1516) {
    const char *result = _getButtonType(static_cast<FormButtonType>(-1));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "unknown");
}

TEST_F(GetButtonTypeTest_1516, ReturnsUnknownForValueThree_1516) {
    // Value 3 is just beyond the defined enum range (0, 1, 2)
    const char *result = _getButtonType(static_cast<FormButtonType>(3));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "unknown");
}

TEST_F(GetButtonTypeTest_1516, CheckEnumValueZero_1516) {
    // formButtonCheck is defined as 0
    EXPECT_EQ(formButtonCheck, 0);
    const char *result = _getButtonType(static_cast<FormButtonType>(0));
    EXPECT_STREQ(result, "check");
}

TEST_F(GetButtonTypeTest_1516, CheckEnumValueOne_1516) {
    // formButtonPush is defined as 1
    EXPECT_EQ(formButtonPush, 1);
    const char *result = _getButtonType(static_cast<FormButtonType>(1));
    EXPECT_STREQ(result, "push");
}

TEST_F(GetButtonTypeTest_1516, CheckEnumValueTwo_1516) {
    // formButtonRadio is defined as 2
    EXPECT_EQ(formButtonRadio, 2);
    const char *result = _getButtonType(static_cast<FormButtonType>(2));
    EXPECT_STREQ(result, "radio");
}

TEST_F(GetButtonTypeTest_1516, ReturnedStringIsNotNull_1516) {
    // Verify all known types return non-null strings
    EXPECT_NE(_getButtonType(formButtonCheck), nullptr);
    EXPECT_NE(_getButtonType(formButtonPush), nullptr);
    EXPECT_NE(_getButtonType(formButtonRadio), nullptr);
    EXPECT_NE(_getButtonType(static_cast<FormButtonType>(100)), nullptr);
}

TEST_F(GetButtonTypeTest_1516, ReturnsUnknownForLargeValue_1516) {
    const char *result = _getButtonType(static_cast<FormButtonType>(1000));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "unknown");
}
