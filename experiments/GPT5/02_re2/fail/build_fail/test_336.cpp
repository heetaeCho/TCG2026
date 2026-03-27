// File: regexp_decref_test_336.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using re2::Regexp;

// Small helper to create a minimal, valid Regexp instance via a public ctor API.
// We avoid any reliance on internal state or behavior.
static Regexp* MakeOneRefLiteral() {
  // Use a simple literal rune with zero parse flags; flags are an enum type.
  return Regexp::NewLiteral(static_cast<Rune>('x'),
                            static_cast<Regexp::ParseFlags>(0));
}

// ----------------------
// Test Suite
// ----------------------

class RegexpDecrefTest_336 : public ::testing::Test {
 protected:
  void TearDown() override {
    // No shared fixture state; individual tests are responsible for balancing
    // Incref/Decref or letting the final Decref destroy the object.
  }
};

// [Normal] Fresh object should report initial refcount of 1.
TEST_F(RegexpDecrefTest_336, RefStartsAtOne_336) {
  Regexp* re = MakeOneRefLiteral();
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->Ref(), 1);

  // Clean up: drop the initial reference; object may self-destroy.
  re->Decref();
}

// [Normal] Incref should increase the observable refcount by 1;
// Decref should bring it back.
TEST_F(RegexpDecrefTest_336, IncrefThenDecref_RoundTrip_336) {
  Regexp* re = MakeOneRefLiteral();
  ASSERT_NE(re, nullptr);

  const int start = re->Ref();
  ASSERT_EQ(start, 1);

  re->Incref();
  EXPECT_EQ(re->Ref(), start + 1);

  re->Decref();
  EXPECT_EQ(re->Ref(), start);

  // Final cleanup.
  re->Decref();
}

// [Boundary] Multiple increments and decrements should net back to the start.
// This exercises the counter without assuming internal limits.
TEST_F(RegexpDecrefTest_336, ManyIncrefThenManyDecref_ReturnsToStart_336) {
  Regexp* re = MakeOneRefLiteral();
  ASSERT_NE(re, nullptr);

  const int start = re->Ref();
  ASSERT_EQ(start, 1);

  constexpr int kN = 1000;
  for (int i = 0; i < kN; ++i) {
    re->Incref();
  }
  EXPECT_EQ(re->Ref(), start + kN);

  for (int i = 0; i < kN; ++i) {
    re->Decref();
  }
  EXPECT_EQ(re->Ref(), start);

  // Final cleanup.
  re->Decref();
}

// [Exceptional/Destruction] Dropping the last reference should safely destroy
// the object. We only assert that calling Decref at ref==1 does not crash;
// we do NOT touch the pointer afterward (no reliance on freed memory).
TEST_F(RegexpDecrefTest_336, DecrefAtOneDestroys_NoCrash_336) {
  Regexp* re = MakeOneRefLiteral();
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->Ref(), 1);

  // After this call, the object may be destroyed. Do not dereference 're'.
  re->Decref();

  // If the process reaches here, Decref at 1 completed without crashing.
  SUCCEED();
}

// [Boundary / Saturation-path smoke] Stress the refcount with a large number
// of increments to (likely) cross any internal saturation threshold, then
// walk it back. We do not assume the threshold value; we only verify that
// observable refcounting is consistent and returns to 1.
TEST_F(RegexpDecrefTest_336, LargeRefcountStress_RoundTripToOne_336) {
  Regexp* re = MakeOneRefLiteral();
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->Ref(), 1);

  // Choose a large N that comfortably exceeds 16-bit limits.
  constexpr int kBig = 100000;  // 1e5

  for (int i = 0; i < kBig; ++i) {
    re->Incref();
  }
  // We can observe the total via Ref(); we don't assume internal representation.
  const int after_inc = re->Ref();
  EXPECT_GE(after_inc, 1 + kBig);

  for (int i = 0; i < kBig; ++i) {
    re->Decref();
  }
  EXPECT_EQ(re->Ref(), 1);

  // Final cleanup: drop the original reference.
  re->Decref();
}

}  // namespace
