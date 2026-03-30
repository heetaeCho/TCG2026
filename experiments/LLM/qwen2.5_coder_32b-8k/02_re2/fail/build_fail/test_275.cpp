#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.cc"

#include <errno.h>



namespace re2 {

namespace re2_internal {



class ParseTest_275 : public ::testing::Test {

protected:

    long dest;

};



TEST_F(ParseTest_275, ValidInputBase10_275) {

    const char* str = "12345";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &dest, 10));

    EXPECT_EQ(dest, 12345L);

}



TEST_F(ParseTest_275, ValidInputBase16_275) {

    const char* str = "1A3F";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &dest, 16));

    EXPECT_EQ(dest, 0x1A3FL);

}



TEST_F(ParseTest_275, ValidInputBase8_275) {

    const char* str = "175";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &dest, 8));

    EXPECT_EQ(dest, 0175L);

}



TEST_F(ParseTest_275, LeadingZerosBase10_275) {

    const char* str = "000123";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &dest, 10));

    EXPECT_EQ(dest, 123L);

}



TEST_F(ParseTest_275, NullDestination_275) {

    const char* str = "12345";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, nullptr, 10));

}



TEST_F(ParseTest_275, EmptyString_275) {

    const char* str = "";

    size_t n = 0;

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_275, NonNumericInput_275) {

    const char* str = "abc";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_275, InputWithLeadingSpaces_275) {

    const char* str = " 123";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_275, InputWithTrailingJunk_275) {

    const char* str = "123abc";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_275, OutOfRangeInput_275) {

    const char* str = "9223372036854775808"; // Max long + 1

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_275, NegativeInputBase10_275) {

    const char* str = "-123";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest, 10)); // Assuming only non-negative numbers are allowed

}



} // namespace re2_internal

} // namespace re2
