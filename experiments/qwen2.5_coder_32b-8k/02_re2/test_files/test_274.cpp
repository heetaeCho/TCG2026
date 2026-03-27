#include <gtest/gtest.h>

#include <limits>



namespace re2 {

namespace re2_internal {



class ParseTest_274 : public ::testing::Test {

protected:

    double result;

};



TEST_F(ParseTest_274, ValidDoubleString_274) {

    const char* str = "123.456";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &result));

    EXPECT_DOUBLE_EQ(result, 123.456);

}



TEST_F(ParseTest_274, ValidIntegerString_274) {

    const char* str = "12345";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &result));

    EXPECT_DOUBLE_EQ(result, 12345.0);

}



TEST_F(ParseTest_274, LeadingWhitespaceString_274) {

    const char* str = "   123.456";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &result));

}



TEST_F(ParseTest_274, TrailingWhitespaceString_274) {

    const char* str = "123.456   ";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &result));

}



TEST_F(ParseTest_274, EmptyString_274) {

    const char* str = "";

    size_t n = 0;

    EXPECT_FALSE(Parse(str, n, &result));

}



TEST_F(ParseTest_274, NullTerminatedString_274) {

    const char* str = "123.456";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &result));

    EXPECT_DOUBLE_EQ(result, 123.456);

}



TEST_F(ParseTest_274, NonNumericString_274) {

    const char* str = "abc123";

    size_t n = strlen(str);

    EXPECT_FALSE(Parse(str, n, &result));

}



TEST_F(ParseTest_274, OverflowingNumber_274) {

    const char* str = "1e309"; // Larger than max double

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &result));

    EXPECT_EQ(result, std::numeric_limits<double>::infinity());

}



TEST_F(ParseTest_274, UnderflowingNumber_274) {

    const char* str = "1e-309"; // Smaller than min double

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, &result));

    EXPECT_EQ(result, 0.0);

}



TEST_F(ParseTest_274, NullDestinationPointer_274) {

    const char* str = "123.456";

    size_t n = strlen(str);

    EXPECT_TRUE(Parse(str, n, nullptr));

}



} // namespace re2_internal

} // namespace re2
