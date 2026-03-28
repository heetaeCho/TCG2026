#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include "./TestProjects/poppler/qt5/src/poppler-form.h"
#include "./TestProjects/poppler/poppler/CryptoSignBackend.h"

namespace Poppler {
    // Mock the dependencies if needed (for external collaborations)
    class MockCryptoSignBackend {
    public:
        MOCK_METHOD(CryptoSignBackend, convertToFrontend, (std::optional<CryptoSign::Backend::Type> type), ());
    };
}

TEST_F(CryptoSignBackendTest_1372, ConvertToFrontend_NSS3_1372) {
    std::optional<CryptoSign::Backend::Type> type = CryptoSign::Backend::Type::NSS3;
    
    std::optional<CryptoSignBackend> result = Poppler::convertToFrontend(type);

    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSignBackend::NSS);
}

TEST_F(CryptoSignBackendTest_1373, ConvertToFrontend_GPGME_1373) {
    std::optional<CryptoSign::Backend::Type> type = CryptoSign::Backend::Type::GPGME;
    
    std::optional<CryptoSignBackend> result = Poppler::convertToFrontend(type);

    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), CryptoSignBackend::GPG);
}

TEST_F(CryptoSignBackendTest_1374, ConvertToFrontend_Empty_1374) {
    std::optional<CryptoSign::Backend::Type> type = std::nullopt;
    
    std::optional<CryptoSignBackend> result = Poppler::convertToFrontend(type);

    EXPECT_FALSE(result.has_value());
}

TEST_F(CryptoSignBackendTest_1375, ConvertToFrontend_Invalid_1375) {
    std::optional<CryptoSign::Backend::Type> type = static_cast<CryptoSign::Backend::Type>(99);  // Invalid type
    
    std::optional<CryptoSignBackend> result = Poppler::convertToFrontend(type);

    EXPECT_FALSE(result.has_value());
}

TEST_F(CryptoSignBackendTest_1376, ConvertToFrontend_MultipleValidTypes_1376) {
    std::optional<CryptoSign::Backend::Type> type1 = CryptoSign::Backend::Type::NSS3;
    std::optional<CryptoSign::Backend::Type> type2 = CryptoSign::Backend::Type::GPGME;
    
    std::optional<CryptoSignBackend> result1 = Poppler::convertToFrontend(type1);
    std::optional<CryptoSignBackend> result2 = Poppler::convertToFrontend(type2);

    EXPECT_TRUE(result1.has_value());
    EXPECT_EQ(result1.value(), CryptoSignBackend::NSS);
    
    EXPECT_TRUE(result2.has_value());
    EXPECT_EQ(result2.value(), CryptoSignBackend::GPG);
}