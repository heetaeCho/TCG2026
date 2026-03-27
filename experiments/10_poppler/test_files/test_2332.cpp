#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"

#include "poppler-private.h"

#include "Form.h"



using namespace testing;



class PopplerFormFieldTest_2332 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock FormWidgetText object

        form_widget_text = new NiceMock<FormWidgetText>(nullptr, nullptr, 0, Ref(), nullptr);

        

        // Create a PopplerFormField and assign the mock widget to it

        field.widget = form_widget_text;

    }



    void TearDown() override {

        delete form_widget_text;

    }



    FormWidgetText* form_widget_text;

    _PopplerFormField field;

};



TEST_F(PopplerFormFieldTest_2332, GetTextType_Normal_2332) {

    EXPECT_CALL(*form_widget_text, isMultiline()).WillOnce(Return(false));

    EXPECT_CALL(*form_widget_text, isFileSelect()).WillOnce(Return(false));



    PopplerFormTextType text_type = poppler_form_field_text_get_text_type(&field);

    EXPECT_EQ(text_type, POPPLER_FORM_TEXT_NORMAL);

}



TEST_F(PopplerFormFieldTest_2332, GetTextType_Multiline_2332) {

    EXPECT_CALL(*form_widget_text, isMultiline()).WillOnce(Return(true));

    EXPECT_CALL(*form_widget_text, isFileSelect()).WillOnce(Return(false));



    PopplerFormTextType text_type = poppler_form_field_text_get_text_type(&field);

    EXPECT_EQ(text_type, POPPLER_FORM_TEXT_MULTILINE);

}



TEST_F(PopplerFormFieldTest_2332, GetTextType_FileSelect_2332) {

    EXPECT_CALL(*form_widget_text, isMultiline()).WillOnce(Return(false));

    EXPECT_CALL(*form_widget_text, isFileSelect()).WillOnce(Return(true));



    PopplerFormTextType text_type = poppler_form_field_text_get_text_type(&field);

    EXPECT_EQ(text_type, POPPLER_FORM_TEXT_FILE_SELECT);

}



TEST_F(PopplerFormFieldTest_2332, GetTextType_MultilineAndFileSelect_2332) {

    EXPECT_CALL(*form_widget_text, isMultiline()).WillOnce(Return(true));

    EXPECT_CALL(*form_widget_text, isFileSelect()).WillOnce(Return(true));



    PopplerFormTextType text_type = poppler_form_field_text_get_text_type(&field);

    // Assuming the function returns MULTILINE when both conditions are true

    EXPECT_EQ(text_type, POPPLER_FORM_TEXT_MULTILINE);

}



TEST_F(PopplerFormFieldTest_2332, GetTextType_WrongFieldType_2332) {

    field.widget->type = formButton;



    EXPECT_THROW(poppler_form_field_text_get_text_type(&field), GError*);

}
