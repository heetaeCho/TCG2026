#include <gtest/gtest.h>

#include <re2/re2_internal.h>



namespace re2 {

namespace re2_internal {



class ParseShortTest : public ::testing::Test {

protected:

    short result;

};



TEST_F(ParseShortTest_277, ValidParse_277) {

    const char* str = "123";

    size_t n = 3;

    EXPECT_TRUE(Parse(str, n, &result, 10));

    EXPECT_EQ(result, 123);

}



TEST_F(ParseShortTest_277, ParseZero_277) {

    const char* str = "0";

    size_t n = 1;

    EXPECT_TRUE(Parse(str, n, &result, 10));

    EXPECT_EQ(result, 0);

}



TEST_F(ParseShortTest_277, ParseNegative_277) {

    const char* str = "-123";

    size_t n = 4;

    EXPECT_TRUE(Parse(str, n, &result, 10));

    EXPECT_EQ(result, -123);

}



TEST_F(ParseShortTest_277, OutOfRangePositive_277) {

    const char* str = "32768";

    size_t n = 5;

    EXPECT_FALSE(Parse(str, n, &result, 10));

}



TEST_F(ParseShortTest_277, OutOfRangeNegative_277) {

    const char* str = "-32769";

    size_t n = 6;

    EXPECT_FALSE(Parse(str, n, &result, 10));

}



TEST_F(ParseShortTest_277, InvalidCharacter_277) {

    const char* str = "abc";

    size_t n = 3;

    EXPECT_FALSE(Parse(str, n, &result, 10));

}



TEST_F(ParseShortTest_277, NullDestination_277) {

    const char* str = "123";

    size_t n = 3;

    EXPECT_TRUE(Parse(str, n, nullptr, 10));

}



TEST_F(ParseShortTest_277, EmptyString_277) {

    const char* str = "";

    size_t n = 0;

    EXPECT_FALSE(Parse(str, n, &result, 10));

}



} // namespace re2_internal

} // namespace re2
