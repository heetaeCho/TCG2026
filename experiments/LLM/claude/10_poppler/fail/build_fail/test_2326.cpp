#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definitions based on the provided interface
typedef enum {
    POPPLER_SIGNATURE_VALID,
    POPPLER_SIGNATURE_INVALID,
    POPPLER_SIGNATURE_DIGEST_MISMATCH,
    POPPLER_SIGNATURE_DECODING_ERROR,
    POPPLER_SIGNATURE_GENERIC_ERROR,
    POPPLER_SIGNATURE_NOT_FOUND,
    POPPLER_SIGNATURE_NOT_VERIFIED
} PopplerSignatureStatus;

typedef enum {
    POPPLER_CERTIFICATE_TRUSTED,
    POPPLER_CERTIFICATE_UNTRUSTED_ISSUER,
    POPPLER_CERTIFICATE_UNKNOWN_ISSUER,
    POPPLER_CERTIFICATE_REVOKED,
    POPPLER_CERTIFICATE_EXPIRED,
    POPPLER_CERTIFICATE_GENERIC_ERROR,
    POPPLER_CERTIFICATE_NOT_VERIFIED
} PopplerCertificateStatus;

// Based on known dependencies, we need these structures
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

struct _PopplerSignatureInfo {
    PopplerSignatureStatus sig_status;
    PopplerCertificateStatus cert_status;
    char *signer_name;
    GDateTime *local_signing_time;
    PopplerCertificateInfo *certificate_info;
};

typedef struct _PopplerSignatureInfo PopplerSignatureInfo;

// External functions we're testing
extern "C" {
void poppler_signature_info_free(PopplerSignatureInfo *siginfo);
void poppler_certificate_info_free(PopplerCertificateInfo *certinfo);
}

class PopplerSignatureInfoFreeTest_2326 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr does not crash
TEST_F(PopplerSignatureInfoFreeTest_2326, FreeNullPointerDoesNotCrash_2326)
{
    // Should safely handle nullptr without crashing
    EXPECT_NO_FATAL_FAILURE(poppler_signature_info_free(nullptr));
}

// Test that passing NULL (C-style) does not crash
TEST_F(PopplerSignatureInfoFreeTest_2326, FreeCStyleNullDoesNotCrash_2326)
{
    PopplerSignatureInfo *siginfo = NULL;
    EXPECT_NO_FATAL_FAILURE(poppler_signature_info_free(siginfo));
}

// Test freeing a properly allocated PopplerSignatureInfo with all fields populated
TEST_F(PopplerSignatureInfoFreeTest_2326, FreeValidSignatureInfo_2326)
{
    PopplerSignatureInfo *siginfo = g_new0(PopplerSignatureInfo, 1);
    siginfo->signer_name = g_strdup("Test Signer");
    siginfo->local_signing_time = g_date_time_new_now_local();
    siginfo->certificate_info = nullptr;
    siginfo->sig_status = POPPLER_SIGNATURE_VALID;
    siginfo->cert_status = POPPLER_CERTIFICATE_TRUSTED;

    // Should free without crashing or leaking
    EXPECT_NO_FATAL_FAILURE(poppler_signature_info_free(siginfo));
}

// Test freeing a PopplerSignatureInfo where signer_name is null
TEST_F(PopplerSignatureInfoFreeTest_2326, FreeSignatureInfoWithNullSignerName_2326)
{
    PopplerSignatureInfo *siginfo = g_new0(PopplerSignatureInfo, 1);
    siginfo->signer_name = nullptr;
    siginfo->local_signing_time = g_date_time_new_now_local();
    siginfo->certificate_info = nullptr;

    EXPECT_NO_FATAL_FAILURE(poppler_signature_info_free(siginfo));
}

// Test freeing a PopplerSignatureInfo with empty signer name
TEST_F(PopplerSignatureInfoFreeTest_2326, FreeSignatureInfoWithEmptySignerName_2326)
{
    PopplerSignatureInfo *siginfo = g_new0(PopplerSignatureInfo, 1);
    siginfo->signer_name = g_strdup("");
    siginfo->local_signing_time = g_date_time_new_now_local();
    siginfo->certificate_info = nullptr;

    EXPECT_NO_FATAL_FAILURE(poppler_signature_info_free(siginfo));
}

// Test freeing with a specific date/time
TEST_F(PopplerSignatureInfoFreeTest_2326, FreeSignatureInfoWithSpecificDateTime_2326)
{
    PopplerSignatureInfo *siginfo = g_new0(PopplerSignatureInfo, 1);
    siginfo->signer_name = g_strdup("Another Signer");
    siginfo->local_signing_time = g_date_time_new_local(2023, 6, 15, 10, 30, 0);
    siginfo->certificate_info = nullptr;

    EXPECT_NO_FATAL_FAILURE(poppler_signature_info_free(siginfo));
}

// Test calling free multiple times with nullptr (idempotent for null)
TEST_F(PopplerSignatureInfoFreeTest_2326, FreeNullMultipleTimes_2326)
{
    EXPECT_NO_FATAL_FAILURE({
        poppler_signature_info_free(nullptr);
        poppler_signature_info_free(nullptr);
        poppler_signature_info_free(nullptr);
    });
}
