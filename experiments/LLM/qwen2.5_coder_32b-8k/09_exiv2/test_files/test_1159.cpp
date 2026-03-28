#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/types.cpp"



namespace Exiv2 {

    // Mock class for any external collaborators if needed

}



using namespace Exiv2;



TEST(parseFloatTest_1159, ValidFloatString_1159) {

    bool ok;

    float result = parseFloat("3.14", ok);

    EXPECT_TRUE(ok);

    EXPECT_FLOAT_EQ(result, 3.14f);

}



TEST(parseFloatTest_1159, InvalidFloatStringValidRational_1159) {

    bool ok;

    float result = parseFloat("2/3", ok);

    EXPECT_TRUE(ok);

    EXPECT_FLOAT_EQ(result, static_cast<float>(2) / 3);

}



TEST(parseFloatTest_1159, RationalWithZeroDenominator_1159) {

    bool ok;

    float result = parseFloat("2/0", ok);

    EXPECT_FALSE(ok);

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST(parseFloatTest_1159, ValidBooleanStringTrue_1159) {

    bool ok;

    float result = parseFloat("true", ok);

    EXPECT_TRUE(ok);

    EXPECT_FLOAT_EQ(result, 1.0f);

}



TEST(parseFloatTest_1159, ValidBooleanStringFalse_1159) {

    bool ok;

    float result = parseFloat("false", ok);

    EXPECT_TRUE(ok);

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST(parseFloatTest_1159, InvalidString_1159) {

    bool ok;

    float result = parseFloat("invalid", ok);

    EXPECT_FALSE(ok);

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST(parseFloatTest_1159, EmptyString_1159) {

    bool ok;

    float result = parseFloat("", ok);

    EXPECT_FALSE(ok);

    EXPECT_FLOAT_EQ(result, 0.0f);

}
