// File: regexp_max_test_155.cc
#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

using PF = Regexp::ParseFlags;

// Helper to get a minimal literal sub-regexp without assuming internals.
static Regexp* MakeLiteralRune(Rune r) {
  return Regexp::NewLiteral(r, static_cast<PF>(0));
}

// ---------- Tests ----------

// Normal operation: bounded repeat should return its upper bound via max().
TEST(RegexpMaxTest_155, BoundedRepeat_ReturnsUpperBound_155) {
  Regexp* lit = MakeLiteralRune('x');
  ASSERT_NE(lit, nullptr) << "NewLiteral should produce a non-null Regexp.";

  Regexp* rep = Regexp::Repeat(lit, static_cast<PF>(0), /*min=*/2, /*max=*/5);
  ASSERT_NE(rep, nullptr) << "Repeat should produce a non-null Regexp.";

  EXPECT_EQ(rep->max(), 5);

  // Clean up if reference counting is active; safe if it’s a no-op.
  rep->Decref();
}

// Boundary: exact-repeat (min == max) should report that exact value.
TEST(RegexpMaxTest_155, ExactRepeat_ReturnsExact_155) {
  Regexp* lit = MakeLiteralRune('a');
  ASSERT_NE(lit, nullptr);

  Regexp* rep = Regexp::Repeat(lit, static_cast<PF>(0), /*min=*/3, /*max=*/3);
  ASSERT_NE(rep, nullptr);

  EXPECT_EQ(rep->max(), 3);

  rep->Decref();
}

// Boundary: zero repeat (min == 0, max == 0) returns 0.
TEST(RegexpMaxTest_155, ZeroRepeat_ReturnsZero_155) {
  Regexp* lit = MakeLiteralRune('z');
  ASSERT_NE(lit, nullptr);

  Regexp* rep = Regexp::Repeat(lit, static_cast<PF>(0), /*min=*/0, /*max=*/0);
  ASSERT_NE(rep, nullptr);

  EXPECT_EQ(rep->max(), 0);

  rep->Decref();
}

// Observable “exceptional”/edge case: negative max should be returned verbatim.
// (No assumption on semantics; we only verify the accessor passes through value.)
TEST(RegexpMaxTest_155, NegativeMax_PassThrough_155) {
  Regexp* lit = MakeLiteralRune('q');
  ASSERT_NE(lit, nullptr);

  Regexp* rep = Regexp::Repeat(lit, static_cast<PF>(0), /*min=*/2, /*max=*/-1);
  ASSERT_NE(rep, nullptr);

  EXPECT_EQ(rep->max(), -1);

  rep->Decref();
}

}  // namespace re2
