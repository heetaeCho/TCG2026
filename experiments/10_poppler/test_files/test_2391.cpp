#include <gtest/gtest.h>

#include "poppler-form-field.cc"



class PopplerSigningDataTest_2391 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->document_owner_password = strdup("owner_password");

    }



    void TearDown() override {

        free(signing_data->document_owner_password);

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2391, GetDocumentOwnerPassword_ReturnsCorrectPassword_2391) {

    EXPECT_STREQ(poppler_signing_data_get_document_owner_password(signing_data), "owner_password");

}



TEST_F(PopplerSigningDataTest_2391, GetDocumentOwnerPassword_ReturnsNullptrForNullPointer_2391) {

    EXPECT_EQ(poppler_signing_data_get_document_owner_password(nullptr), nullptr);

}
