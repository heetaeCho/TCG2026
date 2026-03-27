#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



// Test fixture for PopplerSigningData tests

class PopplerSigningDataTest_2386 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        memset(signing_data, 0, sizeof(PopplerSigningData));

    }



    void TearDown() override {

        if (signing_data) {

            g_clear_pointer(&signing_data->image_path, g_free);

            delete signing_data;

        }

    }



    PopplerSigningData *signing_data = nullptr;

};



// Test normal operation with valid image path

TEST_F(PopplerSigningDataTest_2386, SetImagePath_NormalOperation_2386) {

    const gchar* test_image_path = "/path/to/image.png";

    poppler_signing_data_set_image_path(signing_data, test_image_path);

    ASSERT_STREQ(signing_data->image_path, test_image_path);

}



// Test setting the same image path again

TEST_F(PopplerSigningDataTest_2386, SetImagePath_SamePath_2386) {

    const gchar* test_image_path = "/path/to/image.png";

    poppler_signing_data_set_image_path(signing_data, test_image_path);

    poppler_signing_data_set_image_path(signing_data, test_image_path);

    ASSERT_STREQ(signing_data->image_path, test_image_path);

}



// Test setting a different image path

TEST_F(PopplerSigningDataTest_2386, SetImagePath_DifferentPath_2386) {

    const gchar* first_image_path = "/path/to/first/image.png";

    const gchar* second_image_path = "/path/to/second/image.png";

    poppler_signing_data_set_image_path(signing_data, first_image_path);

    poppler_signing_data_set_image_path(signing_data, second_image_path);

    ASSERT_STREQ(signing_data->image_path, second_image_path);

}



// Test boundary condition with an empty string

TEST_F(PopplerSigningDataTest_2386, SetImagePath_EmptyString_2386) {

    const gchar* empty_string = "";

    poppler_signing_data_set_image_path(signing_data, empty_string);

    ASSERT_STREQ(signing_data->image_path, empty_string);

}



// Test exceptional case with null signing data

TEST_F(PopplerSigningDataTest_2386, SetImagePath_NullSigningData_2386) {

    const gchar* test_image_path = "/path/to/image.png";

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_image_path(nullptr, test_image_path));

}



// Test exceptional case with null image path

TEST_F(PopplerSigningDataTest_2386, SetImagePath_NullImagePath_2386) {

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_image_path(signing_data, nullptr));

}
