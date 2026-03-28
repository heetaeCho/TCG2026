// File: prefilter_info_nomatch_test.cc
#include <gtest/gtest.h>
#include "re2/prefilter.h"

using ::re2::Prefilter;

// Test suite focuses strictly on public/observable behavior.

class PrefilterInfoNoMatchTest_555 : public ::testing::Test {};

// [Normal] NoMatch returns a valid Info instance.
TEST_F(PrefilterInfoNoMatchTest_555, NoMatchReturnsNonNull_555) {
  Prefilter::Info* info = Prefilter::Info::NoMatch();
  ASSERT_NE(info, nullptr);
  delete info;  // Ensure no leaks/crashes on destruction.
}

// [Boundary/Default] NoMatch should not report an exact match set by default.
// We only use the public accessor `is_exact()`.
TEST_F(PrefilterInfoNoMatchTest_555, NoMatchIsNotExactByDefault_555) {
  Prefilter::Info* info = Prefilter::Info::NoMatch();
  ASSERT_NE(info, nullptr);
  EXPECT_FALSE(info->is_exact());
  delete info;
}

// [Observable interaction] TakeMatch should return a Prefilter* created by NoMatch,
// and subsequent TakeMatch calls should reflect transfer semantics (idempotence).
TEST_F(PrefilterInfoNoMatchTest_555, TakeMatchReturnsOnceAndThenNull_555) {
  Prefilter::Info* info = Prefilter::Info::NoMatch();
  ASSERT_NE(info, nullptr);

  Prefilter* first = info->TakeMatch();
  EXPECT_NE(first, nullptr) << "First TakeMatch should yield a Prefilter*";

  Prefilter* second = info->TakeMatch();
  EXPECT_EQ(second, nullptr) << "Second TakeMatch should not yield again";

  delete first;
  delete info;
}

// [General/robustness] ToString() should be callable and produce a non-empty description.
// We do not assert on specific contents to avoid inferring internal details.
TEST_F(PrefilterInfoNoMatchTest_555, ToStringProducesNonEmptyDescription_555) {
  Prefilter::Info* info = Prefilter::Info::NoMatch();
  ASSERT_NE(info, nullptr);

  std::string s = info->ToString();
  EXPECT_FALSE(s.empty());

  delete info;
}
