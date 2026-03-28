// File: re2_partialmatch_test_8.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

using re2::RE2;

class RE2PartialMatchTest_8 : public ::testing::Test {};

// Normal operation: substring exists -> true
TEST_F(RE2PartialMatchTest_8, BasicSubstringMatchReturnsTrue_8) {
  RE2 re("(world)");
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
}

// Normal operation: substring absent -> false
TEST_F(RE2PartialMatchTest_8, NoMatchReturnsFalse_8) {
  RE2 re("xyz");
  EXPECT_FALSE(RE2::PartialMatch("hello world", re));
}

// Observable effect: capture into std::string
TEST_F(RE2PartialMatchTest_8, CapturesStringGroup_8) {
  RE2 re("(world)");
  std::string out;
  ASSERT_TRUE(RE2::PartialMatch("hello world!", re, &out));
  EXPECT_EQ(out, "world");
}

// Observable effect: capture a decimal integer
TEST_F(RE2PartialMatchTest_8, CapturesDecimalInteger_8) {
  RE2 re("x=(\\d+)");
  int value = -1;
  ASSERT_TRUE(RE2::PartialMatch("prefix x=42 suffix", re, &value));
  EXPECT_EQ(value, 42);
}

// Observable effect: capture a hex integer using Hex()
TEST_F(RE2PartialMatchTest_8, CapturesHexIntegerWithHexHelper_8) {
  RE2 re("0x([0-9a-fA-F]+)");
  int value = -1;
  ASSERT_TRUE(RE2::PartialMatch("color=0x1a;", re, RE2::Hex(&value)));
  EXPECT_EQ(value, 0x1a);
}

// Boundary: start anchor should respect beginning-of-text
TEST_F(RE2PartialMatchTest_8, StartAnchorOnlyMatchesAtBeginning_8) {
  RE2 re("^he");
  EXPECT_TRUE(RE2::PartialMatch("hello", re));   // begins with "he"
  EXPECT_FALSE(RE2::PartialMatch("say he", re)); // "he" not at start-of-text
}

// Boundary: empty pattern should succeed (empty regex matches empty string)
TEST_F(RE2PartialMatchTest_8, EmptyPatternMatches_8) {
  RE2 re("");
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
  EXPECT_TRUE(RE2::PartialMatch("", re));
}

// Boundary/robustness: capture present but non-matching overall -> false and no assumption on output
TEST_F(RE2PartialMatchTest_8, CaptureProvidedButNoOverallMatch_8) {
  RE2 re("(abc)");
  std::string out = "unchanged";
  EXPECT_FALSE(RE2::PartialMatch("zzz", re, &out));
  // We don't assert on 'out' here since behavior on failed match is not specified by interface.
}

// Normal operation: multiple captures
TEST_F(RE2PartialMatchTest_8, MultipleCaptures_8) {
  RE2 re("([a-z]+)-(\\d+)");
  std::string word;
  int num = -1;
  ASSERT_TRUE(RE2::PartialMatch("id abc-123 tail", re, &word, &num));
  EXPECT_EQ(word, "abc");
  EXPECT_EQ(num, 123);
}
