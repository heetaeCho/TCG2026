#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CryptoSignBackend.h"



using namespace CryptoSign;

using ::testing::_;

using ::testing::Return;



class CryptoSignFactoryTest : public ::testing::Test {

protected:

    static std::vector<Backend::Type> availableBackends;

};



std::vector<Backend::Type> CryptoSignFactoryTest::availableBackends = {Backend::Type::OpenSSL, Backend::Type::GnuTLS};



TEST_F(CryptoSignFactoryTest_1958, SetPreferredBackend_NormalOperation_1958) {

    Factory::setPreferredBackend(Backend::Type::OpenSSL);

    // No observable behavior to verify directly, but we can check getActive if it matches

    EXPECT_TRUE(Factory::getActive().has_value() && Factory::getActive().value() == Backend::Type::OpenSSL);

}



TEST_F(CryptoSignFactoryTest_1958, GetActive_ReturnsPreferredBackend_1958) {

    Factory::setPreferredBackend(Backend::Type::GnuTLS);

    EXPECT_TRUE(Factory::getActive().has_value() && Factory::getActive().value() == Backend::Type::GnuTLS);

}



TEST_F(CryptoSignFactoryTest_1958, GetAvailable_ReturnsNonEmptyList_1958) {

    auto available = Factory::getAvailable();

    EXPECT_FALSE(available.empty());

    for (const auto& backend : available) {

        EXPECT_NE(std::find(availableBackends.begin(), availableBackends.end(), backend), availableBackends.end());

    }

}



TEST_F(CryptoSignFactoryTest_1958, CreateActive_ReturnsNonNullPointer_1958) {

    Factory::setPreferredBackend(Backend::Type::OpenSSL);

    auto backend = Factory::createActive();

    EXPECT_NE(backend.get(), nullptr);

}



TEST_F(CryptoSignFactoryTest_1958, Create_SpecifiedBackend_ReturnsNonNullPointer_1958) {

    auto backend = Factory::create(Backend::Type::GnuTLS);

    EXPECT_NE(backend.get(), nullptr);

}



TEST_F(CryptoSignFactoryTest_1958, TypeFromString_ValidString_ReturnsValidType_1958) {

    std::string_view validString = "OpenSSL";

    auto backendType = Factory::typeFromString(validString);

    EXPECT_TRUE(backendType.has_value() && backendType.value() == Backend::Type::OpenSSL);

}



TEST_F(CryptoSignFactoryTest_1958, TypeFromString_InvalidString_ReturnsEmptyOptional_1958) {

    std::string_view invalidString = "UnknownBackend";

    auto backendType = Factory::typeFromString(invalidString);

    EXPECT_FALSE(backendType.has_value());

}



TEST_F(CryptoSignFactoryTest_1958, TypeFromString_ValidInt_ReturnsValidType_1958) {

    int validInt = static_cast<int>(Backend::Type::GnuTLS);

    auto backendType = Factory::typeFromString(validInt);

    EXPECT_TRUE(backendType.has_value() && backendType.value() == Backend::Type::GnuTLS);

}



TEST_F(CryptoSignFactoryTest_1958, TypeFromString_InvalidInt_ReturnsEmptyOptional_1958) {

    int invalidInt = 999; // Assuming no backend has this value

    auto backendType = Factory::typeFromString(invalidInt);

    EXPECT_FALSE(backendType.has_value());

}
