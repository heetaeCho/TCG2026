#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.cc"

}



class PopplerSigningDataTest_2354 : public ::testing::Test {

protected:

    void SetUp() override {

        original_data = new PopplerSigningData();

        memset(original_data, 0, sizeof(PopplerSigningData));



        // Initialize some fields for testing

        original_data->destination_filename = g_strdup("test.pdf");

        original_data->signature_text = g_strdup("Signature Text");

        original_data->signature_text_left = g_strdup("Left Signature Text");

        original_data->page = 1;

        original_data->font_size = 12;

        original_data->left_font_size = 10;

        original_data->border_width = 2;

        original_data->field_partial_name = g_strdup("Field Name");

        original_data->reason = g_strdup("Reason for Signing");

        original_data->location = g_strdup("Location");

        original_data->image_path = g_strdup("path/to/image.png");

        original_data->password = g_strdup("user_password");

        original_data->document_owner_password = g_strdup("owner_password");

        original_data->document_user_password = g_strdup("user_doc_password");



        memcpy(&original_data->signature_rect, &testRect, sizeof(PopplerRectangle));

        memcpy(&original_data->font_color, &testColor, sizeof(PopplerColor));

        memcpy(&original_data->border_color, &testColor, sizeof(PopplerColor));

        memcpy(&original_data->background_color, &testColor, sizeof(PopplerColor));

    }



    void TearDown() override {

        g_free(original_data->destination_filename);

        g_free(original_data->signature_text);

        g_free(original_data->signature_text_left);

        g_free(original_data->field_partial_name);

        g_free(original_data->reason);

        g_free(original_data->location);

        g_free(original_data->image_path);

        g_free(original_data->password);

        g_free(original_data->document_owner_password);

        g_free(original_data->document_user_password);



        delete original_data;

    }



    PopplerRectangle testRect = {100, 200, 300, 400};

    PopplerColor testColor = {0, 0, 0};

    PopplerSigningData* original_data = nullptr;

};



TEST_F(PopplerSigningDataTest_2354, CopyCreatesValidInstance_2354) {

    PopplerSigningData* copied_data = poppler_signing_data_copy(original_data);



    EXPECT_NE(copied_data, nullptr);

    EXPECT_STREQ(copied_data->destination_filename, original_data->destination_filename);

    EXPECT_STREQ(copied_data->signature_text, original_data->signature_text);

    EXPECT_STREQ(copied_data->signature_text_left, original_data->signature_text_left);

    EXPECT_EQ(copied_data->page, original_data->page);

    EXPECT_EQ(copied_data->font_size, original_data->font_size);

    EXPECT_EQ(copied_data->left_font_size, original_data->left_font_size);

    EXPECT_EQ(copied_data->border_width, original_data->border_width);

    EXPECT_STREQ(copied_data->field_partial_name, original_data->field_partial_name);

    EXPECT_STREQ(copied_data->reason, original_data->reason);

    EXPECT_STREQ(copied_data->location, original_data->location);

    EXPECT_STREQ(copied_data->image_path, original_data->image_path);

    EXPECT_STREQ(copied_data->password, original_data->password);

    EXPECT_STREQ(copied_data->document_owner_password, original_data->document_owner_password);

    EXPECT_STREQ(copied_data->document_user_password, original_data->document_user_password);



    EXPECT_EQ(memcmp(&copied_data->signature_rect, &original_data->signature_rect, sizeof(PopplerRectangle)), 0);

    EXPECT_EQ(memcmp(&copied_data->font_color, &original_data->font_color, sizeof(PopplerColor)), 0);

    EXPECT_EQ(memcmp(&copied_data->border_color, &original_data->border_color, sizeof(PopplerColor)), 0);

    EXPECT_EQ(memcmp(&copied_data->background_color, &original_data->background_color, sizeof(PopplerColor)), 0);



    g_free(copied_data->destination_filename);

    g_free(copied_data->signature_text);

    g_free(copied_data->signature_text_left);

    g_free(copied_data->field_partial_name);

    g_free(copied_data->reason);

    g_free(copied_data->location);

    g_free(copied_data->image_path);

    g_free(copied_data->password);

    g_free(copied_data->document_owner_password);

    g_free(copied_data->document_user_password);



    g_free(copied_data);

}



TEST_F(PopplerSigningDataTest_2354, CopyWithNullInputReturnsNull_2354) {

    PopplerSigningData* copied_data = poppler_signing_data_copy(nullptr);



    EXPECT_EQ(copied_data, nullptr);

}
