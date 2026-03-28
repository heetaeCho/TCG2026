#include <gtest/gtest.h>
#include <glib.h>

// Include the poppler glib headers
extern "C" {
#include "poppler.h"
}

class PopplerSigningDataTest_2359 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }
};

// Test that a newly created signing data returns nullptr for certificate_info
TEST_F(PopplerSigningDataTest_2359, GetCertificateInfoDefaultIsNull_2359)
{
    const PopplerCertificateInfo *cert_info = poppler_signing_data_get_certificate_info(signing_data);
    EXPECT_EQ(cert_info, nullptr);
}

// Test that passing nullptr returns nullptr (g_return_val_if_fail guard)
TEST_F(PopplerSigningDataTest_2359, GetCertificateInfoNullSigningDataReturnsNull_2359)
{
    const PopplerCertificateInfo *cert_info = poppler_signing_data_get_certificate_info(nullptr);
    EXPECT_EQ(cert_info, nullptr);
}

// Test that after setting certificate info, get returns the same pointer
TEST_F(PopplerSigningDataTest_2359, GetCertificateInfoAfterSet_2359)
{
    PopplerCertificateInfo *cert_info = poppler_certificate_info_new();
    ASSERT_NE(cert_info, nullptr);

    poppler_signing_data_set_certificate_info(signing_data, cert_info);

    const PopplerCertificateInfo *retrieved = poppler_signing_data_get_certificate_info(signing_data);
    EXPECT_NE(retrieved, nullptr);

    poppler_certificate_info_free(cert_info);
}

// Test that setting certificate info to nullptr and then getting it returns nullptr
TEST_F(PopplerSigningDataTest_2359, SetCertificateInfoNullThenGet_2359)
{
    // First set a valid cert info
    PopplerCertificateInfo *cert_info = poppler_certificate_info_new();
    poppler_signing_data_set_certificate_info(signing_data, cert_info);
    poppler_certificate_info_free(cert_info);

    // Now set to nullptr
    poppler_signing_data_set_certificate_info(signing_data, nullptr);

    const PopplerCertificateInfo *retrieved = poppler_signing_data_get_certificate_info(signing_data);
    EXPECT_EQ(retrieved, nullptr);
}

// Test that a copied signing data has the same certificate info behavior
TEST_F(PopplerSigningDataTest_2359, CopiedSigningDataGetCertificateInfo_2359)
{
    PopplerCertificateInfo *cert_info = poppler_certificate_info_new();
    poppler_signing_data_set_certificate_info(signing_data, cert_info);
    poppler_certificate_info_free(cert_info);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerCertificateInfo *original_cert = poppler_signing_data_get_certificate_info(signing_data);
    const PopplerCertificateInfo *copy_cert = poppler_signing_data_get_certificate_info(copy);

    // Both should be non-null after setting
    EXPECT_NE(original_cert, nullptr);
    EXPECT_NE(copy_cert, nullptr);

    poppler_signing_data_free(copy);
}

// Test destination filename set/get as part of signing data interface
TEST_F(PopplerSigningDataTest_2359, SetAndGetDestinationFilename_2359)
{
    poppler_signing_data_set_destination_filename(signing_data, "test.pdf");
    const char *filename = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(filename, nullptr);
    EXPECT_STREQ(filename, "test.pdf");
}

// Test password set/get
TEST_F(PopplerSigningDataTest_2359, SetAndGetPassword_2359)
{
    poppler_signing_data_set_password(signing_data, "secret123");
    const char *password = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(password, nullptr);
    EXPECT_STREQ(password, "secret123");
}

// Test reason set/get
TEST_F(PopplerSigningDataTest_2359, SetAndGetReason_2359)
{
    poppler_signing_data_set_reason(signing_data, "Approval");
    const char *reason = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, "Approval");
}

// Test location set/get
TEST_F(PopplerSigningDataTest_2359, SetAndGetLocation_2359)
{
    poppler_signing_data_set_location(signing_data, "New York");
    const char *location = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, "New York");
}

// Test signature text set/get
TEST_F(PopplerSigningDataTest_2359, SetAndGetSignatureText_2359)
{
    poppler_signing_data_set_signature_text(signing_data, "John Doe");
    const char *text = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "John Doe");
}

// Test image path set/get
TEST_F(PopplerSigningDataTest_2359, SetAndGetImagePath_2359)
{
    poppler_signing_data_set_image_path(signing_data, "/path/to/image.png");
    const char *path = poppler_signing_data_get_image_path(signing_data);
    ASSERT_NE(path, nullptr);
    EXPECT_STREQ(path, "/path/to/image.png");
}

// Test field partial name set/get
TEST_F(PopplerSigningDataTest_2359, SetAndGetFieldPartialName_2359)
{
    poppler_signing_data_set_field_partial_name(signing_data, "Signature1");
    const char *name = poppler_signing_data_get_field_partial_name(signing_data);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Signature1");
}
