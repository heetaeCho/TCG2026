// File: ./TestProjects/yaml-cpp/test/remove_compact_t_no_trailing_zeros_test.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <cstdint>

#include "contrib/dragonbox.h"

namespace {

struct DummyFormat {};

// Helper accessors (assumes unsigned_decimal_fp exposes these as public members).
template <class T>
auto GetSignificand(const T& v) -> decltype(v.significand) {
  return v.significand;
}
template <class T>
auto GetExponent(const T& v) -> decltype(v.exponent) {
  return v.exponent;
}

}  // namespace

TEST(RemoveCompactTNoTrailingZerosTest_340, ReturnsSameValuesForTypicalInputs_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  const std::uint64_t significand = 123456789ull;
  const int exponent = -7;

  auto r = Policy::no_trailing_zeros<DummyFormat>(significand, exponent);

  EXPECT_EQ(GetSignificand(r), significand);
  EXPECT_EQ(GetExponent(r), exponent);
}

TEST(RemoveCompactTNoTrailingZerosTest_340, HandlesZeroSignificand_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  const std::uint32_t significand = 0u;
  const int exponent = 0;

  auto r = Policy::no_trailing_zeros<DummyFormat>(significand, exponent);

  EXPECT_EQ(GetSignificand(r), significand);
  EXPECT_EQ(GetExponent(r), exponent);
}

TEST(RemoveCompactTNoTrailingZerosTest_340, HandlesPositiveExponent_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  const std::uint64_t significand = 42ull;
  const int exponent = 15;

  auto r = Policy::no_trailing_zeros<DummyFormat>(significand, exponent);

  EXPECT_EQ(GetSignificand(r), significand);
  EXPECT_EQ(GetExponent(r), exponent);
}

TEST(RemoveCompactTNoTrailingZerosTest_340, HandlesNegativeExponent_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  const std::uint64_t significand = 9876543210ull;
  const int exponent = -123;

  auto r = Policy::no_trailing_zeros<DummyFormat>(significand, exponent);

  EXPECT_EQ(GetSignificand(r), significand);
  EXPECT_EQ(GetExponent(r), exponent);
}

TEST(RemoveCompactTNoTrailingZerosTest_340, PreservesLargeValues_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  const std::uint64_t significand = (std::numeric_limits<std::uint64_t>::max)();
  const std::int32_t exponent = (std::numeric_limits<std::int32_t>::min)();

  auto r = Policy::no_trailing_zeros<DummyFormat>(significand, exponent);

  EXPECT_EQ(GetSignificand(r), significand);
  EXPECT_EQ(GetExponent(r), exponent);
}

TEST(RemoveCompactTNoTrailingZerosTest_340, IsNoexcept_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  EXPECT_TRUE((noexcept(Policy::no_trailing_zeros<DummyFormat>(
      std::uint64_t{1}, int{0}))));
}

TEST(RemoveCompactTNoTrailingZerosTest_340, HasExpectedReturnType_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  using Sig = std::uint32_t;
  using Exp = std::int32_t;
  using Expected = YAML::jkj::dragonbox::unsigned_decimal_fp<Sig, Exp, false>;

  auto r = Policy::no_trailing_zeros<DummyFormat>(Sig{7}, Exp{-2});
  EXPECT_TRUE((std::is_same<decltype(r), Expected>::value));
}

TEST(RemoveCompactTNoTrailingZerosTest_340, UsableInConstantExpression_340) {
  using Policy = YAML::jkj::dragonbox::policy::trailing_zero::remove_compact_t;

  constexpr std::uint32_t significand = 314159u;
  constexpr int exponent = -9;

  constexpr auto r = Policy::no_trailing_zeros<DummyFormat>(significand, exponent);

  static_assert(GetSignificand(r) == significand, "significand should be preserved");
  static_assert(GetExponent(r) == exponent, "exponent should be preserved");

  // Also assert at runtime for visibility in test output.
  EXPECT_EQ(GetSignificand(r), significand);
  EXPECT_EQ(GetExponent(r), exponent);
}