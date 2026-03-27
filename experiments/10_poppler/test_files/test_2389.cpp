#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming poppler-form-field.h contains the declaration of PopplerSigningData and the function prototype

extern "C" {

    struct _PopplerSigningData;

    typedef struct _PopplerSigningData PopplerSigningData;



    const gchar *poppler_signing_data_get_password(const PopplerSigningData *signing_data);

}



class PopplerSigningDataTest_2389 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->password = nullptr;

    }



    void TearDown() override {

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2389, GetPassword_ReturnsNullptrWhenPasswordIsNullptr_2389) {

    EXPECT_EQ(poppler_signing_data_get_password(signing_data), nullptr);

}



TEST_F(PopplerSigningDataTest_2389, GetPassword_ReturnsCorrectPassword_2389) {

    const char* expected_password = "test_password";

    signing_data->password = strdup(expected_password); // Use strdup to allocate memory for the string

    EXPECT_STREQ(poppler_signing_data_get_password(signing_data), expected_password);

    free(signing_data->password); // Clean up allocated memory

}



TEST_F(PopplerSigningDataTest_2389, GetPassword_ReturnsNullptrWhenSigningDataIsNullptr_2389) {

    EXPECT_EQ(poppler_signing_data_get_password(nullptr), nullptr);

}
