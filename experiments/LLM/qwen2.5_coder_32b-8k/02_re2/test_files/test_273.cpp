#include <gtest/gtest.h>

#include "re2/re2_internal.h"



using namespace re2::re2_internal;



class ParseFloatTest_273 : public ::testing::Test {

protected:

    float dest;

};



TEST_F(ParseFloatTest_273, ValidNumberParsesSuccessfully_273) {

    const char* str = "123.45";

    size_t n = strlen(str);

    ASSERT_TRUE(Parse(str, n, &dest));

    EXPECT_FLOAT_EQ(dest, 123.45f);

}



TEST_F(ParseFloatTest_273, LeadingSpacesIgnored_273) {

    const char* str = "   123.45";

    size_t n = strlen(str);

    ASSERT_TRUE(Parse(str, n, &dest));

    EXPECT_FLOAT_EQ(dest, 123.45f);

}



TEST_F(ParseFloatTest_273, TrailingSpacesIgnored_273) {

    const char* str = "123.45   ";

    size_t n = strlen(str);

    ASSERT_TRUE(Parse(str, n, &dest));

    EXPECT_FLOAT_EQ(dest, 123.45f);

}



TEST_F(ParseFloatTest_273, LeadingAndTrailingSpacesIgnored_273) {

    const char* str = "   123.45   ";

    size_t n = strlen(str);

    ASSERT_TRUE(Parse(str, n, &dest));

    EXPECT_FLOAT_EQ(dest, 123.45f);

}



TEST_F(ParseFloatTest_273, ZeroLengthStringFails_273) {

    const char* str = "";

    size_t n = 0;

    EXPECT_FALSE(Parse(str, n, &dest));

}



TEST_F(ParseFloatTest_273, NonNumericStringFails_273) {

    const char* str = "abc";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest));

}



TEST_F(ParseFloatTest_273, PartiallyNumericStringFails_273) {

    const char* str = "123abc";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest));

}



TEST_F(ParseFloatTest_273, VeryLongNumberFails_273) {

    std::string long_str(201, '9'); // 201 '9's

    const char* str = long_str.c_str();

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &dest));

}



TEST_F(ParseFloatTest_273, LargeNumberParsesSuccessfully_273) {

    const char* str = "1.8e308";

    size_t n = strlen(str);

    ASSERT_TRUE(Parse(str, n, &dest));

    EXPECT_FLOAT_EQ(dest, 1.8e308f);

}



TEST_F(ParseFloatTest_273, NullDestinationPointerAccepted_273) {

    const char* str = "123.45";

    size_t n = strlen(str);

    ASSERT_TRUE(Parse(str, n, nullptr));

}
