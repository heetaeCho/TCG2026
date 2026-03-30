#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "poppler-form-field.h"

}



class PopplerSigningDataTest_2373 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->left_font_size = 10;

    }



    void TearDown() override {

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2373, GetLeftFontSize_ReturnsCorrectValue_2373) {

    EXPECT_EQ(poppler_signing_data_get_left_font_size(signing_data), 10);

}



TEST_F(PopplerSigningDataTest_2373, GetLeftFontSize_NullptrReturnsDefault_2373) {

    EXPECT_EQ(poppler_signing_data_get_left_font_size(nullptr), 12.0);

}



TEST_F(PopplerSigningDataTest_2373, GetLeftFontSize_BoundaryConditionZero_2373) {

    signing_data->left_font_size = 0;

    EXPECT_EQ(poppler_signing_data_get_left_font_size(signing_data), 0);

}



TEST_F(PopplerSigningDataTest_2373, GetLeftFontSize_BoundaryConditionNegative_2373) {

    signing_data->left_font_size = -5;

    EXPECT_EQ(poppler_signing_data_get_left_font_size(signing_data), -5);

}
