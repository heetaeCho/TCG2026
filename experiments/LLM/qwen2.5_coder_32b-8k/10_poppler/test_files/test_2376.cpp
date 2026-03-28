#include <gtest/gtest.h>

#include "poppler-form-field.h"



class PopplerSigningDataTest_2376 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

    }



    void TearDown() override {

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2376, SetBorderWidth_ValidValue_2376) {

    gdouble border_width = 5.0;

    poppler_signing_data_set_border_width(signing_data, border_width);

    EXPECT_EQ(signing_data->border_width, static_cast<int>(border_width));

}



TEST_F(PopplerSigningDataTest_2376, SetBorderWidth_ZeroValue_2376) {

    gdouble border_width = 0.0;

    poppler_signing_data_set_border_width(signing_data, border_width);

    EXPECT_EQ(signing_data->border_width, static_cast<int>(border_width));

}



TEST_F(PopplerSigningDataTest_2376, SetBorderWidth_NegativeValue_Ignored_2376) {

    gdouble border_width = -1.0;

    poppler_signing_data_set_border_width(signing_data, border_width);

    EXPECT_EQ(signing_data->border_width, 0); // Assuming default value is 0

}



TEST_F(PopplerSigningDataTest_2376, SetBorderWidth_NullPointer_Ignored_2376) {

    gdouble border_width = 5.0;

    poppler_signing_data_set_border_width(nullptr, border_width);

    // No way to assert since function returns void and does nothing on nullptr

}
