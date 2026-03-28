// TEST_ID: 309
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include <boost/multiprecision/cpp_int.hpp>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {
using boost::multiprecision::cpp_int;

using YAML::jkj::dragonbox::detail::wuint::uint128;
using YAML::jkj::dragonbox::detail::wuint::umul192_upper128;

static cpp_int ToBig(const uint128& v) {
  cpp_int r = 0;
  r |= cpp_int(v.high());
  r <<= 64;
  r |= cpp_int(v.low());
  return r;
}

static uint128 FromBig128(const cpp_int& v) {
  const cpp_int mask64 = (cpp_int(1) << 64) - 1;
  const std::uint_least64_t low =
      static_cast<std::uint_least64_t>((v & mask64).convert_to<std::uint64_t>());
  const std::uint_least64_t high = static_cast<std::uint_least64_t>(
      ((v >> 64) & mask64).convert_to<std::uint64_t>());
  return uint128{high, low};
}

static uint128 RefU64xU128_Upper128(std::uint_least64_t x, const uint128& y) {
  // Mathematical oracle: upper 128 bits of the 192-bit product (x * y),
  // i.e., floor((x*y) / 2^64).
  const cpp_int prod = cpp_int(x) * ToBig(y);
  const cpp_int upper = (prod >> 64);  // result fits in <= 128 bits
  const cpp_int mask128 = (cpp_int(1) << 128) - 1;
  return FromBig128(upper & mask128);
}
}  // namespace

class Umul192Upper128Test_309 : public ::testing::Test {};

TEST_F(Umul192Upper128Test_309, IsNoexcept_309) {
  const uint128 y{0, 0};
  static_assert(noexcept(umul192_upper128(stdr::uint_least64_t{0}, y)),
                "umul192_upper128 must be noexcept");
  (void)y;
}

TEST_F(Umul192Upper128Test_309, ZeroXAlwaysZero_309) {
  const uint128 ys[] = {
      uint128{0, 0},
      uint128{0, 1},
      uint128{1, 0},
      uint128{std::numeric_limits<std::uint_least64_t>::max(),
              std::numeric_limits<std::uint_least64_t>::max()},
  };

  for (const auto& y : ys) {
    const auto got = umul192_upper128(stdr::uint_least64_t{0}, y);
    EXPECT_EQ(got.high(), 0u);
    EXPECT_EQ(got.low(), 0u);
  }
}

TEST_F(Umul192Upper128Test_309, ZeroYAlwaysZero_309) {
  const uint128 y{0, 0};
  const std::uint_least64_t xs[] = {
      0u,
      1u,
      2u,
      std::numeric_limits<std::uint_least64_t>::max(),
  };

  for (auto x : xs) {
    const auto got = umul192_upper128(static_cast<stdr::uint_least64_t>(x), y);
    EXPECT_EQ(got.high(), 0u);
    EXPECT_EQ(got.low(), 0u);
  }
}

TEST_F(Umul192Upper128Test_309, MatchesOracleOnTypicalValues_309) {
  struct Case {
    std::uint_least64_t x;
    uint128 y;
  };

  const Case cases[] = {
      {1u, uint128{0u, 1u}},
      {2u, uint128{0u, 3u}},
      {3u, uint128{5u, 7u}},
      {0x0123456789abcdefULL, uint128{0xfedcba9876543210ULL, 0x0f0e0d0c0b0a0908ULL}},
      {0xffffffffffffffffULL, uint128{0u, 0xffffffffffffffffULL}},
      {0xffffffffffffffffULL, uint128{0xffffffffffffffffULL, 0u}},
      {0x8000000000000000ULL, uint128{0x7fffffffffffffffULL, 0xffffffffffffffffULL}},
  };

  for (const auto& c : cases) {
    const auto got = umul192_upper128(static_cast<stdr::uint_least64_t>(c.x), c.y);
    const auto exp = RefU64xU128_Upper128(c.x, c.y);
    EXPECT_EQ(got.high(), exp.high()) << "x=" << c.x;
    EXPECT_EQ(got.low(), exp.low()) << "x=" << c.x;
  }
}

TEST_F(Umul192Upper128Test_309, BoundaryMaxValues_309) {
  const std::uint_least64_t x = std::numeric_limits<std::uint_least64_t>::max();
  const uint128 y{std::numeric_limits<std::uint_least64_t>::max(),
                  std::numeric_limits<std::uint_least64_t>::max()};

  const auto got = umul192_upper128(static_cast<stdr::uint_least64_t>(x), y);
  const auto exp = RefU64xU128_Upper128(x, y);

  EXPECT_EQ(got.high(), exp.high());
  EXPECT_EQ(got.low(), exp.low());
}

TEST_F(Umul192Upper128Test_309, BoundarySingleBitPatterns_309) {
  const std::uint_least64_t xs[] = {
      1ULL,
      1ULL << 1,
      1ULL << 31,
      1ULL << 32,
      1ULL << 63,
  };

  const uint128 ys[] = {
      uint128{0u, 1u},
      uint128{0u, 1ULL << 63},
      uint128{1u, 0u},
      uint128{1ULL << 63, 0u},
      uint128{(1ULL << 63), (1ULL << 63)},
  };

  for (auto x : xs) {
    for (const auto& y : ys) {
      const auto got = umul192_upper128(static_cast<stdr::uint_least64_t>(x), y);
      const auto exp = RefU64xU128_Upper128(x, y);
      EXPECT_EQ(got.high(), exp.high()) << "x=" << x;
      EXPECT_EQ(got.low(), exp.low()) << "x=" << x;
    }
  }
}

TEST_F(Umul192Upper128Test_309, CarryHeavyLowPartExercises_309) {
  // Values intended to create lots of carries in the lower 128 bits of x*y,
  // which affect the upper-128-after-shift result.
  const std::uint_least64_t xs[] = {
      0xffffffffffffffffULL,
      0xffffffff00000000ULL,
      0x00000000ffffffffULL,
      0xaaaaaaaaaaaaaaaaULL,
      0x5555555555555555ULL,
  };

  const uint128 ys[] = {
      uint128{0x0000000000000001ULL, 0xffffffffffffffffULL},
      uint128{0x7fffffffffffffffULL, 0xffffffffffffffffULL},
      uint128{0xffffffffffffffffULL, 0xffffffffffffffffULL},
      uint128{0xffffffffffffffffULL, 0x0000000000000001ULL},
  };

  for (auto x : xs) {
    for (const auto& y : ys) {
      const auto got = umul192_upper128(static_cast<stdr::uint_least64_t>(x), y);
      const auto exp = RefU64xU128_Upper128(x, y);
      EXPECT_EQ(got.high(), exp.high()) << "x=" << x;
      EXPECT_EQ(got.low(), exp.low()) << "x=" << x;
    }
  }
}