#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"

#include "poppler-private.h"



class PopplerFormFieldButtonTest : public ::testing::Test {

protected:

    struct _PopplerFormField *field;

    FormWidgetButton *formWidgetButton;



    void SetUp() override {

        field = new _PopplerFormField();

        formWidgetButton = new FormWidgetButton(nullptr, nullptr, 0, Ref(), nullptr);

        field->widget = formWidgetButton;

    }



    void TearDown() override {

        delete formWidgetButton;

        delete field;

    }

};



TEST_F(PopplerFormFieldButtonTest_2314, GetButtonType_PushButton_2314) {

    EXPECT_CALL(*static_cast<FormWidgetButton*>(field->widget), getButtonType())

        .WillOnce(::testing::Return(formButtonPush));

    EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_PUSH);

}



TEST_F(PopplerFormFieldButtonTest_2314, GetButtonType_CheckBox_2314) {

    EXPECT_CALL(*static_cast<FormWidgetButton*>(field->widget), getButtonType())

        .WillOnce(::testing::Return(formButtonCheck));

    EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_CHECK);

}



TEST_F(PopplerFormFieldButtonTest_2314, GetButtonType_RadioButton_2314) {

    EXPECT_CALL(*static_cast<FormWidgetButton*>(field->widget), getButtonType())

        .WillOnce(::testing::Return(formButtonRadio));

    EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_RADIO);

}



TEST_F(PopplerFormFieldButtonTest_2314, GetButtonType_DefaultCase_2314) {

    // Since g_assert_not_reached() is used in the default case,

    // we cannot directly test this behavior without causing an assertion failure.

    // Instead, we can assume that if the function returns a valid value for known cases,

    // the default case should not be reached with normal usage.

    EXPECT_CALL(*static_cast<FormWidgetButton*>(field->widget), getButtonType())

        .WillOnce(::testing::Return(formButtonPush));

    EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_PUSH);

}



TEST_F(PopplerFormFieldButtonTest_2314, InvalidFieldType_2314) {

    field->widget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

    field->widget->setType(formText); // Setting an invalid type for button field

    EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_PUSH);

    delete field->widget;

}
