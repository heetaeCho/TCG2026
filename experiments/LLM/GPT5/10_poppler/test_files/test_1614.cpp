// Decrypt_Aes256KeyExpansion_test_1614.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// NOTE: We include the implementation file to access the internal-linkage (static)
// function under test. This keeps the test black-box with respect to behavior
// (we only observe outputs via the public struct fields).
#include "Decrypt.h"
#include "Decrypt.cc"

namespace {

class Aes256KeyExpansionTest_1614 : public ::testing::Test {
protected:
  static std::array<unsigned char, 32> MakeIncrementingKey() {
    std::array<unsigned char, 32> k{};
    for (size_t i = 0; i < k.size(); ++i) {
      k[i] = static_cast<unsigned char>(i);
    }
    return k;
  }

  static std::array<unsigned char, 32> MakeZeroKey() {
    std::array<unsigned char, 32> k{};
    k.fill(0);
    return k;
  }

  static unsigned int BeWord(const unsigned char *p) {
    return (static_cast<unsigned int>(p[0]) << 24) |
           (static_cast<unsigned int>(p[1]) << 16) |
           (static_cast<unsigned int>(p[2]) << 8) |
           (static_cast<unsigned int>(p[3]));
  }

  static bool AnyDiffInRange(const DecryptAES256State &a,
                             const DecryptAES256State &b,
                             int begin, int endInclusive) {
    for (int i = begin; i <= endInclusive; ++i) {
      if (a.w[i] != b.w[i]) return true;
    }
    return false;
  }
};

TEST_F(Aes256KeyExpansionTest_1614, EncryptCopiesFirst8WordsFromObjKey_1614) {
  DecryptAES256State s{};
  const auto key = MakeIncrementingKey();

  aes256KeyExpansion(&s, key.data(), /*decrypt=*/false);

  // Observable behavior: the first 8 words reflect the 32-byte key material.
  for (int i = 0; i < 8; ++i) {
    const unsigned int expected = BeWord(&key[4 * i]);
    EXPECT_EQ(s.w[i], expected) << "word index " << i;
  }
}

TEST_F(Aes256KeyExpansionTest_1614, DeterministicForSameInput_1614) {
  DecryptAES256State a{};
  DecryptAES256State b{};
  const auto key = MakeIncrementingKey();

  aes256KeyExpansion(&a, key.data(), /*decrypt=*/false);
  aes256KeyExpansion(&b, key.data(), /*decrypt=*/false);

  for (int i = 0; i < 60; ++i) {
    EXPECT_EQ(a.w[i], b.w[i]) << "word index " << i;
  }
}

TEST_F(Aes256KeyExpansionTest_1614, DifferentKeysChangeSchedule_1614) {
  DecryptAES256State a{};
  DecryptAES256State b{};
  auto key1 = MakeZeroKey();
  auto key2 = MakeZeroKey();
  key2[31] = 0x01; // minimal difference

  aes256KeyExpansion(&a, key1.data(), /*decrypt=*/false);
  aes256KeyExpansion(&b, key2.data(), /*decrypt=*/false);

  // We only require that the expanded key differs somewhere.
  EXPECT_TRUE(AnyDiffInRange(a, b, 0, 59));
}

TEST_F(Aes256KeyExpansionTest_1614, DecryptFlagPreservesFirstAndLastWordsButChangesMiddle_1614) {
  DecryptAES256State enc{};
  DecryptAES256State dec{};
  const auto key = MakeIncrementingKey();

  aes256KeyExpansion(&enc, key.data(), /*decrypt=*/false);
  aes256KeyExpansion(&dec, key.data(), /*decrypt=*/true);

  // Observable: some parts remain identical between modes.
  for (int i = 0; i <= 3; ++i) {
    EXPECT_EQ(enc.w[i], dec.w[i]) << "first block word index " << i;
  }
  for (int i = 56; i <= 59; ++i) {
    EXPECT_EQ(enc.w[i], dec.w[i]) << "last block word index " << i;
  }

  // And the decrypt path should adjust at least one word in the middle.
  EXPECT_TRUE(AnyDiffInRange(enc, dec, 4, 55));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(Aes256KeyExpansionTest_1614, DeathOnNullStatePointer_1614) {
  const auto key = MakeIncrementingKey();
  ASSERT_DEATH(
      {
        aes256KeyExpansion(nullptr, key.data(), /*decrypt=*/false);
      },
      ".*");
}

TEST_F(Aes256KeyExpansionTest_1614, DeathOnNullKeyPointer_1614) {
  DecryptAES256State s{};
  ASSERT_DEATH(
      {
        aes256KeyExpansion(&s, nullptr, /*decrypt=*/false);
      },
      ".*");
}
#endif

} // namespace