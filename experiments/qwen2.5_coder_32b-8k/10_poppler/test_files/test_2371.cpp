#include <gtest/gtest.h>

#include "poppler-form-field.cc"



using namespace testing;



// Test fixture for PopplerSigningData tests

class PopplerSigningDataTest_2371 : public ::testing::Test {

protected:

    PopplerSigningData* signing_data;



    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->font_size = 12.0F;

    }



    void TearDown() override {

        delete signing_data;

    }

};



// Test normal operation with a typical font size

TEST_F(PopplerSigningDataTest_2371, NormalFontSize_2371) {

    EXPECT_FLOAT_EQ(poppler_signing_data_get_font_size(signing_data), 12.0F);

}



// Test boundary condition with minimum possible float value for font size

TEST_F(PopplerSigningDataTest_2371, MinFontSize_2371) {

    signing_data->font_size = FLT_MIN;

    EXPECT_FLOAT_EQ(poppler_signing_data_get_font_size(signing_data), FLT_MIN);

}



// Test boundary condition with maximum possible float value for font size

TEST_F(PopplerSigningDataTest_2371, MaxFontSize_2371) {

    signing_data->font_size = FLT_MAX;

    EXPECT_FLOAT_EQ(poppler_signing_data_get_font_size(signing_data), FLT_MAX);

}



// Test null pointer case to ensure it returns default value 20.0F

TEST(PopplerSigningDataTest_2371, NullPointerCase_2371) {

    EXPECT_FLOAT_EQ(poppler_signing_data_get_font_size(nullptr), 20.0F);

}
