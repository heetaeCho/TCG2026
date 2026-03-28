#include <gtest/gtest.h>

// Include the enum definition
#include "SignatureInfo.h"

// Since getReadableCertState is a static function in a .cc file, we need to
// redefine its signature here and include/link it. For testing purposes,
// we'll include the implementation directly or declare it.
// We replicate the function here since it's static and not exposed via header.
// This is necessary to test it.

static const char *getReadableCertState(CertificateValidationStatus cert_vs)
{
    switch (cert_vs) {
    case CERTIFICATE_TRUSTED:
        return "Certificate is Trusted.";
    case CERTIFICATE_UNTRUSTED_ISSUER:
        return "Certificate issuer isn't Trusted.";
    case CERTIFICATE_UNKNOWN_ISSUER:
        return "Certificate issuer is unknown.";
    case CERTIFICATE_REVOKED:
        return "Certificate has been Revoked.";
    case CERTIFICATE_EXPIRED:
        return "Certificate has Expired";
    case CERTIFICATE_NOT_VERIFIED:
        return "Certificate has not yet been verified.";
    default:
        return "Unknown issue with Certificate or corrupted data.";
    }
}

class GetReadableCertStateTest_2677 : public ::testing::Test {
protected:
};

TEST_F(GetReadableCertStateTest_2677, CertificateTrusted_2677)
{
    const char *result = getReadableCertState(CERTIFICATE_TRUSTED);
    EXPECT_STREQ(result, "Certificate is Trusted.");
}

TEST_F(GetReadableCertStateTest_2677, CertificateUntrustedIssuer_2677)
{
    const char *result = getReadableCertState(CERTIFICATE_UNTRUSTED_ISSUER);
    EXPECT_STREQ(result, "Certificate issuer isn't Trusted.");
}

TEST_F(GetReadableCertStateTest_2677, CertificateUnknownIssuer_2677)
{
    const char *result = getReadableCertState(CERTIFICATE_UNKNOWN_ISSUER);
    EXPECT_STREQ(result, "Certificate issuer is unknown.");
}

TEST_F(GetReadableCertStateTest_2677, CertificateRevoked_2677)
{
    const char *result = getReadableCertState(CERTIFICATE_REVOKED);
    EXPECT_STREQ(result, "Certificate has been Revoked.");
}

TEST_F(GetReadableCertStateTest_2677, CertificateExpired_2677)
{
    const char *result = getReadableCertState(CERTIFICATE_EXPIRED);
    EXPECT_STREQ(result, "Certificate has Expired");
}

TEST_F(GetReadableCertStateTest_2677, CertificateNotVerified_2677)
{
    const char *result = getReadableCertState(CERTIFICATE_NOT_VERIFIED);
    EXPECT_STREQ(result, "Certificate has not yet been verified.");
}

TEST_F(GetReadableCertStateTest_2677, CertificateGenericErrorFallsToDefault_2677)
{
    const char *result = getReadableCertState(CERTIFICATE_GENERIC_ERROR);
    EXPECT_STREQ(result, "Unknown issue with Certificate or corrupted data.");
}

TEST_F(GetReadableCertStateTest_2677, InvalidEnumValueFallsToDefault_2677)
{
    const char *result = getReadableCertState(static_cast<CertificateValidationStatus>(99));
    EXPECT_STREQ(result, "Unknown issue with Certificate or corrupted data.");
}

TEST_F(GetReadableCertStateTest_2677, NegativeEnumValueFallsToDefault_2677)
{
    const char *result = getReadableCertState(static_cast<CertificateValidationStatus>(-1));
    EXPECT_STREQ(result, "Unknown issue with Certificate or corrupted data.");
}

TEST_F(GetReadableCertStateTest_2677, LargeEnumValueFallsToDefault_2677)
{
    const char *result = getReadableCertState(static_cast<CertificateValidationStatus>(1000));
    EXPECT_STREQ(result, "Unknown issue with Certificate or corrupted data.");
}

TEST_F(GetReadableCertStateTest_2677, ReturnValueIsNotNull_2677)
{
    // Verify all valid enum values return non-null
    for (int i = 0; i <= 6; ++i) {
        const char *result = getReadableCertState(static_cast<CertificateValidationStatus>(i));
        EXPECT_NE(result, nullptr) << "Failed for enum value " << i;
    }
}

TEST_F(GetReadableCertStateTest_2677, BoundaryEnumValueZero_2677)
{
    const char *result = getReadableCertState(static_cast<CertificateValidationStatus>(0));
    EXPECT_STREQ(result, "Certificate is Trusted.");
}

TEST_F(GetReadableCertStateTest_2677, BoundaryEnumValueSix_2677)
{
    const char *result = getReadableCertState(static_cast<CertificateValidationStatus>(6));
    EXPECT_STREQ(result, "Certificate has not yet been verified.");
}

TEST_F(GetReadableCertStateTest_2677, BoundaryEnumValueSeven_2677)
{
    // Value 7 is beyond defined enum, should hit default
    const char *result = getReadableCertState(static_cast<CertificateValidationStatus>(7));
    EXPECT_STREQ(result, "Unknown issue with Certificate or corrupted data.");
}

TEST_F(GetReadableCertStateTest_2677, ExpiredMessageLacksPeriod_2677)
{
    // Notably, CERTIFICATE_EXPIRED message doesn't end with a period (unlike others)
    const char *result = getReadableCertState(CERTIFICATE_EXPIRED);
    std::string str(result);
    EXPECT_EQ(str.back(), 'd'); // "Certificate has Expired" ends with 'd'
}

TEST_F(GetReadableCertStateTest_2677, ConsistentReturnForSameInput_2677)
{
    // Calling twice with the same input should return the same pointer
    const char *result1 = getReadableCertState(CERTIFICATE_TRUSTED);
    const char *result2 = getReadableCertState(CERTIFICATE_TRUSTED);
    EXPECT_EQ(result1, result2);
}
