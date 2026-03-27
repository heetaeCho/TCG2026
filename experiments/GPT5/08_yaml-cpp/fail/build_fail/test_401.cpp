// File: ./TestProjects/yaml-cpp/test/dragonbox_compute_left_endpoint_for_shorter_interval_case_test_401.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

namespace db = YAML::jkj::dragonbox::detail::wuint;

// Helper: try to create a cache entry in a minimally-assumptive way.
// We avoid inferring internal semantics; we only rely on constructibility.
template <class CacheEntry>
constexpr CacheEntry MakeCacheEntryForTest() {
  if constexpr (std::is_default_constructible<CacheEntry>::value) {
    return CacheEntry{};
  } else if constexpr (std::is_constructible<CacheEntry, std::uint64_t, std::uint64_t>::value) {
    // Common for uint128-like cache entries.
    return CacheEntry{std::uint64_t{0x0123456789ABCDEFu}, std::uint64_t{0x0FEDCBA987654321u}};
  } else if constexpr (std::is_constructible<CacheEntry, std::uint64_t>::value) {
    return CacheEntry{std::uint64_t{0x0123456789ABCDEFu}};
  } else {
    // If the type cannot be constructed in any obvious way, fail at compile time.
    static_assert(std::is_default_constructible<CacheEntry>::value,
                  "Unable to construct cache_entry_type for tests.");
    return CacheEntry{};  // Unreachable; keeps compilers happy.
  }
}

// Helper: detect the cache_entry_type used by the function under test if it exists
// at the expected namespace. This keeps tests resilient to minor refactors.
template <class = void>
struct CacheEntryTypeResolver {
  using type = YAML::jkj::dragonbox::detail::cache_entry_type;
};

using CacheEntryType = typename CacheEntryTypeResolver<>::type;

}  // namespace

// TEST_ID required in both fixture and test names.
class ComputeLeftEndpointForShorterIntervalCaseTest_401 : public ::testing::Test {};

// --- Tests ---

TEST_F(ComputeLeftEndpointForShorterIntervalCaseTest_401, IsNoexcept_401) {
  const CacheEntryType cache = MakeCacheEntryForTest<CacheEntryType>();
  // Beta type intentionally chosen as an unsigned integral.
  constexpr unsigned beta = 0;

  // Observable behavior via the type system: noexcept-ness of the call expression.
  EXPECT_TRUE((noexcept(db::compute_left_endpoint_for_shorter_interval_case(cache, beta))));
}

TEST_F(ComputeLeftEndpointForShorterIntervalCaseTest_401, CanBeEvaluatedAsConstexpr_401) {
  constexpr CacheEntryType cache = MakeCacheEntryForTest<CacheEntryType>();
  constexpr std::uint32_t beta = 0;

  // If this compiles, the function is usable in constant evaluation for these inputs.
  constexpr auto value = db::compute_left_endpoint_for_shorter_interval_case(cache, beta);
  (void)value;

  SUCCEED();
}

TEST_F(ComputeLeftEndpointForShorterIntervalCaseTest_401, ReturnsStableValueForSameInputs_401) {
  const CacheEntryType cache = MakeCacheEntryForTest<CacheEntryType>();

  const auto v1 = db::compute_left_endpoint_for_shorter_interval_case(cache, 0u);
  const auto v2 = db::compute_left_endpoint_for_shorter_interval_case(cache, 0u);

  // Determinism is an observable property expected from a pure-ish utility function.
  EXPECT_EQ(v1, v2);
}

TEST_F(ComputeLeftEndpointForShorterIntervalCaseTest_401, AcceptsDifferentShiftAmountTypes_401) {
  const CacheEntryType cache = MakeCacheEntryForTest<CacheEntryType>();

  // The template parameter is ShiftAmountType; this verifies it is callable with
  // multiple integral types (without asserting numeric semantics).
  const auto v_int = db::compute_left_endpoint_for_shorter_interval_case(cache, int{0});
  const auto v_u16 = db::compute_left_endpoint_for_shorter_interval_case(cache, std::uint16_t{0});
  const auto v_u32 = db::compute_left_endpoint_for_shorter_interval_case(cache, std::uint32_t{0});
  const auto v_u64 = db::compute_left_endpoint_for_shorter_interval_case(cache, std::uint64_t{0});

  // Only verify the calls succeed and produce consistent results for the same numeric beta.
  EXPECT_EQ(v_int, v_u16);
  EXPECT_EQ(v_u16, v_u32);
  EXPECT_EQ(v_u32, v_u64);
}

TEST_F(ComputeLeftEndpointForShorterIntervalCaseTest_401, HandlesSeveralBetaValues_401) {
  const CacheEntryType cache = MakeCacheEntryForTest<CacheEntryType>();

  // Exercise a small range of beta values as boundary-ish probes without asserting
  // implementation-derived relationships.
  const auto v0 = db::compute_left_endpoint_for_shorter_interval_case(cache, 0u);
  const auto v1 = db::compute_left_endpoint_for_shorter_interval_case(cache, 1u);
  const auto v2 = db::compute_left_endpoint_for_shorter_interval_case(cache, 2u);

  // Observable requirement: the function should be callable and return a value.
  // We only assert type consistency (compile-time) and that results are well-formed.
  static_assert(std::is_same<decltype(v0), decltype(v1)>::value, "Return type must be consistent.");
  static_assert(std::is_same<decltype(v1), decltype(v2)>::value, "Return type must be consistent.");

  // No further numeric assertions (to avoid inferring internal logic).
  (void)v0;
  (void)v1;
  (void)v2;

  SUC