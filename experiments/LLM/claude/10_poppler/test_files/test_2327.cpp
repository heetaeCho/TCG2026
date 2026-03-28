#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and type definitions based on the interface
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

typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

typedef struct _PopplerSignatureInfo {
    PopplerSignatureStatus sig_status;
    PopplerCertificateStatus cert_status;
    char *signer_name;
    int *local_signing_time;
    PopplerCertificateInfo *certificate_info;
} PopplerSignatureInfo;

// Declaration of the function under test
extern "C" {
PopplerSignatureStatus poppler_signature_info_get_signature_status(const PopplerSignatureInfo *siginfo);
}

class PopplerSignatureInfoTest_2327 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns POPPLER_SIGNATURE_GENERIC_ERROR
TEST_F(PopplerSignatureInfoTest_2327, NullInputReturnsGenericError_2327)
{
    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(nullptr);
    EXPECT_EQ(result, POPPLER_SIGNATURE_GENERIC_ERROR);
}

// Test that a valid signature info with POPPLER_SIGNATURE_VALID returns correctly
TEST_F(PopplerSignatureInfoTest_2327, ValidSignatureStatusReturnsValid_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_VALID;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_VALID);
}

// Test that POPPLER_SIGNATURE_INVALID is returned correctly
TEST_F(PopplerSignatureInfoTest_2327, InvalidSignatureStatusReturnsInvalid_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_INVALID;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_INVALID);
}

// Test that POPPLER_SIGNATURE_DIGEST_MISMATCH is returned correctly
TEST_F(PopplerSignatureInfoTest_2327, DigestMismatchStatusReturnsDigestMismatch_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_DIGEST_MISMATCH;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_DIGEST_MISMATCH);
}

// Test that POPPLER_SIGNATURE_DECODING_ERROR is returned correctly
TEST_F(PopplerSignatureInfoTest_2327, DecodingErrorStatusReturnsDecodingError_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_DECODING_ERROR;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_DECODING_ERROR);
}

// Test that POPPLER_SIGNATURE_GENERIC_ERROR is returned correctly
TEST_F(PopplerSignatureInfoTest_2327, GenericErrorStatusReturnsGenericError_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_GENERIC_ERROR;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_GENERIC_ERROR);
}

// Test that POPPLER_SIGNATURE_NOT_FOUND is returned correctly
TEST_F(PopplerSignatureInfoTest_2327, NotFoundStatusReturnsNotFound_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_NOT_FOUND;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_NOT_FOUND);
}

// Test that POPPLER_SIGNATURE_NOT_VERIFIED is returned correctly
TEST_F(PopplerSignatureInfoTest_2327, NotVerifiedStatusReturnsNotVerified_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_NOT_VERIFIED;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_NOT_VERIFIED);
}

// Test that the function only reads sig_status and ignores other fields
TEST_F(PopplerSignatureInfoTest_2327, OtherFieldsDoNotAffectResult_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_VALID;
    siginfo.cert_status = POPPLER_CERTIFICATE_REVOKED;
    siginfo.signer_name = const_cast<char *>("test signer");
    siginfo.local_signing_time = nullptr;
    siginfo.certificate_info = nullptr;

    PopplerSignatureStatus result = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result, POPPLER_SIGNATURE_VALID);
}

// Test consistency: calling the function multiple times returns the same result
TEST_F(PopplerSignatureInfoTest_2327, ConsistentReturnOnMultipleCalls_2327)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = POPPLER_SIGNATURE_INVALID;

    PopplerSignatureStatus result1 = poppler_signature_info_get_signature_status(&siginfo);
    PopplerSignatureStatus result2 = poppler_signature_info_get_signature_status(&siginfo);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, POPPLER_SIGNATURE_INVALID);
}
