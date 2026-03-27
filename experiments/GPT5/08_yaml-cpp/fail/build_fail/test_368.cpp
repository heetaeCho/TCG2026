// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_toward_zero_test_368.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using NearestTowardZero =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_zero_t;

template <class T, class = void>
struct IsEqualityComparable : std::false_type {};
template <class T>
struct IsEqualityComparable<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};

template <class T>
constexpr bool IsEqualityComparableV = IsEqualityComparable<T>::value;

class NearestTowardZeroTest_368 : public ::testing::Test {};

TEST_F(NearestTowardZeroTest_368, NormalInterval_IsNoexcept_368) {
  // Observable behavior: the function is declared noexcept in the interface.
  EXPECT_TRUE(noexcept(NearestTowardZero::normal_interval(0)));
  EXPECT_TRUE(noexcept(NearestTowardZero::normal_interval(std::uint32_t{0})));
  EXPECT_TRUE(noexcept(NearestTowardZero::normal_interval(std::int64_t{0})));
}

TEST_F(NearestTowardZeroTest_368, NormalInterval_ReturnTypeIsRightClosedLeftOpen_368) {
  // Observable behavior: return type is part of the interface.
  using Expected =
      YAML::jkj::dragonbox::interval_type::right_closed_left_open;

  using Actual0 = decltype(NearestTowardZero::normal_interval(0));
  using ActualU32 = decltype(NearestTowardZero::normal_interval(std::uint32_t{123}));
  using ActualI64 = decltype(NearestTowardZero::normal_interval(std::int64_t{-1}));

  EXPECT_TRUE((std::is_same<Actual0, Expected>::value));
  EXPECT_TRUE((std::is_same<ActualU32, Expected>::value));
  EXPECT_TRUE((std::is_same<ActualI64, Expected>::value));
}

TEST_F(NearestTowardZeroTest_368, NormalInterval_AcceptsVariousSignedSignificandBitsTypes_368) {
  // Normal operation: template should accept different argument types.
  (void)NearestTowardZero::normal_interval(0);
  (void)NearestTowardZero::normal_interval(1u);
  (void)NearestTowardZero::normal_interval(std::uint8_t{7});
  (void)NearestTowardZero::normal_interval(std::uint32_t{123456u});
  (void)NearestTowardZero::normal_interval(std::int32_t{-123});
  (void)NearestTowardZero::normal_interval(std::int64_t{9223372036854775807LL});
}

TEST_F(NearestTowardZeroTest_368, NormalInterval_BoundaryValuesDoNotCrash_368) {
  // Boundary conditions: extreme values for common integer types.
  (void)NearestTowardZero::normal_interval(std::uint32_t{0});
  (void)NearestTowardZero::normal_interval(std::numeric_limits<std::uint32_t>::max());

  (void)NearestTowardZero::normal_interval(std::int32_t{0});
  (void)NearestTowardZero::normal_interval(std::numeric_limits<std::int32_t>::min());
  (void)NearestTowardZero::normal_interval(std::numeric_limits<std::int32_t>::max());

  (void)NearestTowardZero::normal_interval(std::int64_t{0});
  (void)NearestTowardZero::normal_interval(std::numeric_limits<std::int64_t>::min());
  (void)NearestTowardZero::normal_interval(std::numeric_limits<std::int64_t>::max());
}

TEST_F(NearestTowardZeroTest_368, NormalInterval_ReturnsDefaultConstructedIntervalObject_368) {
  // The provided implementation returns `{}`; we only check what is observable
  // through the public interface:
  // - It is well-formed to obtain a value.
  // - If the type supports equality, equal values compare equal.
  using Interval = decltype(NearestTowardZero::normal_interval(0));

  Interval a = NearestTowardZero::normal_interval(0);
  Interval b = NearestTowardZero::normal_interval(123);

  if constexpr (IsEqualityComparableV<Interval>) {
    EXPECT_EQ(a, b);
    EXPECT_EQ(a, Interval{});
    EXPECT_EQ(b, Interval{});
  } else {
    // No observable comparison available: just ensure values can be created.
    (void)a;
    (void)b;
    SUCCEED();
  }
}

TEST_F(NearestTowardZeroTest_368, NormalInterval_WorksWithUserDefinedTrivialType_368) {
  // Normal operation with a non-primitive type that is copyable.
  struct Bits {
    int v;
  };

  Bits bits{42};
  auto interval = NearestTowardZero::normal_interval(bits);

  // Only verify the return type and that a value is produced.
  using Expected =
      YAML::jkj::dragonbox::interval_type::right_closed_left_open;
  EXPECT_TRUE((std::is_same<decltype(interval), Expected>::value));
}

}  // namespace