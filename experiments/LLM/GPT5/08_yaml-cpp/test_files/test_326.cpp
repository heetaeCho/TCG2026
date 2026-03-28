// File: ./TestProjects/yaml-cpp/test/dragonbox_small_division_by_pow10_test.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class UInt>
UInt Pow10(unsigned n) {
  static_assert(std::is_unsigned<UInt>::value, "UInt must be an unsigned integer type");
  UInt v = UInt(1);
  for (unsigned i = 0; i < n; ++i) {
    v = UInt(v * UInt(10));
  }
  return v;
}

template <int N, class UInt>
UInt CallSmallDivisionByPow10(UInt n) {
  return YAML::jkj::dragonbox::detail::div::small_division_by_pow10<N, UInt>(n);
}

template <int N, class UInt>
UInt MaxAllowedN() {
  // The implementation asserts: n <= compute_power<N + 1>(10).
  // In tests, we mirror that constraint using plain integer arithmetic.
  return Pow10<UInt>(static_cast<unsigned>(N + 1));
}

template <int N, class UInt>
void RunBasicCorrectnessSet() {
  const UInt denom = Pow10<UInt>(static_cast<unsigned>(N));
  // A small but representative set of inputs that stay within the allowed range.
  const UInt max_n = MaxAllowedN<N, UInt>();

  const UInt samples[] = {
      UInt(0),
      UInt(1),
      UInt(9),
      UInt(10),
      UInt(11),
      UInt(19),
      UInt(99),
      UInt(100),
      UInt(101),
      UInt(denom - UInt(1)),
      UInt(denom),
      UInt(denom + UInt(1)),
      UInt(max_n / UInt(2)),
      UInt(max_n - UInt(1)),
      UInt(max_n),
  };

  for (UInt n : samples) {
    if (n > max_n) continue;  // Safety if denom-related values exceed bound for small N.
    const UInt expected = UInt(n / denom);
    const UInt actual = CallSmallDivisionByPow10<N, UInt>(n);
    ASSERT_EQ(actual, expected) << "N=" << N << " n=" << static_cast<unsigned long long>(n);
  }
}

template <int N, class UInt>
void RunMonotonicitySweep() {
  const UInt denom = Pow10<UInt>(static_cast<unsigned>(N));
  const UInt max_n = MaxAllowedN<N, UInt>();

  // Sweep a limited range to keep runtime small but still cover many transitions.
  // Ensure we stay within [0, max_n].
  const UInt limit = (max_n < UInt(2000)) ? max_n : UInt(2000);

  UInt prev = CallSmallDivisionByPow10<N, UInt>(UInt(0));
  ASSERT_EQ(prev, UInt(0)) << "N=" << N;

  for (UInt n = UInt(1); n <= limit; n = UInt(n + UInt(1))) {
    UInt cur = CallSmallDivisionByPow10<N, UInt>(n);
    ASSERT_LE(prev, cur) << "N=" << N << " monotonicity violated at n=" << static_cast<unsigned long long>(n);

    // Output should stay within [0, n/10^N] and should match integer division for allowed domain.
    ASSERT_EQ(cur, UInt(n / denom)) << "N=" << N << " n=" << static_cast<unsigned long long>(n);

    prev = cur;
  }
}

}  // namespace

// -------------------- uint32_t --------------------

TEST(SmallDivisionByPow10Test_326, N0_U32_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<0, std::uint32_t>();
}

TEST(SmallDivisionByPow10Test_326, N1_U32_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<1, std::uint32_t>();
}

TEST(SmallDivisionByPow10Test_326, N2_U32_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<2, std::uint32_t>();
}

TEST(SmallDivisionByPow10Test_326, N3_U32_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<3, std::uint32_t>();
}

TEST(SmallDivisionByPow10Test_326, N1_U32_IsMonotonicOnPrefixRange_326) {
  RunMonotonicitySweep<1, std::uint32_t>();
}

TEST(SmallDivisionByPow10Test_326, N2_U32_IsMonotonicOnPrefixRange_326) {
  RunMonotonicitySweep<2, std::uint32_t>();
}

// -------------------- uint64_t --------------------

TEST(SmallDivisionByPow10Test_326, N0_U64_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<0, std::uint64_t>();
}

TEST(SmallDivisionByPow10Test_326, N1_U64_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<1, std::uint64_t>();
}

TEST(SmallDivisionByPow10Test_326, N2_U64_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<2, std::uint64_t>();
}

TEST(SmallDivisionByPow10Test_326, N3_U64_MatchesIntegerDivision_326) {
  RunBasicCorrectnessSet<3, std::uint64_t>();
}

TEST(SmallDivisionByPow10Test_326, N1_U64_IsMonotonicOnPrefixRange_326) {
  RunMonotonicitySweep<1, std::uint64_t>();
}

TEST(SmallDivisionByPow10Test_326, N2_U64_IsMonotonicOnPrefixRange_326) {
  RunMonotonicitySweep<2, std::uint64_t>();
}

// -------------------- Boundary / edge behaviors --------------------

TEST(SmallDivisionByPow10Test_326, Boundary_MaxAllowedInput_ProducesExpectedQuotient_326) {
  // Pick N=2 as a representative case: allowed n <= 10^(N+1) = 1000.
  constexpr int N = 2;
  const std::uint32_t max_n = MaxAllowedN<N, std::uint32_t>();  // 1000
  const std::uint32_t denom = Pow10<std::uint32_t>(N);          // 100
  const std::uint32_t actual = CallSmallDivisionByPow10<N, std::uint32_t>(max_n);
  EXPECT_EQ(actual, max_n / denom);
}

TEST(SmallDivisionByPow10Test_326, Boundary_JustBelowPowerOf10_ProducesExpectedQuotient_326) {
  // For N=3: denom=1000, allowed max_n=10000.
  constexpr int N = 3;
  const std::uint64_t denom = Pow10<std::uint64_t>(N);
  const std::uint64_t n = UInt64(denom - 1);
  const std::uint64_t actual = CallSmallDivisionByPow10<N, std::uint64_t>(n);
  EXPECT_EQ(actual, n / denom);
}

// -------------------- Error / assertion behavior --------------------
#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST(SmallDivisionByPow10Test_326, Death_WhenInputExceedsMaxAllowed_TriggersAssert_326) {
  // The implementation has: assert(n <= compute_power<N+1>(10)).
  constexpr int N = 2;  // allowed <= 1000
  const std::uint32_t max_n = MaxAllowedN<N, std::uint32_t>();
  const std::uint32_t bad = static_cast<std::uint32_t>(max_n + 1);

  ASSERT_DEATH((void)CallSmallDivisionByPow10<N, std::uint32_t>(bad), "");
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST