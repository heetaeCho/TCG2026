#include <gtest/gtest.h>

#include "poppler-form-field.h"

#include <gmock/gmock.h>



class PopplerSigningDataTest_2372 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->left_font_size = 0; // Initialize to a default value

    }



    void TearDown() override {

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2372, SetLeftFontSize_PositiveValue_2372) {

    poppler_signing_data_set_left_font_size(signing_data, 10.5);

    EXPECT_EQ(signing_data->left_font_size, 10);

}



TEST_F(PopplerSigningDataTest_2372, SetLeftFontSize_ZeroValue_2372) {

    poppler_signing_data_set_left_font_size(signing_data, 0);

    EXPECT_EQ(signing_data->left_font_size, 0);

}



TEST_F(PopplerSigningDataTest_2372, SetLeftFontSize_NegativeValue_2372) {

    poppler_signing_data_set_left_font_size(signing_data, -5.0);

    EXPECT_EQ(signing_data->left_font_size, 0);

}



TEST_F(PopplerSigningDataTest_2372, SetLeftFontSize_NullPointer_2372) {

    poppler_signing_data_set_left_font_size(nullptr, 10.5);

    // No change expected as the function should return early

    EXPECT_EQ(signing_data->left_font_size, 0);

}



TEST_F(PopplerSigningDataTest_2372, SetLeftFontSize_BoundaryValue_2372) {

    poppler_signing_data_set_left_font_size(signing_data, std::numeric_limits<gdouble>::epsilon());

    EXPECT_EQ(signing_data->left_font_size, 0);

}



TEST_F(PopplerSigningDataTest_2372, SetLeftFontSize_LargeValue_2372) {

    poppler_signing_data_set_left_font_size(signing_data, std::numeric_limits<gdouble>::max());

    EXPECT_EQ(signing_data->left_font_size, static_cast<int>(std::numeric_limits<gdouble>::max()));

}
