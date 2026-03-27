// File: ./TestProjects/re2/re2/tests/regexp_fuzz_max_repeat_test_478.cc
#include <climits>
#include "gtest/gtest.h"

// Use the provided interface only.
// We include the header for the setter declaration and refer to the global
// as listed in the prompt (observable module-level state).
#include "re2/regexp.h"

namespace re2 {
// The prompt explicitly lists this global; declare it extern for the tests.
extern int maximum_repeat_count;
}

class RegexpFuzzMaxRepeatTest_478 : public ::testing::Test {
 protected:
  int saved_{};

  void SetUp() override { saved_ = re2::maximum_repeat_count; }
  void TearDown() override { re2::Regexp::FUZZING_ONLY_set_maximum_repeat_count(saved_); }
};

// Normal operation: updates from default to a new positive value.
TEST_F(RegexpFuzzMaxRepeatTest_478, SetsNewPositiveValue_478) {
  // Act
  re2::Regexp::FUZZING_ONLY_set_maximum_repeat_count(123);

  // Assert (observe via the public/global state listed in the prompt)
  EXPECT_EQ(123, re2::maximum_repeat_count);
}

// Boundary: set to zero.
TEST_F(RegexpFuzzMaxRepeatTest_478, AcceptsZero_478) {
  re2::Regexp::FUZZING_ONLY_set_maximum_repeat_count(0);
  EXPECT_EQ(0, re2::maximum_repeat_count);
}

// Boundary: set to a negative number (if allowed by interface, it should be stored verbatim).
TEST_F(RegexpFuzzMaxRepeatTest_478, AcceptsNegativeValue_478) {
  re2::Regexp::FUZZING_ONLY_set_maximum_repeat_count(-1);
  EXPECT_EQ(-1, re2::maximum_repeat_count);
}

// Boundary: set to a very large number (INT_MAX).
TEST_F(RegexpFuzzMaxRepeatTest_478, AcceptsIntMax_478) {
  re2::Regexp::FUZZING_ONLY_set_maximum_repeat_count(INT_MAX);
  EXPECT_EQ(INT_MAX, re2::maximum_repeat_count);
}

// Observable behavior: last call wins (idempotent w.r.t assignment order).
TEST_F(RegexpFuzzMaxRepeatTest_478, LastCallWins_478) {
  re2::Regexp::FUZZING_ONLY_set_maximum_repeat_count(10);
  re2::Regexp::FUZZING_ONLY_set_maximum_repeat_count(20);
  EXPECT_EQ(20, re2::maximum_repeat_count);
}
