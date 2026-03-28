#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"

#include "poppler-private.h"



using namespace testing;



// Mocking dependencies if necessary, here FormWidgetText and its methods.

class MockFormWidgetText : public FormWidgetText {

public:

    MOCK_METHOD(int, getMaxLen, (), (const, override));

};



TEST_F(PopplerFormFieldTest_2335, GetMaxLen_ReturnsCorrectValueForValidFormTextField_2335) {

    // Arrange

    PDFDoc* mockDoc = nullptr;

    Object* mockDictObj = nullptr;

    unsigned int num = 0;

    Ref mockRef;

    FormField* mockFormField = nullptr;



    auto mockWidgetText = std::make_unique<MockFormWidgetText>(mockDoc, mockDictObj, num, mockRef, mockFormField);

    EXPECT_CALL(*mockWidgetText, getMaxLen()).WillOnce(Return(123));



    PopplerFormField formField;

    formField.widget = mockWidgetText.release();



    // Act

    gint result = poppler_form_field_text_get_max_len(&formField);



    // Assert

    EXPECT_EQ(result, 123);

}



TEST_F(PopplerFormFieldTest_2335, GetMaxLen_ReturnsZeroForInvalidFormTextFieldType_2335) {

    // Arrange

    PDFDoc* mockDoc = nullptr;

    Object* mockDictObj = nullptr;

    unsigned int num = 0;

    Ref mockRef;

    FormField* mockFormField = nullptr;



    auto mockWidgetButton = std::make_unique<FormWidget>(mockDoc, mockDictObj, num, mockRef, mockFormField);

    mockWidgetButton->type = formButton; // Invalid type for text field



    PopplerFormField formField;

    formField.widget = mockWidgetButton.release();



    // Act

    gint result = poppler_form_field_text_get_max_len(&formField);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(PopplerFormFieldTest_2335, GetMaxLen_HandlesNullPointer_ReturnsZero_2335) {

    // Arrange

    PopplerFormField* nullFormField = nullptr;



    // Act & Assert

    gint result = poppler_form_field_text_get_max_len(nullFormField);

    EXPECT_EQ(result, 0);

}



TEST_F(PopplerFormFieldTest_2335, GetMaxLen_HandlesNullWidget_ReturnsZero_2335) {

    // Arrange

    PopplerFormField formField;

    formField.widget = nullptr;



    // Act & Assert

    gint result = poppler_form_field_text_get_max_len(&formField);

    EXPECT_EQ(result, 0);

}
