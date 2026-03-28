#include <gtest/gtest.h>
#include "poppler-form.h"
#include "SignatureInfo.h"

// We need to test the static function fromInternal which is in the Poppler namespace.
// Since it's a static function in a .cc file, we may need to access it differently.
// However, based on the interface, we test through the SignatureValidationInfo class
// or directly if the function is accessible.

// Since fromInternal is a static (file-local) function in the .cc file, we cannot
// directly call it from outside. However, the behavior is observable through
// SignatureValidationInfo's public interface. We'll test the mapping by examining
// what the class exposes.

// If we can include the implementation file for testing purposes:
// We replicate the function signature to test it. But since the constraint says
// not to re-implement, we test through the public API that uses this function.

// Given that fromInternal is a static helper used internally, the most practical
// approach for unit testing is to test it through the public interface that calls it.
// The SignatureValidationInfo::certificateStatus() method likely returns the result
// of fromInternal(). We test through constructing SignatureValidationInfo objects
// if possible, or we test the mapping directly if we can access the function.

// For the purpose of this test, we assume the function can be tested by including
// the source or that it's made testable. We'll write tests based on the observable
// mapping behavior.

namespace Poppler {

// Forward declaration - the function is static in the .cc file, so for testing
// we may need to include the .cc file or use a test helper.
// This is a common pattern for testing file-static functions.

} // namespace Poppler

// Include the implementation to access the static function for testing
// This is a standard technique for unit testing file-static functions
#include "poppler-form.cc"

namespace {

class FromInternalTest_1368 : public ::testing::Test {
protected:
    // Helper to call the static function
    Poppler::SignatureValidationInfo::CertificateStatus callFromInternal(CertificateValidationStatus status) {
        return Poppler::fromInternal(status);
    }
};

// Normal operation tests

TEST_F(FromInternalTest_1368, CertificateTrusted_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateTrusted,
              callFromInternal(CERTIFICATE_TRUSTED));
}

TEST_F(FromInternalTest_1368, CertificateUntrustedIssuer_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateUntrustedIssuer,
              callFromInternal(CERTIFICATE_UNTRUSTED_ISSUER));
}

TEST_F(FromInternalTest_1368, CertificateUnknownIssuer_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateUnknownIssuer,
              callFromInternal(CERTIFICATE_UNKNOWN_ISSUER));
}

TEST_F(FromInternalTest_1368, CertificateRevoked_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateRevoked,
              callFromInternal(CERTIFICATE_REVOKED));
}

TEST_F(FromInternalTest_1368, CertificateExpired_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateExpired,
              callFromInternal(CERTIFICATE_EXPIRED));
}

TEST_F(FromInternalTest_1368, CertificateGenericError_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateGenericError,
              callFromInternal(CERTIFICATE_GENERIC_ERROR));
}

TEST_F(FromInternalTest_1368, CertificateNotVerified_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateNotVerified,
              callFromInternal(CERTIFICATE_NOT_VERIFIED));
}

// Boundary / exceptional cases

TEST_F(FromInternalTest_1368, UnknownStatusReturnsGenericError_1368) {
    // Any value not in the enum should fall through to the default case
    // which returns CertificateGenericError
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateGenericError,
              callFromInternal(static_cast<CertificateValidationStatus>(999)));
}

TEST_F(FromInternalTest_1368, NegativeStatusReturnsGenericError_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateGenericError,
              callFromInternal(static_cast<CertificateValidationStatus>(-1)));
}

TEST_F(FromInternalTest_1368, LargeValueReturnsGenericError_1368) {
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateGenericError,
              callFromInternal(static_cast<CertificateValidationStatus>(100)));
}

TEST_F(FromInternalTest_1368, ValueJustAboveEnumRangeReturnsGenericError_1368) {
    // CERTIFICATE_NOT_VERIFIED is 6, test with 7
    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateGenericError,
              callFromInternal(static_cast<CertificateValidationStatus>(7)));
}

// Verify all enum values map correctly (completeness test)
TEST_F(FromInternalTest_1368, AllEnumValuesMappedCorrectly_1368) {
    struct TestCase {
        CertificateValidationStatus input;
        Poppler::SignatureValidationInfo::CertificateStatus expected;
    };

    TestCase cases[] = {
        {CERTIFICATE_TRUSTED, Poppler::SignatureValidationInfo::CertificateTrusted},
        {CERTIFICATE_UNTRUSTED_ISSUER, Poppler::SignatureValidationInfo::CertificateUntrustedIssuer},
        {CERTIFICATE_UNKNOWN_ISSUER, Poppler::SignatureValidationInfo::CertificateUnknownIssuer},
        {CERTIFICATE_REVOKED, Poppler::SignatureValidationInfo::CertificateRevoked},
        {CERTIFICATE_EXPIRED, Poppler::SignatureValidationInfo::CertificateExpired},
        {CERTIFICATE_GENERIC_ERROR, Poppler::SignatureValidationInfo::CertificateGenericError},
        {CERTIFICATE_NOT_VERIFIED, Poppler::SignatureValidationInfo::CertificateNotVerified},
    };

    for (const auto &tc : cases) {
        EXPECT_EQ(tc.expected, callFromInternal(tc.input))
            << "Failed for input status value: " << static_cast<int>(tc.input);
    }
}

} // anonymous namespace
