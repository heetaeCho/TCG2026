// TEST_ID: 393
// File: test_dragonbox_compute_delta_393.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

// The provided snippet shows duplicated namespaces:
// YAML::jkj::dragonbox::jkj::dragonbox
namespace dragonbox_ns = YAML::jkj::dragonbox::jkj::dragonbox;

// Detect presence of `cache_bits` (some dragonbox headers expose it).
template <typename T, typename = void>
struct has_cache_bits : std::false_type {};
template <typename T>
struct has_cache_bits<T, std::void_t<decltype(T::cache_bits)>> : std::true_type {};

// Detect presence of `cache_entry_type` (expected to exist in the namespace).
template <typename T, typename = void>
struct has_cache_entry_type : std::false_type {};
template <typename T>
struct has_cache_entry_type<T, std::void_t<typename T::cache_entry_type>> : std::true_type {};

class ComputeDeltaTest_393 : public ::testing::Test {};

}  // namespace

TEST_F(ComputeDeltaTest_393, IsCallableAndReturnTypeIsUintLeast64_393) {
  static_assert(has_cache_entry_type<dragonbox_ns>::value,
                "dragonbox_ns::cache_entry_type must exist for this test.");

  using Cache = typename dragonbox_ns::cache_entry_type;

  Cache cache{};
  auto out = dragonbox_ns::compute_delta(cache, 0);

  // Verify the observable return type.
  EXPECT_TRUE((std::is_same<decltype(out), std::uint_least64_t>::value));
}

TEST_F(ComputeDeltaTest_393, IsNoexcept_393) {
  static_assert(has_cache_entry_type<dragonbox_ns>::value,
                "dragonbox_ns::cache_entry_type must exist for this test.");

  using Cache = typename dragonbox_ns::cache_entry_type;
  Cache cache{};

  // The interface declares noexcept; verify it's actually noexcept.
  EXPECT_TRUE(noexcept(dragonbox_ns::compute_delta(cache, 0)));
}

TEST_F(ComputeDeltaTest_393, CanBeUsedInConstexprContext_393) {
  static_assert(has_cache_entry_type<dragonbox_ns>::value,
                "dragonbox_ns::cache_entry_type must exist for this test.");

  using Cache = typename dragonbox_ns::cache_entry_type;

  // If Cache is an integral-like type (typical for dragonbox), this should compile.
  // We keep the assertion minimal and only rely on the "all-zero input -> all-zero output"
  // property (safe for bitwise/arithmetic style implementations).
  constexpr Cache cache0 = Cache{0};
  constexpr std::uint_least64_t out0 =
      dragonbox_ns::compute_delta(cache0, 0);
  static_assert(out0 == 0, "Expected zero output for zero cache input.");
  (void)out0;

  SUCCEED();
}

TEST_F(ComputeDeltaTest_393, SameInputsProduceSameOutput_393) {
  static_assert(has_cache_entry_type<dragonbox_ns>::value,
                "dragonbox_ns::cache_entry_type must exist for this test.");

  using Cache = typename dragonbox_ns::cache_entry_type;

  Cache cache = Cache{0};
  auto a = dragonbox_ns::compute_delta(cache, 0);
  auto b = dragonbox_ns::compute_delta(cache, 0);

  EXPECT_EQ(a, b);
}

TEST_F(ComputeDeltaTest_393, SupportsDifferentShiftAmountTypes_393) {
  static_assert(has_cache_entry_type<dragonbox_ns>::value,
                "dragonbox_ns::cache_entry_type must exist for this test.");

  using Cache = typename dragonbox_ns::cache_entry_type;

  Cache cache{};
  // The template parameter is ShiftAmountType; ensure common integer types work.
  auto a = dragonbox_ns::compute_delta(cache, int{0});
  auto b = dragonbox_ns::compute_delta(cache, unsigned{0});
  auto c = dragonbox_ns::compute_delta(cache, std::uint32_t{0});

  EXPECT_TRUE((std::is_same<decltype(a), std::uint_least64_t>::value));
  EXPECT_TRUE((std::is_same<decltype(b), std::uint_least64_t>::value));
  EXPECT_TRUE((std::is_same<decltype(c), std::uint_least64_t>::value));

  // All are for zero cache, should all be zero.
  EXPECT_EQ(a, 0u);
  EXPECT_EQ(b, 0u);
  EXPECT_EQ(c, 0u);
}

TEST_F(ComputeDeltaTest_393, BoundaryBetaValuesIfCacheBitsIsAvailable_393) {
  static_assert(has_cache_entry_type<dragonbox_ns>::value,
                "dragonbox_ns::cache_entry_type must exist for this test.");

  if constexpr (!has_cache_bits<dragonbox_ns>::value) {
    GTEST_SKIP() << "cache_bits is not available in this build; skipping boundary beta test.";
  } else {
    using Cache = typename dragonbox_ns::cache_entry_type;
    Cache cache0 = Cache{0};

    // Exercise boundary betas that should be representable.
    const auto beta_min = 0;
    const auto beta_max = static_cast<int>(dragonbox_ns::cache_bits) - 1;

    auto out_min = dragonbox_ns::compute_delta(cache0, beta_min);
    auto out_max = dragonbox_ns::compute_delta(cache0, beta_max);

    // For zero cache input, outputs should remain zero regardless of beta.
    EXPECT_EQ(out_min, 0u);
    EXPECT_EQ(out_max, 0u);
  }
}