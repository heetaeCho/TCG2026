// File: Decrypt_sha256Ch_test_1628.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// The function under test has internal linkage (static inline) in Decrypt.cc.
// To test it without re-implementing it, include the .cc directly in this TU.
#include "./TestProjects/poppler/poppler/Decrypt.cc"

class Sha256ChTest_1628 : public ::testing::Test {};

TEST_F(Sha256ChTest_1628, ZeroXSelectsZ_1628) {
  const unsigned int x = 0u;

  EXPECT_EQ(sha256Ch(x, 0u, 0u), 0u);
  EXPECT_EQ(sha256Ch(x, 0x12345678u, 0u), 0u);
  EXPECT_EQ(sha256Ch(x, 0u, 0x12345678u), 0x12345678u);
  EXPECT_EQ(sha256Ch(x, 0xFFFFFFFFu, 0x89ABCDEFu), 0x89ABCDEFu);
}

TEST_F(Sha256ChTest_1628, AllOnesXSelectsY_1628) {
  const unsigned int x = std::numeric_limits<unsigned int>::max();

  EXPECT_EQ(sha256Ch(x, 0u, 0u), 0u);
  EXPECT_EQ(sha256Ch(x, 0x12345678u, 0u), 0x12345678u);
  EXPECT_EQ(sha256Ch(x, 0u, 0x12345678u), 0u);
  EXPECT_EQ(sha256Ch(x, 0x89ABCDEFu, 0xFFFFFFFFu), 0x89ABCDEFu);
}

TEST_F(Sha256ChTest_1628, EqualYAndZReturnsThatValue_1628) {
  const unsigned int y = 0xA5A5A5A5u;
  const unsigned int z = 0xA5A5A5A5u;

  EXPECT_EQ(sha256Ch(0u, y, z), y);
  EXPECT_EQ(sha256Ch(std::numeric_limits<unsigned int>::max(), y, z), y);
  EXPECT_EQ(sha256Ch(0x12345678u, y, z), y);
  EXPECT_EQ(sha256Ch(0xFFFFFFFFu ^ 0x12345678u, y, z), y);
}

TEST_F(Sha256ChTest_1628, KnownVector_MixedPatterns_1628) {
  // Precomputed expected output for these inputs (no internal state involved).
  const unsigned int x = 0xF0F0F0F0u;
  const unsigned int y = 0xAAAA5555u;
  const unsigned int z = 0x12345678u;

  EXPECT_EQ(sha256Ch(x, y, z), 0xA2A45658u);
}

TEST_F(Sha256ChTest_1628, KnownVector_AnotherCombination_1628) {
  const unsigned int x = 0x12345678u;
  const unsigned int y = 0x9ABCDEF0u;
  const unsigned int z = 0x0F0F0F0Fu;

  EXPECT_EQ(sha256Ch(x, y, z), 0x1F3F5F77u);
}

TEST_F(Sha256ChTest_1628, DeterministicForSameInputs_1628) {
  const unsigned int x = 0x0F0F0F0Fu;
  const unsigned int y = 0xFFFFFFFFu;
  const unsigned int z = 0x00000000u;

  const unsigned int r1 = sha256Ch(x, y, z);
  const unsigned int r2 = sha256Ch(x, y, z);

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r1, 0x0F0F0F0Fu);
}