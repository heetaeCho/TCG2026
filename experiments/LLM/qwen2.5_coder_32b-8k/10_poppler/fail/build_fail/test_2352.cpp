#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"

#include "poppler-private.h"



class PopplerFormFieldChoiceTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Mock FormWidgetChoice and its dependencies

        formField = new PopplerFormField();

        formField->widget = new FormWidgetChoice(nullptr, nullptr, 0, Ref(), nullptr);

    }



    void TearDown() override {

        delete formField->widget;

        delete formField;

    }



    PopplerFormField* formField;

};



TEST_F(PopplerFormFieldChoiceTest_2352, GetText_NormalOperation_2352) {

    // Arrange

    static_cast<FormWidgetChoice*>(formField->widget)->setEditChoice(std::make_unique<GooString>("Test Choice"));



    // Act

    gchar* result = poppler_form_field_choice_get_text(formField);



    // Assert

    ASSERT_STREQ(result, "Test Choice");

    g_free(result);

}



TEST_F(PopplerFormFieldChoiceTest_2352, GetText_EmptyChoice_2352) {

    // Arrange

    static_cast<FormWidgetChoice*>(formField->widget)->setEditChoice(nullptr);



    // Act

    gchar* result = poppler_form_field_choice_get_text(formField);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerFormFieldChoiceTest_2352, GetText_WrongFieldType_2352) {

    // Arrange

    formField->widget->setType(formButton);  // Incorrect type



    // Act & Assert

    EXPECT_DEATH(poppler_form_field_choice_get_text(formField), ".*");

}



TEST_F(PopplerFormFieldChoiceTest_2352, GetText_ExceptionalCase_2352) {

    // Arrange: Simulate a case where getEditChoice returns a null pointer internally

    static_cast<FormWidgetChoice*>(formField->widget)->setEditChoice(nullptr);



    // Act

    gchar* result = poppler_form_field_choice_get_text(formField);



    // Assert

    ASSERT_EQ(result, nullptr);

}
