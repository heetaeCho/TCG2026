#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "poppler-form-field.cc"

}



class PopplerSigningDataTest_2387 : public ::testing::Test {

protected:

    PopplerSigningData signing_data;



    void SetUp() override {

        signing_data.image_path = nullptr;

    }



    void TearDown() override {

        if (signing_data.image_path) {

            g_free(signing_data.image_path);

            signing_data.image_path = nullptr;

        }

    }

};



TEST_F(PopplerSigningDataTest_2387, GetImagePath_ReturnsNullptrWhenNotSet_2387) {

    EXPECT_EQ(poppler_signing_data_get_image_path(&signing_data), nullptr);

}



TEST_F(PopplerSigningDataTest_2387, GetImagePath_ReturnsImagePathWhenSet_2387) {

    signing_data.image_path = g_strdup("test/image/path.png");

    EXPECT_STREQ(poppler_signing_data_get_image_path(&signing_data), "test/image/path.png");

}



TEST_F(PopplerSigningDataTest_2387, GetImagePath_NullptrInput_ReturnsNullptr_2387) {

    EXPECT_EQ(poppler_signing_data_get_image_path(nullptr), nullptr);

}
