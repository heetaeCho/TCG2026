// File: re2_options_set_longest_match_test_19.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2OptionsLongestMatchTest_19 : public ::testing::Test {
protected:
  RE2::Options opts_;  // Fresh instance for each test
};

// [Normal] Default should be false (observable via the public getter)
TEST_F(RE2OptionsLongestMatchTest_19, DefaultIsFalse_19) {
  EXPECT_FALSE(opts_.longest_match());
}

// [Normal] Setting true should be reflected by the getter
TEST_F(RE2OptionsLongestMatchTest_19, SetTrueReflectsInGetter_19) {
  opts_.set_longest_match(true);
  EXPECT_TRUE(opts_.longest_match());
}

// [Boundary] Toggling true -> false should be reflected by the getter
TEST_F(RE2OptionsLongestMatchTest_19, ToggleTrueThenFalse_19) {
  opts_.set_longest_match(true);
  ASSERT_TRUE(opts_.longest_match());  // Precondition check (observable)
  opts_.set_longest_match(false);
  EXPECT_FALSE(opts_.longest_match());
}

// [Regression/Isolation] Repeatedly setting the same value remains stable (idempotence via observable state)
TEST_F(RE2OptionsLongestMatchTest_19, RepeatedSetTrueIsStable_19) {
  opts_.set_longest_match(true);
  EXPECT_TRUE(opts_.longest_match());
  opts_.set_longest_match(true);
  EXPECT_TRUE(opts_.longest_match());
}

// [Isolation] Changing longest_match should not (observably) flip an unrelated, publicly exposed option
// We verify a commonly queried flag via its public getter (case_sensitive) remains stable.
TEST_F(RE2OptionsLongestMatchTest_19, ChangingLongestMatchDoesNotAffectOtherFlags_19) {
  // Capture an unrelated observable flag
  const bool initial_case_sensitive = opts_.case_sensitive();

  // Flip longest_match a few times
  opts_.set_longest_match(true);
  EXPECT_TRUE(opts_.longest_match());
  EXPECT_EQ(initial_case_sensitive, opts_.case_sensitive());

  opts_.set_longest_match(false);
  EXPECT_FALSE(opts_.longest_match());
  EXPECT_EQ(initial_case_sensitive, opts_.case_sensitive());
}
