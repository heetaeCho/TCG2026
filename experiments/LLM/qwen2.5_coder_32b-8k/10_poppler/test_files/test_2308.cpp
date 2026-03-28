#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"

#include "poppler-private.h"

#include "Form.h"



using namespace testing;



class PopplerFormFieldTest_2308 : public Test {

protected:

    void SetUp() override {

        field = new PopplerFormField();

        formWidgetMock = std::make_unique<StrictMock<FormWidgetMock>>();

        field->widget = formWidgetMock.get();

    }



    void TearDown() override {

        delete field;

    }



    struct _PopplerFormField *field;

    std::unique_ptr<StrictMock<FormWidgetMock>> formWidgetMock;



    class FormWidgetMock : public FormWidget {

    public:

        MOCK_METHOD(FormFieldType, getType, (), (const, override));

    };

};



TEST_F(PopplerFormFieldTest_2308, GetFieldType_ReturnsButton_2308) {

    EXPECT_CALL(*formWidgetMock, getType()).WillOnce(Return(formButton));

    EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_BUTTON);

}



TEST_F(PopplerFormFieldTest_2308, GetFieldType_ReturnsText_2308) {

    EXPECT_CALL(*formWidgetMock, getType()).WillOnce(Return(formText));

    EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

}



TEST_F(PopplerFormFieldTest_2308, GetFieldType_ReturnsChoice_2308) {

    EXPECT_CALL(*formWidgetMock, getType()).WillOnce(Return(formChoice));

    EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

}



TEST_F(PopplerFormFieldTest_2308, GetFieldType_ReturnsSignature_2308) {

    EXPECT_CALL(*formWidgetMock, getType()).WillOnce(Return(formSignature));

    EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_SIGNATURE);

}



TEST_F(PopplerFormFieldTest_2308, GetFieldType_ReturnsUnknownForUnsupportedType_2308) {

    EXPECT_CALL(*formWidgetMock, getType()).WillOnce(Return(static_cast<FormFieldType>(-1)));

    EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_UNKNOWN);

}



TEST_F(PopplerFormFieldTest_2308, GetFieldType_ReturnsUnknownForNullField_2308) {

    EXPECT_EQ(poppler_form_field_get_field_type(nullptr), POPPLER_FORM_FIELD_UNKNOWN);

}
