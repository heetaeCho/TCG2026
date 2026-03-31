#include <gtest/gtest.h>
#include <optional>

// Include necessary headers based on the provided code
#include "poppler-form.h"
#include "CryptoSignBackend.h"

// We need access to the convertToBackend function which is static in the .cc file.
// Since it's static (file-local), we cannot directly call it from a test file.
// We need to re-declare or include the source. Given the constraints, we include the .cc
// to get access to the static function for testing purposes.

// Forward declaration approach won't work for static functions, so we include the source.
// This is a common testing pattern for static/file-local functions.
namespace Poppler {
    static std::optional<CryptoSign::Backend::Type> convertToBackend(std::optional<CryptoSignBackend> backend);
}

// Include the implementation to get the static function definition
#include "poppler-form.cc"

namespace {

class ConvertToBackendTest_1373 : public ::testing::Test {
protected:
};

// Test that passing std::nullopt returns std::nullopt
TEST_F(ConvertToBackendTest_1373, NulloptInputReturnsNullopt_1373)
{
    auto result = Poppler::convertToBackend(std::nullopt);
    EXPECT_FALSE(result.has_value());
}

// Test that passing no value (default constructed optional) returns std::nullopt
TEST_F(ConvertToBackendTest_1373, DefaultOptionalReturnsNullopt_1373)
{
    std::optional<Poppler::CryptoSignBackend> input;
    auto result = Poppler::convertToBackend(input);
    EXPECT_FALSE(result.has_value());
}

// Test that NSS backend converts to NSS3
TEST_F(ConvertToBackendTest_1373, NSSConvertsToNSS3_1373)
{
    auto result = Poppler::convertToBackend(Poppler::CryptoSignBackend::NSS);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::NSS3);
}

// Test that GPG backend converts to GPGME
TEST_F(ConvertToBackendTest_1373, GPGConvertsToGPGME_1373)
{
    auto result = Poppler::convertToBackend(Poppler::CryptoSignBackend::GPG);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::GPGME);
}

// Test that NSS maps to the correct integer value (0)
TEST_F(ConvertToBackendTest_1373, NSSMapsToCorrectEnumValue_1373)
{
    auto result = Poppler::convertToBackend(Poppler::CryptoSignBackend::NSS);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(static_cast<int>(result.value()), 0);
}

// Test that GPG maps to the correct integer value (1)
TEST_F(ConvertToBackendTest_1373, GPGMapsToCorrectEnumValue_1373)
{
    auto result = Poppler::convertToBackend(Poppler::CryptoSignBackend::GPG);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(static_cast<int>(result.value()), 1);
}

// Test that an optional explicitly containing NSS works
TEST_F(ConvertToBackendTest_1373, ExplicitOptionalNSS_1373)
{
    std::optional<Poppler::CryptoSignBackend> input = Poppler::CryptoSignBackend::NSS;
    auto result = Poppler::convertToBackend(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::NSS3);
}

// Test that an optional explicitly containing GPG works
TEST_F(ConvertToBackendTest_1373, ExplicitOptionalGPG_1373)
{
    std::optional<Poppler::CryptoSignBackend> input = Poppler::CryptoSignBackend::GPG;
    auto result = Poppler::convertToBackend(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::GPGME);
}

// Test boundary: an invalid enum value (cast from an out-of-range int) should return nullopt
// This tests the default fall-through in the switch statement
TEST_F(ConvertToBackendTest_1373, InvalidEnumValueReturnsNullopt_1373)
{
    // Cast an invalid integer to the enum type
    auto invalidBackend = static_cast<Poppler::CryptoSignBackend>(99);
    auto result = Poppler::convertToBackend(invalidBackend);
    EXPECT_FALSE(result.has_value());
}

// Test boundary: another invalid enum value (negative)
TEST_F(ConvertToBackendTest_1373, NegativeEnumValueReturnsNullopt_1373)
{
    auto invalidBackend = static_cast<Poppler::CryptoSignBackend>(-1);
    auto result = Poppler::convertToBackend(invalidBackend);
    EXPECT_FALSE(result.has_value());
}

// Test that the result types are distinct for different inputs
TEST_F(ConvertToBackendTest_1373, NSSAndGPGReturnDifferentValues_1373)
{
    auto resultNSS = Poppler::convertToBackend(Poppler::CryptoSignBackend::NSS);
    auto resultGPG = Poppler::convertToBackend(Poppler::CryptoSignBackend::GPG);
    ASSERT_TRUE(resultNSS.has_value());
    ASSERT_TRUE(resultGPG.has_value());
    EXPECT_NE(resultNSS.value(), resultGPG.value());
}

} // anonymous namespace
