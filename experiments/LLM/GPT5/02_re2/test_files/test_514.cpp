// File: maybe_parse_repetition_test.cc

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// Include the implementation TU so we can access the internal-linkage function.
// We are NOT re-implementing anything; just bringing the compiled code into this TU.
#include "re2/parse.cc"

namespace {

using re2::MaybeParseRepetition;

TEST(MaybeParseRepetitionTest_514, ReturnsFalseWhenNotStartingWithBrace_514) {
  absl::string_view s = "3}";
  absl::string_view original = s;
  int lo = -2, hi = -2;
  EXPECT_FALSE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(s, original);  // input should remain unchanged on failure
}

TEST(MaybeParseRepetitionTest_514, ReturnsFalseOnEmptyInput_514) {
  absl::string_view s = "";
  absl::string_view original = s;
  int lo = -2, hi = -2;
  EXPECT_FALSE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(s, original);
}

TEST(MaybeParseRepetitionTest_514, ParsesExactCountSimple_514) {
  absl::string_view s = "{3}";
  int lo = -1, hi = -1;
  ASSERT_TRUE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(lo, 3);
  EXPECT_EQ(hi, 3);          // exact form sets hi == lo
  EXPECT_TRUE(s.empty());    // fully consumed
}

TEST(MaybeParseRepetitionTest_514, ParsesExactCountWithRemainder_514) {
  absl::string_view s = "{2}abc";
  int lo = -1, hi = -1;
  ASSERT_TRUE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(lo, 2);
  EXPECT_EQ(hi, 2);
  EXPECT_EQ(s, "abc");       // remainder after the closing '}'
}

TEST(MaybeParseRepetitionTest_514, ParsesOpenUpperBound_514) {
  absl::string_view s = "{4,}";
  int lo = -1, hi = -1;
  ASSERT_TRUE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(lo, 4);
  EXPECT_EQ(hi, -1);         // open upper bound signaled by -1
  EXPECT_TRUE(s.empty());
}

TEST(MaybeParseRepetitionTest_514, ParsesRangeLowerToUpper_514) {
  absl::string_view s = "{2,5}";
  int lo = -1, hi = -1;
  ASSERT_TRUE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(lo, 2);
  EXPECT_EQ(hi, 5);
  EXPECT_TRUE(s.empty());
}

TEST(MaybeParseRepetitionTest_514, AllowsZeroCounts_514) {
  absl::string_view s1 = "{0}";
  int lo = -1, hi = -1;
  ASSERT_TRUE(MaybeParseRepetition(&s1, &lo, &hi));
  EXPECT_EQ(lo, 0);
  EXPECT_EQ(hi, 0);

  absl::string_view s2 = "{0,0}";
  lo = hi = -1;
  ASSERT_TRUE(MaybeParseRepetition(&s2, &lo, &hi));
  EXPECT_EQ(lo, 0);
  EXPECT_EQ(hi, 0);
}

TEST(MaybeParseRepetitionTest_514, ReturnsFalseOnMissingClosingBrace_514) {
  absl::string_view s = "{3";
  absl::string_view original = s;
  int lo = -2, hi = -2;
  EXPECT_FALSE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(s, original);  // unchanged on failure
}

TEST(MaybeParseRepetitionTest_514, ReturnsFalseOnMissingLowerNumber_514) {
  absl::string_view s = "{,5}";
  absl::string_view original = s;
  int lo = -2, hi = -2;
  EXPECT_FALSE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(s, original);
}

TEST(MaybeParseRepetitionTest_514, ReturnsFalseOnEmptyBraces_514) {
  absl::string_view s = "{}";
  absl::string_view original = s;
  int lo = -2, hi = -2;
  EXPECT_FALSE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(s, original);
}

TEST(MaybeParseRepetitionTest_514, ReturnsFalseOnCommaWithoutUpperAndNoBrace_514) {
  absl::string_view s = "{3,";
  absl::string_view original = s;
  int lo = -2, hi = -2;
  EXPECT_FALSE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(s, original);
}

TEST(MaybeParseRepetitionTest_514, ParsesRangeEvenIfUpperLessThanLower_514) {
  // We don't assume validation beyond observable parsing; just verify what it returns.
  absl::string_view s = "{5,2}";
  int lo = -1, hi = -1;
  ASSERT_TRUE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(lo, 5);
  EXPECT_EQ(hi, 2);
  EXPECT_TRUE(s.empty());
}

TEST(MaybeParseRepetitionTest_514, FailsWhenTrailingGarbageBeforeClosingBrace_514) {
  absl::string_view s = "{12x}";
  absl::string_view original = s;
  int lo = -2, hi = -2;
  EXPECT_FALSE(MaybeParseRepetition(&s, &lo, &hi));
  EXPECT_EQ(s, original);
}

}  // namespace
