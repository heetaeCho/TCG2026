#include <gtest/gtest.h>

#include <optional>

#include "poppler-form.h"

#include "CryptoSignBackend.h"



namespace Poppler {

    static std::optional<CryptoSignBackend> convertToFrontend(std::optional<CryptoSign::Backend::Type> type);

}



class ConvertToFrontendTest_1372 : public ::testing::Test {};



TEST_F(ConvertToFrontendTest_1372, NormalOperation_NSS3_1372) {

    auto result = Poppler::convertToFrontend(CryptoSign::Backend::Type::NSS3);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), Poppler::CryptoSignBackend::NSS);

}



TEST_F(ConvertToFrontendTest_1372, NormalOperation_GPGME_1372) {

    auto result = Poppler::convertToFrontend(CryptoSign::Backend::Type::GPGME);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), Poppler::CryptoSignBackend::GPG);

}



TEST_F(ConvertToFrontendTest_1372, BoundaryCondition_NoValue_1372) {

    auto result = Poppler::convertToFrontend(std::nullopt);

    EXPECT_FALSE(result.has_value());

}
