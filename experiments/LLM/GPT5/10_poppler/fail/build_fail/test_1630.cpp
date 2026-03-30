// Decrypt_sha256Sigma0_test_1630.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// NOTE:
// sha256Sigma0 is a static inline function in Decrypt.cc (internal linkage).
// To test it via its real implementation, we include the .cc directly so the
// function is available in this translation unit.
//
// This is a common technique for unit-testing file-local helpers without
// changing production code.
#include "./TestProjects/poppler/poppler/Decrypt.cc"

class Sha256Sigma0Test_1630 : public ::testing::Test {
protected:
  static void Require32BitUnsignedIntOrSkip()
  {
    if (sizeof(unsigned int) != 4) {
      GTEST_SKIP() << "sha256Sigma0 tests assume 32-bit unsigned int.";
    }
  }
};

TEST_F(Sha256Sigma0Test_1630, ZeroInputProducesZero_1630)
{
  Require32BitUnsignedIntOrSkip();
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0u)), 0x00000000u);
}

TEST_F(Sha256Sigma0Test_1630, OneInputMatchesKnownVector_1630)
{
  Require32BitUnsignedIntOrSkip();
  // Precomputed expected value for input 0x00000001.
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0x00000001u)), 0x40080400u);
}

TEST_F(Sha256Sigma0Test_1630, AllOnesInputMatchesKnownVector_1630)
{
  Require32BitUnsignedIntOrSkip();
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0xFFFFFFFFu)), 0xFFFFFFFFu);
}

TEST_F(Sha256Sigma0Test_1630, PatternInput01234567MatchesKnownVector_1630)
{
  Require32BitUnsignedIntOrSkip();
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0x01234567u)), 0x66654447u);
}

TEST_F(Sha256Sigma0Test_1630, PatternInput89ABCDEFMatchesKnownVector_1630)
{
  Require32BitUnsignedIntOrSkip();
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0x89ABCDEFu)), 0x22210003u);
}

TEST_F(Sha256Sigma0Test_1630, BoundaryHighBitSetMatchesKnownVector_1630)
{
  Require32BitUnsignedIntOrSkip();
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0x80000000u)), 0x20040200u);
}

TEST_F(Sha256Sigma0Test_1630, BoundaryAllButHighBitSetMatchesKnownVector_1630)
{
  Require32BitUnsignedIntOrSkip();
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0x7FFFFFFFu)), 0xDFFBFDDDu);
}

TEST_F(Sha256Sigma0Test_1630, CommonSha256IVWordsMatchKnownVectors_1630)
{
  Require32BitUnsignedIntOrSkip();
  // A couple of well-known 32-bit words (from SHA-256 IV) as additional vectors.
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0x6A09E667u)), 0xCE20B47Eu);
  EXPECT_EQ(static_cast<uint32_t>(sha256Sigma0(0xBB67AE85u)), 0x844E2671u);
}

TEST_F(Sha256Sigma0Test_1630, DeterministicForSameInput_1630)
{
  Require32BitUnsignedIntOrSkip();

  const unsigned int x = 0x89ABCDEFu;
  const uint32_t a = static_cast<uint32_t>(sha256Sigma0(x));
  const uint32_t b = static_cast<uint32_t>(sha256Sigma0(x));
  EXPECT_EQ(a, b);
}