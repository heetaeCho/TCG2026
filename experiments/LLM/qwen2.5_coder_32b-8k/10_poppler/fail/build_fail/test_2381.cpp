#include <gtest/gtest.h>

#include "poppler-form-field.h"



class PopplerSigningDataTest_2381 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->field_partial_name = g_strdup("test_field");

    }



    void TearDown() override {

        g_free(signing_data->field_partial_name);

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2381, GetFieldPartialName_ReturnsCorrectValue_2381) {

    EXPECT_STREQ("test_field", poppler_signing_data_get_field_partial_name(signing_data));

}



TEST_F(PopplerSigningDataTest_2381, GetFieldPartialName_NullPointer_ReturnsEmptyString_2381) {

    EXPECT_STREQ("", poppler_signing_data_get_field_partial_name(nullptr));

}



TEST_F(PopplerSigningDataTest_2381, GetFieldPartialName_EmptyFieldName_ReturnsEmptyString_2381) {

    g_free(signing_data->field_partial_name);

    signing_data->field_partial_name = nullptr;

    EXPECT_STREQ("", poppler_signing_data_get_field_partial_name(signing_data));

}
