// File: ./TestProjects/yaml-cpp/test/dragonbox_umul128_upper64_test_308.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using u64 = std::uint_least64_t;

static inline u64 ExpectedHigh64(u64 x, u64 y) {
#if defined(__SIZEOF_INT128__)
  using u128 = __uint128_t;
  u128 prod = static_cast<u128>(x) * static_cast<u128>(y);
  return static_cast<u64>(prod >> 64);
#elif defined(_MSC_VER) && defined(_M_X64)
  // MSVC x64 provides _umul128: returns low 64, stores high 64.
  #include <intrin.h>
  unsigned __int64 high = 0;
  (void)_umul128(static_cast<unsigned __int64>(x),
                 static_cast<unsigned __int64>(y),
                 &high);
  return static_cast<u64>(high);
#else
  // Fallback: only usable for cases where the expected value is known analytically
  // (tests will avoid calling this function on unsupported platforms).
  (void)x;
  (void)y;
  return 0;
#endif
}

}  // namespace

namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace wuint {

TEST(Umul128Upper64Test_308, IsNoexcept_308) {
  static_assert(noexcept(umul128_upper64(u64{0}, u64{0})),
                "umul128_upper64 must be noexcept");
  SUCCEED();
}

TEST(Umul128Upper64Test_308, ConstexprEvaluationWorks_308) {
  constexpr u64 v1 = umul128_upper64(u64{0}, u64{123});
  constexpr u64 v2 = umul128_upper64(u64{1}, u64{std::numeric_limits<u64>::max()});
  EXPECT_EQ(v1, 0u);
  EXPECT_EQ(v2, 0u);
}

TEST(Umul128Upper64Test_308, ZeroTimesAnythingIsZero_308) {
  EXPECT_EQ(umul128_upper64(u64{0}, u64{0}), u64{0});
  EXPECT_EQ(umul128_upper64(u64{0}, u64{1}), u64{0});
  EXPECT_EQ(umul128_upper64(u64{0}, std::numeric_limits<u64>::max()), u64{0});
  EXPECT_EQ(umul128_upper64(u64{123456789}, u64{0}), u64{0});
}

TEST(Umul128Upper64Test_308, OneTimesAnythingHasZeroHigh64_308) {
  EXPECT_EQ(umul128_upper64(u64{1}, u64{0}), u64{0});
  EXPECT_EQ(umul128_upper64(u64{1}, u64{1}), u64{0});
  EXPECT_EQ(umul128_upper64(u64{1}, std::numeric_limits<u64>::max()), u64{0});
  EXPECT_EQ(umul128_upper64(std::numeric_limits<u64>::max(), u64{1}), u64{0});
}

TEST(Umul128Upper64Test_308, PowerOfTwoCrosses64BitBoundary_308) {
  // 2^63 * 2 = 2^64 -> high64 == 1
  EXPECT_EQ(umul128_upper64(u64{1} << 63, u64{2}), u64{1});
  EXPECT_EQ(umul128_upper64(u64{2}, u64{1} << 63), u64{1});

  // 2^32 * 2^32 = 2^64 -> high64 == 1
  EXPECT_EQ(umul128_upper64(u64{1} << 32, u64{1} << 32), u64{1});

  // (2^32 - 1) * (2^32 - 1) < 2^64 -> high64 == 0
  EXPECT_EQ(umul128_upper64((u64{1} << 32) - 1, (u64{1} << 32) - 1), u64{0});
}

TEST(Umul128Upper64Test_308, CommutativeForSampleValues_308) {
  const u64 samples[] = {
      u64{0},
      u64{1},
      u64{2},
      u64{3},
      (u64{1} << 32) - 1,
      (u64{1} << 32),
      (u64{1} << 63),
      std::numeric_limits<u64>::max(),
      u64{0x0123456789ABCDEFULL},
      u64{0xFEDCBA9876543210ULL},
  };

  for (u64 x : samples) {
    for (u64 y : samples) {
      EXPECT_EQ(umul128_upper64(x, y), umul128_upper64(y, x))
          << "x=" << static_cast<unsigned long long>(x)
          << " y=" << static_cast<unsigned long long>(y);
    }
  }
}

TEST(Umul128Upper64Test_308, MaxTimesMaxMatchesKnownResult_308) {
  // (2^64 - 1)^2 = 2^128 - 2^65 + 1 -> high64 = 2^64 - 2
  const u64 max = std::numeric_limits<u64>::max();
  const u64 expected = std::numeric_limits<u64>::max() - 1;
  EXPECT_EQ(umul128_upper64(max, max), expected);
}

#if defined(__SIZEOF_INT128__) || (defined(_MSC_VER) && defined(_M_X64))
TEST(Umul128Upper64Test_308, MatchesReferenceForVariousVectors_308) {
  struct Vec { u64 x; u64 y; };
  const Vec vecs[] = {
      {u64{0}, u64{0}},
      {u64{0}, u64{123}},
      {u64{1}, u64{123}},
      {u64{2}, u64{3}},
      {u64{10}, u64{20}},
      {u64{0xFFFFFFFFFFFFFFFFULL}, u64{2}},
      {u64{0x8000000000000000ULL}, u64{0x8000000000000000ULL}},
      {u64{0x0123456789ABCDEFULL}, u64{0x1111111111111111ULL}},
      {u64{0xFEDCBA9876543210ULL}, u64{0x2222222222222222ULL}},
      {u64{0x0123456789ABCDEFULL}, u64{0xFEDCBA9876543210ULL}},
  };

  for (const auto& v : vecs) {
    const u64 got = umul128_upper64(v.x, v.y);
    const u64 exp = ExpectedHigh64(v.x, v.y);
    EXPECT_EQ(got, exp)
        << "x=" << static_cast<unsigned long long>(v.x)
        << " y=" << static_cast<unsigned long long>(v.y);
  }
}

TEST(Umul128Upper64Test_308, RandomLookingButDeterministicPairsMatchReference_308) {
  // Deterministic "random-looking" values to exercise a variety of bit patterns.
  const u64 xs[] = {
      u64{0x00000000FFFFFFFFULL},
      u64{0xFFFFFFFF00000000ULL},
      u64{0x7FFFFFFFFFFFFFFFULL},
      u64{0x8000000000000001ULL},
      u64{0xA5A5A5A5A5A5A5A5ULL},
  };
  const u64 ys[] = {
      u64{0x0000000100000001ULL},
      u64{0xDEADBEEFCAFEBABEULL},
      u64{0x0101010101010101ULL},
      u64{0xFFFFFFFFFFFFFFFFULL},
      u64{0x5A5A5A5A5A5A5A5AULL},
  };

  for (u64 x : xs) {
    for (u64 y : ys) {
      EXPECT_EQ(umul128_upper64(x, y), ExpectedHigh64(x, y))
          << "x=" << static_cast<unsigned long long>(x)
          << " y=" << static_cast<unsigned long long>(y);
    }
  }
}
#endif

}}}}}  // namespace YAML::jkj::dragonbox::detail::wuint