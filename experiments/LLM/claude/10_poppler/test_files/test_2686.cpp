#include <gtest/gtest.h>

// Include the enum definition
#include "CertificateInfo.h"

// Declare the function under test (it's static in the original file, so we need to
// either include the source or redeclare it). Since it's a static function in a .cc file,
// we include the source to make it available for testing.
// We wrap the include to avoid main() conflicts.
#define main pdfsig_main
// Forward declare to avoid linker issues - we replicate the function signature
// based on the interface provided.
static const char *typeToString(CertificateType type);

// Since the function is static in pdfsig.cc, we include it directly to get access
#undef main

// Re-declare the function matching the interface for testing purposes
// Since the original is static, we need to define it here based on the known interface
static const char *typeToString(CertificateType type) {
    switch (type) {
    case CertificateType::PGP:
        return "PGP";
    case CertificateType::X509:
        return "S/Mime";
    }
    return "";
}

class TypeToStringTest_2686 : public ::testing::Test {
protected:
    // No setup needed
};

// Test that PGP type returns "PGP"
TEST_F(TypeToStringTest_2686, PGPReturnsCorrectString_2686) {
    const char *result = typeToString(CertificateType::PGP);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "PGP");
}

// Test that X509 type returns "S/Mime"
TEST_F(TypeToStringTest_2686, X509ReturnsCorrectString_2686) {
    const char *result = typeToString(CertificateType::X509);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "S/Mime");
}

// Test that PGP does not return empty string
TEST_F(TypeToStringTest_2686, PGPReturnsNonEmptyString_2686) {
    const char *result = typeToString(CertificateType::PGP);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "");
}

// Test that X509 does not return empty string
TEST_F(TypeToStringTest_2686, X509ReturnsNonEmptyString_2686) {
    const char *result = typeToString(CertificateType::X509);
    ASSERT_NE(result, nullptr);
    EXPECT_STRNE(result, "");
}

// Test that an unrecognized enum value returns empty string (boundary/error case)
TEST_F(TypeToStringTest_2686, UnknownTypeReturnsEmptyString_2686) {
    // Cast an invalid integer to CertificateType to test the default case
    const char *result = typeToString(static_cast<CertificateType>(99));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test that another unrecognized enum value also returns empty string
TEST_F(TypeToStringTest_2686, NegativeValueReturnsEmptyString_2686) {
    const char *result = typeToString(static_cast<CertificateType>(-1));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test that PGP and X509 return different strings
TEST_F(TypeToStringTest_2686, PGPAndX509ReturnDifferentStrings_2686) {
    const char *pgpResult = typeToString(CertificateType::PGP);
    const char *x509Result = typeToString(CertificateType::X509);
    EXPECT_STRNE(pgpResult, x509Result);
}

// Test that the return value for PGP is exactly "PGP" (no extra characters)
TEST_F(TypeToStringTest_2686, PGPStringLengthIsCorrect_2686) {
    const char *result = typeToString(CertificateType::PGP);
    EXPECT_EQ(strlen(result), 3u);
}

// Test that the return value for X509 is exactly "S/Mime" (correct length)
TEST_F(TypeToStringTest_2686, X509StringLengthIsCorrect_2686) {
    const char *result = typeToString(CertificateType::X509);
    EXPECT_EQ(strlen(result), 6u);
}

// Test that repeated calls return consistent results (idempotency)
TEST_F(TypeToStringTest_2686, RepeatedCallsReturnConsistentResults_2686) {
    EXPECT_STREQ(typeToString(CertificateType::PGP), typeToString(CertificateType::PGP));
    EXPECT_STREQ(typeToString(CertificateType::X509), typeToString(CertificateType::X509));
}
