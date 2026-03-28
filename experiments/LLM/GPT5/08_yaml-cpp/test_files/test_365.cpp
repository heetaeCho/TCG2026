// File: test_nearest_toward_minus_infinity_normal_interval_365.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class>
inline constexpr bool kDependentFalse = false;

// Extract an observable "is negative" flag from interval_type::asymmetric_boundary
// without relying on private/internal state. We only read public fields / conversions
// if they exist; otherwise we fail at compile time.
template <class Boundary>
constexpr bool BoundaryIsNegative(const Boundary& b) {
  if constexpr (requires { b.is_negative; }) {
    return static_cast<bool>(b.is_negative);
  } else if constexpr (requires { b.is_negative_; }) {
    return static_cast<bool>(b.is_negative_);
  } else if constexpr (requires { b.negative; }) {
    return static_cast<bool>(b.negative);
  } else if constexpr (std::is_convertible_v<Boundary, bool>) {
    return static_cast<bool>(b);
  } else {
    static_assert(kDependentFalse<Boundary>,
                  "Cannot observe negativity flag from asymmetric_boundary via public interface.");
    return false;
  }
}

// Minimal SignedSignificandBits test doubles used only through the required interface.
struct FakeSignedSignificandBitsBool {
  bool neg{};
  constexpr bool is_negative() const noexcept { return neg; }
};

struct FakeSignedSignificandBitsInt {
  int sign{};  // negative => < 0
  constexpr bool is_negative() const noexcept { return sign < 0; }
};

}  // namespace

TEST(NearestTowardMinusInfinityPolicyTest_365, NormalInterval_PositiveSignYieldsNonNegativeBoundary_365) {
  using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;

  constexpr FakeSignedSignificandBitsBool s{false};
  constexpr auto boundary = Policy::normal_interval(s);

  EXPECT_FALSE(BoundaryIsNegative(boundary));
}

TEST(NearestTowardMinusInfinityPolicyTest_365, NormalInterval_NegativeSignYieldsNegativeBoundary_365) {
  using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;

  constexpr FakeSignedSignificandBitsBool s{true};
  constexpr auto boundary = Policy::normal_interval(s);

  EXPECT_TRUE(BoundaryIsNegative(boundary));
}

TEST(NearestTowardMinusInfinityPolicyTest_365, NormalInterval_WorksWithDifferentSignedSignificandBitsType_365) {
  using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;

  constexpr FakeSignedSignificandBitsInt pos{+1};
  constexpr FakeSignedSignificandBitsInt neg{-1};

  constexpr auto b_pos = Policy::normal_interval(pos);
  constexpr auto b_neg = Policy::normal_interval(neg);

  EXPECT_FALSE(BoundaryIsNegative(b_pos));
  EXPECT_TRUE(BoundaryIsNegative(b_neg));
}

TEST(NearestTowardMinusInfinityPolicyTest_365, NormalInterval_IsNoexcept_365) {
  using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;

  constexpr FakeSignedSignificandBitsBool s{false};
  static_assert(noexcept(Policy::normal_interval(s)),
                "normal_interval(s) is expected to be noexcept per its interface.");

  // Also execute once at runtime.
  (void)Policy::normal_interval(s);
}

TEST(NearestTowardMinusInfinityPolicyTest_365, NormalInterval_IsConstexprEvaluatable_365) {
  using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;

  constexpr FakeSignedSignificandBitsBool s_neg{true};
  constexpr auto boundary = Policy::normal_interval(s_neg);

  static_assert(BoundaryIsNegative(boundary),
                "normal_interval should be constexpr-evaluatable and reflect the sign.");
  EXPECT_TRUE(BoundaryIsNegative(boundary));
}