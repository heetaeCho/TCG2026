#include <gtest/gtest.h>

// Include the necessary headers
#include "poppler-form.h"
#include "CertificateInfo.h"

// We need access to the static function. Since it's in the Poppler namespace
// and defined in the .cc file, we need to either declare it or include the source.
// For testing purposes, we'll re-declare the function signature as it appears
// in the namespace, or we test through the public API that uses it.

// Since fromPopplerCore is a static (file-local) function in the .cc file,
// we cannot directly call it from outside. However, based on the prompt,
// we test the observable behavior through the public interface.
// 
// If we can access it (e.g., via a test helper or by including the .cc),
// we test it directly. Otherwise, we test through public API.
//
// For this test, let's assume we can include the source to test the function directly.

// Forward declare or include what's needed
namespace Poppler {

// Re-declare the function to make it testable
// This mirrors the signature from the .cc file
static CertificateInfo::CertificateType fromPopplerCore(CertificateType type);

} // namespace Poppler

// Include the implementation to get the static function
// This is a common technique for testing file-static functions
#include "poppler-form.cc"

class FromPopplerCoreTest_1366 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: PGP type maps correctly
TEST_F(FromPopplerCoreTest_1366, PGPTypeMapsCorrectly_1366)
{
    auto result = Poppler::fromPopplerCore(CertificateType::PGP);
    EXPECT_EQ(result, Poppler::CertificateInfo::CertificateType::PGP);
}

// Test: X509 type maps correctly
TEST_F(FromPopplerCoreTest_1366, X509TypeMapsCorrectly_1366)
{
    auto result = Poppler::fromPopplerCore(CertificateType::X509);
    EXPECT_EQ(result, Poppler::CertificateInfo::CertificateType::X509);
}

// Test: Unknown/invalid enum value falls back to X509
TEST_F(FromPopplerCoreTest_1366, UnknownTypeFallsBackToX509_1366)
{
    // Cast an invalid integer to CertificateType to simulate an unknown value
    auto invalidType = static_cast<CertificateType>(99);
    auto result = Poppler::fromPopplerCore(invalidType);
    EXPECT_EQ(result, Poppler::CertificateInfo::CertificateType::X509);
}

// Test: Another invalid enum value also falls back to X509
TEST_F(FromPopplerCoreTest_1366, NegativeValueFallsBackToX509_1366)
{
    auto invalidType = static_cast<CertificateType>(-1);
    auto result = Poppler::fromPopplerCore(invalidType);
    EXPECT_EQ(result, Poppler::CertificateInfo::CertificateType::X509);
}

// Test: Boundary - enum value 0 corresponds to X509
TEST_F(FromPopplerCoreTest_1366, EnumValueZeroIsX509_1366)
{
    auto type = static_cast<CertificateType>(0);
    auto result = Poppler::fromPopplerCore(type);
    EXPECT_EQ(result, Poppler::CertificateInfo::CertificateType::X509);
}

// Test: Boundary - enum value 1 corresponds to PGP
TEST_F(FromPopplerCoreTest_1366, EnumValueOneIsPGP_1366)
{
    auto type = static_cast<CertificateType>(1);
    auto result = Poppler::fromPopplerCore(type);
    EXPECT_EQ(result, Poppler::CertificateInfo::CertificateType::PGP);
}

// Test: Large invalid enum value falls back to X509
TEST_F(FromPopplerCoreTest_1366, LargeInvalidValueFallsBackToX509_1366)
{
    auto invalidType = static_cast<CertificateType>(1000);
    auto result = Poppler::fromPopplerCore(invalidType);
    EXPECT_EQ(result, Poppler::CertificateInfo::CertificateType::X509);
}

// Test: Verify PGP result is not equal to X509
TEST_F(FromPopplerCoreTest_1366, PGPResultIsNotX509_1366)
{
    auto result = Poppler::fromPopplerCore(CertificateType::PGP);
    EXPECT_NE(result, Poppler::CertificateInfo::CertificateType::X509);
}

// Test: Verify X509 result is not equal to PGP
TEST_F(FromPopplerCoreTest_1366, X509ResultIsNotPGP_1366)
{
    auto result = Poppler::fromPopplerCore(CertificateType::X509);
    EXPECT_NE(result, Poppler::CertificateInfo::CertificateType::PGP);
}
