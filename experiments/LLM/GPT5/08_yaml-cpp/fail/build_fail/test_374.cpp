// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_always_closed_374_test.cpp

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail::nearest_always_closed_t;

}  // namespace

TEST(DragonboxNearestAlwaysClosedTest_374, ShorterIntervalIsCallableForCommonSignedTypes_374) {
  // Normal operation: the API is callable for typical signed integer types.
  // (We intentionally don't assume anything about the returned value semantics.)
  const auto r_int = Policy::shorter_interval(int{0});
  const auto r_ll = Policy::shorter_interval(long long{1});
  const auto r_schar = Policy::shorter_interval(signed char{-1});

  (void)r_int;
  (void)r_ll;
  (void)r_schar;

  SUCCEED();
}

TEST(DragonboxNearestAlwaysClosedTest_374, ShorterIntervalAcceptsBoundaryValues_374) {
  // Boundary conditions: min/max values for representative signed types.
  const auto r_int_min = Policy::shorter_interval((std::numeric_limits<int>::min)());
  const auto r_int_max = Policy::shorter_interval((std::numeric_limits<int>::max)());
  const auto r_ll_min = Policy::shorter_interval((std::numeric_limits<long long>::min)());
  const auto r_ll_max = Policy::shorter_interval((std::numeric_limits<long long>::max)());

  (void)r_int_min;
  (void)r_int_max;
  (void)r_ll_min;
  (void)r_ll_max;

  SUCCEED();
}

TEST(DragonboxNearestAlwaysClosedTest_374, ShorterIntervalIsNoexcept_374) {
  // Exceptional/error cases (observable): verify the function is noexcept for typical inputs.
  static_assert(noexcept(Policy::shorter_interval(int{0})),
                "shorter_interval(int) must be noexcept");
  static_assert(noexcept(Policy::shorter_interval(long long{-1})),
                "shorter_interval(long long) must be noexcept");

  SUCCEED();
}

TEST(DragonboxNearestAlwaysClosedTest_374, ShorterIntervalReturnTypeIsStableAndUsable_374) {
  // Verify observable interface traits without assuming internal value semantics.
  using RetT = decltype(Policy::shorter_interval(int{0}));

  static_assert(std::is_object_v<RetT>, "Return type should be an object type");
  static_assert(std::is_default_constructible_v<RetT>, "Return type should be default constructible");
  static_assert(std::is_copy_constructible_v<RetT> || std::is_move_constructible_v<RetT>,
                "Return type should be copyable or movable");

  // Runtime sanity: can create and store the result.
  RetT r = Policy::shorter_interval(int{123});
  (void)r;

  SUCCEED();
}

TEST(DragonboxNearestAlwaysClosedTest_374, ShorterIntervalIsConstexprEvaluable_374) {
  // Normal operation: verify the function can be evaluated in a constant expression context.
  // We avoid asserting on the value; only that it is a valid constexpr expression.
  constexpr auto r0 = Policy::shorter_interval(int{0});
  constexpr auto r1 = Policy::shorter_interval(long long{42});
  (void)r0;
  (void)r1;

  SUCCEED();
}