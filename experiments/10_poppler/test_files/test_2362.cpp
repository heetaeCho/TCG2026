#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-form-field.h>



// Mocking structure to simulate PopplerSigningData for testing purposes

struct PopplerSigningData {

    char *destination_filename;

    char *signature_text;

    char *signature_text_left;

    PopplerRectangle signature_rect;

    int left_font_size;

    PopplerColor border_color;

    int border_width;

    PopplerColor background_color;

    char *field_partial_name;

    char *reason;

    char *location;

    char *image_path;

    char *password;

    char *document_owner_password;

    char *document_user_password;

};



class PopplerSigningDataTest : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        memset(signing_data, 0, sizeof(PopplerSigningData));

    }



    void TearDown() override {

        if (signing_data->signature_text) g_free(signing_data->signature_text);

        delete signing_data;

    }



    PopplerSigningData *signing_data;

};



TEST_F(PopplerSigningDataTest_2362, SetSignatureText_NormalOperation_2362) {

    const char* new_signature = "Sample Signature";

    poppler_signing_data_set_signature_text(signing_data, new_signature);

    EXPECT_STREQ(signing_data->signature_text, new_signature);

}



TEST_F(PopplerSigningDataTest_2362, SetSignatureText_NoChangeSameString_2362) {

    const char* initial_signature = "Initial Signature";

    signing_data->signature_text = g_strdup(initial_signature);

    poppler_signing_data_set_signature_text(signing_data, initial_signature);

    EXPECT_STREQ(signing_data->signature_text, initial_signature);

}



TEST_F(PopplerSigningDataTest_2362, SetSignatureText_BoundaryEmptyString_2362) {

    const char* empty_string = "";

    poppler_signing_data_set_signature_text(signing_data, empty_string);

    EXPECT_STREQ(signing_data->signature_text, empty_string);

}



TEST_F(PopplerSigningDataTest_2362, SetSignatureText_ExceptionNullPtrSigningData_2362) {

    const char* new_signature = "Sample Signature";

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_signature_text(nullptr, new_signature));

}



TEST_F(PopplerSigningDataTest_2362, SetSignatureText_ExceptionNullPtrSignatureText_2362) {

    poppler_signing_data_set_signature_text(signing_data, nullptr);

    EXPECT_EQ(signing_data->signature_text, nullptr);

}
