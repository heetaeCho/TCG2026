#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {

namespace re2_internal {



class ParseTest_279 : public ::testing::Test {};



TEST_F(ParseTest_279, ValidParse_279) {

    int result;

    EXPECT_TRUE(Parse("123", 3, &result, 10));

    EXPECT_EQ(result, 123);

}



TEST_F(ParseTest_279, NullDestination_279) {

    EXPECT_TRUE(Parse("123", 3, nullptr, 10));

}



TEST_F(ParseTest_279, OutOfRange_279) {

    int result;

    EXPECT_FALSE(Parse("2147483648", 10, &result, 10)); // 2^31 which is out of range for signed int

}



TEST_F(ParseTest_279, NegativeNumber_279) {

    int result;

    EXPECT_TRUE(Parse("-123", 4, &result, 10));

    EXPECT_EQ(result, -123);

}



TEST_F(ParseTest_279, InvalidCharacter_279) {

    int result;

    EXPECT_FALSE(Parse("123a", 4, &result, 10));

}



TEST_F(ParseTest_279, LeadingZero_279) {

    int result;

    EXPECT_TRUE(Parse("0123", 4, &result, 10));

    EXPECT_EQ(result, 123);

}



TEST_F(ParseTest_279, HexadecimalParse_279) {

    int result;

    EXPECT_TRUE(Parse("1a", 2, &result, 16));

    EXPECT_EQ(result, 26);

}



TEST_F(ParseTest_279, OctalParse_279) {

    int result;

    EXPECT_TRUE(Parse("17", 2, &result, 8));

    EXPECT_EQ(result, 15);

}



TEST_F(ParseTest_279, EmptyString_279) {

    int result;

    EXPECT_FALSE(Parse("", 0, &result, 10));

}



TEST_F(ParseTest_279, LargeValidNumber_279) {

    int result;

    EXPECT_TRUE(Parse("2147483647", 10, &result, 10)); // 2^31 - 1 which is max for signed int

    EXPECT_EQ(result, 2147483647);

}



} // namespace re2_internal

} // namespace re2
