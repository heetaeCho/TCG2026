#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.h"

}



class PopplerSigningDataTest_2390 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));

    }



    void TearDown() override {

        poppler_signing_data_set_document_owner_password(signing_data, nullptr);

        g_free(signing_data);

    }



    PopplerSigningData *signing_data;

};



TEST_F(PopplerSigningDataTest_2390, SetDocumentOwnerPassword_NormalOperation_2390) {

    const gchar* test_password = "test_password";

    poppler_signing_data_set_document_owner_password(signing_data, test_password);

    ASSERT_STREQ(signing_data->document_owner_password, test_password);

}



TEST_F(PopplerSigningDataTest_2390, SetDocumentOwnerPassword_SamePassword_NoChange_2390) {

    const gchar* initial_password = "initial_password";

    poppler_signing_data_set_document_owner_password(signing_data, initial_password);



    // Attempt to set the same password again

    poppler_signing_data_set_document_owner_password(signing_data, initial_password);

    ASSERT_STREQ(signing_data->document_owner_password, initial_password);

}



TEST_F(PopplerSigningDataTest_2390, SetDocumentOwnerPassword_NullPointer_SigningData_2390) {

    const gchar* test_password = "test_password";

    poppler_signing_data_set_document_owner_password(nullptr, test_password);

    // Since there's no observable behavior other than a return if the pointer is null,

    // we just assume it doesn't crash and nothing changes.

}



TEST_F(PopplerSigningDataTest_2390, SetDocumentOwnerPassword_NullPointer_Password_2390) {

    poppler_signing_data_set_document_owner_password(signing_data, nullptr);

    // Since there's no observable behavior other than a return if the pointer is null,

    // we just assume it doesn't crash and nothing changes.

}



TEST_F(PopplerSigningDataTest_2390, SetDocumentOwnerPassword_ChangePassword_2390) {

    const gchar* initial_password = "initial_password";

    poppler_signing_data_set_document_owner_password(signing_data, initial_password);



    const gchar* new_password = "new_password";

    poppler_signing_data_set_document_owner_password(signing_data, new_password);

    ASSERT_STREQ(signing_data->document_owner_password, new_password);

}
