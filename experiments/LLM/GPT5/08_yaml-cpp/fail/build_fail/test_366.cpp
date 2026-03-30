// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_toward_minus_infinity_shorter_interval_test.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;
using Boundary = YAML::jkj::dragonbox::interval_type::asymmetric_boundary;

// Minimal test double for the template parameter expected by shorter_interval().
// Only exposes the observable interface used by the policy (is_negative()).
struct FakeSignedSignificandBits {
  bool neg{};
  constexpr bool is_negative() const noexcept { return neg; }
};

// Comparison helper that prefers public operator== if available.
// Falls back to byte-wise comparison only when the type is trivially copyable.
// (No access to private/internal state.)
template <class T>
bool BoundaryEqual(const T& a, const T& b) {
  if constexpr (requires { a == b; }) {
    return a == b;
  } else if constexpr (std::is_trivially_copyable_v<T>) {
    return std::memcmp(&a, &b, sizeof(T)) == 0;
  } else {
    // If neither equality nor safe byte-compare is available, we cannot compare.
    // In that case, tests should avoid direct equality checks.
    return false;
  }
}

}  // namespace

TEST(NearestTowardMinusInfinityShorterIntervalTest_366,
     NoexceptAndConstexprCallable_366) {
  constexpr FakeSignedSignificandBits s_pos{false};
  constexpr FakeSignedSignificandBits s_neg{true};

  static_assert(noexcept(Policy::shorter_interval(s_pos)),
                "shorter_interval(s) must be noexcept for this SignedSignificandBits type.");
  static_assert(noexcept(Policy::shorter_interval(s_neg)),
                "shorter_interval(s) must be noexcept for this SignedSignificandBits type.");

  // Ensure it is usable in a constant-evaluated context (observable via compilation).
  constexpr Boundary b_pos = Policy::shorter_interval(s_pos);
  constexpr Boundary b_neg = Policy::shorter_interval(s_neg);
  (void)b_pos;
  (void)b_neg;

  SUCCEED();
}

TEST(NearestTowardMinusInfinityShorterIntervalTest_366,
     ReturnsBoundaryConsistentWithIsNegative_366) {
  FakeSignedSignificandBits s_pos{false};
  FakeSignedSignificandBits s_neg{true};

  const Boundary b_pos = Policy::shorter_interval(s_pos);
  const Boundary b_neg = Policy::shorter_interval(s_neg);

  // If the boundary type is comparable (or trivially copyable), the result should
  // differ when the sign differs.
  const bool comparable_or_memcmp =
      (requires { b_pos == b_neg; }) || std::is_trivially_copyable_v<Boundary>;

  if (comparable_or_memcmp) {
    EXPECT_FALSE(BoundaryEqual(b_pos, b_neg));
  } else {
    // If we cannot compare boundaries, at least ensure calls succeed.
    SUCCEED();
  }
}

TEST(NearestTowardMinusInfinityShorterIntervalTest_366,
     DeterministicForSameInput_366) {
  FakeSignedSignificandBits s1{false};
  FakeSignedSignificandBits s2{false};

  const Boundary b1 = Policy::shorter_interval(s1);
  const Boundary b2 = Policy::shorter_interval(s2);

  const bool comparable_or_memcmp =
      (requires { b1 == b2; }) || std::is_trivially_copyable_v<Boundary>;

  if (comparable_or_memcmp) {
    EXPECT_TRUE(BoundaryEqual(b1, b2));
  } else {
    SUCCEED();
  }
}

TEST(NearestTowardMinusInfinityShorterIntervalTest_366,
     MatchesDirectConstructionIfComparable_366) {
  FakeSignedSignificandBits s_pos{false};
  FakeSignedSignificandBits s_neg{true};

  const Boundary b_pos = Policy::shorter_interval(s_pos);
  const Boundary b_neg = Policy::shorter_interval(s_neg);

  // Validate against the publicly constructible boundary form used by the interface.
  // This relies only on public construction and public equality (or safe memcmp).
  const Boundary expected_pos{false};
  const Boundary expected_neg{true};

  const bool comparable_or_memcmp =
      (requires { b_pos == expected_pos; }) || std::is_trivially_copyable_v<Boundary>;

  if (comparable_or_memcmp) {
    EXPECT_TRUE(BoundaryEqual(b_pos, expected_pos));
    EXPECT_TRUE(BoundaryEqual(b_neg, expected_neg));
  } else {
    SUCCEED();
  }
}