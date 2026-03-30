// File: re2_possible_match_range_test_260.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2_PossibleMatchRangeTest_260 : public ::testing::Test {};

// [Behavior] If the underlying program is not constructed (e.g., invalid pattern),
// PossibleMatchRange returns false immediately and does not touch outputs.
TEST_F(RE2_PossibleMatchRangeTest_260, InvalidRegexReturnsFalseAndLeavesMinMaxUnchanged_260) {
  // An obviously invalid regex should fail to compile.
  RE2 re("(");  // invalid pattern
  std::string min = "keep_min";
  std::string max = "keep_max";

  const bool ok = re.PossibleMatchRange(&min, &max, /*maxlen=*/5);

  EXPECT_FALSE(ok);
  // Based on the early-return in the provided code path, outputs remain unchanged.
  EXPECT_EQ(min, "keep_min");
  EXPECT_EQ(max, "keep_max");
}

// [Boundary] When maxlen == 0, the method reports no possible range.
// Observable behavior from snippet: returns false and clears both outputs.
TEST_F(RE2_PossibleMatchRangeTest_260, ZeroMaxLenReturnsFalseAndClearsMinMax_260) {
  RE2 re("abc");  // any valid pattern is fine
  std::string min, max;

  const bool ok = re.PossibleMatchRange(&min, &max, /*maxlen=*/0);

  EXPECT_FALSE(ok);
  EXPECT_EQ(min, "");
  EXPECT_EQ(max, "");
}

// [Normal + Case-fold behavior] With a case-insensitive fixed-prefix pattern and maxlen <= prefix length,
// the snippet upper-cases letters in the min prefix and returns true.
TEST_F(RE2_PossibleMatchRangeTest_260, FoldCaseUppercasesMinPrefix_260) {
  RE2 re("(?i)abc");  // case-insensitive; fixed literal prefix "abc"
  std::string min, max;

  const bool ok = re.PossibleMatchRange(&min, &max, /*maxlen=*/2);

  EXPECT_TRUE(ok);
  // From the provided code: when prefix_foldcase_ is true, lowercase a–z in *min are uppercased.
  // Only the first 'maxlen' chars are taken from the prefix.
  EXPECT_EQ(min, "AB");
  // We don't assert the exact value of max (it may be adjusted by PrefixSuccessor), only that it's non-empty.
  EXPECT_FALSE(max.empty());
  // And its first 2 chars should reflect the taken prefix before any successor logic.
  EXPECT_EQ(max.substr(0, 2), "ab");
}

// [Normal] With a case-sensitive fixed prefix and maxlen smaller than the prefix length,
// the method copies the truncated prefix into both outputs and returns true.
TEST_F(RE2_PossibleMatchRangeTest_260, TruncatesPrefixToMaxLen_260) {
  RE2 re("abcdef");  // fixed literal prefix
  std::string min, max;

  const bool ok = re.PossibleMatchRange(&min, &max, /*maxlen=*/3);

  EXPECT_TRUE(ok);
  EXPECT_EQ(min, "abc");            // truncated to maxlen
  EXPECT_EQ(max.substr(0, 3), "abc");  // starts with the same truncated prefix
}

// [Normal] Case-sensitive literal: min keeps original case for the taken prefix.
TEST_F(RE2_PossibleMatchRangeTest_260, NonFoldCaseKeepsOriginalCase_260) {
  RE2 re("Abc");  // case-sensitive by default
  std::string min, max;

  const bool ok = re.PossibleMatchRange(&min, &max, /*maxlen=*/2);

  EXPECT_TRUE(ok);
  EXPECT_EQ(min, "Ab");              // preserves original case in min
  EXPECT_EQ(max.substr(0, 2), "Ab"); // max begins with the same two characters
}
