#include <gtest/gtest.h>

#include "poppler-form-field.cc"

#include "poppler-page.h"



class PopplerSigningDataTest_2374 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        border_color.red = 0;

        border_color.green = 0;

        border_color.blue = 0;

    }



    void TearDown() override {

        delete signing_data;

    }



    PopplerSigningData* signing_data;

    PopplerColor border_color;

};



TEST_F(PopplerSigningDataTest_2374, SetBorderColor_ValidColor_2374) {

    border_color.red = 255;

    border_color.green = 165;

    border_color.blue = 0;



    poppler_signing_data_set_border_color(signing_data, &border_color);



    EXPECT_EQ(signing_data->border_color.red, 255);

    EXPECT_EQ(signing_data->border_color.green, 165);

    EXPECT_EQ(signing_data->border_color.blue, 0);

}



TEST_F(PopplerSigningDataTest_2374, SetBorderColor_ZeroValues_2374) {

    border_color.red = 0;

    border_color.green = 0;

    border_color.blue = 0;



    poppler_signing_data_set_border_color(signing_data, &border_color);



    EXPECT_EQ(signing_data->border_color.red, 0);

    EXPECT_EQ(signing_data->border_color.green, 0);

    EXPECT_EQ(signing_data->border_color.blue, 0);

}



TEST_F(PopplerSigningDataTest_2374, SetBorderColor_MaxValues_2374) {

    border_color.red = 255;

    border_color.green = 255;

    border_color.blue = 255;



    poppler_signing_data_set_border_color(signing_data, &border_color);



    EXPECT_EQ(signing_data->border_color.red, 255);

    EXPECT_EQ(signing_data->border_color.green, 255);

    EXPECT_EQ(signing_data->border_color.blue, 255);

}



TEST_F(PopplerSigningDataTest_2374, SetBorderColor_NullSigningData_2374) {

    poppler_signing_data_set_border_color(nullptr, &border_color);



    // No assertion needed as g_return_if_fail will handle the null case

}



TEST_F(PopplerSigningDataTest_2374, SetBorderColor_NullBorderColor_2374) {

    poppler_signing_data_set_border_color(signing_data, nullptr);



    // No assertion needed as g_return_if_fail will handle the null case

}
