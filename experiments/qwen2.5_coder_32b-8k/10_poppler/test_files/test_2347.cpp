#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"

#include "Form.h"



using ::testing::NiceMock;

using ::testing::_;



class MockFormWidgetChoice : public FormWidgetChoice {

public:

    MOCK_METHOD(bool, isSelected, (int i), (const override));

};



class PopplerFormFieldTest_2347 : public ::testing::Test {

protected:

    void SetUp() override {

        field = new PopplerFormField();

        formWidgetChoiceMock = new NiceMock<MockFormWidgetChoice>(nullptr, nullptr, 0, Ref(), nullptr);

        field->widget = formWidgetChoiceMock;

    }



    void TearDown() override {

        delete field->widget;

        delete field;

    }



    PopplerFormField* field;

    MockFormWidgetChoice* formWidgetChoiceMock;

};



TEST_F(PopplerFormFieldTest_2347, IsItemSelected_ReturnsTrueForSelectedIndex_2347) {

    EXPECT_CALL(*formWidgetChoiceMock, isSelected(0)).WillOnce(::testing::Return(true));

    ASSERT_TRUE(poppler_form_field_choice_is_item_selected(field, 0));

}



TEST_F(PopplerFormFieldTest_2347, IsItemSelected_ReturnsFalseForDeselectedIndex_2347) {

    EXPECT_CALL(*formWidgetChoiceMock, isSelected(1)).WillOnce(::testing::Return(false));

    ASSERT_FALSE(poppler_form_field_choice_is_item_selected(field, 1));

}



TEST_F(PopplerFormFieldTest_2347, IsItemSelected_BoundaryConditionLowerIndex_2347) {

    EXPECT_CALL(*formWidgetChoiceMock, isSelected(0)).WillOnce(::testing::Return(true));

    ASSERT_TRUE(poppler_form_field_choice_is_item_selected(field, 0));

}



TEST_F(PopplerFormFieldTest_2347, IsItemSelected_BoundaryConditionUpperIndex_2347) {

    EXPECT_CALL(*formWidgetChoiceMock, isSelected(1)).WillOnce(::testing::Return(false));

    ASSERT_FALSE(poppler_form_field_choice_is_item_selected(field, 1));

}



TEST_F(PopplerFormFieldTest_2347, IsItemSelected_OutOfBoundsLowerIndex_ReturnsFalse_2347) {

    ASSERT_FALSE(poppler_form_field_choice_is_item_selected(field, -1));

}



TEST_F(PopplerFormFieldTest_2347, IsItemSelected_OutOfBoundsUpperIndex_ReturnsFalse_2347) {

    EXPECT_CALL(*formWidgetChoiceMock, getNumChoices()).WillOnce(::testing::Return(1));

    ASSERT_FALSE(poppler_form_field_choice_is_item_selected(field, 2));

}



TEST_F(PopplerFormFieldTest_2347, IsItemSelected_NullField_ReturnsFalse_2347) {

    field = nullptr;

    ASSERT_FALSE(poppler_form_field_choice_is_item_selected(field, 0));

}
