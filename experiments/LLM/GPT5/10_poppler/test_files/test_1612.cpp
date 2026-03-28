// Decrypt_aesEncryptBlock_test_1612.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// Poppler header (as given)
#include "Decrypt.h"

// NOTE:
// aesEncryptBlock is a static function in Decrypt.cc (internal linkage).
// To test it as a black box without re-implementing logic, we include the .cc
// so the function is in this test translation unit.
#include "Decrypt.cc"

namespace {

class DecryptAesEncryptBlockTest_1612 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  }

  static DecryptAESState MakeState(uint8_t wSeed, uint8_t bufSeed, bool padding, int bufIdx) {
    DecryptAESState s{};
    // Initialize key schedule deterministically.
    for (int i = 0; i < 44; ++i) {
      // Keep it deterministic and non-trivial.
      s.w[i] = static_cast<unsigned int>(wSeed + i) * 0x01010101u;
    }

    // Fill internal arrays with recognizable patterns.
    for (int i = 0; i < 16; ++i) {
      s.state[i] = static_cast<unsigned char>(0xA0u + i);
      s.cbc[i]   = static_cast<unsigned char>(0xB0u + i);
      s.buf[i]   = static_cast<unsigned char>(bufSeed + i);
    }

    s.paddingReached = padding;
    s.bufIdx = bufIdx;
    return s;
  }

  static std::array<unsigned char, 16> MakeInput(uint8_t seed) {
    std::array<unsigned char, 16> in{};
    for (int i = 0; i < 16; ++i) {
      in[i] = static_cast<unsigned char>(seed + i);
    }
    return in;
  }

  static bool MemEqual(const void* a, const void* b, size_t n) {
    return std::memcmp(a, b, n) == 0;
  }
};

TEST_F(DecryptAesEncryptBlockTest_1612, ResetsBufIdxToZero_1612) {
  auto s = MakeState(/*wSeed=*/1, /*bufSeed=*/10, /*padding=*/false, /*bufIdx=*/15);
  const auto in = MakeInput(/*seed=*/0x11);

  aesEncryptBlock(&s, in.data());

  EXPECT_EQ(s.bufIdx, 0);
}

TEST_F(DecryptAesEncryptBlockTest_1612, DeterministicForSameInitialStateAndInput_1612) {
  auto s1 = MakeState(/*wSeed=*/3, /*bufSeed=*/0x22, /*padding=*/true, /*bufIdx=*/7);
  auto s2 = s1; // clone initial state byte-for-byte
  const auto in = MakeInput(/*seed=*/0x33);

  // Snapshot fields that should not be affected by block encryption as observed through interface.
  // (We only assert invariants that are observable and reasonable for this helper.)
  const auto w_before = s1.w;
  const auto cbc_before = s1.cbc;
  const bool padding_before = s1.paddingReached;

  aesEncryptBlock(&s1, in.data());
  aesEncryptBlock(&s2, in.data());

  EXPECT_EQ(s1.bufIdx, 0);
  EXPECT_EQ(s2.bufIdx, 0);

  // Same input + same starting state => same resulting buf/state (determinism).
  EXPECT_TRUE(MemEqual(s1.buf, s2.buf, 16));
  EXPECT_TRUE(MemEqual(s1.state, s2.state, 16));

  // Key schedule should remain unchanged.
  EXPECT_TRUE(MemEqual(s1.w, w_before, sizeof(w_before)));
  // CBC buffer is separate from buf/state; should remain unchanged by this block helper.
  EXPECT_TRUE(MemEqual(s1.cbc, cbc_before, sizeof(cbc_before)));
  // paddingReached should remain unchanged by encrypting a single block.
  EXPECT_EQ(s1.paddingReached, padding_before);
}

TEST_F(DecryptAesEncryptBlockTest_1612, DifferentInputChangesOutputGivenSameInitialState_1612) {
  auto s1 = MakeState(/*wSeed=*/9, /*bufSeed=*/0x44, /*padding=*/false, /*bufIdx=*/0);
  auto s2 = s1;

  auto in1 = MakeInput(/*seed=*/0x10);
  auto in2 = in1;
  in2[7] ^= 0x01; // minimal change

  aesEncryptBlock(&s1, in1.data());
  aesEncryptBlock(&s2, in2.data());

  // Extremely strong expectation: changing plaintext should change ciphertext block.
  EXPECT_FALSE(MemEqual(s1.buf, s2.buf, 16));
}

TEST_F(DecryptAesEncryptBlockTest_1612, DifferentInitialBufChangesOutputForSameInputAndKey_1612) {
  auto s1 = MakeState(/*wSeed=*/5, /*bufSeed=*/0x00, /*padding=*/false, /*bufIdx=*/3);
  auto s2 = MakeState(/*wSeed=*/5, /*bufSeed=*/0xFF, /*padding=*/false, /*bufIdx=*/3);

  const auto in = MakeInput(/*seed=*/0x55);

  aesEncryptBlock(&s1, in.data());
  aesEncryptBlock(&s2, in.data());

  // buf participates in the initial xor, so different starting buf should affect output.
  EXPECT_FALSE(MemEqual(s1.buf, s2.buf, 16));
}

TEST_F(DecryptAesEncryptBlockTest_1612, DeathOnNullStatePointer_1612) {
  const auto in = MakeInput(/*seed=*/0x01);
  ASSERT_DEATH({ aesEncryptBlock(nullptr, in.data()); }, ".*");
}

TEST_F(DecryptAesEncryptBlockTest_1612, DeathOnNullInputPointer_1612) {
  auto s = MakeState(/*wSeed=*/1, /*bufSeed=*/2, /*padding=*/false, /*bufIdx=*/1);
  ASSERT_DEATH({ aesEncryptBlock(&s, nullptr); }, ".*");
}

} // namespace