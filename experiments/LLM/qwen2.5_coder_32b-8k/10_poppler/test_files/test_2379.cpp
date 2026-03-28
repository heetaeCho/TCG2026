#include <gtest/gtest.h>

#include "poppler-form-field.h"



// Mocking any external dependencies if necessary (none identified in this case)



class PopplerSigningDataTest_2379 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize test data

        signing_data = new PopplerSigningData();

        signing_data->background_color.red = 0.5;

        signing_data->background_color.green = 0.5;

        signing_data->background_color.blue = 0.5;

    }



    void TearDown() override {

        // Clean up test data

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2379, GetBackgroundColor_ReturnsValidColorPointer_2379) {

    const PopplerColor *color = poppler_signing_data_get_background_color(signing_data);

    ASSERT_NE(color, nullptr);

    EXPECT_DOUBLE_EQ(color->red, 0.5);

    EXPECT_DOUBLE_EQ(color->green, 0.5);

    EXPECT_DOUBLE_EQ(color->blue, 0.5);

}



TEST_F(PopplerSigningDataTest_2379, GetBackgroundColor_NullPointer_ReturnsNull_2379) {

    const PopplerColor *color = poppler_signing_data_get_background_color(nullptr);

    EXPECT_EQ(color, nullptr);

}
