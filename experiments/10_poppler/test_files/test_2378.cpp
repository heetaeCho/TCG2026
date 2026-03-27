#include <gtest/gtest.h>

#include "poppler-form-field.h"

#include "poppler-page.h"



class PopplerSigningDataTest_2378 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        color = new PopplerColor();

    }



    void TearDown() override {

        delete signing_data;

        delete color;

    }



    PopplerSigningData* signing_data;

    PopplerColor* color;

};



TEST_F(PopplerSigningDataTest_2378, SetBackgroundColorWithValidColor_2378) {

    // Arrange

    color->red = 255;

    color->green = 0;

    color->blue = 0;



    // Act

    poppler_signing_data_set_background_color(signing_data, color);



    // Assert

    EXPECT_EQ(signing_data->background_color.red, 255);

    EXPECT_EQ(signing_data->background_color.green, 0);

    EXPECT_EQ(signing_data->background_color.blue, 0);

}



TEST_F(PopplerSigningDataTest_2378, SetBackgroundColorWithNullSigningData_2378) {

    // Arrange

    color->red = 255;

    color->green = 0;

    color->blue = 0;



    // Act & Assert

    EXPECT_NO_THROW(poppler_signing_data_set_background_color(nullptr, color));

}



TEST_F(PopplerSigningDataTest_2378, SetBackgroundColorWithNullColor_2378) {

    // Arrange



    // Act & Assert

    EXPECT_NO_THROW(poppler_signing_data_set_background_color(signing_data, nullptr));

}



TEST_F(PopplerSigningDataTest_2378, SetBackgroundColorWithBoundaryValues_2378) {

    // Arrange

    color->red = 0;

    color->green = 0;

    color->blue = 0;



    // Act

    poppler_signing_data_set_background_color(signing_data, color);



    // Assert

    EXPECT_EQ(signing_data->background_color.red, 0);

    EXPECT_EQ(signing_data->background_color.green, 0);

    EXPECT_EQ(signing_data->background_color.blue, 0);



    // Arrange

    color->red = 255;

    color->green = 255;

    color->blue = 255;



    // Act

    poppler_signing_data_set_background_color(signing_data, color);



    // Assert

    EXPECT_EQ(signing_data->background_color.red, 255);

    EXPECT_EQ(signing_data->background_color.green, 255);

    EXPECT_EQ(signing_data->background_color.blue, 255);

}
