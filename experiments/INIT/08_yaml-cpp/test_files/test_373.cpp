// File: ./TestProjects/yaml-cpp/test/dragonbox_policy_decimal_to_binary_rounding_detail_nearest_always_closed_t_373_test.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using Policy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail::nearest_always_closed_t;

// Detect whether T supports operator==.
template <typename T, typename = void>
struct has_equal : std::false_type {};
template <typename T>
struct has_equal<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};
template <typename T>
constexpr bool has_equal_v = has_equal<T>::value;

class DragonboxPolicyNearestAlwaysClosedTest_373 : public ::testing::Test {};

TEST_F(DragonboxPolicyNearestAlwaysClosedTest_373, ReturnTypeIsClosedInterval_373) {
  using Closed = YAML::jkj::dragonbox::interval_type::closed;

  static_assert(std::is_same<decltype(Policy::normal_interval(0)), Closed>::value,
                "normal_interval(int) must return interval_type::closed");
  static_assert(std::is_same<decltype(Policy::normal_interval(0u)), Closed>::value,
                "normal_interval(unsigned) must return interval_type::closed");
  static_assert(std::is_same<decltype(Policy::normal_interval(0ll)), Closed>::value,
                "normal_interval(long long) must return interval_type::closed");

  SUCCEED();
}

TEST_F(DragonboxPolicyNearestAlwaysClosedTest_373, NormalIntervalIsNoexcept_373) {
  static_assert(noexcept(Policy::normal_interval(0)),
                "normal_interval must be noexcept for signed int");
  static_assert(noexcept(Policy::normal_interval(0u)),
                "normal_interval must be noexcept for unsigned int");
  static_assert(noexcept(Policy::normal_interval(-1ll)),
                "normal_interval must be noexcept for long long");

  SUCCEED();
}

TEST_F(DragonboxPolicyNearestAlwaysClosedTest_373, NormalIntervalCallableForBoundaryValues_373) {
  // Boundary-ish inputs for a signed type; we only verify callability and that it doesn't throw.
  EXPECT_NO_THROW((void)Policy::normal_interval(0));
  EXPECT_NO_THROW((void)Policy::normal_interval(1));
  EXPECT_NO_THROW((void)Policy::normal_interval(-1));
  EXPECT_NO_THROW((void)Policy::normal_interval(std::numeric_limits<int>::max()));
  EXPECT_NO_THROW((void)Policy::normal_interval(std::numeric_limits<int>::min()));
}

TEST_F(DragonboxPolicyNearestAlwaysClosedTest_373, ConstexprEvaluationIsPossible_373) {
  // Since the function is declared constexpr, verify it can be used in a constant-evaluated context.
  constexpr auto iv0 = Policy::normal_interval(0);
  constexpr auto iv1 = Policy::normal_interval(123u);
  (void)iv0;
  (void)iv1;

  SUCCEED();
}

TEST_F(DragonboxPolicyNearestAlwaysClosedTest_373, ReturnedValueMatchesDefaultWhenComparable_373) {
  using Closed = YAML::jkj::dragonbox::interval_type::closed;

  const auto got = Policy::normal_interval(7);
  const Closed expected{};

  if constexpr (has_equal_v<Closed>) {
    EXPECT_TRUE(got == expected);
  } else {
    // If the type offers no observable equality, we can only verify it is constructible and returned.
    static_assert(std::is_default_constructible<Closed>::value,
                  "interval_type::closed should be default constructible");
    SUCCEED();
  }
}

}  // namespace