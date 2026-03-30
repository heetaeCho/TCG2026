// File: ./TestProjects/yaml-cpp/test/dragonbox_compute_mul_test_392.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

namespace db = YAML::jkj::dragonbox::jkj::dragonbox;

// Detect whether T supports operator== (C++20 requires-expr).
template <class T>
concept EqualityComparable = requires(const T& a, const T& b) {
  { a == b } -> std::convertible_to<bool>;
};

// A conservative comparison helper for results:
// - If operator== exists, use it.
// - Else if trivially copyable, compare raw bytes.
// - Else, fall back to just checking the type is copyable (no value comparison).
template <class T>
void ExpectSameValue(const T& a, const T& b) {
  if constexpr (EqualityComparable<T>) {
    EXPECT_TRUE(a == b);
  } else if constexpr (std::is_trivially_copyable_v<T>) {
    EXPECT_EQ(0, std::memcmp(&a, &b, sizeof(T)));
  } else {
    // We cannot portably compare values without an observable comparator.
    // Still enforce that the result is copyable so determinism tests can copy it.
    static_assert(std::is_copy_constructible_v<T>,
                  "compute_mul_result should be copy-constructible for this test.");
    (void)a;
    (void)b;
    SUCCEED();
  }
}

}  // namespace

// ---- Tests (TEST_ID: 392) ----

TEST(DragonboxComputeMulTest_392, IsNoexceptCallable_392) {
  // Pure interface-level property: function is declared noexcept.
  static_assert(
      noexcept(db::compute_mul(std::declval<db::carrier_uint>(),
                               std::declval<const db::cache_entry_type&>())),
      "compute_mul must be noexcept as declared.");
}

TEST(DragonboxComputeMulTest_392, AcceptsZeroAndDefaultCache_392) {
  db::cache_entry_type cache{};
  db::carrier_uint u = static_cast<db::carrier_uint>(0);

  // Observable behavior: it is callable and returns a value without throwing.
  EXPECT_NO_THROW({
    auto r = db::compute_mul(u, cache);
    (void)r;
  });
}

TEST(DragonboxComputeMulTest_392, AcceptsNonZeroAndDefaultCache_392) {
  db::cache_entry_type cache{};
  db::carrier_uint u = static_cast<db::carrier_uint>(1);

  EXPECT_NO_THROW({
    auto r = db::compute_mul(u, cache);
    (void)r;
  });
}

TEST(DragonboxComputeMulTest_392, DeterministicForSameInputs_392) {
  db::cache_entry_type cache{};
  db::carrier_uint u = static_cast<db::carrier_uint>(123);

  const auto r1 = db::compute_mul(u, cache);
  const auto r2 = db::compute_mul(u, cache);

  // Observable behavior: same input should yield the same output.
  // Comparison is performed only if the type provides an observable way to compare.
  ExpectSameValue(r1, r2);
}

TEST(DragonboxComputeMulTest_392, BoundaryUValuesDoNotCrash_392) {
  db::cache_entry_type cache{};

  const db::carrier_uint u0 = static_cast<db::carrier_uint>(0);
  const db::carrier_uint u1 = static_cast<db::carrier_uint>(1);

  // Using numeric_limits requires carrier_uint to be an arithmetic type; if it isn't,
  // this test still compiles because we only instantiate it when available.
  if constexpr (std::numeric_limits<db::carrier_uint>::is_specialized) {
    const db::carrier_uint umax = (std::numeric_limits<db::carrier_uint>::max)();

    EXPECT_NO_THROW({ (void)db::compute_mul(u0, cache); });
    EXPECT_NO_THROW({ (void)db::compute_mul(u1, cache); });
    EXPECT_NO_THROW({ (void)db::compute_mul(umax, cache); });
  } else {
    // Fallback: still exercise a couple of values.
    EXPECT_NO_THROW({ (void)db::compute_mul(u0, cache); });
    EXPECT_NO_THROW({ (void)db::compute_mul(u1, cache); });
  }
}

TEST(DragonboxComputeMulTest_392, WorksWithConstCacheReference_392) {
  const db::cache_entry_type cache{};
  db::carrier_uint u = static_cast<db::carrier_uint>(7);

  EXPECT_NO_THROW({
    auto r = db::compute_mul(u, cache);
    (void)r;
  });
}