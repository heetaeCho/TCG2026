#include <gtest/gtest.h>

#include "poppler-form-field.h"



// Mocking external collaborators if needed (not required in this case)



// Test fixture for PopplerSigningData tests

class PopplerSigningDataTest_2365 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a sample PopplerSigningData structure

        signing_data = new _PopplerSigningData();

        signing_data->signature_text_left = g_strdup("Sample Signature Text Left");

    }



    void TearDown() override {

        // Clean up the allocated memory

        if (signing_data) {

            g_free(signing_data->signature_text_left);

            delete signing_data;

            signing_data = nullptr;

        }

    }



    PopplerSigningData *signing_data;

};



// Test normal operation

TEST_F(PopplerSigningDataTest_2365, GetSignatureTextLeft_ReturnsCorrectValue_2365) {

    const gchar* result = poppler_signing_data_get_signature_text_left(signing_data);

    EXPECT_STREQ(result, "Sample Signature Text Left");

}



// Test boundary condition with nullptr input

TEST_F(PopplerSigningDataTest_2365, GetSignatureTextLeft_NullInput_ReturnsNullptr_2365) {

    const gchar* result = poppler_signing_data_get_signature_text_left(nullptr);

    EXPECT_EQ(result, nullptr);

}
