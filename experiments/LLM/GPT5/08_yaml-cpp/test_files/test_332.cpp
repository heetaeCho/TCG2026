// TEST_ID: 332
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

namespace db = YAML::jkj::dragonbox;

template <class CacheEntry>
auto High64(const CacheEntry& e) -> std::uint64_t {
  return static_cast<std::uint64_t>(e.high());
}
template <class CacheEntry>
auto Low64(const CacheEntry& e) -> std::uint64_t {
  return static_cast<std::uint64_t>(e.low());
}

template <class Holder, class DecExpT>
static DecExpT PickInRange(DecExpT v) {
  if constexpr (requires { Holder::min_k; Holder::max_k; }) {
    const auto min_k = static_cast<DecExpT>(Holder::min_k);
    const auto max_k = static_cast<DecExpT>(Holder::max_k);
    if (v < min_k) return min_k;
    if (v > max_k) return max_k;
    return v;
  } else {
    // Fallback: keep the value as-is (tests below use conservative values).
    return v;
  }
}

template <class Holder, class ShiftT, class DecExpT>
static void ExpectDeterministicForK(DecExpT k) {
  // Black-box determinism: same input => same output.
  const auto a = Holder::template get_cache<ShiftT, DecExpT>(k);
  const auto b = Holder::template get_cache<ShiftT, DecExpT>(k);

  EXPECT_EQ(High64(a), High64(b));
  EXPECT_EQ(Low64(a), Low64(b));
}

template <class Holder>
static void RunCommonPropertyTestsForHolder() {
  using ShiftA = std::uint32_t;
  using ShiftB = std::uint8_t;

  // Prefer using Holder's declared range when available; otherwise use conservative k values.
  const int k0 = PickInRange<Holder, int>(0);
  const int k1 = PickInRange<Holder, int>(1);
  const int km1 = PickInRange<Holder, int>(-1);

  // noexcept is an observable part of the interface contract.
  static_assert(noexcept(Holder::template get_cache<ShiftA, int>(k0)),
                "get_cache must be noexcept for tested instantiation");

  // Determinism for representative ks.
  ExpectDeterministicForK<Holder, ShiftA, int>(k0);
  ExpectDeterministicForK<Holder, ShiftA, int>(k1);
  ExpectDeterministicForK<Holder, ShiftA, int>(km1);

  // Determinism should not depend on ShiftAmountType choice.
  ExpectDeterministicForK<Holder, ShiftB, int>(k0);
  ExpectDeterministicForK<Holder, ShiftB, int>(k1);
  ExpectDeterministicForK<Holder, ShiftB, int>(km1);

  // Consistency across DecimalExponentType widths for the same numeric k.
  const auto c_i32 =
      Holder::template get_cache<ShiftA, std::int32_t>(static_cast<std::int32_t>(k0));
  const auto c_i64 =
      Holder::template get_cache<ShiftA, std::int64_t>(static_cast<std::int64_t>(k0));
  EXPECT_EQ(High64(c_i32), High64(c_i64));
  EXPECT_EQ(Low64(c_i32), Low64(c_i64));

  // Boundary-focused checks when min_k/max_k are available.
  if constexpr (requires { Holder::min_k; Holder::max_k; }) {
    using DecT = decltype(Holder::min_k);
    const auto min_k = static_cast<DecT>(Holder::min_k);
    const auto max_k = static_cast<DecT>(Holder::max_k);

    // Exact boundaries should be callable and deterministic.
    ExpectDeterministicForK<Holder, ShiftA, DecT>(min_k);
    ExpectDeterministicForK<Holder, ShiftA, DecT>(max_k);

    // Near-boundaries (avoid overflow when range is tiny).
    if (min_k < max_k) {
      ExpectDeterministicForK<Holder, ShiftA, DecT>(static_cast<DecT>(min_k + 1));
      ExpectDeterministicForK<Holder, ShiftA, DecT>(static_cast<DecT>(max_k - 1));
    }
  }
}

}  // namespace

// These tests assume the dragonbox header provides ieee754 formats in detail and a cache holder
// for them, which is the typical integration pattern in this codebase.

TEST(DragonboxGetCacheTest_332, DoubleFormat_PropertiesAndBoundaries_332) {
  using Holder =
      db::compressed_cache_holder<db::detail::ieee754_binary64, void>;
  RunCommonPropertyTestsForHolder<Holder>();
}

TEST(DragonboxGetCacheTest_332, FloatFormat_PropertiesAndBoundaries_332) {
  using Holder =
      db::compressed_cache_holder<db::detail::ieee754_binary32, void>;
  RunCommonPropertyTestsForHolder<Holder>();
}

TEST(DragonboxGetCacheTest_332, DifferentShiftTypesSameKProduceStableResults_332) {
  using Holder =
      db::compressed_cache_holder<db::detail::ieee754_binary64, void>;

  const int k = PickInRange<Holder, int>(0);

  const auto a = Holder::template get_cache<std::uint32_t, int>(k);
  const auto b = Holder::template get_cache<std::uint8_t, int>(k);

  // Observable contract: cache entry should be a pure function of k (shift type should not change it).
  EXPECT_EQ(High64(a), High64(b));
  EXPECT_EQ(Low64(a), Low64(b));
}

TEST(DragonboxGetCacheTest_332, MultipleCallsAcrossManyKsAreDeterministic_332) {
  using Holder =
      db::compressed_cache_holder<db::detail::ieee754_binary64, void>;

  // Exercise a small set of ks that are either within the holder's known range or clamped to it.
  const int ks[] = {
      PickInRange<Holder, int>(-10),
      PickInRange<Holder, int>(-1),
      PickInRange<Holder, int>(0),
      PickInRange<Holder, int>(1),
      PickInRange<Holder, int>(10),
  };

  for (int k : ks) {
    const auto x1 = Holder::template get_cache<std::uint32_t, int>(k);
    const auto x2 = Holder::template get_cache<std::uint32_t, int>(k);
    const auto x3 = Holder::template get_cache<std::uint32_t, int>(k);

    EXPECT_EQ(High64(x1), High64(x2));
    EXPECT_EQ(Low64(x1), Low64(x2));
    EXPECT_EQ(High64(x2), High64(x3));
    EXPECT_EQ(Low64(x2), Low64(x3));
  }
}