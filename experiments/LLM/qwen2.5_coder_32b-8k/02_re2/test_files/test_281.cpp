#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.cc" // Assuming the header or inline file inclusion for re2::Parse



namespace {



using namespace re2;

using namespace re2_internal;



class ParseTest_281 : public ::testing::Test {

protected:

    long long dest;

};



TEST_F(ParseTest_281, ValidNumber_281) {

    const char* str = "12345";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &dest, 10));

    EXPECT_EQ(dest, 12345);

}



TEST_F(ParseTest_281, ValidNumberWithRadix_281) {

    const char* str = "1A";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &dest, 16));

    EXPECT_EQ(dest, 26);

}



TEST_F(ParseTest_281, EmptyString_281) {

    const char* str = "";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_281, NullDestination_281) {

    const char* str = "12345";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, nullptr, 10));

}



TEST_F(ParseTest_281, InvalidNumber_281) {

    const char* str = "123abc";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_281, LeadingWhitespace_281) {

    const char* str = " 12345";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10)); // Assuming no leading whitespace is allowed

}



TEST_F(ParseTest_281, TrailingWhitespace_281) {

    const char* str = "12345 ";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10)); // Assuming no trailing whitespace is allowed

}



TEST_F(ParseTest_281, NumberTooLong_281) {

    std::string long_str(kMaxNumberLength + 1, '9');

    size_t n = long_str.size();

    EXPECT_FALSE(Parse(long_str.c_str(), n, &dest, 10));

}



TEST_F(ParseTest_281, NegativeNumber_281) {

    const char* str = "-12345";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &dest, 10));

    EXPECT_EQ(dest, -12345);

}



TEST_F(ParseTest_281, OverflowNumber_281) {

    std::string max_str("9223372036854775807"); // LLONG_MAX

    size_t n = max_str.size();

    EXPECT_TRUE(Parse(max_str.c_str(), n, &dest, 10));

    EXPECT_EQ(dest, LLONG_MAX);



    std::string overflow_str("9223372036854775808");

    n = overflow_str.size();

    EXPECT_FALSE(Parse(overflow_str.c_str(), n, &dest, 10)); // Overflow case

}



TEST_F(ParseTest_281, UnderflowNumber_281) {

    std::string min_str("-9223372036854775808"); // LLONG_MIN

    size_t n = min_str.size();

    EXPECT_TRUE(Parse(min_str.c_str(), n, &dest, 10));

    EXPECT_EQ(dest, LLONG_MIN);



    std::string underflow_str("-9223372036854775809");

    n = underflow_str.size();

    EXPECT_FALSE(Parse(underflow_str.c_str(), n, &dest, 10)); // Underflow case

}



} // namespace
