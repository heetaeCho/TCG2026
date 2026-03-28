#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



// Assuming the struct definition provided is correct and complete

struct _PopplerSigningData {

    char * destination_filename;

    char * signature_text;

    char * signature_text_left;

    PopplerRectangle signature_rect;

    int left_font_size;

    PopplerColor border_color;

    int border_width;

    PopplerColor background_color;

    char * field_partial_name;

    char * reason;

    char * location;

    char * image_path;

    char * password;

    char * document_owner_password;

    char * document_user_password;

    gdouble font_size; // Assuming this is part of the struct

};



class PopplerSigningDataTest_2370 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new _PopplerSigningData();

        signing_data->font_size = 10.0; // Default font size for testing

    }



    void TearDown() override {

        delete signing_data;

    }



    _PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2370, SetFontSize_PositiveValue_2370) {

    gdouble new_font_size = 14.5;

    poppler_signing_data_set_font_size(signing_data, new_font_size);

    EXPECT_DOUBLE_EQ(signing_data->font_size, new_font_size);

}



TEST_F(PopplerSigningDataTest_2370, SetFontSize_ZeroValue_2370) {

    gdouble zero_font_size = 0.0;

    poppler_signing_data_set_font_size(signing_data, zero_font_size);

    EXPECT_DOUBLE_EQ(signing_data->font_size, 10.0); // Should remain unchanged

}



TEST_F(PopplerSigningDataTest_2370, SetFontSize_NegativeValue_2370) {

    gdouble negative_font_size = -5.0;

    poppler_signing_data_set_font_size(signing_data, negative_font_size);

    EXPECT_DOUBLE_EQ(signing_data->font_size, 10.0); // Should remain unchanged

}



TEST_F(PopplerSigningDataTest_2370, SetFontSize_NullPointer_2370) {

    gdouble new_font_size = 12.0;

    poppler_signing_data_set_font_size(nullptr, new_font_size);

    // No observable change as function should return early

}
