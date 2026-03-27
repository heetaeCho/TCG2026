// File: regexp_min_test_154.cc
#include "re2/regexp.h"
#include <gtest/gtest.h>

namespace re2 {

// Helper alias for flags with zero-as-default.
using PF = Regexp::ParseFlags;

class RegexpMinTest_154 : public ::testing::Test {};

// [Normal] A simple bounded repeat should report the specified lower bound.
TEST_F(RegexpMinTest_154, ReturnsMinForRepeat_154) {
  Regexp* atom = Regexp::NewLiteral(static_cast<Rune>('a'), static_cast<PF>(0));
  ASSERT_NE(atom, nullptr);

  Regexp* rep = Regexp::Repeat(atom, static_cast<PF>(0), /*min=*/3, /*max=*/5);
  ASSERT_NE(rep, nullptr);

  EXPECT_EQ(rep->min(), 3);

  // Tear-down: Release the top-level node. (Ownership of sub is internal.)
  rep->Decref();
}

// [Boundary] Allowing zero repetitions: lower bound should be 0.
TEST_F(RegexpMinTest_154, ReturnsZeroWhenMinIsZero_154) {
  Regexp* atom = Regexp::NewLiteral(static_cast<Rune>('x'), static_cast<PF>(0));
  ASSERT_NE(atom, nullptr);

  Regexp* rep = Regexp::Repeat(atom, static_cast<PF>(0), /*min=*/0, /*max=*/4);
  ASSERT_NE(rep, nullptr);

  EXPECT_EQ(rep->min(), 0);

  rep->Decref();
}

// [Boundary] Larger lower bounds should be reported exactly.
TEST_F(RegexpMinTest_154, ReturnsLargeMin_154) {
  Regexp* atom = Regexp::NewLiteral(static_cast<Rune>('z'), static_cast<PF>(0));
  ASSERT_NE(atom, nullptr);

  const int big_min = 1000;  // Representative “large” bound (still reasonable).
  Regexp* rep = Regexp::Repeat(atom, static_cast<PF>(0), /*min=*/big_min, /*max=*/big_min + 5);
  ASSERT_NE(rep, nullptr);

  EXPECT_EQ(rep->min(), big_min);

  rep->Decref();
}

}  // namespace re2
