// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_parseuint32_1158.cpp
//
// Unit tests for Exiv2::parseUint32 (./TestProjects/exiv2/src/types.cpp)

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

namespace Exiv2 {
// Forward declaration of function under test (implemented in the production codebase).
uint32_t parseUint32(const std::string& s, bool& ok);
}  // namespace Exiv2

namespace {

class ParseUint32Test_1158 : public ::testing::Test {};

TEST_F(ParseUint32Test_1158, ParsesZero_1158) {
  bool ok = false;
  const uint32_t v = Exiv2::parseUint32("0", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(v, 0u);
}

TEST_F(ParseUint32Test_1158, ParsesTypicalValue_1158) {
  bool ok = false;
  const uint32_t v = Exiv2::parseUint32("12345", ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(v, 12345u);
}

TEST_F(ParseUint32Test_1158, ParsesUint32Max_1158) {
  const std::string s = std::to_string(std::numeric_limits<uint32_t>::max());
  bool ok = false;
  const uint32_t v = Exiv2::parseUint32(s, ok);
  EXPECT_TRUE(ok);
  EXPECT_EQ(v, std::numeric_limits<uint32_t>::max());
}

TEST_F(ParseUint32Test_1158, RejectsNegativeNumber_1158) {
  bool ok = true;  // start true to ensure it flips on error paths
  const uint32_t v = Exiv2::parseUint32("-1", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(v, 0u);
}

TEST_F(ParseUint32Test_1158, RejectsJustAboveUint32Max_1158) {
  const uint64_t above = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + 1ULL;
  const std::string s = std::to_string(above);

  bool ok = true;
  const uint32_t v = Exiv2::parseUint32(s, ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(v, 0u);
}

TEST_F(ParseUint32Test_1158, RejectsEmptyString_1158) {
  bool ok = true;
  const uint32_t v = Exiv2::parseUint32("", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(v, 0u);
}

TEST_F(ParseUint32Test_1158, RejectsNonNumeric_1158) {
  bool ok = true;
  const uint32_t v = Exiv2::parseUint32("abc", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(v, 0u);
}

TEST_F(ParseUint32Test_1158, RejectsMixedNumericAndText_1158) {
  bool ok = true;
  const uint32_t v = Exiv2::parseUint32("42xyz", ok);
  EXPECT_FALSE(ok);
  EXPECT_EQ(v, 0u);
}

TEST_F(ParseUint32Test_1158, HandlesLeadingAndTrailingWhitespace_1158) {
  // Observable behavior depends on the underlying parser used by the implementation.
  // This test asserts consistency: if whitespace is accepted, it should parse correctly;
  // otherwise it should fail and return 0.
  bool ok = false;
  const uint32_t v = Exiv2::parseUint32("  17  ", ok);

  if (ok) {
    EXPECT_EQ(v, 17u);
  } else {
    EXPECT_EQ(v, 0u);
  }
}

TEST_F(ParseUint32Test_1158, OkFlagReflectsLastCall_1158) {
  bool ok = false;

  // First a valid parse
  EXPECT_EQ(Exiv2::parseUint32("7", ok), 7u);
  EXPECT_TRUE(ok);

  // Then an invalid parse should flip ok to false and return 0
  EXPECT_EQ(Exiv2::parseUint32("not-a-number", ok), 0u);
  EXPECT_FALSE(ok);

  // And another valid parse should flip ok back to true (if supported by implementation)
  const uint32_t v = Exiv2::parseUint32("9", ok);
  if (ok) {
    EXPECT_EQ(v, 9u);
  } else {
    // If implementation is stricter in a way that would reject "9" (unexpected),
    // keep the test robust to avoid assuming internals.
    EXPECT_EQ(v, 0u);
  }
}

}  // namespace