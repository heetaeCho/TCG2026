// File: re2_find_and_consume_test_10.cc
#include "re2/re2.h"
#include "gtest/gtest.h"
#include <string>

using re2::RE2;

// Fixture kept minimal; we test via public API only.
class FindAndConsumeTest_10 : public ::testing::Test {};

// [Normal] Finds match anywhere and advances past the match.
TEST_F(FindAndConsumeTest_10, FindsAnywhereAndAdvances_10) {
  RE2 re("(\\d+)");
  std::string s = "xx123yy";
  absl::string_view input(s);

  std::string captured;
  ASSERT_TRUE(RE2::FindAndConsume(&input, re, &captured));
  EXPECT_EQ(captured, "123");           // observed via capture
  EXPECT_EQ(input, "yy");               // input advanced past match (and prefix dropped)
}

// [Normal] Captures multiple groups into typed outputs.
TEST_F(FindAndConsumeTest_10, CapturesMultipleGroupsAndConverts_10) {
  RE2 re("([0-9]+)-([0-9]+)");
  std::string s = "foo 42-900 bar";
  absl::string_view input(s);

  int a = -1, b = -1;
  ASSERT_TRUE(RE2::FindAndConsume(&input, re, &a, &b));
  EXPECT_EQ(a, 42);
  EXPECT_EQ(b, 900);
  EXPECT_EQ(input, " bar");             // advanced to just after the match
}

// [Boundary] Beginning-anchor (^) applies to current input start.
TEST_F(FindAndConsumeTest_10, AnchorCaretMatchesAtCurrentStart_10) {
  RE2 re("^h");                          // must match at the beginning of *current* input
  std::string s = "hello";
  absl::string_view input(s);

  ASSERT_TRUE(RE2::FindAndConsume(&input, re));
  EXPECT_EQ(input, "ello");              // consumed the 'h'

  // Now ^ must match 'e' at the new beginning
  RE2 re2("^e");
  ASSERT_TRUE(RE2::FindAndConsume(&input, re2));
  EXPECT_EQ(input, "llo");
}

// [Boundary] Subsequent calls continue where prior left off (tokenizing).
TEST_F(FindAndConsumeTest_10, RepeatedCallsTokenizeWords_10) {
  RE2 word_re("([A-Za-z]+)");
  std::string s = "  alpha  beta gamma ";
  absl::string_view input(s);

  std::string w;

  ASSERT_TRUE(RE2::FindAndConsume(&input, word_re, &w));
  EXPECT_EQ(w, "alpha");

  ASSERT_TRUE(RE2::FindAndConsume(&input, word_re, &w));
  EXPECT_EQ(w, "beta");

  ASSERT_TRUE(RE2::FindAndConsume(&input, word_re, &w));
  EXPECT_EQ(w, "gamma");

  // No more words; input likely has trailing spaces. Next call should fail
  // and must NOT change input.
  absl::string_view before = input;
  EXPECT_FALSE(RE2::FindAndConsume(&input, word_re, &w));
  EXPECT_EQ(input, before);
}

// [Error/Exceptional] Type conversion failure yields false and no consumption.
TEST_F(FindAndConsumeTest_10, TypeConversionFailureDoesNotConsume_10) {
  RE2 re("(\\w+)");
  std::string s = "abc";                 // text that cannot parse into int
  absl::string_view input(s);

  int as_int = 0;
  absl::string_view before = input;
  EXPECT_FALSE(RE2::FindAndConsume(&input, re, &as_int));  // cannot parse "abc" to int
  EXPECT_EQ(input, before);              // input unchanged on failure
}

// [No match] Returns false and leaves input untouched.
TEST_F(FindAndConsumeTest_10, NoMatchLeavesInputUntouched_10) {
  RE2 re("xyz");
  std::string s = "abcdef";
  absl::string_view input(s);

  absl::string_view before = input;
  EXPECT_FALSE(RE2::FindAndConsume(&input, re));
  EXPECT_EQ(input, before);
}

// [Unicode/UTF-8] Works with non-ASCII; consumes after digits following multibyte text.
TEST_F(FindAndConsumeTest_10, HandlesUTF8AndAdvances_10) {
  RE2 re("(\\d+)");
  std::string s = u8"한글ABC123";
  absl::string_view input(s);

  std::string digits;
  ASSERT_TRUE(RE2::FindAndConsume(&input, re, &digits));
  EXPECT_EQ(digits, "123");
  EXPECT_TRUE(input.empty());            // consumed to the end
}
