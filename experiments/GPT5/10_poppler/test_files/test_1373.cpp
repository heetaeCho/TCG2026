#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include "poppler-form.h"
#include "CryptoSignBackend.h"

// Test fixture for Poppler::convertToBackend function
class ConvertToBackendTest_1373 : public ::testing::Test {
protected:
    // You can set up common test resources here if needed
    void SetUp() override {}
    void TearDown() override {}
};

// Test case: Normal operation - convert to NSS3 backend
TEST_F(ConvertToBackendTest_1373, ConvertToNSS3Backend_1373) {
    std::optional<Poppler::CryptoSignBackend> inputBackend = Poppler::CryptoSignBackend::NSS;
    std::optional<CryptoSign::Backend::Type> result = Poppler::convertToBackend(inputBackend);

    // Verify that the result matches NSS3 backend
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), CryptoSign::Backend::Type::NSS3);
}

// Test case: Normal operation - convert to GPGME backend
TEST_F(ConvertToBackendTest_1373, ConvertToGPGMEBackend_1373) {
    std::optional<Poppler::CryptoSignBackend> inputBackend = Poppler::CryptoSignBackend::GPG;
    std::optional<CryptoSign::Backend::Type> result = Poppler::convertToBackend(inputBackend);

    // Verify that the result matches GPGME backend
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), CryptoSign::Backend::Type::GPGME);
}

// Test case: Boundary condition - empty input, should return std::nullopt
TEST_F(ConvertToBackendTest_1373, ConvertToNullOptWhenEmptyInput_1373) {
    std::optional<Poppler::CryptoSignBackend> inputBackend = std::nullopt;
    std::optional<CryptoSign::Backend::Type> result = Poppler::convertToBackend(inputBackend);

    // Verify that the result is std::nullopt
    ASSERT_FALSE(result.has_value());
}

// Test case: Boundary condition - unrecognized backend value, should return std::nullopt
TEST_F(ConvertToBackendTest_1373, ConvertToNullOptWhenUnrecognizedInput_1373) {
    // Creating a backend value that does not exist in the enum
    std::optional<Poppler::CryptoSignBackend> inputBackend = static_cast<Poppler::CryptoSignBackend>(999); // Invalid value
    std::optional<CryptoSign::Backend::Type> result = Poppler::convertToBackend(inputBackend);

    // Verify that the result is std::nullopt
    ASSERT_FALSE(result.has_value());
}