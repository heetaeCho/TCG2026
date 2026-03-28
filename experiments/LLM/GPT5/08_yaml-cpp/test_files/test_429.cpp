// File: dragonbox_to_decimal_test_429.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class T>
using DecayT = std::remove_cv_t<std::remove_reference_t<T>>;

// ---- Introspection helpers for common return-type layouts ----
template <class R>
constexpr bool HasSignificand() {
  return requires(R r) { r.significand; } || requires(R r) { r.mantissa; };
}

template <class R>
constexpr bool HasExponent() {
  return requires(R r) { r.exponent; } || requires(R r) { r.exp; };
}

template <class R>
constexpr bool HasNegativeFlag() {
  return requires(R r) { r.is_negative; } || requires(R r) { r.negative; } ||
         requires(R r) { r.sign; };
}

template <class R>
auto GetSignificand(const R& r) {
  if constexpr (requires { r.significand; }) {
    return r.significand;
  } else if constexpr (requires { r.mantissa; }) {
    return r.mantissa;
  } else {
    static_assert(HasSignificand<R>(), "Return type does not expose a significand-like member");
    return 0;
  }
}

template <class R>
auto GetExponent(const R& r) {
  if constexpr (requires { r.exponent; }) {
    return r.exponent;
  } else if constexpr (requires { r.exp; }) {
    return r.exp;
  } else {
    static_assert(HasExponent<R>(), "Return type does not expose an exponent-like member");
    return 0;
  }
}

template <class R>
bool GetIsNegative(const R& r) {
  if constexpr (requires { r.is_negative; }) {
    return static_cast<bool>(r.is_negative);
  } else if constexpr (requires { r.negative; }) {
    return static_cast<bool>(r.negative);
  } else if constexpr (requires { r.sign; }) {
    // Some implementations store sign as bool or +/-1.
    if constexpr (std::is_same_v<DecayT<decltype(r.sign)>, bool>) {
      return r.sign;
    } else {
      return r.sign != 0;
    }
  } else {
    static_assert(HasNegativeFlag<R>(), "Return type does not expose a sign/negative-like member");
    return false;
  }
}

template <class R>
void ExpectDecimalEqual(const R& a, const R& b) {
  if constexpr (HasSignificand<R>() && HasExponent<R>()) {
    EXPECT_EQ(GetSignificand(a), GetSignificand(b));
    EXPECT_EQ(GetExponent(a), GetExponent(b));
    if constexpr (HasNegativeFlag<R>()) {
      EXPECT_EQ(GetIsNegative(a), GetIsNegative(b));
    }
  } else if constexpr (std::is_trivially_copyable_v<R>) {
    // Fallback: compare object representation for deterministic equality.
    EXPECT_EQ(0, std::memcmp(&a, &b, sizeof(R)));
  } else {
    // As a last resort, require operator== if present.
    if constexpr (requires(R x, R y) { x == y; }) {
      EXPECT_TRUE(a == b);
    } else {
      // We cannot make stronger observable claims about R.
      SUCCEED();
    }
  }
}

template <class Float>
auto CallToDecimal(Float x) {
  return YAML::jkj::dragonbox::to_decimal(x);
}

}  // namespace

// ---------- Tests (TEST_ID suffix = 429) ----------

TEST(DragonboxToDecimalTest_429, IsNoexceptForFloatAndDouble_429) {
  static_assert(noexcept(YAML::jkj::dragonbox::to_decimal(1.0f)));
  static_assert(noexcept(YAML::jkj::dragonbox::to_decimal(1.0)));
  SUCCEED();
}

TEST(DragonboxToDecimalTest_429, DeterministicForSameInput_Float_429) {
  float x = 1.2345f;
  auto r1 = CallToDecimal(x);
  auto r2 = CallToDecimal(x);
  ExpectDecimalEqual(r1, r2);
}

TEST(DragonboxToDecimalTest_429, DeterministicForSameInput_Double_429) {
  double x = 1.23456789012345;
  auto r1 = CallToDecimal(x);
  auto r2 = CallToDecimal(x);
  ExpectDecimalEqual(r1, r2);
}

TEST(DragonboxToDecimalTest_429, WorksForRepresentativeFiniteNonZeroValues_Float_429) {
  const float values[] = {
      1.0f,
      -1.0f,
      0.1f,
      -0.1f,
      std::numeric_limits<float>::min(),      // smallest positive normal
      std::numeric_limits<float>::denorm_min(),
      std::numeric_limits<float>::max(),
  };

  for (float x : values) {
    // Contract: finite and nonzero should not assert/crash.
    ASSERT_TRUE(std::isfinite(x));
    ASSERT_NE(x, 0.0f);
    (void)CallToDecimal(x);
  }
  SUCCEED();
}

TEST(DragonboxToDecimalTest_429, WorksForRepresentativeFiniteNonZeroValues_Double_429) {
  const double values[] = {
      1.0,
      -1.0,
      0.1,
      -0.1,
      std::numeric_limits<double>::min(),      // smallest positive normal
      std::numeric_limits<double>::denorm_min(),
      std::numeric_limits<double>::max(),
  };

  for (double x : values) {
    ASSERT_TRUE(std::isfinite(x));
    ASSERT_NE(x, 0.0);
    (void)CallToDecimal(x);
  }
  SUCCEED();
}

TEST(DragonboxToDecimalTest_429, NegativeAndPositiveHaveConsistentMagnitudeWhenObservable_429) {
  // This test only asserts relationships that are observable via exposed members.
  // If the return type exposes sign + (significand, exponent), we expect |x| and |-x|
  // to match in those magnitude components, while the sign flips.
  const double x = 12345.6789;
  auto pos = CallToDecimal(x);
  auto neg = CallToDecimal(-x);

  if constexpr (HasSignificand<decltype(pos)>() && HasExponent<decltype(pos)>()) {
    EXPECT_EQ(GetSignificand(pos), GetSignificand(neg));
    EXPECT_EQ(GetExponent(pos), GetExponent(neg));
  }

  if constexpr (HasNegativeFlag<decltype(pos)>()) {
    EXPECT_NE(GetIsNegative(pos), GetIsNegative(neg));
  } else {
    SUCCEED();
  }
}

#if GTEST_HAS_DEATH_TEST
TEST(DragonboxToDecimalTest_429, AssertsOnZeroInDebug_429) {
#ifndef NDEBUG
  // The implementation has: assert(br.is_finite() && br.is_nonzero());
  EXPECT_DEATH((void)YAML::jkj::dragonbox::to_decimal(0.0f), "");
  EXPECT_DEATH((void)YAML::jkj::dragonbox::to_decimal(0.0), "");
#else
  GTEST_SKIP() << "Asserts are disabled in release (NDEBUG).";
#endif
}

TEST(DragonboxToDecimalTest_429, AssertsOnInfinityInDebug_429) {
#ifndef NDEBUG
  float inf_f = std::numeric_limits<float>::infinity();
  double inf_d = std::numeric_limits<double>::infinity();
  EXPECT_DEATH((void)YAML::jkj::dragonbox::to_decimal(inf_f), "");
  EXPECT_DEATH((void)YAML::jkj::dragonbox::to_decimal(-inf_d), "");
#else
  GTEST_SKIP() << "Asserts are disabled in release (NDEBUG).";
#endif
}

TEST(DragonboxToDecimalTest_429, AssertsOnNaNInDebug_429) {
#ifndef NDEBUG
  float nan_f = std::numeric_limits<float>::quiet_NaN();
  double nan_d = std::numeric_limits<double>::quiet_NaN();
  EXPECT_DEATH((void)YAML::jkj::dragonbox::to_decimal(nan_f), "");
  EXPECT_DEATH((void)YAML::jkj::dragonbox::to_decimal(nan_d), "");
#else
  GTEST_SKIP() << "Asserts are disabled in release (NDEBUG).";
#endif
}
#endif  // GTEST_HAS_DEATH_TEST