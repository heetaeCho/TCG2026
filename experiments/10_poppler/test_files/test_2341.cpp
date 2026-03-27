#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"

#include "poppler-private.h"



using ::testing::NiceMock;

using ::testing::_;



class MockFormWidgetChoice : public FormWidgetChoice {

public:

    MOCK_CONST_METHOD0(hasEdit, bool());

};



class PopplerFormFieldTest_2341 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_form_widget_choice = new NiceMock<MockFormWidgetChoice>(nullptr, nullptr, 0, Ref(), nullptr);

        poppler_form_field = new PopplerFormField();

        poppler_form_field->widget = mock_form_widget_choice;

    }



    void TearDown() override {

        delete poppler_form_field;

        delete mock_form_widget_choice;

    }



    MockFormWidgetChoice* mock_form_widget_choice;

    PopplerFormField* poppler_form_field;

};



TEST_F(PopplerFormFieldTest_2341, IsEditable_ReturnsTrueWhenHasEditIsTrue_2341) {

    EXPECT_CALL(*mock_form_widget_choice, hasEdit()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(poppler_form_field_choice_is_editable(poppler_form_field));

}



TEST_F(PopplerFormFieldTest_2341, IsEditable_ReturnsFalseWhenHasEditIsFalse_2341) {

    EXPECT_CALL(*mock_form_widget_choice, hasEdit()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(poppler_form_field_choice_is_editable(poppler_form_field));

}



TEST_F(PopplerFormFieldTest_2341, IsEditable_AssertsWhenWidgetIsNotFormChoice_2341) {

    poppler_form_field->widget = new FormWidget(nullptr, nullptr);

    EXPECT_DEATH(poppler_form_field_choice_is_editable(poppler_form_field), ".*g_return_val_if_fail.*");

    delete poppler_form_field->widget;

}
