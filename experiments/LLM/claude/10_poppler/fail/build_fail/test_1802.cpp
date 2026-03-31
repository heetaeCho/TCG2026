#include <gtest/gtest.h>

// Include necessary headers
#include "SignatureInfo.h"

// NSS CMS Verification Status enum - these are defined in NSS headers
// We need to replicate the enum values to test without full NSS dependency
typedef enum {
    NSSCMSVS_Unverified = 0,
    NSSCMSVS_GoodSignature = 1,
    NSSCMSVS_BadSignature = 2,
    NSSCMSVS_DigestMismatch = 3,
    NSSCMSVS_SigningCertNotFound = 4,
    NSSCMSVS_SigningCertNotTrusted = 5,
    NSSCMSVS_SignatureAlgorithmUnknown = 6,
    NSSCMSVS_SignatureAlgorithmUnsupported = 7,
    NSSCMSVS_MalformedSignature = 8,
    NSSCMSVS_ProcessingError = 9
} NSSCMSVerificationStatus;

// Declaration of the function under test (it's static in the .cc file,
// so we need to include it or re-declare it for testing purposes)
// Since the function is static, we include the source to make it accessible in this TU
// We use a workaround: redefine static as nothing for test inclusion
#define static
#include "NSSCryptoSignBackend.cc"
#undef static

class NSSSigTranslateTest_1802 : public ::testing::Test {
protected:
    // No setup needed
};

// Test: GoodSignature maps to SIGNATURE_VALID
TEST_F(NSSSigTranslateTest_1802, GoodSignatureReturnsValid_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_GoodSignature);
    EXPECT_EQ(result, SIGNATURE_VALID);
}

// Test: BadSignature maps to SIGNATURE_INVALID
TEST_F(NSSSigTranslateTest_1802, BadSignatureReturnsInvalid_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_BadSignature);
    EXPECT_EQ(result, SIGNATURE_INVALID);
}

// Test: DigestMismatch maps to SIGNATURE_DIGEST_MISMATCH
TEST_F(NSSSigTranslateTest_1802, DigestMismatchReturnsDigestMismatch_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_DigestMismatch);
    EXPECT_EQ(result, SIGNATURE_DIGEST_MISMATCH);
}

// Test: ProcessingError maps to SIGNATURE_DECODING_ERROR
TEST_F(NSSSigTranslateTest_1802, ProcessingErrorReturnsDecodingError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_ProcessingError);
    EXPECT_EQ(result, SIGNATURE_DECODING_ERROR);
}

// Test: Unverified (not explicitly handled) maps to SIGNATURE_GENERIC_ERROR
TEST_F(NSSSigTranslateTest_1802, UnverifiedReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_Unverified);
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}

// Test: SigningCertNotFound maps to SIGNATURE_GENERIC_ERROR (default case)
TEST_F(NSSSigTranslateTest_1802, SigningCertNotFoundReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_SigningCertNotFound);
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}

// Test: SigningCertNotTrusted maps to SIGNATURE_GENERIC_ERROR (default case)
TEST_F(NSSSigTranslateTest_1802, SigningCertNotTrustedReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_SigningCertNotTrusted);
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}

// Test: SignatureAlgorithmUnknown maps to SIGNATURE_GENERIC_ERROR (default case)
TEST_F(NSSSigTranslateTest_1802, SignatureAlgorithmUnknownReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_SignatureAlgorithmUnknown);
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}

// Test: SignatureAlgorithmUnsupported maps to SIGNATURE_GENERIC_ERROR (default case)
TEST_F(NSSSigTranslateTest_1802, SignatureAlgorithmUnsupportedReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_SignatureAlgorithmUnsupported);
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}

// Test: MalformedSignature maps to SIGNATURE_GENERIC_ERROR (default case)
TEST_F(NSSSigTranslateTest_1802, MalformedSignatureReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(NSSCMSVS_MalformedSignature);
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}

// Test: An arbitrary out-of-range value maps to SIGNATURE_GENERIC_ERROR (default case)
TEST_F(NSSSigTranslateTest_1802, UnknownValueReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(static_cast<NSSCMSVerificationStatus>(999));
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}

// Test: Negative value (if cast is possible) maps to SIGNATURE_GENERIC_ERROR
TEST_F(NSSSigTranslateTest_1802, NegativeValueReturnsGenericError_1802)
{
    SignatureValidationStatus result = NSS_SigTranslate(static_cast<NSSCMSVerificationStatus>(-1));
    EXPECT_EQ(result, SIGNATURE_GENERIC_ERROR);
}
