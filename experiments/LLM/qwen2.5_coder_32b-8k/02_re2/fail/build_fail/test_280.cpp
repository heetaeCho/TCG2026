#include <gtest/gtest.h>

#include <limits>



using namespace re2::re2_internal;



class ParseTest_280 : public ::testing::Test {

protected:

    unsigned int result;

};



TEST_F(ParseTest_280, ValidInputBase10_280) {

    const char* str = "42";

    EXPECT_TRUE(Parse(str, strlen(str), &result, 10));

    EXPECT_EQ(result, 42u);

}



TEST_F(ParseTest_280, ValidInputBase16_280) {

    const char* str = "2A";

    EXPECT_TRUE(Parse(str, strlen(str), &result, 16));

    EXPECT_EQ(result, 42u);

}



TEST_F(ParseTest_280, ZeroValue_280) {

    const char* str = "0";

    EXPECT_TRUE(Parse(str, strlen(str), &result, 10));

    EXPECT_EQ(result, 0u);

}



TEST_F(ParseTest_280, MaxUnsignedInt_280) {

    const char* str = "4294967295"; // UINT_MAX in base 10

    EXPECT_TRUE(Parse(str, strlen(str), &result, 10));

    EXPECT_EQ(result, std::numeric_limits<unsigned int>::max());

}



TEST_F(ParseTest_280, OutOfRangeUnsignedInt_280) {

    const char* str = "4294967296"; // UINT_MAX + 1 in base 10

    EXPECT_FALSE(Parse(str, strlen(str), &result, 10));

}



TEST_F(ParseTest_280, InvalidCharacter_280) {

    const char* str = "42a";

    EXPECT_FALSE(Parse(str, strlen(str), &result, 10));

}



TEST_F(ParseTest_280, EmptyString_280) {

    const char* str = "";

    EXPECT_FALSE(Parse(str, strlen(str), &result, 10));

}



TEST_F(ParseTest_280, NullDestination_280) {

    const char* str = "42";

    EXPECT_TRUE(Parse(str, strlen(str), nullptr, 10));

}
