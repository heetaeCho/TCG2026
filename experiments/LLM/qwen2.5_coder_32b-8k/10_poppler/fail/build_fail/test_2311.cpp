#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.h"

}



using namespace testing;



class PopplerFormFieldTest : public Test {

protected:

    struct _PopplerFormField field;

    FormWidget formWidget;



    void SetUp() override {

        field.widget = &formWidget;

        // Assuming default constructor initializes isReadOnly to false

    }

};



TEST_F(PopplerFormFieldTest_2311, IsReadOnly_ReturnsFalse_WhenNotSetToReadOnly_2311) {

    EXPECT_FALSE(poppler_form_field_is_read_only(&field));

}



TEST_F(PopplerFormFieldTest_2311, IsReadOnly_ReturnsTrue_WhenSetToReadOnly_2311) {

    formWidget.setReadOnly(true);

    EXPECT_TRUE(poppler_form_field_is_read_only(&field));

}



TEST_F(PopplerFormFieldTest_2311, IsReadOnly_ReturnsFalse_AfterResettingFromReadOnly_2311) {

    formWidget.setReadOnly(true);

    formWidget.setReadOnly(false);

    EXPECT_FALSE(poppler_form_field_is_read_only(&field));

}



TEST_F(PopplerFormFieldTest_2311, IsReadOnly_HandlesNullFieldPointer_2311) {

    EXPECT_EQ(poppler_form_field_is_read_only(nullptr), FALSE);

}



TEST_F(PopplerFormFieldTest_2311, IsReadOnly_HandlesNullWidgetPointer_2311) {

    field.widget = nullptr;

    EXPECT_EQ(poppler_form_field_is_read_only(&field), FALSE);

}
