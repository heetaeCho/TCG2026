// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_to_even_test_357.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t;

template <class T>
using ShorterIntervalReturnT =
    decltype(Policy::shorter_interval(std::declval<T>()));

}  // namespace

// Compile-time interface checks (no runtime observability needed).
static_assert(noexcept(Policy::shorter_interval(std::int32_t{0})),
              "shorter_interval(int32_t) must be noexcept");
static_assert(noexcept(Policy::shorter_interval(std::int64_t{0})),
              "shorter_interval(int64_t) must be noexcept");
static_assert(std::is_default_constructible_v<ShorterIntervalReturnT<std::int32_t>>,
              "Return type should be default constructible (returned via {})");

TEST(DragonboxNearestToEvenTest_357, ShorterIntervalCallableWithSigned32_357) {
  const auto v = Policy::shorter_interval(std::int32_t{0});
  (void)v;
  SUCCEED();
}

TEST(DragonboxNearestToEvenTest_357, ShorterIntervalCallableWithSigned64_357) {
  const auto v = Policy::shorter_interval(std::int64_t{123});
  (void)v;
  SUCCEED();
}

TEST(DragonboxNearestToEvenTest_357, ShorterIntervalIsConstexprEvaluable_357) {
  // This verifies the function can be used in constant evaluation contexts.
  constexpr auto v = Policy::shorter_interval(std::int32_t{0});
  (void)v;
  SUCCEED();
}

TEST(DragonboxNearestToEvenTest_357, ShorterIntervalHandlesSignedBoundaryValues_357) {
  const auto v1 = Policy::shorter_interval(std::numeric_limits<std::int32_t>::min());
  const auto v2 = Policy::shorter_interval(std::numeric_limits<std::int32_t>::max());
  const auto v3 = Policy::shorter_interval(std::int32_t{-1});
  const auto v4 = Policy::shorter_interval(std::int32_t{1});
  (void)v1; (void)v2; (void)v3; (void)v4;
  SUCCEED();
}

TEST(DragonboxNearestToEvenTest_357, ShorterIntervalAcceptsDifferentIntegralTypes_357) {
  // The template parameter is unconstrained at the interface level; ensure common types work.
  const auto a = Policy::shorter_interval(short{-7});
  const auto b = Policy::shorter_interval(int{42});
  const auto c = Policy::shorter_interval(long long{999});
  (void)a; (void)b; (void)c;
  SUCCEED();
}

TEST(DragonboxNearestToEvenTest_357, ShorterIntervalReturnTypeIsConsistentAcrossCalls_357) {
  using R1 = ShorterIntervalReturnT<std::int32_t>;
  using R2 = decltype(Policy::shorter_interval(std::int32_t{17}));
  static_assert(std::is_same_v<R1, R2>, "Return type should not depend on value for same argument type");

  const auto v = Policy::shorter_interval(std::int32_t{17});
  (void)v;
  SUCCEED();
}