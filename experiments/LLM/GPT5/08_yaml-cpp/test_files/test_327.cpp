// File: ./TestProjects/yaml-cpp/test/dragonbox_divide_by_pow10_test_327.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>
#include <vector>

#include "contrib/dragonbox.h"

namespace {

template <class UInt>
constexpr UInt Pow10(int n) {
  UInt v = 1;
  for (int i = 0; i < n; ++i) v = static_cast<UInt>(v * static_cast<UInt>(10));
  return v;
}

template <int N, class UInt>
constexpr UInt Expected(UInt n) {
  return static_cast<UInt>(n / Pow10<UInt>(N));
}

class DivideByPow10Test_327 : public ::testing::Test {};

}  // namespace

TEST_F(DivideByPow10Test_327, UInt32_N1_WithinBound_MatchesDivision_327) {
  using UInt = std::uint_least32_t;
  constexpr int N = 1;
  constexpr UInt n_max = static_cast<UInt>(UINT32_C(1073741828));  // per header condition

  const std::vector<UInt> cases = {
      UInt(0),
      UInt(1),
      UInt(9),
      UInt(10),
      UInt(11),
      static_cast<UInt>(Pow10<UInt>(N) - 1),
      static_cast<UInt>(Pow10<UInt>(N)),
      static_cast<UInt>(Pow10<UInt>(N) + 1),
      static_cast<UInt>(n_max / 2),
      static_cast<UInt>(n_max - 1),
      static_cast<UInt>(n_max),
  };

  for (UInt n : cases) {
    const auto got =
        YAML::jkj::dragonbox::detail::div::divide_by_pow10<N, UInt, n_max>(n);
    EXPECT_EQ(got, Expected<N>(n)) << "n=" << n;
  }
}

TEST_F(DivideByPow10Test_327, UInt64_N1_WithinBound_MatchesDivision_327) {
  using UInt = std::uint_least64_t;
  constexpr int N = 1;
  constexpr UInt n_max = static_cast<UInt>(UINT64_C(4611686018427387908));  // per header condition

  const std::vector<UInt> cases = {
      UInt(0),
      UInt(1),
      UInt(9),
      UInt(10),
      UInt(11),
      static_cast<UInt>(Pow10<UInt>(N) - 1),
      static_cast<UInt>(Pow10<UInt>(N)),
      static_cast<UInt>(Pow10<UInt>(N) + 1),
      static_cast<UInt>(n_max / 2),
      static_cast<UInt>(n_max - 1),
      static_cast<UInt>(n_max),
  };

  for (UInt n : cases) {
    const auto got =
        YAML::jkj::dragonbox::detail::div::divide_by_pow10<N, UInt, n_max>(n);
    EXPECT_EQ(got, Expected<N>(n)) << "n=" << static_cast<unsigned long long>(n);
  }
}

TEST_F(DivideByPow10Test_327, UInt32_N2_MatchesDivision_327) {
  using UInt = std::uint_least32_t;
  constexpr int N = 2;
  // No n_max restriction is stated in the visible specialization for (UInt32, N==2),
  // but we still keep inputs small and representative.
  constexpr UInt n_max = std::numeric_limits<UInt>::max();

  const std::vector<UInt> cases = {
      UInt(0),
      UInt(1),
      UInt(99),
      UInt(100),
      UInt(101),
      static_cast<UInt>(Pow10<UInt>(N) - 1),
      static_cast<UInt>(Pow10<UInt>(N)),
      static_cast<UInt>(Pow10<UInt>(N) + 1),
      UInt(12345),
      UInt(99999),
      UInt(100000),
      std::numeric_limits<UInt>::max(),
  };

  for (UInt n : cases) {
    const auto got =
        YAML::jkj::dragonbox::detail::div::divide_by_pow10<N, UInt, n_max>(n);
    EXPECT_EQ(got, Expected<N>(n)) << "n=" << n;
  }
}

TEST_F(DivideByPow10Test_327, UInt64_N3_WithinBound_MatchesDivision_327) {
  using UInt = std::uint_least64_t;
  constexpr int N = 3;
  constexpr UInt n_max = static_cast<UInt>(UINT64_C(15534100272597517998));  // per header condition

  const std::vector<UInt> cases = {
      UInt(0),
      UInt(1),
      UInt(999),
      UInt(1000),
      UInt(1001),
      static_cast<UInt>(Pow10<UInt>(N) - 1),
      static_cast<UInt>(Pow10<UInt>(N)),
      static_cast<UInt>(Pow10<UInt>(N) + 1),
      static_cast<UInt>(n_max / 2),
      static_cast<UInt>(n_max - 1),
      static_cast<UInt>(n_max),
  };

  for (UInt n : cases) {
    const auto got =
        YAML::jkj::dragonbox::detail::div::divide_by_pow10<N, UInt, n_max>(n);
    EXPECT_EQ(got, Expected<N>(n)) << "n=" << static_cast<unsigned long long>(n);
  }
}

TEST_F(DivideByPow10Test_327, FallbackPath_StillMatchesDivision_327) {
  using UInt = std::uint_least64_t;
  constexpr int N = 4;  // not shown as a specialized case in the provided snippet
  constexpr UInt n_max = std::numeric_limits<UInt>::max();

  const std::vector<UInt> cases = {
      UInt(0),
      UInt(1),
      UInt(9999),
      UInt(10000),
      UInt(10001),
      static_cast<UInt>(Pow10<UInt>(N) - 1),
      static_cast<UInt>(Pow10<UInt>(N)),
      static_cast<UInt>(Pow10<UInt>(N) + 1),
      UInt(123456789012345ULL),
      std::numeric_limits<UInt>::max(),
  };

  for (UInt n : cases) {
    const auto got =
        YAML::jkj::dragonbox::detail::div::divide_by_pow10<N, UInt, n_max>(n);
    EXPECT_EQ(got, Expected<N>(n)) << "n=" << static_cast<unsigned long long>(n);
  }
}

TEST_F(DivideByPow10Test_327, CompileTimeEvaluation_WorksForSimpleConstants_327) {
  using UInt32 = std::uint_least32_t;
  using UInt64 = std::uint_least64_t;

  // These are compile-time checks that the function is usable in constexpr contexts
  // (consistent with its signature and noexcept/constexpr intent).
  {
    constexpr UInt32 n_max32 = static_cast<UInt32>(UINT32_C(1073741828));
    constexpr UInt32 n = 1234;
    constexpr auto got =
        YAML::jkj::dragonbox::detail::div::divide_by_pow10<1, UInt32, n_max32>(n);
    static_assert(got == Expected<1>(n), "constexpr divide_by_pow10 failed for UInt32 N=1");
  }
  {
    constexpr UInt64 n_max64 = static_cast<UInt64>(UINT64_C(4611686018427387908));
    constexpr UInt64 n = 9876543210ULL;
    constexpr auto got =
        YAML::jkj::dragonbox::detail::div::divide_by_pow10<1, UInt64, n_max64>(n);
    static_assert(got == Expected<1>(n), "constexpr divide_by_pow10 failed for UInt64 N=1");
  }

  SUCCEED();
}