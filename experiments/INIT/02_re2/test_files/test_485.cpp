// File: apply_fold_test_485.cc
#include <gtest/gtest.h>
#include <cstdint>

// The partial dependency we were given.
#include "re2/unicode_casefold.h"

// Forward declarations to match the public interface used by the code under test.
// We do NOT include or re-implement any internal logic.
namespace re2 {
  using Rune = int;  // Matches typical RE2 definition and satisfies the signature.
  Rune ApplyFold(const CaseFold* f, Rune r);
}  // namespace re2

using re2::ApplyFold;
using re2::CaseFold;
using re2::Rune;

// ---------- Normal operation ----------

TEST(ApplyFoldTest_485, AddsPositiveDelta_485) {
  CaseFold f;
  f.delta = 123;  // Arbitrary non-special value; we assert only the observable result.
  const Rune input = 1000;
  const Rune out = ApplyFold(&f, input);
  EXPECT_EQ(out, input + f.delta);
}

TEST(ApplyFoldTest_485, AddsNegativeDelta_485) {
  CaseFold f;
  f.delta = -321;  // Arbitrary negative delta.
  const Rune input = 777;
  const Rune out = ApplyFold(&f, input);
  EXPECT_EQ(out, input + f.delta);
}

// ---------- Boundary-ish values (without relying on internal state) ----------

TEST(ApplyFoldTest_485, ZeroDeltaReturnsSameRune_485) {
  CaseFold f;
  f.delta = 0;
  const Rune input = 42;
  const Rune out = ApplyFold(&f, input);
  EXPECT_EQ(out, input);
}

TEST(ApplyFoldTest_485, LargePositiveInputAndDelta_485) {
  CaseFold f;
  f.delta = 2000000000 / 4;  // Keep well within int range to avoid overflow assumptions.
  const Rune input = 200000000; // Chosen conservatively to avoid UB/overflow concerns.
  const Rune out = ApplyFold(&f, input);
  EXPECT_EQ(out, input + f.delta);
}

TEST(ApplyFoldTest_485, LargeNegativeDelta_485) {
  CaseFold f;
  f.delta = -(2000000000 / 5);  // Large negative but safe magnitude.
  const Rune input = 300000000;
  const Rune out = ApplyFold(&f, input);
  EXPECT_EQ(out, input + f.delta);
}

// ---------- Idempotence with identical inputs (pure function behavior) ----------

TEST(ApplyFoldTest_485, DeterministicForSameInputs_485) {
  CaseFold f;
  f.delta = 1357;  // Arbitrary non-special value.
  const Rune input = 2468;

  const Rune out1 = ApplyFold(&f, input);
  const Rune out2 = ApplyFold(&f, input);
  EXPECT_EQ(out1, out2);
  EXPECT_EQ(out1, input + f.delta);
}
