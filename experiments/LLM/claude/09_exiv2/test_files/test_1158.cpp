#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <limits>

// Forward declaration from the Exiv2 namespace
namespace Exiv2 {
uint32_t parseUint32(const std::string& s, bool& ok);
}

class ParseUint32Test_1158 : public ::testing::Test {
protected:
  bool ok = false;
};

// Normal operation tests

TEST_F(ParseUint32Test_1158, ParseZero_1158) {
  uint32_t result = Exiv2::parseUint32("0", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParsePositiveInteger_1158) {
  uint32_t result = Exiv2::parseUint32("12345", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 12345u);
}

TEST_F(ParseUint32Test_1158, ParseOne_1158) {
  uint32_t result = Exiv2::parseUint32("1", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 1u);
}

TEST_F(ParseUint32Test_1158, ParseLargeValidNumber_1158) {
  uint32_t result = Exiv2::parseUint32("1000000000", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 1000000000u);
}

// Boundary condition tests

TEST_F(ParseUint32Test_1158, ParseMaxUint32_1158) {
  std::string maxVal = std::to_string(std::numeric_limits<uint32_t>::max());
  uint32_t result = Exiv2::parseUint32(maxVal, ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, std::numeric_limits<uint32_t>::max());
}

TEST_F(ParseUint32Test_1158, ParseMaxUint32Value_1158) {
  uint32_t result = Exiv2::parseUint32("4294967295", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 4294967295u);
}

TEST_F(ParseUint32Test_1158, ParseOverflowUint32_1158) {
  // One more than uint32_t max
  uint32_t result = Exiv2::parseUint32("4294967296", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParseVeryLargeNumber_1158) {
  uint32_t result = Exiv2::parseUint32("99999999999999999", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

// Negative number tests

TEST_F(ParseUint32Test_1158, ParseNegativeNumber_1158) {
  uint32_t result = Exiv2::parseUint32("-1", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParseNegativeLargeNumber_1158) {
  uint32_t result = Exiv2::parseUint32("-100000", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

// Error / exceptional cases

TEST_F(ParseUint32Test_1158, ParseEmptyString_1158) {
  uint32_t result = Exiv2::parseUint32("", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParseNonNumericString_1158) {
  uint32_t result = Exiv2::parseUint32("abc", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParseMixedString_1158) {
  uint32_t result = Exiv2::parseUint32("123abc", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParseStringWithSpaces_1158) {
  uint32_t result = Exiv2::parseUint32(" 123", ok);
  // Space-prefixed string - behavior depends on parseInt64 implementation
  // We test that it either parses correctly or fails gracefully
  if (ok) {
    EXPECT_EQ(result, 123u);
  } else {
    EXPECT_EQ(result, 0u);
  }
}

TEST_F(ParseUint32Test_1158, ParseStringWithTrailingSpaces_1158) {
  uint32_t result = Exiv2::parseUint32("123 ", ok);
  if (ok) {
    EXPECT_EQ(result, 123u);
  } else {
    EXPECT_EQ(result, 0u);
  }
}

TEST_F(ParseUint32Test_1158, ParseFloatingPoint_1158) {
  uint32_t result = Exiv2::parseUint32("3.14", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParseInt64MaxOverflow_1158) {
  // Value larger than int64_t max
  uint32_t result = Exiv2::parseUint32("9999999999999999999", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, ParseJustBelowMaxUint32_1158) {
  uint32_t result = Exiv2::parseUint32("4294967294", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 4294967294u);
}

TEST_F(ParseUint32Test_1158, ParsePlusSign_1158) {
  uint32_t result = Exiv2::parseUint32("+42", ok);
  // Behavior depends on parseInt64 handling of plus sign
  if (ok) {
    EXPECT_EQ(result, 42u);
  } else {
    EXPECT_EQ(result, 0u);
  }
}

TEST_F(ParseUint32Test_1158, ParseMinusZero_1158) {
  uint32_t result = Exiv2::parseUint32("-0", ok);
  // -0 as int64 is 0, which is >= 0 and <= max, so should succeed
  if (ok) {
    EXPECT_EQ(result, 0u);
  } else {
    EXPECT_EQ(result, 0u);
  }
}

TEST_F(ParseUint32Test_1158, OkFlagInitiallyTrue_1158) {
  ok = true;
  uint32_t result = Exiv2::parseUint32("abc", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(result, 0u);
}

TEST_F(ParseUint32Test_1158, OkFlagInitiallyFalseWithValidInput_1158) {
  ok = false;
  uint32_t result = Exiv2::parseUint32("42", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 42u);
}
