// Mul0dTable_test_1607.cc
//
// Unit tests for Mul0dTable (from Decrypt.cc)
// Constraints respected:
// - Treat implementation as black box (no assumptions about table contents).
// - Verify only observable behavior through the public interface.

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <utility>

// Mul0dTable is defined in Decrypt.cc (not a public header in the provided snippet).
// Including the implementation file is a common approach for testing internal-only types.
#include "Decrypt.cc"

class Mul0dTableTest_1607 : public ::testing::Test {};

TEST_F(Mul0dTableTest_1607, IsDefaultConstructible_1607) {
  EXPECT_TRUE((std::is_default_constructible<Mul0dTable>::value));
}

TEST_F(Mul0dTableTest_1607, CallOperatorHasExpectedSignature_1607) {
  using Ret = decltype(std::declval<const Mul0dTable&>()(std::declval<uint8_t>()));
  EXPECT_TRUE((std::is_same<Ret, unsigned char>::value));
  EXPECT_TRUE((std::is_same<decltype(std::declval<uint8_t>()), uint8_t>::value));
}

TEST_F(Mul0dTableTest_1607, CanBeUsedInConstexprContext_1607) {
  // We do not assert any specific numeric value (black-box).
  // The mere fact this compiles proves ctor+operator() can form a constant expression.
  constexpr Mul0dTable t{};
  constexpr unsigned char v0 = t(uint8_t{0});
  constexpr unsigned char v1 = t(uint8_t{1});
  static_assert(v0 == v0, "Must be a valid constant expression");
  static_assert(v1 == v1, "Must be a valid constant expression");

  // Also ensure runtime usage works.
  (void)v0;
  (void)v1;
  SUCCEED();
}

TEST_F(Mul0dTableTest_1607, BoundaryInputsAreCallable_1607) {
  const Mul0dTable t;

  // Boundary conditions for uint8_t domain: 0 and 255.
  volatile unsigned char out0 = t(uint8_t{0});
  volatile unsigned char out255 = t(uint8_t{255});

  // Observable guarantee: returns an unsigned char (always within [0,255]).
  EXPECT_LE(static_cast<int>(out0), 255);
  EXPECT_GE(static_cast<int>(out0), 0);
  EXPECT_LE(static_cast<int>(out255), 255);
  EXPECT_GE(static_cast<int>(out255), 0);
}

TEST_F(Mul0dTableTest_1607, DeterministicForSameInstanceAndInput_1607) {
  const Mul0dTable t;

  const uint8_t inputs[] = {uint8_t{0}, uint8_t{1}, uint8_t{2}, uint8_t{127}, uint8_t{128}, uint8_t{254}, uint8_t{255}};
  for (uint8_t x : inputs) {
    const unsigned char a = t(x);
    const unsigned char b = t(x);
    EXPECT_EQ(a, b) << "Expected deterministic output for repeated calls with same input";
  }
}

TEST_F(Mul0dTableTest_1607, ConsistentAcrossInstancesForAllByteValues_1607) {
  // This checks an observable property: two default-constructed instances behave the same.
  // It does not assume any specific mapping, only consistency.
  const Mul0dTable t1;
  const Mul0dTable t2;

  for (int i = 0; i <= 255; ++i) {
    const auto x = static_cast<uint8_t>(i);
    EXPECT_EQ(t1(x), t2(x)) << "Mismatch at input byte value " << i;
  }
}

TEST_F(Mul0dTableTest_1607, ExhaustiveDomainCallDoesNotCrash_1607) {
  const Mul0dTable t;

  // No explicit error/exception channel in the interface; just ensure calls are valid
  // over the entire uint8_t domain.
  for (int i = 0; i <= 255; ++i) {
    const auto x = static_cast<uint8_t>(i);
    volatile unsigned char out = t(x);
    (void)out;
  }

  SUCCEED();
}