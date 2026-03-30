// TEST_ID: 178
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "tinyxml2.h"

using tinyxml2::XMLUtil;

namespace {

TEST(XMLUtilToUnsigned64Test_178, ParsesZeroDecimal_178)
{
    uint64_t value = 123u;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0", &value));
    EXPECT_EQ(0u, value);
}

TEST(XMLUtilToUnsigned64Test_178, ParsesDecimalWithLeadingWhitespace_178)
{
    uint64_t value = 0u;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("   42", &value));
    EXPECT_EQ(42u, value);
}

TEST(XMLUtilToUnsigned64Test_178, ParsesDecimalWithLeadingZeros_178)
{
    uint64_t value = 0u;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("00000123", &value));
    EXPECT_EQ(123u, value);
}

TEST(XMLUtilToUnsigned64Test_178, ParsesMaxUint64Decimal_178)
{
    const uint64_t kMax = std::numeric_limits<uint64_t>::max();
    uint64_t value = 0u;

    // 18446744073709551615 == UINT64_MAX
    EXPECT_TRUE(XMLUtil::ToUnsigned64("18446744073709551615", &value));
    EXPECT_EQ(kMax, value);
}

TEST(XMLUtilToUnsigned64Test_178, ParsesHexWith0xPrefixLowercase_178)
{
    uint64_t value = 0u;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0x10", &value));
    EXPECT_EQ(16u, value);
}

TEST(XMLUtilToUnsigned64Test_178, ParsesHexWith0XPrefixUppercase_178)
{
    uint64_t value = 0u;
    EXPECT_TRUE(XMLUtil::ToUnsigned64("0XfF", &value));
    EXPECT_EQ(255u, value);
}

TEST(XMLUtilToUnsigned64Test_178, RejectsEmptyString_178)
{
    uint64_t value = 777u;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("", &value));
}

TEST(XMLUtilToUnsigned64Test_178, RejectsNonNumeric_178)
{
    uint64_t value = 777u;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("not_a_number", &value));
}

TEST(XMLUtilToUnsigned64Test_178, RejectsHexPrefixWithoutDigits_178)
{
    uint64_t value = 777u;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("0x", &value));
    EXPECT_FALSE(XMLUtil::ToUnsigned64("0X", &value));
}

TEST(XMLUtilToUnsigned64Test_178, RejectsOnlyWhitespace_178)
{
    uint64_t value = 777u;
    EXPECT_FALSE(XMLUtil::ToUnsigned64("   \t\r\n", &value));
}

}  // namespace
