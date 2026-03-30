#include <gtest/gtest.h>

#include "poppler-form-field.cc"  // Assuming this file contains the necessary declarations



class PopplerSigningDataTest_2363 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new _PopplerSigningData();

        signing_data->signature_text = strdup("Sample Signature Text");

    }



    void TearDown() override {

        free(signing_data->signature_text);

        delete signing_data;

    }



    _PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2363, GetSignatureText_ReturnsCorrectValue_2363) {

    EXPECT_STREQ(poppler_signing_data_get_signature_text(signing_data), "Sample Signature Text");

}



TEST_F(PopplerSigningDataTest_2363, GetSignatureText_NullPointer_ReturnsNull_2363) {

    EXPECT_EQ(poppler_signing_data_get_signature_text(nullptr), nullptr);

}
