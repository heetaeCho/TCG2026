// File: ./TestProjects/yaml-cpp/test/dragonbox_compute_delta_test_399.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

// Include the header under test.
#include "contrib/dragonbox.h"

namespace {

// The snippet shows compute_delta shifting `cache.high()` and returning a 64-bit value.
// We avoid relying on any internal constants by using the bit-width of uint_least64_t.
constexpr int kHighBits = std::numeric_limits<std::uint_least64_t>::digits;

// Helper to create a "cache-like" value.
// The provided dependency snippet suggests uint128(high, low) exists and has high().
using UInt128 = YAML::jkj::dragonbox::detail::wuint::uint128;

// Try to refer to compute_delta where it most commonly lives in dragonbox within yaml-cpp.
template <class ShiftAmountType>
constexpr std::uint_least64_t CallComputeDelta(const UInt128& cache, ShiftAmountType beta) {
  return YAML::jkj::dragonbox::detail::wuint::compute_delta(cache, beta);
}

}  // namespace

TEST(ComputeDeltaTest_399, BetaMaxReturnsHighUnshifted_399) {
  const UInt128 cache{/*high=*/std::uint_least64_t{0x0123456789abcdefULL},
                      /*low=*/std::uint_least64_t{0ULL}};

  // Boundary: beta = kHighBits - 1 => shift by 0 => result should equal cache.high().
  const auto out = CallComputeDelta(cache, std::integral_constant<int, kHighBits - 1>{});
  EXPECT_EQ(out, std::uint_least64_t{0x0123456789abcdefULL});
}

TEST(ComputeDeltaTest_399, BetaZeroExtractsMsbBit_399) {
  {
    const UInt128 cache{/*high=*/(std::uint_least64_t{1} << (kHighBits - 1)),
                        /*low=*/0ULL};
    const auto out = CallComputeDelta(cache, 0);
    EXPECT_EQ(out, std::uint_least64_t{1});
  }
  {
    const UInt128 cache{/*high=*/0ULL, /*low=*/0ULL};
    const auto out = CallComputeDelta(cache, 0);
    EXPECT_EQ(out, std::uint_least64_t{0});
  }
}

TEST(ComputeDeltaTest_399, BetaOneExtractsTopTwoBitsAsValue_399) {
  // Put the top two bits as "10" at the MSB positions.
  const std::uint_least64_t high =
      (std::uint_least64_t{1} << (kHighBits - 1));  // MSB=1, next bit=0
  const UInt128 cache{/*high=*/high, /*low=*/0ULL};

  // For beta=1, we expect the returned value to be 2 (binary "10").
  const auto out = CallComputeDelta(cache, 1);
  EXPECT_EQ(out, std::uint_least64_t{2});
}

TEST(ComputeDeltaTest_399, IncreasingBetaRevealsMorePrefixBits_399) {
  // Use a recognizable prefix: MSB.. = 1011....
  // We'll place 0b1011 at the top and leave the rest zero.
  std::uint_least64_t high = 0;
  high |= (std::uint_least64_t{1} << (kHighBits - 1));  // 1
  high |= (std::uint_least64_t{0} << (kHighBits - 2));  // 0
  high |= (std::uint_least64_t{1} << (kHighBits - 3));  // 1
  high |= (std::uint_least64_t{1} << (kHighBits - 4));  // 1

  const UInt128 cache{/*high=*/high, /*low=*/0ULL};

  // beta=0 => "1"
  EXPECT_EQ(CallComputeDelta(cache, 0), std::uint_least64_t{1});

  // beta=1 => "10" = 2
  EXPECT_EQ(CallComputeDelta(cache, 1), std::uint_least64_t{2});

  // beta=2 => "101" = 5
  EXPECT_EQ(CallComputeDelta(cache, 2), std::uint_least64_t{5});

  // beta=3 => "1011" = 11
  EXPECT_EQ(CallComputeDelta(cache, 3), std::uint_least64_t{11});
}

TEST(ComputeDeltaTest_399, AcceptsDifferentShiftAmountTypes_399) {
  const UInt128 cache{/*high=*/(std::uint_least64_t{1} << (kHighBits - 1)),
                      /*low=*/0ULL};

  // Same observable output for different beta types.
  EXPECT_EQ(CallComputeDelta(cache, static_cast<unsigned>(0)), std::uint_least64_t{1});
  EXPECT_EQ(CallComputeDelta(cache, static_cast<std::uint32_t>(0)), std::uint_least64_t{1});
  EXPECT_EQ(CallComputeDelta(cache, static_cast<std::uint8_t>(0)), std::uint_least64_t{1});
}

TEST(ComputeDeltaTest_399, ConstexprEvaluatesAtCompileTime_399) {
  constexpr UInt128 cache{/*high=*/(std::uint_least64_t{1} << (kHighBits - 1)),
                          /*low=*/0ULL};

  constexpr auto out0 = CallComputeDelta(cache, 0);
  constexpr auto outMax = CallComputeDelta(cache, std::integral_constant<int, kHighBits - 1>{});

  static_assert(out0 == 1, "compute_delta(beta=0) should extract MSB as 1 for this input");
  static_assert(outMax == (std::uint_least64_t{1} << (kHighBits - 1)),
                "compute_delta(beta=max) should return high() unshifted for this input");

  // Also verify at runtime (helps catch ODR/constexpr differences in some builds).
  EXPECT_EQ(out0, std::uint_least64_t{1});
  EXPECT_EQ(outMax, (std::uint_least64_t{1} << (kHighBits - 1)));
}