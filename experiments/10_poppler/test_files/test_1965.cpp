#include <gtest/gtest.h>

#include "CryptoSignBackend.h"

#include <optional>

#include <vector>



using namespace CryptoSign;



class FactoryTest_1965 : public ::testing::Test {

protected:

    FactoryTest_1965() {}

};



TEST_F(FactoryTest_1965, CreateActiveReturnsNullptrWhenNoPreferredBackendSet_1965) {

    EXPECT_EQ(nullptr, Factory::createActive());

}



TEST_F(FactoryTest_1965, SetPreferredBackendAndGetActiveConsistent_1965) {

    Factory::setPreferredBackend(Backend::Type::NSS3);

    auto activeBackend = Factory::getActive();

    ASSERT_TRUE(activeBackend.has_value());

    EXPECT_EQ(Backend::Type::NSS3, activeBackend.value());



    Factory::setPreferredBackend(Backend::Type::GPGME);

    activeBackend = Factory::getActive();

    ASSERT_TRUE(activeBackend.has_value());

    EXPECT_EQ(Backend::Type::GPGME, activeBackend.value());

}



TEST_F(FactoryTest_1965, TypeFromStringReturnsCorrectEnumValues_1965) {

    auto typeFromStr = Factory::typeFromString("NSS3");

    ASSERT_TRUE(typeFromStr.has_value());

    EXPECT_EQ(Backend::Type::NSS3, typeFromStr.value());



    typeFromStr = Factory::typeFromString("GPGME");

    ASSERT_TRUE(typeFromStr.has_value());

    EXPECT_EQ(Backend::Type::GPGME, typeFromStr.value());

}



TEST_F(FactoryTest_1965, TypeFromStringReturnsNulloptForUnknownString_1965) {

    auto typeFromStr = Factory::typeFromString("UNKNOWN");

    EXPECT_FALSE(typeFromStr.has_value());



    typeFromStr = Factory::typeFromString("");

    EXPECT_FALSE(typeFromStr.has_value());

}



TEST_F(FactoryTest_1965, CreateWithValidTypeReturnsNonNullPtr_1965) {

    auto backendNSS3 = Factory::create(Backend::Type::NSS3);

#if ENABLE_NSS3

    ASSERT_NE(nullptr, backendNSS3.get());

#else

    EXPECT_EQ(nullptr, backendNSS3.get());

#endif



    auto backendGPGME = Factory::create(Backend::Type::GPGME);

#if ENABLE_GPGME

    ASSERT_NE(nullptr, backendGPGME.get());

#else

    EXPECT_EQ(nullptr, backendGPGME.get());

#endif

}



TEST_F(FactoryTest_1965, CreateWithInvalidTypeReturnsNullptr_1965) {

    Backend::Type invalidType = static_cast<Backend::Type>(-1);

    auto backend = Factory::create(invalidType);

    EXPECT_EQ(nullptr, backend.get());

}
