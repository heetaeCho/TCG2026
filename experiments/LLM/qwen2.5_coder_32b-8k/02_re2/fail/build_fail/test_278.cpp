#include <gtest/gtest.h>

#include <limits>



namespace re2 {

namespace re2_internal {



template <> bool Parse(const char* str, size_t n, unsigned short* dest, int radix);



}  // namespace re2_internal

}  // namespace re2



using ::re2::re2_internal::Parse;



class ParseTest_278 : public ::testing::Test {

protected:

    unsigned short result;

};



TEST_F(ParseTest_278, NormalOperationBase10_278) {

    const char* str = "1234";

    size_t n = 4;

    ASSERT_TRUE(Parse(str, n, &result, 10));

    EXPECT_EQ(result, 1234);

}



TEST_F(ParseTest_278, NormalOperationBase16_278) {

    const char* str = "ABC";

    size_t n = 3;

    ASSERT_TRUE(Parse(str, n, &result, 16));

    EXPECT_EQ(result, 0xabc);

}



TEST_F(ParseTest_278, ZeroValue_278) {

    const char* str = "0";

    size_t n = 1;

    ASSERT_TRUE(Parse(str, n, &result, 10));

    EXPECT_EQ(result, 0);

}



TEST_F(ParseTest_278, MaxValueBase10_278) {

    const char* str = "65535";

    size_t n = 5;

    ASSERT_TRUE(Parse(str, n, &result, 10));

    EXPECT_EQ(result, std::numeric_limits<unsigned short>::max());

}



TEST_F(ParseTest_278, MaxValueBase16_278) {

    const char* str = "FFFF";

    size_t n = 4;

    ASSERT_TRUE(Parse(str, n, &result, 16));

    EXPECT_EQ(result, std::numeric_limits<unsigned short>::max());

}



TEST_F(ParseTest_278, OutOfRangeBase10_278) {

    const char* str = "65536";

    size_t n = 5;

    ASSERT_FALSE(Parse(str, n, &result, 10));

}



TEST_F(ParseTest_278, OutOfRangeBase16_278) {

    const char* str = "10000";

    size_t n = 5;

    ASSERT_FALSE(Parse(str, n, &result, 16));

}



TEST_F(ParseTest_278, InvalidCharacter_278) {

    const char* str = "123G";

    size_t n = 4;

    ASSERT_FALSE(Parse(str, n, &result, 10));

}



TEST_F(ParseTest_278, NullDestinationPointer_278) {

    const char* str = "1234";

    size_t n = 4;

    EXPECT_TRUE(Parse(str, n, nullptr, 10));

}



TEST_F(ParseTest_278, EmptyString_278) {

    const char* str = "";

    size_t n = 0;

    ASSERT_FALSE(Parse(str, n, &result, 10));

}
