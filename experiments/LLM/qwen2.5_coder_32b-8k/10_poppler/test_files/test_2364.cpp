#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"



using namespace testing;



class PopplerSigningDataTest_2364 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));

    }



    void TearDown() override {

        poppler_signing_data_set_signature_text_left(signing_data, nullptr);

        g_free(signing_data);

    }



    PopplerSigningData *signing_data;

};



TEST_F(PopplerSigningDataTest_2364, SetSignatureTextLeft_NormalOperation_2364) {

    const gchar* text = "Sample Text";

    poppler_signing_data_set_signature_text_left(signing_data, text);

    EXPECT_STREQ(signing_data->signature_text_left, text);

}



TEST_F(PopplerSigningDataTest_2364, SetSignatureTextLeft_BoundaryCondition_NullInput_2364) {

    poppler_signing_data_set_signature_text_left(nullptr, "Sample Text");

    // No crash and no change expected

    EXPECT_EQ(signing_data->signature_text_left, nullptr);

}



TEST_F(PopplerSigningDataTest_2364, SetSignatureTextLeft_BoundaryCondition_EmptyString_2364) {

    const gchar* text = "";

    poppler_signing_data_set_signature_text_left(signing_data, text);

    EXPECT_STREQ(signing_data->signature_text_left, text);

}



TEST_F(PopplerSigningDataTest_2364, SetSignatureTextLeft_IdempotentOperation_2364) {

    const gchar* text = "Sample Text";

    poppler_signing_data_set_signature_text_left(signing_data, text);

    poppler_signing_data_set_signature_text_left(signing_data, text);

    EXPECT_STREQ(signing_data->signature_text_left, text);

}



TEST_F(PopplerSigningDataTest_2364, SetSignatureTextLeft_UpdateWithDifferentString_2364) {

    const gchar* initialText = "Initial Text";

    const gchar* newText = "New Text";

    poppler_signing_data_set_signature_text_left(signing_data, initialText);

    poppler_signing_data_set_signature_text_left(signing_data, newText);

    EXPECT_STREQ(signing_data->signature_text_left, newText);

}



TEST_F(PopplerSigningDataTest_2364, SetSignatureTextLeft_SetNullAfterValue_2364) {

    const gchar* text = "Sample Text";

    poppler_signing_data_set_signature_text_left(signing_data, text);

    poppler_signing_data_set_signature_text_left(signing_data, nullptr);

    EXPECT_EQ(signing_data->signature_text_left, nullptr);

}
