#include <gtest/gtest.h>

#include "poppler-form-field.cc"

#include "poppler-page.h"



class PopplerSigningDataTest_2353 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = poppler_signing_data_new();

    }



    void TearDown() override {

        g_free(signing_data->password);

        g_free(signing_data);

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2353, DefaultValuesSetCorrectly_2353) {

    EXPECT_STREQ("", signing_data->password);

    EXPECT_EQ(0, signing_data->page);

    EXPECT_DOUBLE_EQ(10.0, signing_data->font_size);

    EXPECT_DOUBLE_EQ(20.0, signing_data->left_font_size);

    EXPECT_DOUBLE_EQ(1.5, signing_data->border_width);

}



TEST_F(PopplerSigningDataTest_2353, BackgroundColorSetCorrectly_2353) {

    EXPECT_EQ(0xEF00, signing_data->background_color.red);

    EXPECT_EQ(0xEF00, signing_data->background_color.green);

    EXPECT_EQ(0xEF00, signing_data->background_color.blue);

}



TEST_F(PopplerSigningDataTest_2353, BorderColorSetCorrectly_2353) {

    EXPECT_EQ(0xFFFF, signing_data->border_color.red);

    EXPECT_EQ(0x00, signing_data->border_color.green);

    EXPECT_EQ(0x00, signing_data->border_color.blue);

}



TEST_F(PopplerSigningDataTest_2353, FontColorSetCorrectly_2353) {

    EXPECT_EQ(0xFFFF, signing_data->font_color.red);

    EXPECT_EQ(0x00, signing_data->font_color.green);

    EXPECT_EQ(0x00, signing_data->font_color.blue);

}
