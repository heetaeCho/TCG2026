#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"



using namespace testing;



class PopplerFormFieldTest : public ::testing::Test {

protected:

    MockFunction<const GooString*()> mockGetAlternateUiName;

    FormWidget* formWidget;

    PopplerFormField* popplerFormField;



    void SetUp() override {

        formWidget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

        EXPECT_CALL(*formWidget, getAlternateUiName())

            .WillRepeatedly(Invoke(mockGetAlternateUiName.AsStdFunction()));

        popplerFormField = new PopplerFormField();

        popplerFormField->widget = formWidget;

    }



    void TearDown() override {

        delete popplerFormField;

        delete formWidget;

    }

};



TEST_F(PopplerFormFieldTest_2320, GetAlternateUiName_ReturnsNonNullString_2320) {

    const char* expectedString = "Sample Alternate UI Name";

    GooString gooString(expectedString);

    EXPECT_CALL(mockGetAlternateUiName).WillOnce(Return(&gooString));



    gchar* result = poppler_form_field_get_alternate_ui_name(popplerFormField);

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, expectedString);

    g_free(result);

}



TEST_F(PopplerFormFieldTest_2320, GetAlternateUiName_ReturnsNull_2320) {

    EXPECT_CALL(mockGetAlternateUiName).WillOnce(Return(nullptr));



    gchar* result = poppler_form_field_get_alternate_ui_name(popplerFormField);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerFormFieldTest_2320, GetAlternateUiName_InvalidField_ReturnsNull_2320) {

    PopplerFormField* invalidPopplerFormField = nullptr;



    gchar* result = poppler_form_field_get_alternate_ui_name(invalidPopplerFormField);

    ASSERT_EQ(result, nullptr);

}
