#include <gtest/gtest.h>

#include "Form.h"



class FormButtonTypeTest : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(FormButtonTypeTest_1516, GetButtonType_PushButton_1516) {

    EXPECT_STREQ(_getButtonType(formButtonPush), "push");

}



TEST_F(FormButtonTypeTest_1516, GetButtonType_CheckButton_1516) {

    EXPECT_STREQ(_getButtonType(formButtonCheck), "check");

}



TEST_F(FormButtonTypeTest_1516, GetButtonType_RadioButton_1516) {

    EXPECT_STREQ(_getButtonType(formButtonRadio), "radio");

}



TEST_F(FormButtonTypeTest_1516, GetButtonType_DefaultCase_1516) {

    // Assuming an invalid enum value like -1 is passed

    EXPECT_STREQ(_getButtonType(static_cast<FormButtonType>(-1)), "unknown");

}



TEST_F(FormButtonTypeTest_1516, GetButtonType_UnhandledEnumValue_1516) {

    // Assuming an unhandled enum value like 3 is passed

    EXPECT_STREQ(_getButtonType(static_cast<FormButtonType>(3)), "unknown");

}
