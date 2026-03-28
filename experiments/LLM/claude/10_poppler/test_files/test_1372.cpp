#include <gtest/gtest.h>
#include <optional>

// Include necessary headers based on the provided code
#include "poppler-form.h"
#include "CryptoSignBackend.h"

// Since convertToFrontend is a static function in the .cc file, we need to
// either make it accessible or replicate its declaration for testing.
// Given that it's static (file-local), we include the .cc file directly
// to gain access to it for testing purposes.

// We need to declare/access the function. Since it's static in the .cc file,
// we include the source to make it available in this translation unit.
namespace Poppler {
    static std::optional<CryptoSignBackend> convertToFrontend(std::optional<CryptoSign::Backend::Type> type);
}

// Include the implementation to get the static function
#include "poppler-form.cc"

class ConvertToFrontendTest_1372 : public ::testing::Test {
protected:
};

// Test that passing std::nullopt returns std::nullopt
TEST_F(ConvertToFrontendTest_1372, NulloptInput_ReturnsNullopt_1372)
{
    auto result = Poppler::convertToFrontend(std::nullopt);
    EXPECT_FALSE(result.has_value());
}

// Test that NSS3 backend type converts to NSS CryptoSignBackend
TEST_F(ConvertToFrontendTest_1372, NSS3_ConvertsToNSS_1372)
{
    auto result = Poppler::convertToFrontend(CryptoSign::Backend::Type::NSS3);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), Poppler::CryptoSignBackend::NSS);
}

// Test that GPGME backend type converts to GPG CryptoSignBackend
TEST_F(ConvertToFrontendTest_1372, GPGME_ConvertsToGPG_1372)
{
    auto result = Poppler::convertToFrontend(CryptoSign::Backend::Type::GPGME);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), Poppler::CryptoSignBackend::GPG);
}

// Test that an optional containing NSS3 has a value
TEST_F(ConvertToFrontendTest_1372, NSS3_HasValue_1372)
{
    std::optional<CryptoSign::Backend::Type> input = CryptoSign::Backend::Type::NSS3;
    auto result = Poppler::convertToFrontend(input);
    EXPECT_TRUE(result.has_value());
}

// Test that an optional containing GPGME has a value
TEST_F(ConvertToFrontendTest_1372, GPGME_HasValue_1372)
{
    std::optional<CryptoSign::Backend::Type> input = CryptoSign::Backend::Type::GPGME;
    auto result = Poppler::convertToFrontend(input);
    EXPECT_TRUE(result.has_value());
}

// Test that NSS maps to enum value 0
TEST_F(ConvertToFrontendTest_1372, NSS_EnumValue_1372)
{
    auto result = Poppler::convertToFrontend(CryptoSign::Backend::Type::NSS3);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(static_cast<int>(result.value()), 0);
}

// Test that GPG maps to enum value 1
TEST_F(ConvertToFrontendTest_1372, GPG_EnumValue_1372)
{
    auto result = Poppler::convertToFrontend(CryptoSign::Backend::Type::GPGME);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(static_cast<int>(result.value()), 1);
}

// Test that an unknown/invalid backend type returns nullopt
// This tests the default return at the end of the switch
TEST_F(ConvertToFrontendTest_1372, InvalidBackendType_ReturnsNullopt_1372)
{
    // Create an invalid enum value by casting an integer that doesn't correspond to any valid enum
    auto invalidType = static_cast<CryptoSign::Backend::Type>(999);
    std::optional<CryptoSign::Backend::Type> input = invalidType;
    auto result = Poppler::convertToFrontend(input);
    EXPECT_FALSE(result.has_value());
}

// Test consistency: calling the function multiple times with same input yields same result
TEST_F(ConvertToFrontendTest_1372, Consistency_NSS3_1372)
{
    auto result1 = Poppler::convertToFrontend(CryptoSign::Backend::Type::NSS3);
    auto result2 = Poppler::convertToFrontend(CryptoSign::Backend::Type::NSS3);
    ASSERT_TRUE(result1.has_value());
    ASSERT_TRUE(result2.has_value());
    EXPECT_EQ(result1.value(), result2.value());
}

// Test consistency: calling the function multiple times with nullopt yields nullopt
TEST_F(ConvertToFrontendTest_1372, Consistency_Nullopt_1372)
{
    auto result1 = Poppler::convertToFrontend(std::nullopt);
    auto result2 = Poppler::convertToFrontend(std::nullopt);
    EXPECT_FALSE(result1.has_value());
    EXPECT_FALSE(result2.has_value());
}

// Test that NSS3 and GPGME map to different frontend values
TEST_F(ConvertToFrontendTest_1372, DifferentInputs_DifferentOutputs_1372)
{
    auto nssResult = Poppler::convertToFrontend(CryptoSign::Backend::Type::NSS3);
    auto gpgResult = Poppler::convertToFrontend(CryptoSign::Backend::Type::GPGME);
    ASSERT_TRUE(nssResult.has_value());
    ASSERT_TRUE(gpgResult.has_value());
    EXPECT_NE(nssResult.value(), gpgResult.value());
}
