// TEST_ID: 312
// File: test_umul96_lower64_312.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <random>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::umul96_lower64;

class Umul96Lower64Test_312 : public ::testing::Test {
protected:
  static std::uint64_t ExpectedLower64(std::uint32_t x, std::uint64_t y) {
#if defined(__SIZEOF_INT128__)
    const unsigned __int128 prod =
        static_cast<unsigned __int128>(x) * static_cast<unsigned __int128>(y);
    return static_cast<std::uint64_t>(prod & static_cast<unsigned __int128>(0xFFFFFFFFFFFFFFFFull));
#else
    // Portable fallback: compute (x * y) mod 2^64 via 32-bit limbs without using 128-bit.
    // This is *not* reusing internal implementation; it is an independent modular product.
    const std::uint64_t y_lo = static_cast<std::uint32_t>(y);
    const std::uint64_t y_hi = static_cast<std::uint32_t>(y >> 32);

    const std::uint64_t p0 = static_cast<std::uint64_t>(x) * y_lo; // up to 64 bits
    const std::uint64_t p1 = static_cast<std::uint64_t>(x) * y_hi; // up to 64 bits

    // (x*y) = p0 + (p1 << 32). Taking mod 2^64:
    return p0 + (p1 << 32);
#endif
  }
};

TEST_F(Umul96Lower64Test_312, IsNoexcept_312) {
  static_assert(noexcept(umul96_lower64(std::uint32_t{0}, std::uint64_t{0})),
                "umul96_lower64 must be noexcept");
  SUCCEED();
}

TEST_F(Umul96Lower64Test_312, ReturnTypeIsUintLeast64_312) {
  using Ret = decltype(umul96_lower64(std::uint32_t{0}, std::uint64_t{0}));
  static_assert(std::is_same<Ret, std::uint_least64_t>::value,
                "Return type must be std::uint_least64_t");
  SUCCEED();
}

TEST_F(Umul96Lower64Test_312, ZeroOperandsProduceZero_312) {
  EXPECT_EQ(umul96_lower64(0u, 0ull), 0ull);
  EXPECT_EQ(umul96_lower64(0u, 123456789ull), 0ull);
  EXPECT_EQ(umul96_lower64(123456789u, 0ull), 0ull);
}

TEST_F(Umul96Lower64Test_312, OneOperandsMatchOtherLower64_312) {
  const std::uint64_t y = 0xFEDCBA9876543210ull;
  EXPECT_EQ(umul96_lower64(1u, y), ExpectedLower64(1u, y));

  const std::uint32_t x = 0xDEADBEEFu;
  EXPECT_EQ(umul96_lower64(x, 1ull), ExpectedLower64(x, 1ull));
}

TEST_F(Umul96Lower64Test_312, MaxValuesBoundary_312) {
  const std::uint32_t x = std::numeric_limits<std::uint32_t>::max();
  const std::uint64_t y = std::numeric_limits<std::uint64_t>::max();
  EXPECT_EQ(umul96_lower64(x, y), ExpectedLower64(x, y));
}

TEST_F(Umul96Lower64Test_312, HighBitsInYDoNotBreakLower64Computation_312) {
  const std::uint32_t x = 0xFFFFFFFFu;
  const std::uint64_t y = 0xFFFFFFFF00000000ull; // high 32 bits set, low 32 bits zero
  EXPECT_EQ(umul96_lower64(x, y), ExpectedLower64(x, y));
}

TEST_F(Umul96Lower64Test_312, MixedPatterns_312) {
  struct Case {
    std::uint32_t x;
    std::uint64_t y;
  };

  const Case cases[] = {
      {0x00000001u, 0x0000000100000001ull},
      {0x80000000u, 0x0000000200000003ull},
      {0x12345678u, 0x9ABCDEF012345678ull},
      {0x0000FFFFu, 0xFFFF0000FFFF0000ull},
      {0xFFFF0000u, 0x0000FFFF0000FFFFull},
  };

  for (const auto& c : cases) {
    EXPECT_EQ(umul96_lower64(c.x, c.y), ExpectedLower64(c.x, c.y))
        << "x=" << c.x << " y=" << c.y;
  }
}

TEST_F(Umul96Lower64Test_312, DeterministicRandomCoverage_312) {
  std::mt19937_64 rng(312); // fixed seed for reproducibility
  std::uniform_int_distribution<std::uint32_t> dist_x(
      0u, std::numeric_limits<std::uint32_t>::max());
  std::uniform_int_distribution<std::uint64_t> dist_y(
      0ull, std::numeric_limits<std::uint64_t>::max());

  for (int i = 0; i < 200; ++i) {
    const std::uint32_t x = dist_x(rng);
    const std::uint64_t y = dist_y(rng);
    EXPECT_EQ(umul96_lower64(x, y), ExpectedLower64(x, y))
        << "iteration=" << i << " x=" << x << " y=" << y;
  }
}

TEST_F(Umul96Lower64Test_312, UsableInConstantEvaluation_312) {
  // Verify it can be used in constant evaluation contexts (constexpr).
  constexpr std::uint32_t x = 0x12345678u;
  constexpr std::uint64_t y = 0x9ABCDEF012345678ull;
  constexpr std::uint64_t got = umul96_lower64(x, y);

#if defined(__SIZEOF_INT128__)
  constexpr unsigned __int128 prod =
      static_cast<unsigned __int128>(x) * static_cast<unsigned __int128>(y);
  constexpr std::uint64_t expect =
      static_cast<std::uint64_t>(prod & static_cast<unsigned __int128>(0xFFFFFFFFFFFFFFFFull));
  static_assert(got == expect, "constexpr result mismatch");
#endif

  EXPECT_EQ(got, ExpectedLower64(x, y));
}

}  // namespace