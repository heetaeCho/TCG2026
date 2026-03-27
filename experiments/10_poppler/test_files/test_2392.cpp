#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



using namespace testing;



struct PopplerSigningDataTest : public ::testing::Test {

    PopplerSigningData signing_data;



    void SetUp() override {

        memset(&signing_data, 0, sizeof(PopplerSigningData));

    }



    void TearDown() override {

        g_clear_pointer(&signing_data.document_user_password, g_free);

    }

};



TEST_F(PopplerSigningDataTest_2392, SetDocumentUserPassword_NormalOperation_2392) {

    const gchar* password = "user123";

    poppler_signing_data_set_document_user_password(&signing_data, password);

    EXPECT_STREQ(signing_data.document_user_password, password);

}



TEST_F(PopplerSigningDataTest_2392, SetDocumentUserPassword_SamePassword_NoChange_2392) {

    const gchar* password = "user123";

    signing_data.document_user_password = g_strdup(password);

    poppler_signing_data_set_document_user_password(&signing_data, password);

    EXPECT_STREQ(signing_data.document_user_password, password);

}



TEST_F(PopplerSigningDataTest_2392, SetDocumentUserPassword_NullPointer_SigningData_2392) {

    const gchar* password = "user123";

    poppler_signing_data_set_document_user_password(nullptr, password);

    EXPECT_EQ(signing_data.document_user_password, nullptr);

}



TEST_F(PopplerSigningDataTest_2392, SetDocumentUserPassword_NullPointer_Password_2392) {

    poppler_signing_data_set_document_user_password(&signing_data, nullptr);

    EXPECT_EQ(signing_data.document_user_password, nullptr);

}



TEST_F(PopplerSigningDataTest_2392, SetDocumentUserPassword_ChangePassword_FreePrevious_2392) {

    const gchar* password1 = "user123";

    const gchar* password2 = "newPass456";

    signing_data.document_user_password = g_strdup(password1);

    poppler_signing_data_set_document_user_password(&signing_data, password2);

    EXPECT_STREQ(signing_data.document_user_password, password2);

}
