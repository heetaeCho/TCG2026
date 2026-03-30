#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



using namespace testing;



class PopplerSignatureInfoTest_2325 : public ::testing::Test {

protected:

    void SetUp() override {

        original_info = g_new0(PopplerSignatureInfo, 1);

        original_info->sig_status = 42;

        original_info->cert_status = POPPLER_CERTIFICATE_STATUS_GOOD;

        original_info->signer_name = g_strdup("John Doe");

        original_info->local_signing_time = g_date_time_new_utc(2023, 10, 5, 12, 0, 0);

        original_info->certificate_info = g_new0(PopplerCertificateInfo, 1); // Assuming this is a simple struct

    }



    void TearDown() override {

        g_free(original_info->signer_name);

        g_date_time_unref(original_info->local_signing_time);

        g_free(original_info->certificate_info);

        g_free(original_info);

        if (copied_info) {

            g_free(copied_info->signer_name);

            g_date_time_unref(copied_info->local_signing_time);

            g_free(copied_info->certificate_info);

            g_free(copied_info);

        }

    }



    PopplerSignatureInfo *original_info = nullptr;

    PopplerSignatureInfo *copied_info = nullptr;

};



TEST_F(PopplerSignatureInfoTest_2325, CopyCreatesNewInstance_2325) {

    copied_info = poppler_signature_info_copy(original_info);

    EXPECT_NE(copied_info, original_info);

}



TEST_F(PopplerSignatureInfoTest_2325, CopyPreservesSigStatus_2325) {

    copied_info = poppler_signature_info_copy(original_info);

    EXPECT_EQ(copied_info->sig_status, original_info->sig_status);

}



TEST_F(PopplerSignatureInfoTest_2325, CopyPreservesCertStatus_2325) {

    copied_info = poppler_signature_info_copy(original_info);

    EXPECT_EQ(copied_info->cert_status, original_info->cert_status);

}



TEST_F(PopplerSignatureInfoTest_2325, CopyPreservesSignerName_2325) {

    copied_info = poppler_signature_info_copy(original_info);

    EXPECT_STREQ(copied_info->signer_name, original_info->signer_name);

}



TEST_F(PopplerSignatureInfoTest_2325, CopyPreservesLocalSigningTime_2325) {

    copied_info = poppler_signature_info_copy(original_info);

    EXPECT_TRUE(g_date_time_equal(copied_info->local_signing_time, original_info->local_signing_time));

}



TEST_F(PopplerSignatureInfoTest_2325, CopyPreservesCertificateInfo_2325) {

    copied_info = poppler_signature_info_copy(original_info);

    // Assuming certificate_info is a simple struct and direct comparison is valid

    EXPECT_EQ(copied_info->certificate_info, original_info->certificate_info);

}



TEST_F(PopplerSignatureInfoTest_2325, CopyHandlesNullInput_2325) {

    copied_info = poppler_signature_info_copy(nullptr);

    EXPECT_EQ(copied_info, nullptr);

}
