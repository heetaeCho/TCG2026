// Decrypt_sha256sigma0_test_1632.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <vector>

#if __has_include(<bit>)
#include <bit>
#endif

// NOTE:
// sha256sigma0() is declared `static inline` inside Decrypt.cc, so it is not link-visible.
// To test it through its provided interface, we include the translation unit directly.
//
// If your build already compiles Decrypt.cc into the test binary, this include may cause
// duplicate symbol errors. In that case, compile this test as the only TU that includes
// Decrypt.cc, or adjust your build to exclude Decrypt.cc from separate compilation for
// this test target.
#include "./TestProjects/poppler/poppler/Decrypt.cc"

namespace {

static inline uint32_t RotateRight32(uint32_t x, unsigned int r) {
  r &= 31u;
  return (r == 0) ? x : ((x >> r) | (x << (32u - r)));
}

// Reference implementation as an *oracle* based on the standard SHA-256 "small sigma0" definition.
// This is used only to validate observable behavior (return value) of sha256sigma0().
static inline uint32_t ReferenceSigma0(uint32_t x) {
#if defined(__cpp_lib_bitops) && (__cpp_lib_bitops >= 201907L)
  // Prefer standard library rotation if available (C++20).
  return static_cast<uint32_t>(std::rotr(x, 7) ^ std::rotr(x, 18) ^ (x >> 3));
#else
  return static_cast<uint32_t>(RotateRight32(x, 7) ^ RotateRight32(x, 18) ^ (x >> 3));
#endif
}

}  // namespace

TEST(Sha256Sigma0Test_1632, ReturnsExpectedForZero_1632) {
  const uint32_t x = 0u;
  const uint32_t got = static_cast<uint32_t>(sha256sigma0(static_cast<unsigned int>(x)));
  EXPECT_EQ(got, ReferenceSigma0(x));
  EXPECT_EQ(got, 0u);
}

TEST(Sha256Sigma0Test_1632, ReturnsExpectedForAllOnes_1632) {
  const uint32_t x = std::numeric_limits<uint32_t>::max();
  const uint32_t got = static_cast<uint32_t>(sha256sigma0(static_cast<unsigned int>(x)));
  EXPECT_EQ(got, ReferenceSigma0(x));
}

TEST(Sha256Sigma0Test_1632, ReturnsExpectedForSingleBitPatterns_1632) {
  const std::vector<uint32_t> inputs = {
      1u,
      2u,
      0x80000000u,  // high bit set
      0x00010000u,  // mid bit set
  };

  for (uint32_t x : inputs) {
    const uint32_t got = static_cast<uint32_t>(sha256sigma0(static_cast<unsigned int>(x)));
    EXPECT_EQ(got, ReferenceSigma0(x)) << "x=0x" << std::hex << x;
  }
}

TEST(Sha256Sigma0Test_1632, MatchesReferenceOnRepresentativeValues_1632) {
  const std::vector<uint32_t> inputs = {
      0x00000001u,
      0x00000008u,
      0x12345678u,
      0x89ABCDEFu,
      0x0F0F0F0Fu,
      0xF0F0F0F0u,
      0xAAAAAAAAu,
      0x55555555u,
      0xDEADBEEFu,
      0xCAFEBABEu,
  };

  for (uint32_t x : inputs) {
    const uint32_t got = static_cast<uint32_t>(sha256sigma0(static_cast<unsigned int>(x)));
    EXPECT_EQ(got, ReferenceSigma0(x)) << "x=0x" << std::hex << x;
  }
}

TEST(Sha256Sigma0Test_1632, IsDeterministicForSameInput_1632) {
  const uint32_t x = 0x13579BDFu;
  const uint32_t a = static_cast<uint32_t>(sha256sigma0(static_cast<unsigned int>(x)));
  const uint32_t b = static_cast<uint32_t>(sha256sigma0(static_cast<unsigned int>(x)));
  const uint32_t c = static_cast<uint32_t>(sha256sigma0(static_cast<unsigned int>(x)));
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}