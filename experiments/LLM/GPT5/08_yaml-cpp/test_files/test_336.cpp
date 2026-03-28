// File: ./TestProjects/yaml-cpp/test/dragonbox_trailing_zero_ignore_t_test_336.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <tuple>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

struct DummyFormat_336 {};

// Detection helpers to read back the returned unsigned_decimal_fp without
// relying on private/internal state (only observable/public access patterns).
template <class T>
concept HasSignificandExponentMembers_336 = requires(const T& v) {
  v.significand;
  v.exponent;
};

template <class T>
concept HasTupleGet_336 = requires(const T& v) {
  std::get<0>(v);
  std::get<1>(v);
};

template <class T>
constexpr auto GetSignificand_336(const T& v) {
  if constexpr (HasSignificandExponentMembers_336<T>) {
    return v.significand;
  } else if constexpr (HasTupleGet_336<T>) {
    return std::get<0>(v);
  } else {
    static_assert(sizeof(T) == 0,
                  "Returned type is not introspectable via .significand/.exponent or std::get<>.");
  }
}

template <class T>
constexpr auto GetExponent_336(const T& v) {
  if constexpr (HasSignificandExponentMembers_336<T>) {
    return v.exponent;
  } else if constexpr (HasTupleGet_336<T>) {
    return std::get<1>(v);
  } else {
    static_assert(sizeof(T) == 0,
                  "Returned type is not introspectable via .significand/.exponent or std::get<>.");
  }
}

using IgnoreT_336 = YAML::jkj::dragonbox::policy::trailing_zero::ignore_t;

class TrailingZeroIgnoreTest_336 : public ::testing::Test {};

}  // namespace

TEST_F(TrailingZeroIgnoreTest_336, ReturnsSameValues_Basic_336) {
  constexpr std::uint64_t sig = 123456789ULL;
  constexpr int exp = -7;

  constexpr auto out = IgnoreT_336::no_trailing_zeros<DummyFormat_336>(sig, exp);

  EXPECT_EQ(GetSignificand_336(out), sig);
  EXPECT_EQ(GetExponent_336(out), exp);
}

TEST_F(TrailingZeroIgnoreTest_336, WorksWithZeroSignificand_336) {
  constexpr std::uint64_t sig = 0;
  constexpr int exp = 0;

  constexpr auto out = IgnoreT_336::no_trailing_zeros<DummyFormat_336>(sig, exp);

  EXPECT_EQ(GetSignificand_336(out), sig);
  EXPECT_EQ(GetExponent_336(out), exp);
}

TEST_F(TrailingZeroIgnoreTest_336, BoundaryValues_ArePreserved_336) {
  constexpr std::uint64_t sig = (std::numeric_limits<std::uint64_t>::max)();
  constexpr int exp = (std::numeric_limits<int>::min)();

  constexpr auto out = IgnoreT_336::no_trailing_zeros<DummyFormat_336>(sig, exp);

  EXPECT_EQ(GetSignificand_336(out), sig);
  EXPECT_EQ(GetExponent_336(out), exp);
}

TEST_F(TrailingZeroIgnoreTest_336, SupportsDifferentInputIntegerTypes_336) {
  {
    constexpr std::uint32_t sig = 42u;
    constexpr std::int16_t exp = -3;

    constexpr auto out = IgnoreT_336::no_trailing_zeros<DummyFormat_336>(sig, exp);

    EXPECT_EQ(GetSignificand_336(out), sig);
    EXPECT_EQ(GetExponent_336(out), exp);
  }
  {
    constexpr std::uint8_t sig = 255u;
    constexpr std::int32_t exp = 17;

    constexpr auto out = IgnoreT_336::no_trailing_zeros<DummyFormat_336>(sig, exp);

    EXPECT_EQ(GetSignificand_336(out), sig);
    EXPECT_EQ(GetExponent_336(out), exp);
  }
}

TEST_F(TrailingZeroIgnoreTest_336, IsNoexcept_336) {
  static_assert(noexcept(IgnoreT_336::no_trailing_zeros<DummyFormat_336>(
      std::uint64_t{1}, int{2})));
  SUCCEED();
}

TEST_F(TrailingZeroIgnoreTest_336, IsConstexprUsable_336) {
  constexpr auto out = IgnoreT_336::no_trailing_zeros<DummyFormat_336>(
      std::uint64_t{7}, int{-9});

  static_assert(GetSignificand_336(out) == 7);
  static_assert(GetExponent_336(out) == -9);

  EXPECT_EQ(GetSignificand_336(out), 7u);
  EXPECT_EQ(GetExponent_336(out), -9);
}

TEST_F(TrailingZeroIgnoreTest_336, ReturnTypeMatchesTemplateArguments_336) {
  using SigT = std::uint64_t;
  using ExpT = int;

  using Expected =
      YAML::jkj::dragonbox::unsigned_decimal_fp<SigT, ExpT, false>;

  using Actual = decltype(IgnoreT_336::no_trailing_zeros<DummyFormat_336>(
      SigT{1}, ExpT{2}));

  static_assert(std::is_same_v<Actual, Expected>);
  SUCCEED();
}