// File: test_float_bits_is_finite_298.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

struct CountingFormatTraits_298 {
  using carrier_uint = std::uint32_t;
  using exponent_int = int;

  static inline int call_count = 0;
  static inline exponent_int last_arg = 0;

  static bool is_finite(exponent_int e) noexcept {
    ++call_count;
    last_arg = e;
    // Arbitrary, deterministic behavior for testing delegation:
    // even => true, odd => false
    return (e % 2) == 0;
  }

  static void Reset() noexcept {
    call_count = 0;
    last_arg = 0;
  }
};

using FloatBits_298 = YAML::jkj::dragonbox::float_bits<CountingFormatTraits_298>;
using ExponentInt_298 = typename FloatBits_298::exponent_int;

class FloatBitsIsFiniteTest_298 : public ::testing::Test {
 protected:
  void SetUp() override { CountingFormatTraits_298::Reset(); }
};

}  // namespace

TEST_F(FloatBitsIsFiniteTest_298, IsFiniteIsNoexcept_298) {
  const FloatBits_298 fb{};
  const ExponentInt_298 e = 0;
  static_assert(noexcept(fb.is_finite(e)), "is_finite(exponent_int) must be noexcept");
}

TEST_F(FloatBitsIsFiniteTest_298, DelegatesToFormatTraitsAndReturnsValue_298) {
  const FloatBits_298 fb{};

  EXPECT_TRUE(fb.is_finite(static_cast<ExponentInt_298>(10)));
  EXPECT_EQ(CountingFormatTraits_298::call_count, 1);
  EXPECT_EQ(CountingFormatTraits_298::last_arg, static_cast<ExponentInt_298>(10));

  EXPECT_FALSE(fb.is_finite(static_cast<ExponentInt_298>(11)));
  EXPECT_EQ(CountingFormatTraits_298::call_count, 2);
  EXPECT_EQ(CountingFormatTraits_298::last_arg, static_cast<ExponentInt_298>(11));
}

TEST_F(FloatBitsIsFiniteTest_298, WorksWhenCalledOnConstObject_298) {
  const FloatBits_298 fb{};

  (void)fb.is_finite(static_cast<ExponentInt_298>(2));
  EXPECT_EQ(CountingFormatTraits_298::call_count, 1);
  EXPECT_EQ(CountingFormatTraits_298::last_arg, static_cast<ExponentInt_298>(2));
}

TEST_F(FloatBitsIsFiniteTest_298, BoundaryValuesAreForwardedToTraits_298) {
  const FloatBits_298 fb{};

  const ExponentInt_298 min_e = (std::numeric_limits<ExponentInt_298>::min)();
  const ExponentInt_298 max_e = (std::numeric_limits<ExponentInt_298>::max)();

  EXPECT_EQ(fb.is_finite(min_e), CountingFormatTraits_298::is_finite(min_e));
  // Note: the line above calls traits once directly; reset to validate forwarding cleanly.
  CountingFormatTraits_298::Reset();

  (void)fb.is_finite(min_e);
  EXPECT_EQ(CountingFormatTraits_298::call_count, 1);
  EXPECT_EQ(CountingFormatTraits_298::last_arg, min_e);

  (void)fb.is_finite(max_e);
  EXPECT_EQ(CountingFormatTraits_298::call_count, 2);
  EXPECT_EQ(CountingFormatTraits_298::last_arg, max_e);
}