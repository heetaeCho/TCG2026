#include <gtest/gtest.h>

#include "CryptoSignBackend.h"



using namespace CryptoSign;



// Test suite for Factory::typeFromString(std::string_view string)

class FactoryTypeFromStringTest_1960 : public ::testing::Test {

protected:

    // No setup or teardown required for this simple function.

};



TEST_F(FactoryTypeFromStringTest_1960, EmptyStringReturnsNullopt_1960) {

    std::string_view input = "";

    auto result = Factory::typeFromString(input);

    EXPECT_FALSE(result.has_value());

}



TEST_F(FactoryTypeFromStringTest_1960, GPGStringReturnsGPGME_1960) {

    std::string_view input = "GPG";

    auto result = Factory::typeFromString(input);

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, Backend::Type::GPGME);

}



TEST_F(FactoryTypeFromStringTest_1960, NSSStringReturnsNSS3_1960) {

    std::string_view input = "NSS";

    auto result = Factory::typeFromString(input);

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, Backend::Type::NSS3);

}



TEST_F(FactoryTypeFromStringTest_1960, InvalidStringReturnsNullopt_1960) {

    std::string_view input = "INVALID";

    auto result = Factory::typeFromString(input);

    EXPECT_FALSE(result.has_value());

}
