#include <gtest/gtest.h>

#include "re2/util/pcre.h"



using namespace re2;



class PCREArgTest_184 : public ::testing::Test {

protected:

    PCRE::Arg arg;

};



TEST_F(PCREArgTest_184, ParseNullString_184) {

    EXPECT_TRUE(arg.Parse("", 0));

}



TEST_F(PCREArgTest_184, ParseValidInteger_184) {

    int value = 0;

    PCRE::Arg arg_int(&value);

    EXPECT_TRUE(arg_int.Parse("123", 3));

    EXPECT_EQ(value, 123);

}



TEST_F(PCREArgTest_184, ParseInvalidInteger_184) {

    int value = 0;

    PCRE::Arg arg_int(&value);

    EXPECT_FALSE(arg_int.Parse("abc", 3));

    EXPECT_EQ(value, 0); // Value should remain unchanged on failure

}



TEST_F(PCREArgTest_184, ParseValidFloat_184) {

    float value = 0.0f;

    PCRE::Arg arg_float(&value);

    EXPECT_TRUE(arg_float.Parse("123.456", 7));

    EXPECT_FLOAT_EQ(value, 123.456f);

}



TEST_F(PCREArgTest_184, ParseInvalidFloat_184) {

    float value = 0.0f;

    PCRE::Arg arg_float(&value);

    EXPECT_FALSE(arg_float.Parse("abc", 3));

    EXPECT_FLOAT_EQ(value, 0.0f); // Value should remain unchanged on failure

}



TEST_F(PCREArgTest_184, ParseValidString_184) {

    std::string value;

    PCRE::Arg arg_string(&value);

    EXPECT_TRUE(arg_string.Parse("hello", 5));

    EXPECT_EQ(value, "hello");

}



TEST_F(PCREArgTest_184, ParseEmptyString_184) {

    std::string value;

    PCRE::Arg arg_string(&value);

    EXPECT_TRUE(arg_string.Parse("", 0));

    EXPECT_EQ(value, ""); // Empty string should be parsed successfully

}



TEST_F(PCREArgTest_184, ParseLongBoundary_184) {

    long value = 0;

    PCRE::Arg arg_long(&value);

    EXPECT_TRUE(arg_long.Parse("2147483647", 10));

    EXPECT_EQ(value, 2147483647L);



    EXPECT_FALSE(arg_long.Parse("2147483648", 10)); // Overflow

}



TEST_F(PCREArgTest_184, ParseULongBoundary_184) {

    unsigned long value = 0;

    PCRE::Arg arg_ulong(&value);

    EXPECT_TRUE(arg_ulong.Parse("4294967295", 10));

    EXPECT_EQ(value, 4294967295UL);



    EXPECT_FALSE(arg_ulong.Parse("4294967296", 10)); // Overflow

}



TEST_F(PCREArgTest_184, ParseShortBoundary_184) {

    short value = 0;

    PCRE::Arg arg_short(&value);

    EXPECT_TRUE(arg_short.Parse("32767", 5));

    EXPECT_EQ(value, 32767);



    EXPECT_FALSE(arg_short.Parse("32768", 5)); // Overflow

}



TEST_F(PCREArgTest_184, ParseUShortBoundary_184) {

    unsigned short value = 0;

    PCRE::Arg arg_ushort(&value);

    EXPECT_TRUE(arg_ushort.Parse("65535", 5));

    EXPECT_EQ(value, 65535);



    EXPECT_FALSE(arg_ushort.Parse("65536", 5)); // Overflow

}



TEST_F(PCREArgTest_184, ParseIntBoundary_184) {

    int value = 0;

    PCRE::Arg arg_int(&value);

    EXPECT_TRUE(arg_int.Parse("2147483647", 10));

    EXPECT_EQ(value, 2147483647);



    EXPECT_FALSE(arg_int.Parse("2147483648", 10)); // Overflow

}



TEST_F(PCREArgTest_184, ParseUIntBoundary_184) {

    unsigned int value = 0;

    PCRE::Arg arg_uint(&value);

    EXPECT_TRUE(arg_uint.Parse("4294967295", 10));

    EXPECT_EQ(value, 4294967295U);



    EXPECT_FALSE(arg_uint.Parse("4294967296", 10)); // Overflow

}



TEST_F(PCREArgTest_184, ParseLongLongBoundary_184) {

    long long value = 0;

    PCRE::Arg arg_longlong(&value);

    EXPECT_TRUE(arg_longlong.Parse("9223372036854775807", 19));

    EXPECT_EQ(value, 9223372036854775807LL);



    EXPECT_FALSE(arg_longlong.Parse("9223372036854775808", 19)); // Overflow

}



TEST_F(PCREArgTest_184, ParseULongLongBoundary_184) {

    unsigned long long value = 0;

    PCRE::Arg arg_ulonglong(&value);

    EXPECT_TRUE(arg_ulonglong.Parse("18446744073709551615", 20));

    EXPECT_EQ(value, 18446744073709551615ULL);



    EXPECT_FALSE(arg_ulonglong.Parse("18446744073709551616", 20)); // Overflow

}
