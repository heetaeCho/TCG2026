// File: dragonbox_compressed_cache_holder_test_330.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// --- Detection helpers (avoid assuming internal layout) ----------------------

template <class T>
concept HasMinK = requires { T::min_k; };

template <class T>
concept HasMaxK = requires { T::max_k; };

template <class T>
concept HasCacheHolderMinK = requires { cache_holder<T>::min_k; };

template <class T>
concept HasCacheHolderMaxK = requires { cache_holder<T>::max_k; };

template <class Holder, class FloatFormat>
constexpr auto MinK() {
  if constexpr (HasMinK<Holder>) {
    return Holder::min_k;
  } else if constexpr (HasCacheHolderMinK<FloatFormat>) {
    return cache_holder<FloatFormat>::min_k;
  } else {
    // If neither is exposed publicly, we cannot safely pick a boundary value.
    // Returning 0 lets compilation proceed, and tests that depend on boundaries
    // will be conditionally skipped via constexpr checks below.
    return 0;
  }
}

template <class Holder, class FloatFormat>
constexpr auto MaxK() {
  if constexpr (HasMaxK<Holder>) {
    return Holder::max_k;
  } else if constexpr (HasCacheHolderMaxK<FloatFormat>) {
    return cache_holder<FloatFormat>::max_k;
  } else {
    return 0;
  }
}

template <class Holder, class ShiftAmountType, class DecimalExponentType>
concept CanGetCache = requires(DecimalExponentType k) {
  { Holder::template get_cache<ShiftAmountType, DecimalExponentType>(k) };
};

template <class Holder, class ShiftAmountType, class DecimalExponentType>
concept GetCacheIsNoexcept = requires(DecimalExponentType k) {
  {
    Holder::template get_cache<ShiftAmountType, DecimalExponentType>(k)
  } noexcept;
};

}  // namespace

// NOTE:
// We intentionally do NOT assume any particular FloatFormat names beyond the
// fact that the header defines some usable FloatFormat for dragonbox caches.
// In typical dragonbox integrations, these are commonly named like
// `ieee754_binary32` and `ieee754_binary64`. We try both when available.

namespace {

template <class FloatFormat>
struct CompressedCacheHolderTestTypes_330 {
  using Format = FloatFormat;
  using Holder = compressed_cache_holder<Format, void>;
  using Shift = std::uint32_t;
  using Exp = int;
};

template <class T>
concept HasBinary32 = requires { typename T::ieee754_binary32; };

template <class T>
concept HasBinary64 = requires { typename T::ieee754_binary64; };

// Some dragonbox ports place formats directly in the namespace (not nested).
template <class = void>
concept HasIeee754Binary32 = requires { typename ::YAML::jkj::dragonbox::ieee754_binary32; };

template <class = void>
concept HasIeee754Binary64 = requires { typename ::YAML::jkj::dragonbox::ieee754_binary64; };

}  // namespace

// ---------------------- Tests for ieee754_binary32 ---------------------------

#if HasIeee754Binary32<>
using Format32_330 = ::YAML::jkj::dragonbox::ieee754_binary32;
using Types32_330 = CompressedCacheHolderTestTypes_330<Format32_330>;

TEST(CompressedCacheHolderTest_330, GetCacheIsCallableForBinary32_330) {
  static_assert(CanGetCache<typename Types32_330::Holder, typename Types32_330::Shift,
                            typename Types32_330::Exp>);
  SUCCEED();
}

TEST(CompressedCacheHolderTest_330, GetCacheIsNoexceptForBinary32_330) {
  static_assert(GetCacheIsNoexcept<typename Types32_330::Holder, typename Types32_330::Shift,
                                   typename Types32_330::Exp>);
  SUCCEED();
}

TEST(CompressedCacheHolderTest_330, GetCacheIsConstexprUsableForBinary32_330) {
  using Holder = typename Types32_330::Holder;
  using Shift = typename Types32_330::Shift;
  using Exp = typename Types32_330::Exp;

  constexpr Exp k = MinK<Holder, Format32_330>();
  // This statement must be constant-evaluable if get_cache is constexpr.
  constexpr auto entry = Holder::template get_cache<Shift, Exp>(k);
  (void)entry;

  SUCCEED();
}

TEST(CompressedCacheHolderTest_330, GetCacheIsDeterministicForSameK_Binary32_330) {
  using Holder = typename Types32_330::Holder;
  using Shift = typename Types32_330::Shift;
  using Exp = typename Types32_330::Exp;

  constexpr Exp k = MinK<Holder, Format32_330>();
  const auto a = Holder::template get_cache<Shift, Exp>(k);
  const auto b = Holder::template get_cache<Shift, Exp>(k);

  // Black-box expectation: calling the same pure accessor twice with the same
  // input should yield the same value.
  EXPECT_EQ(a, b);
}

TEST(CompressedCacheHolderTest_330, GetCacheWorksAtMinKAndMaxK_Binary32_330) {
  using Holder = typename Types32_330::Holder;
  using Shift = typename Types32_330::Shift;
  using Exp = typename Types32_330::Exp;

  constexpr Exp min_k = MinK<Holder, Format32_330>();
  constexpr Exp max_k = MaxK<Holder, Format32_330>();

  if constexpr ((min_k != 0) || HasMinK<Holder> || HasCacheHolderMinK<Format32_330>) {
    // We can at least call min_k safely when it's exposed.
    const auto e_min = Holder::template get_cache<Shift, Exp>(min_k);
    (void)e_min;
    SUCCEED();
  } else {
    GTEST_SKIP() << "min_k is not exposed publicly; cannot select a safe boundary exponent.";
  }

  if constexpr ((max_k != 0) || HasMaxK<Holder> || HasCacheHolderMaxK<Format32_330>) {
    const auto e_max = Holder::template get_cache<Shift, Exp>(max_k);
    (void)e_max;
    SUCCEED();
  } else {
    GTEST_SKIP() << "max_k is not exposed publicly; cannot select a safe boundary exponent.";
  }
}

TEST(CompressedCacheHolderTest_330, GetCacheDifferentInputsAreCallable_Binary32_330) {
  using Holder = typename Types32_330::Holder;
  using Shift = typename Types32_330::Shift;
  using Exp = typename Types32_330::Exp;

  constexpr Exp min_k = MinK<Holder, Format32_330>();
  constexpr Exp max_k = MaxK<Holder, Format32_330>();

  // Only do a second call with a different k if we can form a plausible in-range value.
  if constexpr ((HasMinK<Holder> || HasCacheHolderMinK<Format32_330>) &&
                (HasMaxK<Holder> || HasCacheHolderMaxK<Format32_330>) && (min_k < max_k)) {
    const auto a = Holder::template get_cache<Shift, Exp>(min_k);
    const auto b = Holder::template get_cache<Shift, Exp>(min_k + 1);
    (void)a;
    (void)b;
    SUCCEED();
  } else {
    // If range is not known, we avoid guessing an exponent (could be UB).
    GTEST_SKIP() << "Range [min_k, max_k] not available; cannot safely test multiple distinct k values.";
  }
}
#endif  // HasIeee754Binary32<>

// ---------------------- Tests for ieee754_binary64 ---------------------------

#if HasIeee754Binary64<>
using Format64_330 = ::YAML::jkj::dragonbox::ieee754_binary64;
using Types64_330 = CompressedCacheHolderTestTypes_330<Format64_330>;

TEST(CompressedCacheHolderTest_330, GetCacheIsCallableForBinary64_330) {
  static_assert(CanGetCache<typename Types64_330::Holder, typename Types64_330::Shift,
                            typename Types64_330::Exp>);
  SUCCEED();
}

TEST(CompressedCacheHolderTest_330, GetCacheIsNoexceptForBinary64_330) {
  static_assert(GetCacheIsNoexcept<typename Types64_330::Holder, typename Types64_330::Shift,
                                   typename Types64_330::Exp>);
  SUCCEED();
}

TEST(CompressedCacheHolderTest_330, GetCacheIsConstexprUsableForBinary64_330) {
  using Holder = typename Types64_330::Holder;
  using Shift = typename Types64_330::Shift;
  using Exp = typename Types64_330::Exp;

  constexpr Exp k = MinK<Holder, Format64_330>();
  constexpr auto entry = Holder::template get_cache<Shift, Exp>(k);
  (void)entry;

  SUCCEED();
}

TEST(CompressedCacheHolderTest_330, GetCacheIsDeterministicForSameK_Binary64_330) {
  using Holder = typename Types64_330::Holder;
  using Shift = typename Types64_330::Shift;
  using Exp = typename Types64_330::Exp;

  constexpr Exp k = MinK<Holder, Format64_330>();
  const auto a = Holder::template get_cache<Shift, Exp>(k);
  const auto b = Holder::template get_cache<Shift, Exp>(k);

  EXPECT_EQ(a, b);
}

TEST(CompressedCacheHolderTest_330, GetCacheWorksAtMinKAndMaxK_Binary64_330) {
  using Holder = typename Types64_330::Holder;
  using Shift = typename Types64_330::Shift;
  using Exp = typename Types64_330::Exp;

  constexpr Exp min_k = MinK<Holder, Format64_330>();
  constexpr Exp max_k = MaxK<Holder, Format64_330>();

  if constexpr ((min_k != 0) || HasMinK<Holder> || HasCacheHolderMinK<Format64_330>) {
    const auto e_min = Holder::template get_cache<Shift, Exp>(min_k);
    (void)e_min;
    SUCCEED();
  } else {
    GTEST_SKIP() << "min_k is not exposed publicly; cannot select a safe boundary exponent.";
  }

  if constexpr ((max_k != 0) || HasMaxK<Holder> || HasCacheHolderMaxK<Format64_330>) {
    const auto e_max = Holder::template get_cache<Shift, Exp>(max_k);
    (void)e_max;
    SUCCEED();
  } else {
    GTEST_SKIP() << "max_k is not exposed publicly; cannot select a safe boundary exponent.";
  }
}

TEST(CompressedCacheHolderTest_330, GetCacheDifferentInputsAreCallable_Binary64_330) {
  using Holder = typename Types64_330::Holder;
  using Shift = typename Types64_330::Shift;
  using Exp = typename Types64_330::Exp;

  constexpr Exp min_k = MinK<Holder, Format64_330>();
  constexpr Exp max_k = MaxK<Holder, Format64_330>();

  if constexpr ((HasMinK<Holder> || HasCacheHolderMinK<Format64_330>) &&
                (HasMaxK<Holder> || HasCacheHolderMaxK<Format64_330>) && (min_k < max_k)) {
    const auto a = Holder::template get_cache<Shift, Exp>(min_k);
    const auto b = Holder::template get_cache<Shift, Exp>(min_k + 1);
    (void)a;
    (void)b;
    SUCCEED();
  } else {
    GTEST_SKIP() << "Range [min_k, max_k] not available; cannot safely test multiple distinct k values.";
  }
}
#endif  // HasIeee754Binary64<>

// ---------------------- Fallback if no known formats exist -------------------

#if !HasIeee754Binary32<> && !HasIeee754Binary64<>
TEST(CompressedCacheHolderTest_330, NoKnownFloatFormatsAvailable_330) {
  GTEST_SKIP()
      << "No known FloatFormat types (ieee754_binary32/ieee754_binary64) are visible in this build; "
         "cannot instantiate compressed_cache_holder tests.";
}
#endif