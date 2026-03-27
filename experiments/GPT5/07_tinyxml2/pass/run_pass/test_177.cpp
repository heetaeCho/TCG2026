// TEST_ID: 177
//
// Unit tests for tinyxml2::XMLUtil::ToInt64
//
// Notes:
// - Treats implementation as a black box: verifies only observable behavior (return value + output).
// - Avoids undefined/unstable scenarios (e.g., null pointers, overflow inputs) that could crash or be platform-dependent.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "tinyxml2.h"

namespace {

class XMLUtilToInt64Test_177 : public ::testing::Test {
protected:
    tinyxml2::XMLUtil util;
};

TEST_F(XMLUtilToInt64Test_177, ParsesPositiveDecimal_177) {
    int64_t v = -1;
    const bool ok = util.ToInt64("12345", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(12345));
}

TEST_F(XMLUtilToInt64Test_177, ParsesNegativeDecimal_177) {
    int64_t v = 0;
    const bool ok = util.ToInt64("-9876", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(-9876));
}

TEST_F(XMLUtilToInt64Test_177, ParsesDecimalWithLeadingWhitespace_177) {
    int64_t v = 0;
    const bool ok = util.ToInt64("   42", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(42));
}

TEST_F(XMLUtilToInt64Test_177, ParsesDecimalWithTrailingWhitespace_177) {
    int64_t v = 0;
    const bool ok = util.ToInt64("42   ", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(42));
}

TEST_F(XMLUtilToInt64Test_177, ParsesZeroDecimal_177) {
    int64_t v = 123;
    const bool ok = util.ToInt64("0", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(0));
}

TEST_F(XMLUtilToInt64Test_177, ParsesInt64MaxDecimal_177) {
    const int64_t expected = std::numeric_limits<int64_t>::max();

    int64_t v = 0;
    const bool ok = util.ToInt64("9223372036854775807", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, expected);
}

TEST_F(XMLUtilToInt64Test_177, ParsesInt64MinDecimal_177) {
    const int64_t expected = std::numeric_limits<int64_t>::min();

    int64_t v = 0;
    const bool ok = util.ToInt64("-9223372036854775808", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, expected);
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexWith0xPrefixLowercase_177) {
    int64_t v = 0;
    const bool ok = util.ToInt64("0x1a", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(26));
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexWith0xPrefixUppercaseX_177) {
    int64_t v = 0;
    const bool ok = util.ToInt64("0X1A", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(26));
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexZero_177) {
    int64_t v = 123;
    const bool ok = util.ToInt64("0x0", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, static_cast<int64_t>(0));
}

TEST_F(XMLUtilToInt64Test_177, ParsesHexThatFitsInInt64_177) {
    // 0x7FFFFFFFFFFFFFFF == int64 max
    int64_t v = 0;
    const bool ok = util.ToInt64("0x7FFFFFFFFFFFFFFF", &v);

    EXPECT_TRUE(ok);
    EXPECT_EQ(v, std::numeric_limits<int64_t>::max());
}

TEST_F(XMLUtilToInt64Test_177, ReturnsFalseForEmptyString_177) {
    int64_t v = 777;
    const bool ok = util.ToInt64("", &v);

    EXPECT_FALSE(ok);
    // v is unspecified on failure; we only assert it didn't spuriously succeed.
}

TEST_F(XMLUtilToInt64Test_177, ReturnsFalseForNonNumeric_177) {
    int64_t v = 777;
    const bool ok = util.ToInt64("not-a-number", &v);

    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilToInt64Test_177, ReturnsFalseForHexPrefixWithoutDigits_177) {
    int64_t v = 777;
    const bool ok = util.ToInt64("0x", &v);

    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilToInt64Test_177, ReturnsFalseForSignOnly_177) {
    int64_t v = 777;
    const bool ok = util.ToInt64("-", &v);

    EXPECT_FALSE(ok);
}

}  // namespace
