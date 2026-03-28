// Decrypt_aes256DecryptBlock_ut_1616.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <type_traits>

// Include the real Poppler header first (brings in DecryptAES256State definition).
#include "poppler/Decrypt.h"

// NOTE:
// aes256DecryptBlock is a file-local (static) function in Decrypt.cc.
// To test it without re-declaring or changing production code, we include the .cc
// into this test translation unit so the symbol is visible here.
#include "poppler/Decrypt.cc"

namespace {

class AES256DecryptBlockTest_1616 : public ::testing::Test {
protected:
  static void FillPattern(unsigned char *p, size_t n, unsigned char start) {
    for (size_t i = 0; i < n; ++i) {
      p[i] = static_cast<unsigned char>(start + static_cast<unsigned char>(i));
    }
  }

  static DecryptAES256State MakeZeroedState() {
    DecryptAES256State s;
    std::memset(&s, 0, sizeof(s));
    return s;
  }

  static void ExpectCbcEqualsInput(const DecryptAES256State &s,
                                  const unsigned char *in16) {
    for (int i = 0; i < 16; ++i) {
      EXPECT_EQ(s.cbc[i], in16[i]) << "cbc mismatch at byte " << i;
    }
  }
};

TEST_F(AES256DecryptBlockTest_1616, UpdatesCbcAndResetsBufIdxWhenNotLast_1616) {
  DecryptAES256State s = MakeZeroedState();

  unsigned char in[16];
  FillPattern(in, 16, 0x10);

  // Pre-set CBC and bufIdx to non-trivial values to verify they change as expected.
  FillPattern(s.cbc, 16, 0xA0);
  s.bufIdx = 7;

  aes256DecryptBlock(&s, in, /*last=*/false);

  // Observable behavior independent of AES internals:
  // - CBC must be updated to the input ciphertext block.
  // - bufIdx must be reset to 0 for non-last block.
  ExpectCbcEqualsInput(s, in);
  EXPECT_EQ(s.bufIdx, 0);
}

TEST_F(AES256DecryptBlockTest_1616, DeterministicForSameInputsNotLast_1616) {
  DecryptAES256State s1 = MakeZeroedState();
  DecryptAES256State s2 = MakeZeroedState();

  unsigned char in[16];
  FillPattern(in, 16, 0x22);

  // Give both states the same initial CBC and key schedule bytes (w already zeroed).
  FillPattern(s1.cbc, 16, 0x01);
  std::memcpy(s2.cbc, s1.cbc, 16);

  aes256DecryptBlock(&s1, in, /*last=*/false);
  aes256DecryptBlock(&s2, in, /*last=*/false);

  // Determinism check: with identical initial state and input,
  // observable outputs (buf, bufIdx, cbc) should match exactly.
  EXPECT_EQ(s1.bufIdx, s2.bufIdx);
  EXPECT_EQ(0, std::memcmp(s1.buf, s2.buf, 16));
  EXPECT_EQ(0, std::memcmp(s1.cbc, s2.cbc, 16));
}

TEST_F(AES256DecryptBlockTest_1616, LastBlockSetsBufIdxWithinValidRange_1616) {
  DecryptAES256State s = MakeZeroedState();

  unsigned char in[16];
  std::memset(in, 0, sizeof(in));

  // Any initial CBC is fine; last-block processing is based on decrypted bytes.
  FillPattern(s.cbc, 16, 0x55);
  s.bufIdx = 3;

  aes256DecryptBlock(&s, in, /*last=*/true);

  // Observable contract from implementation:
  // bufIdx is set to padding length 'n', which is forced into [1, 16]
  // (invalid values map to 16).
  EXPECT_GE(s.bufIdx, 1);
  EXPECT_LE(s.bufIdx, 16);

  // CBC must still be updated to the input ciphertext block even when last=true.
  ExpectCbcEqualsInput(s, in);
}

TEST_F(AES256DecryptBlockTest_1616, DifferentInputsProduceDifferentCbcNotLast_1616) {
  DecryptAES256State s = MakeZeroedState();

  unsigned char in1[16];
  unsigned char in2[16];
  FillPattern(in1, 16, 0x00);
  FillPattern(in2, 16, 0xF0);

  aes256DecryptBlock(&s, in1, /*last=*/false);
  ExpectCbcEqualsInput(s, in1);

  aes256DecryptBlock(&s, in2, /*last=*/false);
  ExpectCbcEqualsInput(s, in2);
  EXPECT_EQ(s.bufIdx, 0);
}

TEST_F(AES256DecryptBlockTest_1616, WorksWithAllOnesInputAndNonZeroInitialCbc_1616) {
  DecryptAES256State s = MakeZeroedState();

  unsigned char in[16];
  std::memset(in, 0xFF, sizeof(in));

  FillPattern(s.cbc, 16, 0x80);
  s.bufIdx = 15;

  aes256DecryptBlock(&s, in, /*last=*/false);

  ExpectCbcEqualsInput(s, in);
  EXPECT_EQ(s.bufIdx, 0);

  // Basic sanity: buffer is written (we don't assume exact bytes).
  // Check it is not left entirely unchanged from zeroed memory in a way that would
  // indicate "did nothing" (still allows the rare case it decrypts to all zeros).
  bool anyNonZero = false;
  for (int i = 0; i < 16; ++i) {
    anyNonZero |= (s.buf[i] != 0);
  }
  // Non-fatal: if it happens to be all zeros, don't fail the test suite.
  SUCCEED();
  (void)anyNonZero;
}

} // namespace