// File: filtered_re2_add_test_472.cc

#include "re2/filtered_re2.h"
#include "re2/re2.h"

#include <gtest/gtest.h>

using re2::FilteredRE2;
using re2::RE2;

class FilteredRE2AddTest_472 : public ::testing::Test {
protected:
  FilteredRE2 fr_;
};

// Normal operation: valid regex gets added, id starts at 0 and increments
TEST_F(FilteredRE2AddTest_472, Add_ValidPatternAssignsSequentialIDs_472) {
  RE2::Options opt1;                // default options
  int id0 = -1;
  auto code0 = fr_.Add("abc", opt1, &id0);

  EXPECT_EQ(id0, 0);                // first added pattern gets id 0
  EXPECT_EQ(fr_.NumRegexps(), 1);   // exactly one regex stored now
  EXPECT_TRUE(fr_.GetRE2(0).ok());  // stored RE2 must be OK
  EXPECT_EQ(code0, fr_.GetRE2(0).error_code());  // returned code matches stored RE2

  RE2::Options opt2;                // add a second valid pattern
  int id1 = -1;
  auto code1 = fr_.Add("def", opt2, &id1);

  EXPECT_EQ(id1, 1);                // second added pattern gets id 1
  EXPECT_EQ(fr_.NumRegexps(), 2);   // two regexes stored
  EXPECT_TRUE(fr_.GetRE2(1).ok());
  EXPECT_EQ(code1, fr_.GetRE2(1).error_code());

  // Sanity: the patterns are the ones we added (observable via RE2::pattern()).
  EXPECT_EQ(fr_.GetRE2(0).pattern(), "abc");
  EXPECT_EQ(fr_.GetRE2(1).pattern(), "def");
}

// Boundary-ish normal case: empty pattern is a valid regex that should be added
TEST_F(FilteredRE2AddTest_472, Add_EmptyPatternIsAcceptedAndAssignedId_472) {
  RE2::Options opts;
  int id = -1;
  auto code = fr_.Add("", opts, &id);

  EXPECT_EQ(id, 0);
  EXPECT_EQ(fr_.NumRegexps(), 1);
  EXPECT_TRUE(fr_.GetRE2(0).ok());
  EXPECT_EQ(code, fr_.GetRE2(0).error_code());
  EXPECT_EQ(fr_.GetRE2(0).pattern(), "");
}

// Error/exceptional case observable via interface: invalid regex is NOT added and id remains unchanged
TEST_F(FilteredRE2AddTest_472, Add_InvalidPatternDoesNotAddAndLeavesIdUnchanged_472) {
  RE2::Options opts;
  opts.set_log_errors(false);  // avoid logging side effects for the test
  int id = -1;

  auto code = fr_.Add("(", opts, &id);  // syntactically invalid

  (void)code; // We don't assert on specific enum values; only on observable effects.
  EXPECT_EQ(fr_.NumRegexps(), 0) << "Invalid pattern must not be stored";
  EXPECT_EQ(id, -1) << "Id should remain untouched on failure";
}

// Option propagation (observable via returned RE2): case sensitivity flag respected
TEST_F(FilteredRE2AddTest_472, Add_RespectsOptionsCaseSensitivity_472) {
  RE2::Options opts;
  opts.set_case_sensitive(false);   // make it case-insensitive
  int id = -1;

  auto code = fr_.Add("ABC", opts, &id);

  EXPECT_EQ(id, 0);
  EXPECT_EQ(fr_.NumRegexps(), 1);
  EXPECT_TRUE(fr_.GetRE2(0).ok());
  EXPECT_EQ(code, fr_.GetRE2(0).error_code());

  // Verify the option is reflected in the stored RE2 instance
  EXPECT_FALSE(fr_.GetRE2(0).options().case_sensitive());
}

// Sequential id assignment across mixed add attempts (success then failure then success)
TEST_F(FilteredRE2AddTest_472, Add_MixedSuccessAndFailureYieldsCorrectIds_472) {
  // First: success
  RE2::Options opts_ok;
  int id0 = -1;
  fr_.Add("x+", opts_ok, &id0);
  ASSERT_EQ(id0, 0);
  ASSERT_EQ(fr_.NumRegexps(), 1);

  // Second: failure (invalid), should not change count nor consume an id
  RE2::Options opts_bad;
  opts_bad.set_log_errors(false);
  int id_bad = 123;  // sentinel that should remain unchanged
  fr_.Add("([)", opts_bad, &id_bad);
  EXPECT_EQ(fr_.NumRegexps(), 1);
  EXPECT_EQ(id_bad, 123);

  // Third: success, should receive id 1
  int id1 = -1;
  fr_.Add("y?", opts_ok, &id1);
  EXPECT_EQ(fr_.NumRegexps(), 2);
  EXPECT_EQ(id1, 1);
}
