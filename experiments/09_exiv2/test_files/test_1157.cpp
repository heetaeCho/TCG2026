#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include "types.cpp"



using namespace Exiv2;



TEST(parseInt64Test_1157, ValidInt64String_ReturnsCorrectValue_1157) {

    bool ok = false;

    int64_t result = parseInt64("12345", ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 12345);

}



TEST(parseInt64Test_1157, ValidFloatString_ReturnsCorrectValue_1157) {

    bool ok = false;

    int64_t result = parseInt64("123.45", ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 123); // static_cast<int64_t>(123.45f)

}



TEST(parseInt64Test_1157, ValidRationalString_ReturnsCorrectValue_1157) {

    bool ok = false;

    int64_t result = parseInt64("123/4", ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 30); // static_cast<int64_t>(123.0f / 4)

}



TEST(parseInt64Test_1157, ValidBoolString_ReturnsCorrectValue_1157) {

    bool ok = false;

    int64_t resultTrue = parseInt64("true", ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(resultTrue, 1);



    ok = false;

    int64_t resultFalse = parseInt64("false", ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(resultFalse, 0);

}



TEST(parseInt64Test_1157, InvalidString_ReturnsZeroAndOkFalse_1157) {

    bool ok = false;

    int64_t result = parseInt64("invalid", ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0);

}



TEST(parseInt64Test_1157, RationalWithZeroDenominator_ReturnsZeroAndOkFalse_1157) {

    bool ok = false;

    int64_t result = parseInt64("123/0", ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0);

}



TEST(parseInt64Test_1157, EmptyString_ReturnsZeroAndOkFalse_1157) {

    bool ok = false;

    int64_t result = parseInt64("", ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0);

}
