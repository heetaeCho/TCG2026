#include <glib.h>
#include <poppler.h>
#include "gtest/gtest.h"

// Test fixture for poppler_get_available_signing_certificates
class PopplerSigningCertificatesTest_2407 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated list
        if (cert_list_) {
            g_list_free_full(cert_list_, reinterpret_cast<GDestroyNotify>(poppler_certificate_info_free));
            cert_list_ = nullptr;
        }
    }

    GList *cert_list_ = nullptr;
};

// Test that the function returns either nullptr or a valid GList
TEST_F(PopplerSigningCertificatesTest_2407, ReturnsNullOrValidList_2407)
{
    cert_list_ = poppler_get_available_signing_certificates();
    // The function should return either nullptr (no backend/no certs) or a valid list
    // We can't control the backend, but we can verify the return is usable
    if (cert_list_ != nullptr) {
        EXPECT_GE(g_list_length(cert_list_), 1u);
    } else {
        SUCCEED() << "No signing backend available or no certificates found";
    }
}

// Test that calling the function multiple times doesn't crash and returns consistent types
TEST_F(PopplerSigningCertificatesTest_2407, MultipleCallsDoNotCrash_2407)
{
    GList *list1 = poppler_get_available_signing_certificates();
    GList *list2 = poppler_get_available_signing_certificates();

    // Both calls should return the same number of certificates (consistent behavior)
    guint len1 = list1 ? g_list_length(list1) : 0;
    guint len2 = list2 ? g_list_length(list2) : 0;
    EXPECT_EQ(len1, len2);

    if (list1) {
        g_list_free_full(list1, reinterpret_cast<GDestroyNotify>(poppler_certificate_info_free));
    }
    if (list2) {
        g_list_free_full(list2, reinterpret_cast<GDestroyNotify>(poppler_certificate_info_free));
    }
}

// Test that each element in the returned list is a non-null PopplerCertificateInfo
TEST_F(PopplerSigningCertificatesTest_2407, AllElementsAreNonNull_2407)
{
    cert_list_ = poppler_get_available_signing_certificates();
    if (cert_list_ == nullptr) {
        SUCCEED() << "No backend or certificates available, skipping element check";
        return;
    }

    for (GList *l = cert_list_; l != nullptr; l = l->next) {
        EXPECT_NE(l->data, nullptr) << "Certificate info element should not be null";
    }
}

// Test that if certificates are returned, we can access certificate info properties
TEST_F(PopplerSigningCertificatesTest_2407, CertificateInfoAccessible_2407)
{
    cert_list_ = poppler_get_available_signing_certificates();
    if (cert_list_ == nullptr) {
        SUCCEED() << "No backend or certificates available";
        return;
    }

    PopplerCertificateInfo *info = static_cast<PopplerCertificateInfo *>(cert_list_->data);
    ASSERT_NE(info, nullptr);

    // Try to get the certificate ID - should not crash
    const char *id = poppler_certificate_info_get_id(info);
    // id might be null or a valid string, but calling shouldn't crash
    (void)id;
}

// Test that the returned list length matches expected non-negative value
TEST_F(PopplerSigningCertificatesTest_2407, ListLengthIsNonNegative_2407)
{
    cert_list_ = poppler_get_available_signing_certificates();
    if (cert_list_ != nullptr) {
        guint length = g_list_length(cert_list_);
        EXPECT_GT(length, 0u);
    }
}
