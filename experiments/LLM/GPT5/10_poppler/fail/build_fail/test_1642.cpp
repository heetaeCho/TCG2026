// Decrypt_sha512sigma1_test_1642.cc
#include <gtest/gtest.h>

#include <cstdint>

// NOTE:
// sha512sigma1 is a "static inline" function in Decrypt.cc, so it is not link-visible
// from other translation units. To test it as a black box without re-implementing it,
// we include the .cc file directly into this test TU.
//
// If your build system already compiles Decrypt.cc separately, ensure this test file is
// compiled WITHOUT also linking another Decrypt.cc object to avoid duplicate symbols.
#include "Decrypt.cc"

namespace {

class Sha512Sigma1Test_1642 : public ::testing::Test {};

TEST_F(Sha512Sigma1Test_1642, ZeroInputReturnsZero_1642) {
  const uint64_t out = sha512sigma1(0ULL);
  EXPECT_EQ(out, 0ULL);
}

TEST_F(Sha512Sigma1Test_1642, DeterministicForSameInput_1642) {
  const uint64_t x = 0x0123456789ABCDEFULL;

  const uint64_t out1 = sha512sigma1(x);
  const uint64_t out2 = sha512sigma1(x);
  const uint64_t out3 = sha512sigma1(x);

  EXPECT_EQ(out1, out2);
  EXPECT_EQ(out2, out3);
}

TEST_F(Sha512Sigma1Test_1642, LinearityOverXor_1642) {
  // Rotations, shifts, and XOR are linear over GF(2), so for a function composed only
  // of those operations, f(a ^ b) == f(a) ^ f(b).
  //
  // This is an observable behavioral property test (metamorphic), not a reimplementation
  // of internal logic.
  const uint64_t a = 0x0F0E0D0C0B0A0908ULL;
  const uint64_t b = 0xF0E1D2C3B4A59687ULL;

  const uint64_t fa = sha512sigma1(a);
  const uint64_t fb = sha512sigma1(b);
  const uint64_t fab = sha512sigma1(a ^ b);

  EXPECT_EQ(fab, (fa ^ fb));
}

TEST_F(Sha512Sigma1Test_1642, LinearityWithZeroIsIdentity_1642) {
  const uint64_t a = 0xDEADBEEFCAFEBABEULL;

  const uint64_t fa = sha512sigma1(a);
  const uint64_t f0 = sha512sigma1(0ULL);
  const uint64_t fa_xor_0 = sha512sigma1(a ^ 0ULL);

  EXPECT_EQ(f0, 0ULL);
  EXPECT_EQ(fa_xor_0, fa);
}

TEST_F(Sha512Sigma1Test_1642, HandlesUint64Boundaries_1642) {
  // Boundary inputs: smallest, largest, and a couple of edge-ish values.
  const uint64_t xs[] = {
      0ULL,
      1ULL,
      0x8000000000000000ULL,
      0xFFFFFFFFFFFFFFFFULL,
  };

  // Observable behavior: function is callable and produces stable results for boundaries.
  for (uint64_t x : xs) {
    const uint64_t out1 = sha512sigma1(x);
    const uint64_t out2 = sha512sigma1(x);
    EXPECT_EQ(out1, out2) << "x=" << std::hex << x;
  }

  // Extra observable special-case: already covered, but keep explicit.
  EXPECT_EQ(sha512sigma1(0ULL), 0ULL);
}

}  // namespace