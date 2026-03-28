#include <glib.h>
#include <gtest/gtest.h>

// Include the poppler glib headers
#include "poppler.h"

class PopplerSigningDataCertificateInfoTest_2358 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;
    PopplerCertificateInfo *cert_info = nullptr;

    void SetUp() override {
        signing_data = poppler_signing_data_new();
        cert_info = poppler_certificate_info_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
        }
        if (cert_info) {
            poppler_certificate_info_free(cert_info);
        }
    }
};

// Test normal operation: setting certificate info on signing data
TEST_F(PopplerSigningDataCertificateInfoTest_2358, SetCertificateInfoNormal_2358) {
    poppler_signing_data_set_certificate_info(signing_data, cert_info);
    
    const PopplerCertificateInfo *retrieved = poppler_signing_data_get_certificate_info(signing_data);
    ASSERT_NE(retrieved, nullptr);
    // The retrieved pointer should be a copy, not the same pointer
    EXPECT_NE(retrieved, cert_info);
}

// Test that passing NULL signing_data does not crash (g_return_if_fail handles it)
TEST_F(PopplerSigningDataCertificateInfoTest_2358, NullSigningDataDoesNotCrash_2358) {
    // g_return_if_fail will print a warning and return, should not crash
    poppler_signing_data_set_certificate_info(nullptr, cert_info);
    // If we reach here, the test passes (no crash)
}

// Test that passing NULL certificate_info does not crash
TEST_F(PopplerSigningDataCertificateInfoTest_2358, NullCertificateInfoDoesNotCrash_2358) {
    poppler_signing_data_set_certificate_info(signing_data, nullptr);
    // If we reach here, the test passes (no crash)
}

// Test that both NULL parameters do not crash
TEST_F(PopplerSigningDataCertificateInfoTest_2358, BothNullDoesNotCrash_2358) {
    poppler_signing_data_set_certificate_info(nullptr, nullptr);
    // If we reach here, the test passes (no crash)
}

// Test setting certificate info makes a copy (not storing the same pointer)
TEST_F(PopplerSigningDataCertificateInfoTest_2358, SetCertificateInfoMakesCopy_2358) {
    poppler_signing_data_set_certificate_info(signing_data, cert_info);
    
    const PopplerCertificateInfo *retrieved = poppler_signing_data_get_certificate_info(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_NE(retrieved, cert_info);
}

// Test replacing certificate info (set it twice)
TEST_F(PopplerSigningDataCertificateInfoTest_2358, ReplaceCertificateInfo_2358) {
    PopplerCertificateInfo *cert_info2 = poppler_certificate_info_new();
    
    poppler_signing_data_set_certificate_info(signing_data, cert_info);
    const PopplerCertificateInfo *first = poppler_signing_data_get_certificate_info(signing_data);
    ASSERT_NE(first, nullptr);
    
    poppler_signing_data_set_certificate_info(signing_data, cert_info2);
    const PopplerCertificateInfo *second = poppler_signing_data_get_certificate_info(signing_data);
    ASSERT_NE(second, nullptr);
    
    // The two retrieved pointers should be different since different cert_infos were set
    EXPECT_NE(second, first);
    
    poppler_certificate_info_free(cert_info2);
}

// Test self-assignment: setting the same certificate_info that's already stored
TEST_F(PopplerSigningDataCertificateInfoTest_2358, SelfAssignmentDoesNotCrash_2358) {
    poppler_signing_data_set_certificate_info(signing_data, cert_info);
    
    const PopplerCertificateInfo *retrieved = poppler_signing_data_get_certificate_info(signing_data);
    ASSERT_NE(retrieved, nullptr);
    
    // Setting the same pointer that's already stored - self-assignment guard
    poppler_signing_data_set_certificate_info(signing_data, retrieved);
    
    const PopplerCertificateInfo *retrieved2 = poppler_signing_data_get_certificate_info(signing_data);
    EXPECT_NE(retrieved2, nullptr);
    // Should be the same pointer since self-assignment is a no-op
    EXPECT_EQ(retrieved2, retrieved);
}

// Test setting certificate info multiple times in succession
TEST_F(PopplerSigningDataCertificateInfoTest_2358, MultipleSetOperations_2358) {
    for (int i = 0; i < 10; i++) {
        PopplerCertificateInfo *temp_cert = poppler_certificate_info_new();
        poppler_signing_data_set_certificate_info(signing_data, temp_cert);
        
        const PopplerCertificateInfo *retrieved = poppler_signing_data_get_certificate_info(signing_data);
        ASSERT_NE(retrieved, nullptr);
        EXPECT_NE(retrieved, temp_cert);
        
        poppler_certificate_info_free(temp_cert);
    }
}
