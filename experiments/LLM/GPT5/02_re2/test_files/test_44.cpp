// File: re2_hex_arg_test_44.cc

#include "gtest/gtest.h"
#include "re2/re2.h"

#include <cstdint>
#include <string>

using re2::RE2;

class RE2HexTest_44 : public ::testing::Test {
protected:
  // Helper that runs a simple full match of one hex capture into T via Hex(T*).
  template <typename T>
  bool FullMatchHexInto(const std::string& s, T* out) {
    // The pattern captures one or more hex digits (no 0x prefix assumed).
    RE2 re("^([0-9A-Fa-f]+)$");
    return RE2::FullMatch(s, re, re.Hex(out));
  }
};

// Normal operation: lowercase hex parses into signed int.
TEST_F(RE2HexTest_44, ParsesLowercaseHex_44) {
  int v = -1;
  ASSERT_TRUE(FullMatchHexInto("7f", &v));
  EXPECT_EQ(v, 0x7f);
}

// Normal operation: uppercase hex parses into signed int.
TEST_F(RE2HexTest_44, ParsesUppercaseHex_44) {
  int v = -1;
  ASSERT_TRUE(FullMatchHexInto("2A", &v));
  EXPECT_EQ(v, 0x2A);
}

// Normal operation: mixed-case hex parses into signed int.
TEST_F(RE2HexTest_44, ParsesMixedCaseHex_44) {
  int v = -1;
  ASSERT_TRUE(FullMatchHexInto("AbCd", &v));
  EXPECT_EQ(v, 0xABCD);
}

// Normal operation: zero parses correctly for unsigned type.
TEST_F(RE2HexTest_44, ParsesZero_Unsigned32_44) {
  uint32_t v = 1234;  // initial value shouldn't matter; we only assert on success path.
  ASSERT_TRUE(FullMatchHexInto("0", &v));
  EXPECT_EQ(v, static_cast<uint32_t>(0));
}

// Boundary (large value that still fits in uint32_t): FFFFFFFF -> 4294967295.
TEST_F(RE2HexTest_44, ParsesMaxUint32_44) {
  uint32_t v = 0;
  ASSERT_TRUE(FullMatchHexInto("FFFFFFFF", &v));
  EXPECT_EQ(v, 0xFFFFFFFFu);
}

// Boundary (large value that fits in uint64_t): 7FFFFFFFFFFFFFFF.
TEST_F(RE2HexTest_44, ParsesLargeUint64_44) {
  uint64_t v = 0;
  ASSERT_TRUE(FullMatchHexInto("7FFFFFFFFFFFFFFF", &v));
  EXPECT_EQ(v, 0x7FFFFFFFFFFFFFFFull);
}

// Exceptional/error case: non-hex input fails the match/parse.
TEST_F(RE2HexTest_44, FailsOnNonHex_44) {
  int v = 0;
  EXPECT_FALSE(FullMatchHexInto("xyz", &v));  // Not hex digits; observable failure.
}

// Exceptional/error case: input with non-hex characters fails.
TEST_F(RE2HexTest_44, FailsOnMixedAlphaBeyondHex_44) {
  int v = 0;
  EXPECT_FALSE(FullMatchHexInto("12G4", &v));  // 'G' is not a hex digit; observable failure.
}

// Pattern mismatch case: string with 0x prefix is not captured by the chosen pattern.
TEST_F(RE2HexTest_44, PatternDoesNotAllow0xPrefix_44) {
  // This verifies behavior through the *pattern* (not the parser), ensuring we only
  // match hex digits as specified by the regex used by the test.
  int v = 0;
  EXPECT_FALSE(FullMatchHexInto("0x2A", &v));
}
