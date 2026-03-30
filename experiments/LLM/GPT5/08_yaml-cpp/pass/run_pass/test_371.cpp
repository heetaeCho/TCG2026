// File: ./TestProjects/yaml-cpp/test/dragonbox_policy_nearest_away_from_zero_test_371.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Fixture name includes TEST_ID per requirement.
class DragonboxNearestAwayFromZeroPolicyTest_371 : public ::testing::Test {};

using Policy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_away_from_zero_t;

template <class T>
constexpr bool IsNoexceptCallableFor(T v) {
  return noexcept(Policy::normal_interval(v));
}

template <class T>
using NormalIntervalReturnT = decltype(Policy::normal_interval(std::declval<T>()));

}  // namespace

TEST_F(DragonboxNearestAwayFromZeroPolicyTest_371, NormalInterval_IsCallableForCommonSignedIntegers_371) {
  // Normal operation: just verify the API is usable for typical signed types.
  (void)Policy::normal_interval(static_cast<int>(0));
  (void)Policy::normal_interval(static_cast<int>(1));
  (void)Policy::normal_interval(static_cast<long>(-1));
  (void)Policy::normal_interval(static_cast<long long>(42));
  (void)Policy::normal_interval(static_cast<std::int32_t>(-123));
  (void)Policy::normal_interval(static_cast<std::int64_t>(123456789));
  SUCCEED();
}

TEST_F(DragonboxNearestAwayFromZeroPolicyTest_371, NormalInterval_IsCallableOnBoundaryValues_371) {
  // Boundary conditions: min/max/zero for representative signed integer types.
  (void)Policy::normal_interval(std::numeric_limits<int>::min());
  (void)Policy::normal_interval(std::numeric_limits<int>::max());
  (void)Policy::normal_interval(0);

  (void)Policy::normal_interval(std::numeric_limits<long long>::min());
  (void)Policy::normal_interval(std::numeric_limits<long long>::max());
  SUCCEED();
}

TEST_F(DragonboxNearestAwayFromZeroPolicyTest_371, NormalInterval_IsNoexcept_371) {
  // Exceptional/error behavior observable through the interface: it is declared noexcept.
  static_assert(IsNoexceptCallableFor<int>(0), "normal_interval(int) must be noexcept");
  static_assert(IsNoexceptCallableFor<long long>(-1), "normal_interval(long long) must be noexcept");

  // Also check at runtime (redundant but keeps the intent visible in test output).
  EXPECT_TRUE((noexcept(Policy::normal_interval(0))));
  EXPECT_TRUE((noexcept(Policy::normal_interval(-1LL))));
}

TEST_F(DragonboxNearestAwayFromZeroPolicyTest_371, NormalInterval_ReturnTypeIsStableAcrossInputs_371) {
  // Observable behavior: same static function, same template argument => same return type.
  using R1 = NormalIntervalReturnT<int>;
  using R2 = decltype(Policy::normal_interval(123));
  static_assert(std::is_same_v<R1, R2>, "Return type should not depend on the value");

  // Across different *SignedSignificandBits* types, return type might or might not differ
  // depending on the library definition; we avoid assuming equality across T.
  (void)Policy::normal_interval(0);
  (void)Policy::normal_interval(0LL);
  SUCCEED();
}

TEST_F(DragonboxNearestAwayFromZeroPolicyTest_371, NormalInterval_IsUsableInConstantEvaluation_371) {
  // The function is declared constexpr; verify it can be used in a constant-evaluated context.
  // We avoid making any assumptions about the returned object's fields or equality semantics.
  constexpr auto r0 = Policy::normal_interval(0);
  constexpr auto r1 = Policy::normal_interval(1);

  (void)r0;
  (void)r1;
  SUCCEED();
}