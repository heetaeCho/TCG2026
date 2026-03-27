// TEST_ID: 311
#include <cstdint>
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::uint128;
using YAML::jkj::dragonbox::detail::wuint::umul192_lower128;

static inline void Mul64To128(std::uint64_t a, std::uint64_t b, std::uint64_t& hi, std::uint64_t& lo) {
  unsigned __int128 p = static_cast<unsigned __int128>(a) * static_cast<unsigned __int128>(b);
  lo = static_cast<std::uint64_t>(p);
  hi = static_cast<std::uint64_t>(p >> 64);
}

// Reference for the *lower 128 bits* of (x * y), where x is 64-bit and y is 128-bit.
// y = y_high*2^64 + y_low
// x*y = x*y_low + (x*y_high)*2^64
// lower128 = [low64 = lo0] + [high64 = (hi0 + lo1) mod 2^64] * 2^64
static inline uint128 RefLower128Of64x128(std::uint64_t x, const uint128& y) {
  std::uint64_t hi0 = 0, lo0 = 0;
  std::uint64_t hi1 = 0, lo1 = 0;

  Mul64To128(x, y.low(), hi0, lo0);
  Mul64To128(x, y.high(), hi1, lo1);  // hi1 does not contribute to lower 128 bits.

  const std::uint64_t high64 = static_cast<std::uint64_t>(hi0 + lo1);  // wraps mod 2^64
  return uint128{high64, lo0};
}

static inline void ExpectUint128Eq(const uint128& got, const uint128& expected) {
  EXPECT_EQ(got.high(), expected.high());
  EXPECT_EQ(got.low(), expected.low());
}

}  // namespace

// Compile-time sanity check (if these APIs are usable in constexpr context).
// This does not assume implementation details; it only asserts observable results
// for a simple, deterministic input using the reference arithmetic above.
TEST(UMul192Lower128Test_311, ConstexprEvaluates_311) {
  constexpr std::uint64_t x = 7;
  constexpr uint128 y{3, 5};  // y = 3*2^64 + 5

  constexpr uint128 got = umul192_lower128(x, y);

  // expected:
  // x*y_low = 7*5 = 35 => lo0=35, hi0=0
  // x*y_high = 7*3 = 21 => lo1=21
  // high64 = 0 + 21 = 21
  static_assert(got.high() == 21, "high64 mismatch");
  static_assert(got.low() == 35, "low64 mismatch");

  // Also assert at runtime to keep test output consistent.
  EXPECT_EQ(got.high(), 21u);
  EXPECT_EQ(got.low(), 35u);
}

TEST(UMul192Lower128Test_311, ZeroInputsProduceZero_311) {
  {
    const uint128 y{0, 0};
    const uint128 got = umul192_lower128(0, y);
    ExpectUint128Eq(got, uint128{0, 0});
  }
  {
    const uint128 y{123, 456};
    const uint128 got = umul192_lower128(0, y);
    ExpectUint128Eq(got, uint128{0, 0});
  }
  {
    const uint128 y{0, 0};
    const uint128 got = umul192_lower128(UINT64_C(999), y);
    ExpectUint128Eq(got, uint128{0, 0});
  }
}

TEST(UMul192Lower128Test_311, MultiplyByOneMatchesLower128OfY_311) {
  const uint128 y{UINT64_C(0x1122334455667788), UINT64_C(0x99aabbccddeeff00)};
  const uint128 got = umul192_lower128(UINT64_C(1), y);
  // When x == 1, the lower 128 bits of x*y should equal y itself.
  ExpectUint128Eq(got, y);
}

TEST(UMul192Lower128Test_311, MatchesReferenceForRepresentativeValues_311) {
  struct Vec {
    std::uint64_t x;
    std::uint64_t yh;
    std::uint64_t yl;
  };

  const Vec cases[] = {
      {UINT64_C(2), UINT64_C(0), UINT64_C(1)},
      {UINT64_C(3), UINT64_C(1), UINT64_C(0)},
      {UINT64_C(10), UINT64_C(0x0123456789abcdef), UINT64_C(0xfedcba9876543210)},
      {UINT64_C(0xffffffffffffffff), UINT64_C(0), UINT64_C(0xffffffffffffffff)},
      {UINT64_C(0xffffffffffffffff), UINT64_C(0xffffffffffffffff), UINT64_C(0xffffffffffffffff)},
      {UINT64_C(0x8000000000000000), UINT64_C(0x0000000000000001), UINT64_C(0)},
      {UINT64_C(0x7fffffffffffffff), UINT64_C(0xdeadbeefdeadbeef), UINT64_C(0x0123012301230123)},
  };

  for (const auto& c : cases) {
    const uint128 y{c.yh, c.yl};
    const uint128 got = umul192_lower128(c.x, y);
    const uint128 expected = RefLower128Of64x128(c.x, y);
    ExpectUint128Eq(got, expected);
  }
}

TEST(UMul192Lower128Test_311, CarryFromLowProductAffectsHigh64_311) {
  // Choose values that force a non-zero hi0 from x * y.low().
  const std::uint64_t x = UINT64_C(0xffffffffffffffff);
  const uint128 y{UINT64_C(0x0000000000000001), UINT64_C(0xffffffffffffffff)};

  const uint128 got = umul192_lower128(x, y);
  const uint128 expected = RefLower128Of64x128(x, y);

  // This test specifically checks behavior when (x * y.low()) overflows 64 bits.
  EXPECT_NE(expected.high(), 0u);
  ExpectUint128Eq(got, expected);
}

TEST(UMul192Lower128Test_311, High64WrapsModulo2To64_311) {
  // Construct a case where hi0 + lo1 overflows 64 bits to validate wraparound behavior
  // of the returned high 64 bits in the lower-128 result.
  //
  // x*y.low => hi0 near max
  // x*y.high => lo1 near max
  const std::uint64_t x = UINT64_C(0xffffffffffffffff);
  const uint128 y{UINT64_C(0xffffffffffffffff), UINT64_C(0xffffffffffffffff)};

  const uint128 got = umul192_lower128(x, y);
  const uint128 expected = RefLower128Of64x128(x, y);

  // We don't assert "it must overflow" directly; we assert equality to the reference,
  // which includes modulo 2^64 wrapping in the high word.
  ExpectUint128Eq(got, expected);
}