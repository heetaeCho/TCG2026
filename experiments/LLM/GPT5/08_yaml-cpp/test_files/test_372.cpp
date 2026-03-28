// TEST_ID: 372
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

// Adjust include if your build exposes a different include root.
#include "contrib/dragonbox.h"

namespace {

using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_away_from_zero_t;

template <typename T>
using ShorterIntervalReturnT = decltype(Policy::shorter_interval(std::declval<T>()));

template <typename, typename = void>
struct HasEquality : std::false_type {};

template <typename T>
struct HasEquality<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};

class NearestAwayFromZeroShorterIntervalTest_372 : public ::testing::Test {};

}  // namespace

TEST_F(NearestAwayFromZeroShorterIntervalTest_372, Signature_IsNoexcept_AndReturnTypeMatches_372) {
  // Verify noexcept as part of the observable interface contract.
  static_assert(noexcept(Policy::shorter_interval(std::int32_t{0})),
                "shorter_interval must be noexcept for int32_t");
  static_assert(noexcept(Policy::shorter_interval(std::int64_t{0})),
                "shorter_interval must be noexcept for int64_t");

  // Verify return type matches the declared type in the interface.
  using Expected = YAML::jkj::dragonbox::interval_type::left_closed_right_open;
  static_assert(std::is_same_v<ShorterIntervalReturnT<std::int32_t>, Expected>,
                "Return type mismatch for int32_t");
  static_assert(std::is_same_v<ShorterIntervalReturnT<std::int64_t>, Expected>,
                "Return type mismatch for int64_t");
}

TEST_F(NearestAwayFromZeroShorterIntervalTest_372, Constexpr_CallCompiles_372) {
  // If the implementation supports constexpr evaluation, this should compile.
  // (We don't assume any particular value semantics; just that it can be formed as constexpr.)
  constexpr auto r32 = Policy::shorter_interval(std::int32_t{0});
  constexpr auto r64 = Policy::shorter_interval(std::int64_t{1});

  (void)r32;
  (void)r64;

  SUCCEED();
}

TEST_F(NearestAwayFromZeroShorterIntervalTest_372, NormalInputs_DoNotThrow_AndReturnObjectsAreValid_372) {
  EXPECT_NO_THROW({
    auto r0 = Policy::shorter_interval(std::int32_t{0});
    auto r1 = Policy::shorter_interval(std::int32_t{1});
    auto rn = Policy::shorter_interval(std::int32_t{-1});
    (void)r0;
    (void)r1;
    (void)rn;
  });
}

TEST_F(NearestAwayFromZeroShorterIntervalTest_372, BoundaryInputs_DoNotThrow_372) {
  EXPECT_NO_THROW({
    auto rmin32 = Policy::shorter_interval(std::numeric_limits<std::int32_t>::min());
    auto rmax32 = Policy::shorter_interval(std::numeric_limits<std::int32_t>::max());
    auto rmin64 = Policy::shorter_interval(std::numeric_limits<std::int64_t>::min());
    auto rmax64 = Policy::shorter_interval(std::numeric_limits<std::int64_t>::max());
    (void)rmin32;
    (void)rmax32;
    (void)rmin64;
    (void)rmax64;
  });
}

TEST_F(NearestAwayFromZeroShorterIntervalTest_372, ReturnValue_CanBeComparedToDefaultIfEqualityExists_372) {
  using Ret = ShorterIntervalReturnT<std::int32_t>;
  const auto actual = Policy::shorter_interval(std::int32_t{0});

  // Only verify equality if the type supports it (keeps the test robust across implementations).
  if constexpr (HasEquality<Ret>::value) {
    const Ret expected{};
    EXPECT_TRUE(actual == expected);
  } else {
    SUCCEED();
  }
}