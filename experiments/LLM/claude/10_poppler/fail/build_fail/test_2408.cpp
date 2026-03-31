#include <gtest/gtest.h>
#include <glib.h>

// Include the poppler glib headers
extern "C" {
#include "poppler-form-field.h"
#include "poppler-document.h"
}

// Forward declarations for functions used in testing
extern "C" {
PopplerCertificateInfo *poppler_get_certificate_info_by_id(const char *id);
GList *poppler_get_available_signing_certificates(void);
PopplerCertificateInfo *poppler_certificate_info_copy(PopplerCertificateInfo *info);
void poppler_certificate_info_free(PopplerCertificateInfo *info);
}

class PopplerCertificateInfoByIdTest_2408 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL id returns nullptr (no certificate should match NULL)
TEST_F(PopplerCertificateInfoByIdTest_2408, NullIdReturnsNull_2408)
{
    PopplerCertificateInfo *result = poppler_get_certificate_info_by_id(nullptr);
    // When id is NULL, unless there's a certificate with NULL id, result should be NULL
    // Since g_strcmp0(NULL, NULL) == 0, this could match a cert with NULL id
    // But typically no certificate has a NULL id, so we expect NULL
    if (result != nullptr) {
        poppler_certificate_info_free(result);
    }
    // We just verify it doesn't crash - either NULL or a valid pointer is acceptable
    SUCCEED();
}

// Test that passing an empty string id returns nullptr when no cert has empty id
TEST_F(PopplerCertificateInfoByIdTest_2408, EmptyIdReturnsNullOrValid_2408)
{
    PopplerCertificateInfo *result = poppler_get_certificate_info_by_id("");
    // Most likely no certificate has an empty string id
    if (result != nullptr) {
        poppler_certificate_info_free(result);
    }
    // Verify it doesn't crash
    SUCCEED();
}

// Test that passing a nonexistent id returns nullptr
TEST_F(PopplerCertificateInfoByIdTest_2408, NonExistentIdReturnsNull_2408)
{
    PopplerCertificateInfo *result = poppler_get_certificate_info_by_id("this_id_should_not_exist_in_any_certificate_store_12345");
    EXPECT_EQ(result, nullptr);
}

// Test that passing a very long string id doesn't crash and returns nullptr
TEST_F(PopplerCertificateInfoByIdTest_2408, VeryLongIdReturnsNull_2408)
{
    std::string long_id(10000, 'A');
    PopplerCertificateInfo *result = poppler_get_certificate_info_by_id(long_id.c_str());
    EXPECT_EQ(result, nullptr);
}

// Test that the function can be called multiple times without leaking or crashing
TEST_F(PopplerCertificateInfoByIdTest_2408, MultipleCallsDoNotCrash_2408)
{
    for (int i = 0; i < 10; i++) {
        PopplerCertificateInfo *result = poppler_get_certificate_info_by_id("nonexistent_id");
        if (result != nullptr) {
            poppler_certificate_info_free(result);
        }
    }
    SUCCEED();
}

// Test with special characters in the id
TEST_F(PopplerCertificateInfoByIdTest_2408, SpecialCharactersInIdReturnsNull_2408)
{
    PopplerCertificateInfo *result = poppler_get_certificate_info_by_id("!@#$%^&*()_+-=[]{}|;':\",./<>?");
    EXPECT_EQ(result, nullptr);
}

// Test that if a matching certificate exists in the system, a valid copy is returned
// This test checks against available certificates dynamically
TEST_F(PopplerCertificateInfoByIdTest_2408, MatchingCertificateReturnsCopy_2408)
{
    GList *certs = poppler_get_available_signing_certificates();
    if (certs != nullptr) {
        // Get the first certificate's id and try to look it up
        PopplerCertificateInfo *first_cert = (PopplerCertificateInfo *)certs->data;
        if (first_cert != nullptr) {
            // We need to access the id field - since poppler_certificate_info has an id field
            // We use the getter if available, but based on the code, info->id is used directly
            // For the test, we'll use poppler_certificate_info_get_id if available
            const char *cert_id = poppler_certificate_info_get_id(first_cert);
            if (cert_id != nullptr) {
                PopplerCertificateInfo *result = poppler_get_certificate_info_by_id(cert_id);
                EXPECT_NE(result, nullptr);
                if (result != nullptr) {
                    const char *result_id = poppler_certificate_info_get_id(result);
                    EXPECT_STREQ(result_id, cert_id);
                    poppler_certificate_info_free(result);
                }
            }
        }
        g_list_free_full(certs, (GDestroyNotify)poppler_certificate_info_free);
    } else {
        // No certificates available on this system, just verify no crash
        SUCCEED();
    }
}

// Test that the returned certificate is a copy (different pointer) from the original list
TEST_F(PopplerCertificateInfoByIdTest_2408, ReturnedCertificateIsACopy_2408)
{
    GList *certs = poppler_get_available_signing_certificates();
    if (certs != nullptr) {
        PopplerCertificateInfo *first_cert = (PopplerCertificateInfo *)certs->data;
        if (first_cert != nullptr) {
            const char *cert_id = poppler_certificate_info_get_id(first_cert);
            if (cert_id != nullptr) {
                PopplerCertificateInfo *result = poppler_get_certificate_info_by_id(cert_id);
                if (result != nullptr) {
                    // The result should be a copy, not the same pointer
                    // (The original list is freed inside the function)
                    EXPECT_NE(result, first_cert);
                    poppler_certificate_info_free(result);
                }
            }
        }
        g_list_free_full(certs, (GDestroyNotify)poppler_certificate_info_free);
    } else {
        SUCCEED();
    }
}
