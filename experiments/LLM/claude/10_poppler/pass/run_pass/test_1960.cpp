#include <gtest/gtest.h>
#include <optional>
#include <string_view>

// Include the header for CryptoSign
#include "CryptoSignBackend.h"

class CryptoSignFactoryTest_1960 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "GPG" maps to Backend::Type::GPGME
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_GPG_ReturnsGPGME_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("GPG"));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::GPGME);
}

// Test that "NSS" maps to Backend::Type::NSS3
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_NSS_ReturnsNSS3_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("NSS"));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::NSS3);
}

// Test that empty string returns nullopt
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_EmptyString_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view(""));
    EXPECT_FALSE(result.has_value());
}

// Test that an unrecognized string returns nullopt
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_UnknownString_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("UNKNOWN"));
    EXPECT_FALSE(result.has_value());
}

// Test that a lowercase "gpg" returns nullopt (case sensitivity)
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_LowercaseGPG_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("gpg"));
    EXPECT_FALSE(result.has_value());
}

// Test that a lowercase "nss" returns nullopt (case sensitivity)
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_LowercaseNSS_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("nss"));
    EXPECT_FALSE(result.has_value());
}

// Test that a string with extra whitespace returns nullopt
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_GPGWithSpaces_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view(" GPG"));
    EXPECT_FALSE(result.has_value());
}

// Test that a string with trailing whitespace returns nullopt
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_GPGWithTrailingSpace_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("GPG "));
    EXPECT_FALSE(result.has_value());
}

// Test that "NSS3" is not recognized (only "NSS" is valid)
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_NSS3_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("NSS3"));
    EXPECT_FALSE(result.has_value());
}

// Test that "GPGME" is not recognized (only "GPG" is valid)
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_GPGME_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("GPGME"));
    EXPECT_FALSE(result.has_value());
}

// Test with a single character string
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_SingleChar_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("G"));
    EXPECT_FALSE(result.has_value());
}

// Test with a null-like but non-empty string
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_RandomString_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("OpenSSL"));
    EXPECT_FALSE(result.has_value());
}

// Test mixed case variations
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_MixedCaseGpg_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("Gpg"));
    EXPECT_FALSE(result.has_value());
}

TEST_F(CryptoSignFactoryTest_1960, TypeFromString_MixedCaseNss_ReturnsNullopt_1960) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("Nss"));
    EXPECT_FALSE(result.has_value());
}

// Test with very long string
TEST_F(CryptoSignFactoryTest_1960, TypeFromString_VeryLongString_ReturnsNullopt_1960) {
    std::string longStr(1000, 'A');
    auto result = CryptoSign::Factory::typeFromString(std::string_view(longStr));
    EXPECT_FALSE(result.has_value());
}
