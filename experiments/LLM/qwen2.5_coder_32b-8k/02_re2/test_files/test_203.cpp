#include <gtest/gtest.h>

#include <cstring>

#include <errno.h>

#include "./TestProjects/re2/util/pcre.cc"



using namespace re2;



TEST(parse_double_float_Test_203, NormalOperationDouble_203) {

    const char* str = "123.456";

    size_t n = strlen(str);

    double result;

    bool success = parse_double_float(str, n, false, &result);

    EXPECT_TRUE(success);

    EXPECT_DOUBLE_EQ(result, 123.456);

}



TEST(parse_double_float_Test_203, NormalOperationFloat_203) {

    const char* str = "123.456";

    size_t n = strlen(str);

    float result;

    bool success = parse_double_float(str, n, true, &result);

    EXPECT_TRUE(success);

    EXPECT_FLOAT_EQ(result, 123.456f);

}



TEST(parse_double_float_Test_203, ZeroLengthString_203) {

    const char* str = "";

    size_t n = 0;

    double result;

    bool success = parse_double_float(str, n, false, &result);

    EXPECT_FALSE(success);

}



TEST(parse_double_float_Test_203, ExceedMaxLength_203) {

    const int kMaxLength = 201;

    char str[kMaxLength];

    memset(str, 'a', sizeof(str) - 1); // Fill with 'a's

    str[kMaxLength - 1] = '\0';

    size_t n = strlen(str);

    double result;

    bool success = parse_double_float(str, n, false, &result);

    EXPECT_FALSE(success);

}



TEST(parse_double_float_Test_203, NonNumericString_203) {

    const char* str = "abc";

    size_t n = strlen(str);

    double result;

    bool success = parse_double_float(str, n, false, &result);

    EXPECT_FALSE(success);

}



TEST(parse_double_float_Test_203, LeadingWhitespace_203) {

    const char* str = " 123.456";

    size_t n = strlen(str);

    double result;

    bool success = parse_double_float(str, n, false, &result);

    EXPECT_FALSE(success);

}



TEST(parse_double_float_Test_203, TrailingWhitespace_203) {

    const char* str = "123.456 ";

    size_t n = strlen(str);

    double result;

    bool success = parse_double_float(str, n, false, &result);

    EXPECT_FALSE(success);

}



TEST(parse_double_float_Test_203, NullDestination_203) {

    const char* str = "123.456";

    size_t n = strlen(str);

    bool success = parse_double_float(str, n, false, nullptr);

    EXPECT_TRUE(success);

}



TEST(parse_double_float_Test_203, InvalidNumber_203) {

    const char* str = "123abc";

    size_t n = strlen(str);

    double result;

    bool success = parse_double_float(str, n, false, &result);

    EXPECT_FALSE(success);

}
