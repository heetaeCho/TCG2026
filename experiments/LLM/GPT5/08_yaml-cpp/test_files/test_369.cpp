// File: ./TestProjects/yaml-cpp/test/dragonbox_nearest_toward_zero_shorter_interval_test_369.cpp

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_zero_t;

// Detection idiom: check if T supports operator==
template <class T, class = void>
struct has_equal : std::false_type {};
template <class T>
struct has_equal<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};
template <class T>
inline constexpr bool has_equal_v = has_equal<T>::value;

template <class SignedSignificandBits>
using RetT = decltype(Policy::shorter_interval(std::declval<SignedSignificandBits>()));

class NearestTowardZeroShorterIntervalTest_369 : public ::testing::Test {};

TEST_F(NearestTowardZeroShorterIntervalTest_369, IsNoexceptAndReturnsExpectedType_369) {
  // Must be noexcept for at least one representative instantiation.
  static_assert(noexcept(Policy::shorter_interval(0)), "shorter_interval(int) must be noexcept");

  // Return type should be the declared type.
  static_assert(std::is_same_v<RetT<int>, YAML::jkj::dragonbox::interval_type::right_closed_left_open>,
                "Return type mismatch for shorter_interval(int)");

  // Also verify for another integral type.
  static_assert(noexcept(Policy::shorter_interval(std::int64_t{0})),
                "shorter_interval(int64_t) must be noexcept");
  static_assert(
      std::is_same_v<RetT<std::int64_t>, YAML::jkj::dragonbox::interval_type::right_closed_left_open>,
      "Return type mismatch for shorter_interval(int64_t)");
}

TEST_F(NearestTowardZeroShorterIntervalTest_369, CanBeEvaluatedAtCompileTime_369) {
  // Verify the call is usable in a constant-evaluated context (constexpr friendly).
  constexpr auto v0 = Policy::shorter_interval(0);
  (void)v0;

  constexpr auto v1 = Policy::shorter_interval(1);
  (void)v1;
}

TEST_F(NearestTowardZeroShorterIntervalTest_369, AcceptsVariousIntegralTypes_369) {
  // Signed types
  (void)Policy::shorter_interval(short{0});
  (void)Policy::shorter_interval(int{0});
  (void)Policy::shorter_interval(long{0});
  (void)Policy::shorter_interval(long long{0});
  (void)Policy::shorter_interval(std::int64_t{0});

  // Unsigned types (template is unconstrained in the interface; ensure it is callable)
  (void)Policy::shorter_interval(unsigned short{0});
  (void)Policy::shorter_interval(unsigned int{0});
  (void)Policy::shorter_interval(unsigned long{0});
  (void)Policy::shorter_interval(unsigned long long{0});
  (void)Policy::shorter_interval(std::uint64_t{0});
}

TEST_F(NearestTowardZeroShorterIntervalTest_369, HandlesBoundaryValues_369) {
  // These are boundary-ish values observable via the public interface (must be callable, no throw).
  (void)Policy::shorter_interval(0);
  (void)Policy::shorter_interval(1);
  (void)Policy::shorter_interval(-1);

  (void)Policy::shorter_interval(std::numeric_limits<int>::min());
  (void)Policy::shorter_interval(std::numeric_limits<int>::max());

  (void)Policy::shorter_interval(std::numeric_limits<std::int64_t>::min());
  (void)Policy::shorter_interval(std::numeric_limits<std::int64_t>::max());

  (void)Policy::shorter_interval(std::numeric_limits<std::uint64_t>::max());
}

TEST_F(NearestTowardZeroShorterIntervalTest_369, ReturnedValueIsComparableToDefaultIfEqualityExists_369) {
  using R = RetT<int>;
  const auto r = Policy::shorter_interval(0);

  if constexpr (has_equal_v<R>) {
    // If the type provides equality, verify the returned value equals a default-constructed instance.
    EXPECT_EQ(r, R{});
  } else {
    // If no equality is available, we still validated callability and type properties elsewhere.
    SUCCEED();
  }
}

TEST_F(NearestTowardZeroShorterIntervalTest_369, MultipleCallsAreWellFormed_369) {
  // Ensure repeated calls are valid and do not require any setup/teardown observable via interface.
  const auto a = Policy::shorter_interval(0);
  const auto b = Policy::shorter_interval(123);
  (void)a;
  (void)b;

  using R = RetT<int>;
  if constexpr (has_equal_v<R>) {
    // If equality exists, at least ensure values are comparable (no assumptions about semantics).
    (void)(a == b);
    SUCCEED();
  } else {
    SUCCEED();
  }
}

}  // namespace