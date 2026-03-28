// File: ./TestProjects/tinyxml2/tests/test_xmlutil_toint_172.cpp

#include <climits>
#include <gtest/gtest.h>

#include "tinyxml2.h"

using tinyxml2::XMLUtil;

namespace {

TEST(XMLUtilToIntTest_172, ParsesDecimalZero_172) {
    int v = 123;
    const bool ok = XMLUtil::ToInt("0", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, 0);
}

TEST(XMLUtilToIntTest_172, ParsesDecimalPositive_172) {
    int v = 0;
    const bool ok = XMLUtil::ToInt("42", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, 42);
}

TEST(XMLUtilToIntTest_172, ParsesDecimalNegative_172) {
    int v = 0;
    const bool ok = XMLUtil::ToInt("-17", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, -17);
}

TEST(XMLUtilToIntTest_172, ParsesDecimalIntMax_172) {
    int v = 0;
    const bool ok = XMLUtil::ToInt("2147483647", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, INT_MAX);
}

TEST(XMLUtilToIntTest_172, ParsesDecimalIntMin_172) {
    int v = 0;
    const bool ok = XMLUtil::ToInt("-2147483648", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, INT_MIN);
}

TEST(XMLUtilToIntTest_172, ParsesHexLowercase0x_172) {
    int v = 0;
    const bool ok = XMLUtil::ToInt("0x2A", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, 42);
}

TEST(XMLUtilToIntTest_172, ParsesHexUppercase0X_172) {
    int v = 0;
    const bool ok = XMLUtil::ToInt("0X2a", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, 42);
}

TEST(XMLUtilToIntTest_172, ParsesHexIntMax_172) {
    int v = 0;
    const bool ok = XMLUtil::ToInt("0x7fffffff", &v);
    EXPECT_TRUE(ok);
    EXPECT_EQ(v, INT_MAX);
}

TEST(XMLUtilToIntTest_172, ReturnsFalseOnNonNumericDecimalAndDoesNotModifyValue_172) {
    int v = 777;
    const bool ok = XMLUtil::ToInt("abc", &v);
    EXPECT_FALSE(ok);
    EXPECT_EQ(v, 777);
}

TEST(XMLUtilToIntTest_172, ReturnsFalseOnInvalidHexAndDoesNotModifyValue_172) {
    int v = -99;
    const bool ok = XMLUtil::ToInt("0xG", &v);
    EXPECT_FALSE(ok);
    EXPECT_EQ(v, -99);
}

TEST(XMLUtilToIntTest_172, ReturnsFalseOnEmptyStringAndDoesNotModifyValue_172) {
    int v = 5;
    const bool ok = XMLUtil::ToInt("", &v);
    EXPECT_FALSE(ok);
    EXPECT_EQ(v, 5);
}

TEST(XMLUtilToIntTest_172, ReturnsFalseOnHexWithMinusSignAndDoesNotModifyValue_172) {
    int v = 101;
    const bool ok = XMLUtil::ToInt("0x-1", &v);
    EXPECT_FALSE(ok);
    EXPECT_EQ(v, 101);
}

}  // namespace
