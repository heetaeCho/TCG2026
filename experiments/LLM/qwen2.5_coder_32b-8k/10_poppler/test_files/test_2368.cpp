#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"

#include "poppler-page.h"



class PopplerSigningDataTest_2368 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        font_color = new PopplerColor{0, 0, 0}; // Default black color

    }



    void TearDown() override {

        delete signing_data;

        delete font_color;

    }



    PopplerSigningData* signing_data;

    PopplerColor* font_color;

};



TEST_F(PopplerSigningDataTest_2368, SetFontColorNormalOperation_2368) {

    PopplerColor new_color = {255, 0, 0}; // Red color

    poppler_signing_data_set_font_color(signing_data, &new_color);

    EXPECT_EQ(signing_data->font_color.red, 255);

    EXPECT_EQ(signing_data->font_color.green, 0);

    EXPECT_EQ(signing_data->font_color.blue, 0);

}



TEST_F(PopplerSigningDataTest_2368, SetFontColorBoundaryConditions_2368) {

    PopplerColor boundary_color = {0, 0, 0};

    poppler_signing_data_set_font_color(signing_data, &boundary_color);

    EXPECT_EQ(signing_data->font_color.red, 0);

    EXPECT_EQ(signing_data->font_color.green, 0);

    EXPECT_EQ(signing_data->font_color.blue, 0);



    boundary_color = {255, 255, 255};

    poppler_signing_data_set_font_color(signing_data, &boundary_color);

    EXPECT_EQ(signing_data->font_color.red, 255);

    EXPECT_EQ(signing_data->font_color.green, 255);

    EXPECT_EQ(signing_data->font_color.blue, 255);

}



TEST_F(PopplerSigningDataTest_2368, SetFontColorNullPointer_2368) {

    // Test with null signing_data

    poppler_signing_data_set_font_color(nullptr, font_color);

    // No change expected as function should return early



    // Test with null font_color

    PopplerColor* null_font_color = nullptr;

    poppler_signing_data_set_font_color(signing_data, null_font_color);

    // No change expected as function should return early

}



TEST_F(PopplerSigningDataTest_2368, SetFontColorSameColor_2368) {

    PopplerColor same_color = {0, 0, 0}; // Default black color

    poppler_signing_data_set_font_color(signing_data, &same_color);

    EXPECT_EQ(signing_data->font_color.red, 0);

    EXPECT_EQ(signing_data->font_color.green, 0);

    EXPECT_EQ(signing_data->font_color.blue, 0);

}
