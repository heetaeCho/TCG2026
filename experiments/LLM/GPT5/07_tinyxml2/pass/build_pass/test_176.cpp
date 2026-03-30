// File: ./TestProjects/tinyxml2/test_XMLUtil_ToDouble_176.cpp

#include <gtest/gtest.h>
#include <cmath>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLUtilToDoubleTest_176 : public ::testing::Test {
protected:
    XMLUtil util; // Works whether ToDouble is static or non-static (static can be called on an instance too).
};

TEST_F(XMLUtilToDoubleTest_176, ParsesZero_176) {
    double v = 123.456;
    const bool ok = util.ToDouble("0", &v);

    ASSERT_TRUE(ok);
    EXPECT_DOUBLE_EQ(v, 0.0);
}

TEST_F(XMLUtilToDoubleTest_176, ParsesPositiveDecimal_176) {
    double v = 0.0;
    const bool ok = util.ToDouble("3.14159", &v);

    ASSERT_TRUE(ok);
    EXPECT_NEAR(v, 3.14159, 1e-12);
}

TEST_F(XMLUtilToDoubleTest_176, ParsesNegativeDecimal_176) {
    double v = 0.0;
    const bool ok = util.ToDouble("-2.5", &v);

    ASSERT_TRUE(ok);
    EXPECT_DOUBLE_EQ(v, -2.5);
}

TEST_F(XMLUtilToDoubleTest_176, ParsesScientificNotation_176) {
    double v = 0.0;
    const bool ok = util.ToDouble("1e3", &v);

    ASSERT_TRUE(ok);
    EXPECT_DOUBLE_EQ(v, 1000.0);
}

TEST_F(XMLUtilToDoubleTest_176, AcceptsLeadingWhitespace_176) {
    double v = 0.0;
    const bool ok = util.ToDouble("   42.0", &v);

    ASSERT_TRUE(ok);
    EXPECT_DOUBLE_EQ(v, 42.0);
}

TEST_F(XMLUtilToDoubleTest_176, ReturnsFalseForNonNumericString_176) {
    double v = 987.654;  // Do not assert whether it changes on failure (implementation-defined).
    const bool ok = util.ToDouble("not_a_number", &v);

    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilToDoubleTest_176, ReturnsFalseForEmptyString_176) {
    double v = 987.654;  // Do not assert whether it changes on failure (implementation-defined).
    const bool ok = util.ToDouble("", &v);

    EXPECT_FALSE(ok);
}
