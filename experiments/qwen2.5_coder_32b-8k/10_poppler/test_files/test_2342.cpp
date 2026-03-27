#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"



class PopplerFormFieldTest_2342 : public ::testing::Test {

protected:

    void SetUp() override {

        // Mocking FormWidgetChoice to test the interface function

        form_widget_choice = new testing::NiceMock<MockFormWidgetChoice>();

        field.widget = form_widget_choice;

    }



    void TearDown() override {

        delete form_widget_choice;

    }



    PopplerFormField field;

    MockFormWidgetChoice* form_widget_choice;



    class MockFormWidgetChoice : public FormWidgetChoice {

    public:

        using FormWidgetChoice::FormWidgetChoice;

        MOCK_METHOD(bool, isMultiSelect, (), (const));

    };

};



TEST_F(PopplerFormFieldTest_2342, CanSelectMultiple_ReturnsTrueWhenIsMultiSelectReturnsTrue_2342) {

    EXPECT_CALL(*form_widget_choice, isMultiSelect()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(poppler_form_field_choice_can_select_multiple(&field));

}



TEST_F(PopplerFormFieldTest_2342, CanSelectMultiple_ReturnsFalseWhenIsMultiSelectReturnsFalse_2342) {

    EXPECT_CALL(*form_widget_choice, isMultiSelect()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(poppler_form_field_choice_can_select_multiple(&field));

}



TEST_F(PopplerFormFieldTest_2342, CanSelectMultiple_TypeAssertionFailsIfWidgetIsNotFormChoice_2342) {

    // This test case cannot be directly tested as g_return_val_if_fail is a runtime assertion

    // and we assume the caller provides correct type. We mock the widget to not be FormWidgetChoice

    field.widget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

    EXPECT_FALSE(poppler_form_field_choice_can_select_multiple(&field));

    delete field.widget;

}
