#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include <limits.h>



using namespace re2;

using namespace re2_internal;



class ParseTest_276 : public ::testing::Test {

protected:

    unsigned long dest;

};



TEST_F(ParseTest_276, ValidNumberParsing_276) {

    const char* str = "12345";

    size_t n = 5;

    EXPECT_TRUE(Parse(str, n, &dest, 10));

    EXPECT_EQ(dest, 12345ul);

}



TEST_F(ParseTest_276, ZeroLengthString_276) {

    const char* str = "";

    size_t n = 0;

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_276, NegativeNumberParsing_276) {

    const char* str = "-12345";

    size_t n = 6;

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_276, NonNumericString_276) {

    const char* str = "abcde";

    size_t n = 5;

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_276, NumberWithJunkAtEnd_276) {

    const char* str = "12345abc";

    size_t n = 8;

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_276, NullDestinationPointer_276) {

    const char* str = "12345";

    size_t n = 5;

    EXPECT_TRUE(Parse(str, n, nullptr, 10));

}



TEST_F(ParseTest_276, LargeNumberWithinRange_276) {

    const char* str = "4294967295"; // max unsigned long on 32-bit system

    size_t n = 10;

    EXPECT_TRUE(Parse(str, n, &dest, 10));

    EXPECT_EQ(dest, 4294967295ul);

}



TEST_F(ParseTest_276, NumberExceedingULongMax_276) {

    const char* str = "4294967296"; // one more than max unsigned long on 32-bit system

    size_t n = 10;

    EXPECT_FALSE(Parse(str, n, &dest, 10));

}



TEST_F(ParseTest_276, NumberWithLeadingZeros_276) {

    const char* str = "00012345";

    size_t n = 8;

    EXPECT_TRUE(Parse(str, n, &dest, 10));

    EXPECT_EQ(dest, 12345ul);

}



TEST_F(ParseTest_276, HexadecimalParsing_276) {

    const char* str = "1A";

    size_t n = 2;

    EXPECT_TRUE(Parse(str, n, &dest, 16));

    EXPECT_EQ(dest, 26ul);

}



TEST_F(ParseTest_276, OctalParsing_276) {

    const char* str = "175";

    size_t n = 3;

    EXPECT_TRUE(Parse(str, n, &dest, 8));

    EXPECT_EQ(dest, 125ul);

}
