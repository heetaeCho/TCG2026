#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"

#include "poppler-private.h"



class PopplerFormFieldTest_2339 : public ::testing::Test {

protected:

    void SetUp() override {

        // Mocking FormWidgetText

        form_widget_text = new testing::NiceMock<FormWidgetText>(nullptr, nullptr, 0, Ref(), nullptr);

        field.widget = form_widget_text;

    }



    void TearDown() override {

        delete form_widget_text;

    }



    PopplerFormField field;

    FormWidgetText* form_widget_text;

};



TEST_F(PopplerFormFieldTest_2339, IsPassword_ReturnsTrue_WhenFormWidgetTextIsPassword_2339) {

    EXPECT_CALL(*form_widget_text, isPassword()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(poppler_form_field_text_is_password(&field));

}



TEST_F(PopplerFormFieldTest_2339, IsPassword_ReturnsFalse_WhenFormWidgetTextIsNotPassword_2339) {

    EXPECT_CALL(*form_widget_text, isPassword()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(poppler_form_field_text_is_password(&field));

}



TEST_F(PopplerFormFieldTest_2339, IsPassword_AssertsOnIncorrectFieldType_2339) {

    field.widget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

    EXPECT_DEATH({ poppler_form_field_text_is_password(&field); }, "Assertion failed");

    delete field.widget;

}
