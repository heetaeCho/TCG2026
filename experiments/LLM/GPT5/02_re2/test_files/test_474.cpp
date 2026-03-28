// File: filtered_re2_slowfirstmatch_test.cc
#include <gtest/gtest.h>
#include "re2/filtered_re2.h"
#include "re2/re2.h"

using re2::FilteredRE2;
using re2::RE2;

class FilteredRE2Test_474 : public ::testing::Test {};

// [Normal] Empty matcher set should never match.
TEST_F(FilteredRE2Test_474, SlowFirstMatch_EmptyReturnsMinusOne_474) {
  FilteredRE2 fr;
  EXPECT_EQ(-1, fr.SlowFirstMatch("anything"));
  EXPECT_EQ(-1, fr.SlowFirstMatch(""));  // empty text also returns -1
}

// [Normal] Single regex added: matching text returns index 0; non-matching returns -1.
TEST_F(FilteredRE2Test_474, SlowFirstMatch_SingleRegexMatchesAtIndex0_474) {
  FilteredRE2 fr;
  RE2::Options opts;  // default options
  int id = -1;

  // Add a simple literal pattern.
  auto ec = fr.Add("foo", opts, &id);
  // We don't assert on ec details; we only rely on observable SlowFirstMatch behavior.
  (void)ec;

  EXPECT_EQ(0, fr.SlowFirstMatch("foo"));
  EXPECT_EQ(0, fr.SlowFirstMatch("xxfooyy"));   // Partial match anywhere
  EXPECT_EQ(-1, fr.SlowFirstMatch("bar"));      // No match
}

// [Normal] Multiple regexes where more than one would match: the first added wins.
TEST_F(FilteredRE2Test_474, SlowFirstMatch_MultipleRegex_FirstAddedWins_474) {
  FilteredRE2 fr;
  RE2::Options opts;
  int id = -1;

  // Add in order: "bar" then "foo".
  fr.Add("bar", opts, &id);
  fr.Add("foo", opts, &id);

  // Text matches both "foo" and "bar"; first added ("bar") should win -> index 0.
  EXPECT_EQ(0, fr.SlowFirstMatch("foobar"));

  // If only the second pattern matches, index should be 1.
  EXPECT_EQ(1, fr.SlowFirstMatch("xxxfoo"));
}

// [Boundary/Exceptional-as-observable] No regex matches among multiple: return -1.
TEST_F(FilteredRE2Test_474, SlowFirstMatch_MultipleRegex_NoMatches_474) {
  FilteredRE2 fr;
  RE2::Options opts;
  int id = -1;

  fr.Add("abc", opts, &id);
  fr.Add("def", opts, &id);

  EXPECT_EQ(-1, fr.SlowFirstMatch("ghi"));
  EXPECT_EQ(-1, fr.SlowFirstMatch(""));  // empty text doesn't match these literals
}

// [Boundary] Move-constructed object preserves observable matching order/behavior.
TEST_F(FilteredRE2Test_474, SlowFirstMatch_AfterMoveConstruction_PreservesBehavior_474) {
  RE2::Options opts;
  int id = -1;

  FilteredRE2 original;
  original.Add("abc", opts, &id);  // would match at index 0
  original.Add("xyz", opts, &id);  // would match at index 1

  // Move-construct into a new instance; behavior should remain observable the same.
  FilteredRE2 moved(std::move(original));

  // Text that matches both patterns; first-added ("abc") should still win -> index 0.
  EXPECT_EQ(0, moved.SlowFirstMatch("---abcxyz---"));

  // Text that matches only the second pattern -> index 1.
  EXPECT_EQ(1, moved.SlowFirstMatch("...xyz..."));

  // Non-matching text -> -1.
  EXPECT_EQ(-1, moved.SlowFirstMatch("nope"));
}
