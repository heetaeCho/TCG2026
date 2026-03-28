// Decrypt_sha512sigma0_test_1641.cc
#include <gtest/gtest.h>
#include <cstdint>

// NOTE:
// sha512sigma0() is declared `static inline` in Decrypt.cc, so it has internal linkage.
// To test it without re-implementing or altering production code, we include the .cc here.
#include "Decrypt.cc"

namespace {

class DecryptSha512Sigma0Test_1641 : public ::testing::Test {};

TEST_F(DecryptSha512Sigma0Test_1641, ReturnsZeroForZero_1641) {
  const uint64_t x = 0u;
  EXPECT_EQ(sha512sigma0(x), 0u);
}

TEST_F(DecryptSha512Sigma0Test_1641, KnownVectorOne_1641) {
  const uint64_t x = 1u;
  EXPECT_EQ(sha512sigma0(x), 0x8100000000000000ULL);
}

TEST_F(DecryptSha512Sigma0Test_1641, KnownVectorAllOnes_1641) {
  const uint64_t x = 0xFFFFFFFFFFFFFFFFULL;
  EXPECT_EQ(sha512sigma0(x), 0x01FFFFFFFFFFFFFFULL);
}

TEST_F(DecryptSha512Sigma0Test_1641, KnownVectorAscendingBytes_1641) {
  const uint64_t x = 0x0123456789ABCDEFULL;
  EXPECT_EQ(sha512sigma0(x), 0x6F92C77C6C4F1AA1ULL);
}

TEST_F(DecryptSha512Sigma0Test_1641, KnownVectorHighestBitSet_1641) {
  const uint64_t x = 0x8000000000000000ULL;
  EXPECT_EQ(sha512sigma0(x), 0x4180000000000000ULL);
}

TEST_F(DecryptSha512Sigma0Test_1641, KnownVectorLowestBitsAllSet_1641) {
  const uint64_t x = 0x7FFFFFFFFFFFFFFFULL;
  EXPECT_EQ(sha512sigma0(x), 0x407FFFFFFFFFFFFFULL);
}

TEST_F(DecryptSha512Sigma0Test_1641, KnownVectorRepeatingNibblePattern_1641) {
  const uint64_t x = 0xF0F0F0F0F0F0F0F0ULL;
  EXPECT_EQ(sha512sigma0(x), 0x8969696969696969ULL);
}

TEST_F(DecryptSha512Sigma0Test_1641, DeterministicForSameInput_1641) {
  const uint64_t x = 0x0123456789ABCDEFULL;
  const uint64_t a = sha512sigma0(x);
  const uint64_t b = sha512sigma0(x);
  EXPECT_EQ(a, b);
}

TEST_F(DecryptSha512Sigma0Test_1641, ProducesDifferentResultsForDifferentInputs_1641) {
  const uint64_t a = 0x0000000000000001ULL;
  const uint64_t b = 0x0000000000000002ULL;

  // Not asserting any internal formula—just that distinct inputs should not
  // trivially collapse to the same output for these representative values.
  EXPECT_NE(sha512sigma0(a), sha512sigma0(b));
}

} // namespace