// File: ./TestProjects/yaml-cpp/test/dragonbox_umul128_test.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <random>
#include <utility>

#include <boost/multiprecision/cpp_int.hpp>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::umul128;

// Helper: compute expected 128-bit product using an independent big-int type.
static std::pair<std::uint_least64_t, std::uint_least64_t>
ExpectedHiLo(std::uint_least64_t x, std::uint_least64_t y) {
  using boost::multiprecision::uint128_t;

  const uint128_t prod = uint128_t{x} * uint128_t{y};
  const uint128_t mask64 = (uint128_t{1} << 64) - 1;

  const auto lo = static_cast<std::uint_least64_t>(prod & mask64);
  const auto hi = static_cast<std::uint_least64_t>(prod >> 64);
  return {hi, lo};
}

// If umul128 is usable in constant evaluation, this gives a compile-time sanity check.
// (If the header/compiler config doesn’t allow constexpr here, it will just fail to compile,
// which is still a valid signal for this test translation unit.)
constexpr bool kCanConstexprCheck = true;
#if defined(_MSC_VER) && !defined(__clang__)
// Some MSVC modes may not allow constexpr evaluation depending on JKJ_IF_CONSTEVAL path;
// keep the static_asserts lightweight.
#endif

static_assert(noexcept(umul128(0, 0)), "umul128 must be noexcept");

constexpr auto kR1 = umul128(3, 5);
static_assert(kR1.high_ == 0 && kR1.low_ == 15, "umul128 constexpr check failed");

class Umul128Test_307 : public ::testing::Test {
protected:
  static void ExpectProduct(std::uint_least64_t x, std::uint_least64_t y) {
    const auto expected = ExpectedHiLo(x, y);
    const auto got = umul128(x, y);
    EXPECT_EQ(got.high_, expected.first) << "x=" << x << " y=" << y;
    EXPECT_EQ(got.low_, expected.second) << "x=" << x << " y=" << y;
  }
};

}  // namespace

TEST_F(Umul128Test_307, ZeroTimesAnythingIsZero_307) {
  const std::uint_least64_t max = (std::numeric_limits<std::uint_least64_t>::max)();

  ExpectProduct(0, 0);
  ExpectProduct(0, 1);
  ExpectProduct(1, 0);
  ExpectProduct(0, max);
  ExpectProduct(max, 0);
}

TEST_F(Umul128Test_307, OneTimesAnythingIsIdentity_307) {
  const std::uint_least64_t max = (std::numeric_limits<std::uint_least64_t>::max)();

  ExpectProduct(1, 1);
  ExpectProduct(1, 2);
  ExpectProduct(2, 1);
  ExpectProduct(1, max);
  ExpectProduct(max, 1);
}

TEST_F(Umul128Test_307, MaxTimesMaxMatchesKnownBoundary_307) {
  const std::uint_least64_t max = (std::numeric_limits<std::uint_least64_t>::max)();

  const auto got = umul128(max, max);

  // (2^64 - 1)^2 = 2^128 - 2^65 + 1
  // hi = 0xFFFFFFFFFFFFFFFE, lo = 0x0000000000000001
  EXPECT_EQ(got.high_, std::uint_least64_t{0xFFFFFFFFFFFFFFFEull});
  EXPECT_EQ(got.low_,  std::uint_least64_t{0x0000000000000001ull});

  // Also cross-check against independent big-int computation.
  const auto expected = ExpectedHiLo(max, max);
  EXPECT_EQ(got.high_, expected.first);
  EXPECT_EQ(got.low_, expected.second);
}

TEST_F(Umul128Test_307, PowerOfTwoAndCarryCrossingCases_307) {
  // These are chosen to exercise carries across 32-bit and 64-bit boundaries.
  ExpectProduct(std::uint_least64_t{1} << 32, std::uint_least64_t{1} << 32);  // = 2^64
  ExpectProduct((std::uint_least64_t{1} << 63), 2);                           // = 2^64
  ExpectProduct((std::uint_least64_t{1} << 63), 3);                           // hi should be 1, lo should be 2^63
  ExpectProduct(0xFFFFFFFFull, 0xFFFFFFFFull);                                // 32-bit max squared
  ExpectProduct(0x1'0000'0000ull, 0xFFFFFFFFull);                             // around 2^32
}

TEST_F(Umul128Test_307, CommutativityHoldsForSampledValues_307) {
  const std::uint_least64_t values[] = {
      0ull,
      1ull,
      2ull,
      3ull,
      7ull,
      0xFFFFFFFFull,
      0x1'0000'0000ull,
      0x8000'0000'0000'0000ull,
      0x7FFF'FFFF'FFFF'FFFFull,
      0x0123'4567'89AB'CDEFuLL,
      0xFEDC'BA98'7654'3210uLL,
      (std::numeric_limits<std::uint_least64_t>::max)(),
  };

  for (auto x : values) {
    for (auto y : values) {
      const auto a = umul128(x, y);
      const auto b = umul128(y, x);
      EXPECT_EQ(a.high_, b.high_) << "x=" << x << " y=" << y;
      EXPECT_EQ(a.low_,  b.low_)  << "x=" << x << " y=" << y;
    }
  }
}

TEST_F(Umul128Test_307, MatchesIndependentBigIntForRandomVectors_307) {
  std::mt19937_64 rng(0xC0FFEE1234ULL);
  for (int i = 0; i < 200; ++i) {
    const std::uint_least64_t x = static_cast<std::uint_least64_t>(rng());
    const std::uint_least64_t y = static_cast<std::uint_least64_t>(rng());
    ExpectProduct(x, y);
  }
}