// TEST_ID: 310
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <random>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::wuint::umul96_upper64;

// Reference computation for: floor((x * y) / 2^32).
// Implemented in a way that is portable across common toolchains.
static inline std::uint64_t RefU64_Umul96Upper64(std::uint32_t x, std::uint64_t y) {
#if defined(__SIZEOF_INT128__)
  __uint128_t prod = static_cast<__uint128_t>(x) * static_cast<__uint128_t>(y);
  return static_cast<std::uint64_t>(prod >> 32);
#elif defined(_MSC_VER) && defined(_M_X64)
  // Use MSVC intrinsic _umul128 for a 64x64->128 multiply.
  // We want (x * y) >> 32, but x is 32-bit, so we can still safely do 64x64.
  unsigned __int64 high = 0;
  unsigned __int64 low = _umul128(static_cast<unsigned __int64>(x), static_cast<unsigned __int64>(y), &high);
  // Combine (high:low) >> 32.
  return (static_cast<std::uint64_t>(high) << 32) | (static_cast<std::uint64_t>(low) >> 32);
#else
  // Fully portable fallback (no 128-bit type or MSVC x64 intrinsic available).
  // This computes floor((x*y)/2^32) using arithmetic decomposition.
  const std::uint32_t yh = static_cast<std::uint32_t>(y >> 32);
  const std::uint32_t yl = static_cast<std::uint32_t>(y);

  const std::uint64_t xyl = static_cast<std::uint64_t>(x) * static_cast<std::uint64_t>(yl);
  const std::uint64_t xyh = static_cast<std::uint64_t>(x) * static_cast<std::uint64_t>(yh);

  return xyh + (xyl >> 32);
#endif
}

class Umul96Upper64Test_310 : public ::testing::Test {};

TEST_F(Umul96Upper64Test_310, ZeroInputsReturnZero_310) {
  EXPECT_EQ(umul96_upper64(0u, 0ull), 0ull);
  EXPECT_EQ(umul96_upper64(0u, 123456789ull), 0ull);
  EXPECT_EQ(umul96_upper64(123u, 0ull), 0ull);
}

TEST_F(Umul96Upper64Test_310, OneTimesYMatchesShiftedY_310) {
  // For x=1: floor((1*y)/2^32) == y >> 32.
  const std::uint64_t y1 = 0x0000000100000000ull;
  const std::uint64_t y2 = 0xFFFFFFFF00000000ull;
  const std::uint64_t y3 = 0x123456789ABCDEF0ull;

  EXPECT_EQ(umul96_upper64(1u, y1), (y1 >> 32));
  EXPECT_EQ(umul96_upper64(1u, y2), (y2 >> 32));
  EXPECT_EQ(umul96_upper64(1u, y3), (y3 >> 32));
}

TEST_F(Umul96Upper64Test_310, PowersOfTwoXBoundaryBehavior_310) {
  const std::uint64_t y = 0xFEDCBA9876543210ull;

  // x = 2^31 and x = 2^32-1 are interesting 32-bit boundary values.
  const std::uint32_t x1 = 0x80000000u;
  const std::uint32_t x2 = 0xFFFFFFFFu;

  EXPECT_EQ(umul96_upper64(x1, y), RefU64_Umul96Upper64(x1, y));
  EXPECT_EQ(umul96_upper64(x2, y), RefU64_Umul96Upper64(x2, y));
}

TEST_F(Umul96Upper64Test_310, MaxValuesMatchReference_310) {
  const std::uint32_t x = std::numeric_limits<std::uint32_t>::max();
  const std::uint64_t y = std::numeric_limits<std::uint64_t>::max();

  EXPECT_EQ(umul96_upper64(x, y), RefU64_Umul96Upper64(x, y));
}

TEST_F(Umul96Upper64Test_310, VariedHandpickedValuesMatchReference_310) {
  struct Case {
    std::uint32_t x;
    std::uint64_t y;
  };

  const Case cases[] = {
      {2u, 0x00000000FFFFFFFFull},
      {3u, 0x0000000100000001ull},
      {0x0000FFFFu, 0xFFFF00000000FFFFull},
      {0x00ABCDEFu, 0x0123456789ABCDEFull},
      {0x13579BDFu, 0xFEDCBA9876543210ull},
  };

  for (const auto& c : cases) {
    EXPECT_EQ(umul96_upper64(c.x, c.y), RefU64_Umul96Upper64(c.x, c.y))
        << "x=" << c.x << " y=" << c.y;
  }
}

TEST_F(Umul96Upper64Test_310, RandomizedSamplesMatchReference_310) {
  std::mt19937_64 rng(0xC0FFEE310ull);
  std::uniform_int_distribution<std::uint32_t> dist32(
      0u, std::numeric_limits<std::uint32_t>::max());
  std::uniform_int_distribution<std::uint64_t> dist64(
      0ull, std::numeric_limits<std::uint64_t>::max());

  // Keep sample count moderate to avoid flaky long runtimes.
  for (int i = 0; i < 2000; ++i) {
    const std::uint32_t x = dist32(rng);
    const std::uint64_t y = dist64(rng);
    EXPECT_EQ(umul96_upper64(x, y), RefU64_Umul96Upper64(x, y))
        << "iteration=" << i << " x=" << x << " y=" << y;
  }
}

// Compile-time checks (if the header provides constexpr behavior in this build).
#if defined(__SIZEOF_INT128__) || (defined(_MSC_VER) && defined(_M_X64))
TEST_F(Umul96Upper64Test_310, ConstexprEvaluationMatchesReference_310) {
#if defined(__SIZEOF_INT128__)
  constexpr std::uint32_t x = 0x89ABCDEFu;
  constexpr std::uint64_t y = 0x0123456789ABCDEFull;
  constexpr std::uint64_t expected =
      static_cast<std::uint64_t>((static_cast<__uint128_t>(x) * static_cast<__uint128_t>(y)) >> 32);
  constexpr std::uint64_t got = umul96_upper64(x, y);
  static_assert(got == expected, "umul96_upper64 constexpr result mismatch");
  EXPECT_EQ(got, expected);
#else
  // On MSVC x64, constexpr support may vary with intrinsics; still do a runtime check.
  const std::uint32_t x = 0x89ABCDEFu;
  const std::uint64_t y = 0x0123456789ABCDEFull;
  EXPECT_EQ(umul96_upper64(x, y), RefU64_Umul96Upper64(x, y));
#endif
}
#endif

}  // namespace