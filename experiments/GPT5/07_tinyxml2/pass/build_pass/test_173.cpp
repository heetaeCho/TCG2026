// File: ./TestProjects/tinyxml2/tests/test_xmlutil_tounsigned_173.cpp

#include <gtest/gtest.h>

#include <climits>
#include <cstdint>

#include "tinyxml2.h"

using tinyxml2::XMLUtil;

class XMLUtilToUnsignedTest_173 : public ::testing::Test {
protected:
    XMLUtil util; // Call as member function (works whether it's static or non-static in the real build).
};

TEST_F(XMLUtilToUnsignedTest_173, ParsesDecimalNumber_173) {
    unsigned value = 0;
    const bool ok = util.ToUnsigned("42", &value);

    EXPECT_TRUE(ok);
    EXPECT_EQ(value, 42u);
}

TEST_F(XMLUtilToUnsignedTest_173, ParsesDecimalWithLeadingAndTrailingWhitespace_173) {
    unsigned value = 0;
    const bool ok = util.ToUnsigned("   7   ", &value);

    EXPECT_TRUE(ok);
    EXPECT_EQ(value, 7u);
}

TEST_F(XMLUtilToUnsignedTest_173, ParsesHexWith0xPrefix_173) {
    unsigned value = 0;
    const bool ok = util.ToUnsigned("0x10", &value);

    EXPECT_TRUE(ok);
    EXPECT_EQ(value, 16u);
}

TEST_F(XMLUtilToUnsignedTest_173, ParsesHexWith0XPrefix_173) {
    unsigned value = 0;
    const bool ok = util.ToUnsigned("0XFF", &value);

    EXPECT_TRUE(ok);
    EXPECT_EQ(value, 255u);
}

TEST_F(XMLUtilToUnsignedTest_173, AcceptsNegativeSignAndConvertsToUnsigned_173) {
    unsigned value = 0;
    const bool ok = util.ToUnsigned("-1", &value);

    EXPECT_TRUE(ok);
    EXPECT_EQ(value, static_cast<unsigned>(-1)); // well-defined modulo conversion
}

TEST_F(XMLUtilToUnsignedTest_173, AcceptsTrailingGarbageAfterNumber_173) {
    unsigned value = 0;
    const bool ok = util.ToUnsigned("123abc", &value);

    EXPECT_TRUE(ok);
    EXPECT_EQ(value, 123u);
}

TEST_F(XMLUtilToUnsignedTest_173, ReturnsFalseForEmptyStringAndDoesNotModifyValue_173) {
    unsigned value = 999u;
    const bool ok = util.ToUnsigned("", &value);

    EXPECT_FALSE(ok);
    EXPECT_EQ(value, 999u);
}

TEST_F(XMLUtilToUnsignedTest_173, ReturnsFalseForNonNumericStringAndDoesNotModifyValue_173) {
    unsigned value = 1234u;
    const bool ok = util.ToUnsigned("abc", &value);

    EXPECT_FALSE(ok);
    EXPECT_EQ(value, 1234u);
}

TEST_F(XMLUtilToUnsignedTest_173, ReturnsFalseForHexPrefixWithoutDigitsAndDoesNotModifyValue_173) {
    unsigned value = 77u;
    const bool ok = util.ToUnsigned("0x", &value);

    EXPECT_FALSE(ok);
    EXPECT_EQ(value, 77u);
}

TEST_F(XMLUtilToUnsignedTest_173, ParsesMaximumUnsignedDecimal_173) {
    unsigned value = 0;

    // Build UINT_MAX as a decimal string without assuming the bit width beyond what's in <climits>.
    const std::string maxStr = std::to_string(static_cast<unsigned long long>(UINT_MAX));
    const bool ok = util.ToUnsigned(maxStr.c_str(), &value);

    EXPECT_TRUE(ok);
    EXPECT_EQ(value, UINT_MAX);
}
