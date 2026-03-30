#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-form.cc"

#include "./TestProjects/poppler/qt5/src/poppler-form.h"



using namespace Poppler;



TEST(CryptoSignConversionTests_1373, ConvertToBackend_NSS_1373) {

    auto result = convertToBackend(std::optional<CryptoSignBackend>(CryptoSignBackend::NSS));

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::NSS3);

}



TEST(CryptoSignConversionTests_1373, ConvertToBackend_GPG_1373) {

    auto result = convertToBackend(std::optional<CryptoSignBackend>(CryptoSignBackend::GPG));

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), CryptoSign::Backend::Type::GPGME);

}



TEST(CryptoSignConversionTests_1373, ConvertToBackend_None_1373) {

    auto result = convertToBackend(std::nullopt);

    ASSERT_FALSE(result.has_value());

}
