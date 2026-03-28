// File: myStringReplace_test_2720.cc
#include <gtest/gtest.h>

#include <string>

// pdftotext.cc is a utility with its own main() in many builds.
// To include it into this test TU (so we can call the file-local `static`
// function `myStringReplace`), we rename main before inclusion.
#define main pdftotext_main_2720
#include "utils/pdftotext.cc"
#undef main

namespace {

class MyStringReplaceTest_2720 : public ::testing::Test {};

TEST_F(MyStringReplaceTest_2720, ReplacesSingleOccurrence_2720) {
  const std::string in = "hello world";
  const std::string out = myStringReplace(in, "world", "poppler");
  EXPECT_EQ(out, "hello poppler");
}

TEST_F(MyStringReplaceTest_2720, ReturnsUnchangedWhenOldTokenNotFound_2720) {
  const std::string in = "hello world";
  const std::string out = myStringReplace(in, "missing", "x");
  EXPECT_EQ(out, in);
}

TEST_F(MyStringReplaceTest_2720, ReplacesMultipleOccurrences_2720) {
  const std::string in = "one fish two fish red fish blue fish";
  const std::string out = myStringReplace(in, "fish", "cat");
  EXPECT_EQ(out, "one cat two cat red cat blue cat");
}

TEST_F(MyStringReplaceTest_2720, ReplacesAtBeginningAndEnd_2720) {
  const std::string in = "token middle token";
  const std::string out = myStringReplace(in, "token", "X");
  EXPECT_EQ(out, "X middle X");
}

TEST_F(MyStringReplaceTest_2720, HandlesEmptyInputString_2720) {
  const std::string in = "";
  const std::string out = myStringReplace(in, "a", "b");
  EXPECT_EQ(out, "");
}

TEST_F(MyStringReplaceTest_2720, AllowsRemovingByReplacingWithEmptyNewToken_2720) {
  const std::string in = "a-b-c-d";
  const std::string out = myStringReplace(in, "-", "");
  EXPECT_EQ(out, "abcd");
}

TEST_F(MyStringReplaceTest_2720, OldTokenLongerThanInputDoesNothing_2720) {
  const std::string in = "abc";
  const std::string out = myStringReplace(in, "abcdef", "X");
  EXPECT_EQ(out, "abc");
}

TEST_F(MyStringReplaceTest_2720, OldTokenEqualsNewTokenLeavesStringEffectivelyUnchanged_2720) {
  const std::string in = "repeat repeat";
  const std::string out = myStringReplace(in, "repeat", "repeat");
  EXPECT_EQ(out, in);
}

TEST_F(MyStringReplaceTest_2720, ReplacementDoesNotReReplaceIntroducedSubstrings_2720) {
  // If replacing "a" with "aa", a naive algorithm could loop forever re-matching.
  // Observable requirement here: function returns and performs finite replacements.
  const std::string in = "a";
  const std::string out = myStringReplace(in, "a", "aa");
  EXPECT_EQ(out, "aa");
}

TEST_F(MyStringReplaceTest_2720, ReplacesNonOverlappingMatchesWithAdvancingSearch_2720) {
  // Boundary-style case with repeated characters and a multi-char token.
  // We assert only on the observable output.
  const std::string in = "aaaa";
  const std::string out = myStringReplace(in, "aa", "a");
  EXPECT_EQ(out, "aa");
}

TEST_F(MyStringReplaceTest_2720, ReplacesAdjacentMatches_2720) {
  const std::string in = "xxxx";
  const std::string out = myStringReplace(in, "xx", "Y");
  EXPECT_EQ(out, "YY");
}

// NOTE: We intentionally do NOT test oldToken == "".
// For many find/replace loops, an empty token can lead to non-termination,
// and the interface provides no observable error channel to assert on safely.

}  // namespace