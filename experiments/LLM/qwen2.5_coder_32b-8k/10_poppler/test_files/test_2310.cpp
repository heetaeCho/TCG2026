#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary header files are included for PopplerFormField and related types.

extern "C" {

    gdouble poppler_form_field_get_font_size(PopplerFormField *field);

}



class PopplerFormFieldTest_2310 : public ::testing::Test {

protected:

    virtual void SetUp() {

        field = reinterpret_cast<PopplerFormField*>(malloc(sizeof(PopplerFormField)));

        memset(field, 0, sizeof(PopplerFormField));

    }



    virtual void TearDown() {

        free(field);

    }



    PopplerFormField* field;

};



TEST_F(PopplerFormFieldTest_2310, GetFontSize_ReturnsZeroForValidField_2310) {

    EXPECT_EQ(poppler_form_field_get_font_size(field), 0.0);

}



TEST_F(PopplerFormFieldTest_2310, GetFontSize_ReturnsZeroForNullField_2310) {

    EXPECT_EQ(poppler_form_field_get_font_size(nullptr), 0.0);

}
