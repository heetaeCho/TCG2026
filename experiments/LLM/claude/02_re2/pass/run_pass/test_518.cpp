#include "gtest/gtest.h"

// We need to access the UnHex function which is in the re2 namespace
// but declared static in parse.cc. Since it's static, we need to include
// the source file directly or find another way to test it.
// 
// Since UnHex is a static function in parse.cc, we cannot directly link to it
// from an external test file. However, we can test it through the public
// parsing interface of re2, or we include the .cc file directly.
// For the purpose of this test, we'll include the source to access the static function.

// We need the re2 headers and dependencies
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// Since UnHex is static in parse.cc, we test it indirectly through the
// regex parsing interface. Hex escapes in regex patterns (like \x41 for 'A')
// exercise the UnHex function.

class UnHexTest_518 : public ::testing::Test {
 protected:
};

// Test that hex escape sequences with digits 0-9 work correctly in regex parsing
TEST_F(UnHexTest_518, HexDigits0Through9_518) {
  // \x30 = '0', \x39 = '9'
  EXPECT_TRUE(RE2::FullMatch("0", "\\x30"));
  EXPECT_TRUE(RE2::FullMatch("9", "\\x39"));
  EXPECT_TRUE(RE2::FullMatch("5", "\\x35"));
}

// Test that hex escape sequences with uppercase A-F work correctly
TEST_F(UnHexTest_518, HexUppercaseAToF_518) {
  // \x41 = 'A', \x46 = 'F'
  EXPECT_TRUE(RE2::FullMatch("A", "\\x41"));
  EXPECT_TRUE(RE2::FullMatch("F", "\\x46"));
  EXPECT_TRUE(RE2::FullMatch("C", "\\x43"));
}

// Test that hex escape sequences with lowercase a-f work correctly
TEST_F(UnHexTest_518, HexLowercaseAToF_518) {
  // \x61 = 'a', \x66 = 'f'
  EXPECT_TRUE(RE2::FullMatch("a", "\\x61"));
  EXPECT_TRUE(RE2::FullMatch("f", "\\x66"));
  EXPECT_TRUE(RE2::FullMatch("d", "\\x64"));
}

// Test mixed case hex digits
TEST_F(UnHexTest_518, HexMixedCase_518) {
  // \x4A = 'J', \x4a = 'J' (both should work the same)
  EXPECT_TRUE(RE2::FullMatch("J", "\\x4A"));
  EXPECT_TRUE(RE2::FullMatch("J", "\\x4a"));
}

// Test hex value 0x00 (null byte boundary)
TEST_F(UnHexTest_518, HexBoundaryZero_518) {
  std::string null_str(1, '\x00');
  EXPECT_TRUE(RE2::FullMatch(null_str, "\\x00"));
}

// Test hex value 0xFF (maximum single byte)
TEST_F(UnHexTest_518, HexBoundaryFF_518) {
  // \xFF is max single byte hex
  std::string s(1, '\xFF');
  RE2 re("\\xff", RE2::Latin1);
  EXPECT_TRUE(RE2::FullMatch(s, re));
}

// Test hex escapes in character classes
TEST_F(UnHexTest_518, HexInCharacterClass_518) {
  EXPECT_TRUE(RE2::FullMatch("A", "[\\x41-\\x5A]"));   // A-Z
  EXPECT_TRUE(RE2::FullMatch("Z", "[\\x41-\\x5A]"));
  EXPECT_FALSE(RE2::FullMatch("a", "[\\x41-\\x5A]"));
}

// Test multi-digit hex with \x{...} syntax
TEST_F(UnHexTest_518, HexBraceNotation_518) {
  // \x{41} = 'A'
  EXPECT_TRUE(RE2::FullMatch("A", "\\x{41}"));
  EXPECT_TRUE(RE2::FullMatch("a", "\\x{61}"));
}

// Test Unicode code points via hex
TEST_F(UnHexTest_518, HexUnicodeCodePoints_518) {
  // \x{263A} = ☺ (white smiling face)
  EXPECT_TRUE(RE2::FullMatch("☺", "\\x{263A}"));
  EXPECT_TRUE(RE2::FullMatch("☺", "\\x{263a}"));
}

// Test that all individual hex digit values produce correct results
TEST_F(UnHexTest_518, AllHexDigitValues_518) {
  // Test each hex digit from 0-F by constructing patterns
  // \x30='0' through \x39='9'
  for (int i = 0; i <= 9; i++) {
    std::string ch(1, '0' + i);
    std::string pattern = "\\x3" + std::string(1, '0' + i);
    EXPECT_TRUE(RE2::FullMatch(ch, pattern)) << "Failed for digit " << i;
  }
}

// Test that invalid hex escape produces parse error
TEST_F(UnHexTest_518, InvalidHexEscape_518) {
  // \xGG is not a valid hex escape
  RE2 re("\\xGG");
  EXPECT_FALSE(re.ok());
}

// Test empty hex brace notation
TEST_F(UnHexTest_518, EmptyHexBraceNotation_518) {
  RE2 re("\\x{}");
  // Empty hex should be an error or match \0
  // The behavior depends on implementation
  if (re.ok()) {
    std::string null_str(1, '\x00');
    // Just verify it doesn't crash
    RE2::FullMatch(null_str, re);
  }
}

// Test that \x with exactly two hex digits works
TEST_F(UnHexTest_518, HexTwoDigitExact_518) {
  // \x20 = space
  EXPECT_TRUE(RE2::FullMatch(" ", "\\x20"));
  // \x7E = '~'
  EXPECT_TRUE(RE2::FullMatch("~", "\\x7E"));
  EXPECT_TRUE(RE2::FullMatch("~", "\\x7e"));
}

}  // namespace re2
