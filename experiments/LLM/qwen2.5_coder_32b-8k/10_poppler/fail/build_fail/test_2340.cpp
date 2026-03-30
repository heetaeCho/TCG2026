#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"

#include "poppler-private.h"

#include "Form.h"



// Mocking FormWidgetChoice to simulate its behavior without accessing internal state

class MockFormWidgetChoice : public FormWidgetChoice {

public:

    MOCK_METHOD(bool, isCombo, (), (const, override));

};



TEST_F(FormFieldChoiceTest_2340, GetChoiceType_Returns_COMBO_For_Combo_Widget_2340) {

    // Arrange

    PDFDoc* doc = nullptr;

    Object* dictObj = nullptr;

    unsigned int num = 0;

    Ref ref;

    FormField* p = nullptr;

    MockFormWidgetChoice mockFormWidgetChoice(doc, dictObj, num, ref, p);

    EXPECT_CALL(mockFormWidgetChoice, isCombo()).WillOnce(testing::Return(true));



    PopplerFormField field;

    field.widget = &mockFormWidgetChoice;



    // Act

    PopplerFormChoiceType result = poppler_form_field_choice_get_choice_type(&field);



    // Assert

    ASSERT_EQ(result, POPPLER_FORM_CHOICE_COMBO);

}



TEST_F(FormFieldChoiceTest_2340, GetChoiceType_Returns_LIST_For_List_Widget_2340) {

    // Arrange

    PDFDoc* doc = nullptr;

    Object* dictObj = nullptr;

    unsigned int num = 0;

    Ref ref;

    FormField* p = nullptr;

    MockFormWidgetChoice mockFormWidgetChoice(doc, dictObj, num, ref, p);

    EXPECT_CALL(mockFormWidgetChoice, isCombo()).WillOnce(testing::Return(false));



    PopplerFormField field;

    field.widget = &mockFormWidgetChoice;



    // Act

    PopplerFormChoiceType result = poppler_form_field_choice_get_choice_type(&field);



    // Assert

    ASSERT_EQ(result, POPPLER_FORM_CHOICE_LIST);

}



TEST_F(FormFieldChoiceTest_2340, GetChoiceType_Returns_COMBO_For_Null_Widget_2340) {

    // Arrange

    PopplerFormField field;

    field.widget = nullptr;



    // Act & Assert

    EXPECT_DEATH(poppler_form_field_choice_get_choice_type(&field), ".*g_return_val_if_fail.*");

}



TEST_F(FormFieldChoiceTest_2340, GetChoiceType_Returns_COMBO_For_Wrong_Type_Widget_2340) {

    // Arrange

    PDFDoc* doc = nullptr;

    Object* dictObj = nullptr;

    unsigned int num = 0;

    Ref ref;

    FormField* p = nullptr;



    class MockFormWidgetOther : public FormWidget {

    public:

        MOCK_METHOD(FormFieldType, getType, (), (const, override));

    };



    MockFormWidgetOther mockFormWidgetOther;

    EXPECT_CALL(mockFormWidgetOther, getType()).WillOnce(testing::Return(formText));



    PopplerFormField field;

    field.widget = &mockFormWidgetOther;



    // Act & Assert

    EXPECT_DEATH(poppler_form_field_choice_get_choice_type(&field), ".*g_return_val_if_fail.*");

}
