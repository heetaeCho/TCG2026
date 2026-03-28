// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::versionNumberHexString()
// File: ./TestProjects/exiv2/src/version.cpp
//
// Constraints respected:
// - Treat implementation as a black box (no internal logic assumptions beyond observable behavior).
// - Test only via the public interface.
// - No private state access.
// - Include normal, boundary-ish, and error/exception observability where possible.
//
// TEST_ID: 987
// *****************************************************************

#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <exiv2/version.hpp>  // Exiv2::versionNumber(), Exiv2::versionNumberHexString()

namespace {

bool IsLowerHex(char c) {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

}  // namespace

class VersionHexStringTest_987 : public ::testing::Test {};

TEST_F(VersionHexStringTest_987, ReturnsSixLowercaseHexDigits_987) {
  const std::string s = Exiv2::versionNumberHexString();

  // Observable formatting requirements implied by "{:06x}":
  // - width 6 with leading zeros
  // - lowercase hex digits
  ASSERT_EQ(s.size(), 6u) << "Expected a fixed-width 6-character hex string";
  EXPECT_TRUE(std::all_of(s.begin(), s.end(), IsLowerHex))
      << "Expected only lowercase hexadecimal characters [0-9a-f]";
}

TEST_F(VersionHexStringTest_987, IsDeterministicAcrossCalls_987) {
  const std::string a = Exiv2::versionNumberHexString();
  const std::string b = Exiv2::versionNumberHexString();
  const std::string c = Exiv2::versionNumberHexString();
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST_F(VersionHexStringTest_987, MatchesVersionNumberLower24BitsAsHex_987) {
  // We do NOT assume anything about how versionNumber() is formed, only that
  // versionNumberHexString() is a hex formatting of versionNumber() with width 6.
  const unsigned int v = Exiv2::versionNumber();
  const std::string s = Exiv2::versionNumberHexString();

  // Parse hex string as an integer; if formatting is correct, it should parse.
  unsigned long parsed = 0;
  ASSERT_NO_THROW({
    parsed = std::stoul(s, nullptr, 16);
  });

  // Since the string is width 6 hex digits, it can represent 0..0xFFFFFF.
  // If versionNumber() is larger, formatting will (by width=6) reflect the low 24 bits.
  const unsigned long expected = static_cast<unsigned long>(v) & 0xFFFFFFul;
  EXPECT_EQ(parsed, expected);
}

TEST_F(VersionHexStringTest_987, LeadingZerosAppearWhenValueIsSmall_987) {
  // Boundary-ish check without assuming an exact value:
  // if parsed value is less than 0x100000, the 6-wide formatting must include at least one leading '0'.
  const std::string s = Exiv2::versionNumberHexString();
  unsigned long parsed = 0;
  ASSERT_NO_THROW({ parsed = std::stoul(s, nullptr, 16); });

  if (parsed < 0x100000ul) {
    EXPECT_EQ(s.front(), '0') << "Expected at least one leading zero for values < 0x100000";
  } else {
    SUCCEED() << "Value is large enough that a leading zero is not required; check is not applicable.";
  }
}

TEST_F(VersionHexStringTest_987, DoesNotContainUppercaseHexLetters_987) {
  const std::string s = Exiv2::versionNumberHexString();
  const bool has_upper = std::any_of(s.begin(), s.end(), [](unsigned char ch) {
    return std::isalpha(ch) && std::isupper(ch);
  });
  EXPECT_FALSE(has_upper) << "Expected lowercase-only hex formatting";
}