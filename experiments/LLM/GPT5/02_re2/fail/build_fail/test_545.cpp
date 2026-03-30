// File: prefilter_info_and_test.cc
#include "gtest/gtest.h"
#include "re2/prefilter.h"

using re2::Prefilter;

namespace {

// Helper: create two simple, valid Info objects via public factories.
// We avoid making any assumptions about internal state.
static Prefilter::Info* MakeSimpleInfoA() {
  // Use a literal (latin1) to get a concrete, non-null Info instance.
  return Prefilter::Info::LiteralLatin1('a');
}

static Prefilter::Info* MakeSimpleInfoB() {
  return Prefilter::Info::LiteralLatin1('b');
}

// ---------- Tests ----------

// Normal operation: both inputs non-null → returns a NEW Info* whose
// observable property `is_exact()` must be false (per implementation).
TEST(PrefilterInfoAnd_545, BothNonNull_IsExactBecomesFalse_545) {
  Prefilter::Info* a = MakeSimpleInfoA();
  Prefilter::Info* b = MakeSimpleInfoB();

  Prefilter::Info* result = Prefilter::Info::And(a, b);

  // BothNonNull path should allocate a new Info.
  // The result pointer must differ from inputs (observable identity).
  ASSERT_NE(result, a);
  ASSERT_NE(result, b);

  // Observable contract from implementation: is_exact_ is set to false.
  EXPECT_FALSE(result->is_exact());

  // Clean up the only remaining live object.
  delete result;
}

// Boundary: left is null → returns right as-is (same pointer), not destroyed.
TEST(PrefilterInfoAnd_545, LeftNull_ReturnsRightPointer_545) {
  Prefilter::Info* b = MakeSimpleInfoB();
  Prefilter::Info* result = Prefilter::Info::And(nullptr, b);

  // Should be exactly the right-hand pointer (identity preserved).
  EXPECT_EQ(result, b);

  // It must still be usable (e.g., ToString() should be callable).
  // We do not assert any specific string contents.
  (void)result->ToString();

  // Clean up.
  delete result;  // equals b
}

// Boundary: right is null → returns left as-is (same pointer), not destroyed.
TEST(PrefilterInfoAnd_545, RightNull_ReturnsLeftPointer_545) {
  Prefilter::Info* a = MakeSimpleInfoA();
  Prefilter::Info* result = Prefilter::Info::And(a, nullptr);

  // Should be exactly the left-hand pointer (identity preserved).
  EXPECT_EQ(result, a);

  // Still usable.
  (void)result->ToString();

  // Clean up.
  delete result;  // equals a
}

// Boundary: both null → returns null.
TEST(PrefilterInfoAnd_545, BothNull_ReturnsNull_545) {
  Prefilter::Info* result = Prefilter::Info::And(nullptr, nullptr);
  EXPECT_EQ(result, nullptr);
}

// Additional observable check: when both inputs are non-null, result must be a fresh object
// (different identity) even if inputs are distinct; we already asserted NE above,
// but make it explicit and isolated here.
TEST(PrefilterInfoAnd_545, BothNonNull_ReturnsFreshObject_545) {
  Prefilter::Info* a = MakeSimpleInfoA();
  Prefilter::Info* b = MakeSimpleInfoB();

  Prefilter::Info* result = Prefilter::Info::And(a, b);

  ASSERT_NE(result, nullptr);
  EXPECT_NE(result, a);
  EXPECT_NE(result, b);

  delete result;
}

}  // namespace
