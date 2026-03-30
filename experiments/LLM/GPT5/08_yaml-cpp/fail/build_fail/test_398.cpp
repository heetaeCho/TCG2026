// File: test_compute_mul_398.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

// The provided snippet shows an unusually repeated namespace nesting.
// We follow it exactly to reach the function under test.
namespace db = ::YAML::jkj::dragonbox::jkj::dragonbox::jkj::dragonbox::jkj::dragonbox;
namespace wuint = db::detail::wuint;

class ComputeMulTest_398 : public ::testing::Test {};

// Helper: create a cache entry in a way that is robust to aggregate vs non-aggregate types.
// If the type is aggregate, brace-initialize with two 64-bit values (common for Dragonbox caches).
// Otherwise, fall back to value-initialization.
template <class CacheEntry>
CacheEntry MakeCacheEntry(std::uint_least64_t a, std::uint_least64_t b) {
  if constexpr (std::is_aggregate_v<CacheEntry>) {
    return CacheEntry{a, b};
  } else {
    (void)a;
    (void)b;
    return CacheEntry{};
  }
}

TEST_F(ComputeMulTest_398, IsNoexcept_398) {
  using carrier_uint = decltype(wuint::carrier_uint{});
  using cache_entry_type = wuint::cache_entry_type;

  cache_entry_type cache = MakeCacheEntry<cache_entry_type>(0, 0);
  carrier_uint u = carrier_uint{0};

  static_assert(noexcept(wuint::compute_mul(u, cache)),
                "compute_mul is expected to be noexcept (per signature).");
  (void)cache;
  (void)u;
}

TEST_F(ComputeMulTest_398, MatchesUmul192Upper128ForZeroCache_398) {
  using carrier_uint = decltype(wuint::carrier_uint{});
  using cache_entry_type = wuint::cache_entry_type;

  const cache_entry_type cache = MakeCacheEntry<cache_entry_type>(0, 0);

  const carrier_uint inputs[] = {
      carrier_uint{0},
      carrier_uint{1},
      carrier_uint{2},
      std::numeric_limits<carrier_uint>::max(),
  };

  for (carrier_uint u : inputs) {
    const auto r = wuint::umul192_upper128(u, cache);
    const auto out = wuint::compute_mul(u, cache);

    // compute_mul_result is constructed as { r.high(), r.low() == 0 } in the snippet.
    // We avoid depending on member names by using structured binding.
    const auto [out_high, out_low_is_zero] = out;

    EXPECT_EQ(out_high, r.high()) << "u=" << static_cast<unsigned long long>(u);
    EXPECT_EQ(out_low_is_zero, (r.low() == 0))
        << "u=" << static_cast<unsigned long long>(u);
  }
}

TEST_F(ComputeMulTest_398, MatchesUmul192Upper128ForNonZeroCache_398) {
  using carrier_uint = decltype(wuint::carrier_uint{});
  using cache_entry_type = wuint::cache_entry_type;

  // Use non-trivial values to exercise more paths without assuming internal math details.
  const cache_entry_type cache =
      MakeCacheEntry<cache_entry_type>(std::uint_least64_t{0x0123456789abcdefULL},
                                       std::uint_least64_t{0xfedcba9876543210ULL});

  const carrier_uint inputs[] = {
      carrier_uint{0},
      carrier_uint{1},
      carrier_uint{12345},
      std::numeric_limits<carrier_uint>::max(),
  };

  for (carrier_uint u : inputs) {
    const auto r = wuint::umul192_upper128(u, cache);
    const auto out = wuint::compute_mul(u, cache);

    const auto [out_high, out_low_is_zero] = out;

    EXPECT_EQ(out_high, r.high()) << "u=" << static_cast<unsigned long long>(u);
    EXPECT_EQ(out_low_is_zero, (r.low() == 0))
        << "u=" << static_cast<unsigned long long>(u);
  }
}

TEST_F(ComputeMulTest_398, LowZeroFlagIsConsistentAcrossDifferentCaches_398) {
  using carrier_uint = decltype(wuint::carrier_uint{});
  using cache_entry_type = wuint::cache_entry_type;

  const cache_entry_type cache_a = MakeCacheEntry<cache_entry_type>(0, 0);
  const cache_entry_type cache_b =
      MakeCacheEntry<cache_entry_type>(std::uint_least64_t{0xffffffffffffffffULL},
                                       std::uint_least64_t{1ULL});

  // Pick a couple of values, including boundaries.
  const carrier_uint inputs[] = {
      carrier_uint{0},
      carrier_uint{1},
      std::numeric_limits<carrier_uint>::max(),
  };

  for (carrier_uint u : inputs) {
    const auto r_a = wuint::umul192_upper128(u, cache_a);
    const auto r_b = wuint::umul192_upper128(u, cache_b);

    const auto [out_high_a, out_low_is_zero_a] = wuint::compute_mul(u, cache_a);
    const auto [out_high_b, out_low_is_zero_b] = wuint::compute_mul(u, cache_b);

    // Verify wrapper correctness independently for each cache.
    EXPECT_EQ(out_high_a, r_a.high()) << "u=" << static_cast<unsigned long long>(u);
    EXPECT_EQ(out_low_is_zero_a, (r_a.low() == 0))
        << "u=" << static_cast<unsigned long long>(u);

    EXPECT_EQ(out_high_b, r_b.high()) << "u=" << static_cast<unsigned long long>(u);
    EXPECT_EQ(out_low_is_zero_b, (r_b.low() == 0))
        << "u=" << static_cast<unsigned long long>(u);
  }
}

TEST_F(ComputeMulTest_398, CanBeCalledInConstexprContextWhenSupported_398) {
  using carrier_uint = decltype(wuint::carrier_uint{});
  using cache_entry_type = wuint::cache_entry_type;

#if defined(__cpp_constexpr) && (__cpp_constexpr >= 201907L)
  // JKJ_CONSTEXPR20 suggests this may be intended to be constexpr in C++20.
  // This test is written to compile even if the compiler/library disables constexpr here:
  // it only *attempts* constexpr evaluation when the toolchain supports it.
  constexpr cache_entry_type cache = MakeCacheEntry<cache_entry_type>(0, 0);
  constexpr carrier_uint u = carrier_uint{1};

  constexpr auto out = wuint::compute_mul(u, cache);
  (void)out;
#else
  SUCCEED();
#endif
}

}  // namespace