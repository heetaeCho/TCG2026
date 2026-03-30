// Decrypt_aes256EncryptBlock_test_1615.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <cstring>

// We include the implementation unit to access the internal static helper.
// IMPORTANT: This test file must be built without also compiling/linking Decrypt.cc
// as a separate translation unit, otherwise you'll get duplicate symbol errors.
#include "Decrypt.cc"

namespace {

constexpr size_t kBlockSize = 16;

template <typename T>
static void FillWithPattern(T *data, size_t n, uint32_t seed) {
  // Simple deterministic pattern (not crypto); just to avoid uninitialized data.
  for (size_t i = 0; i < n; ++i) {
    data[i] = static_cast<T>((seed + static_cast<uint32_t>(i * 131u)) & 0xFFu);
  }
}

static void FillU32Pattern(uint32_t *data, size_t n, uint32_t seed) {
  for (size_t i = 0; i < n; ++i) {
    // Deterministic, non-random.
    data[i] = seed ^ static_cast<uint32_t>(0x9E3779B9u * (i + 1));
  }
}

static void CopyState(const DecryptAES256State &src, DecryptAES256State *dst) {
  std::memcpy(dst, &src, sizeof(DecryptAES256State));
}

static bool BlockEq(const unsigned char *a, const unsigned char *b, size_t n) {
  return std::memcmp(a, b, n) == 0;
}

class Aes256EncryptBlockTest_1615 : public ::testing::Test {
protected:
  static void InitStateDeterministic(DecryptAES256State *s, uint32_t seedW, uint32_t seedBuf,
                                    int initialBufIdx) {
    // Fill round key schedule buffer deterministically.
    // (We do NOT assume anything about correctness of key expansion;
    //  only that the function should behave deterministically for a given state.)
    FillU32Pattern(reinterpret_cast<uint32_t *>(s->w), sizeof(s->w) / sizeof(s->w[0]), seedW);

    // Fill working buffers deterministically.
    FillWithPattern<unsigned char>(reinterpret_cast<unsigned char *>(s->buf),
                                   sizeof(s->buf) / sizeof(s->buf[0]), seedBuf);
    FillWithPattern<unsigned char>(reinterpret_cast<unsigned char *>(s->state),
                                   sizeof(s->state) / sizeof(s->state[0]), seedBuf ^ 0xA5u);

    s->bufIdx = initialBufIdx;
  }
};

TEST_F(Aes256EncryptBlockTest_1615, ResetsBufIdxToZero_1615) {
  DecryptAES256State s;
  InitStateDeterministic(&s, /*seedW=*/0x11111111u, /*seedBuf=*/0x22u, /*initialBufIdx=*/7);

  unsigned char in[kBlockSize];
  FillWithPattern<unsigned char>(in, kBlockSize, /*seed=*/0x33u);

  aes256EncryptBlock(&s, in);

  EXPECT_EQ(s.bufIdx, 0);
}

TEST_F(Aes256EncryptBlockTest_1615, DeterministicForSameStateAndInput_1615) {
  DecryptAES256State s1;
  DecryptAES256State s2;
  InitStateDeterministic(&s1, /*seedW=*/0xABCDEF01u, /*seedBuf=*/0x44u, /*initialBufIdx=*/-1);
  CopyState(s1, &s2);

  unsigned char in[kBlockSize];
  FillWithPattern<unsigned char>(in, kBlockSize, /*seed=*/0x55u);

  aes256EncryptBlock(&s1, in);
  aes256EncryptBlock(&s2, in);

  EXPECT_EQ(s1.bufIdx, 0);
  EXPECT_EQ(s2.bufIdx, 0);

  // Observable effect: the produced chaining buffer should match for identical inputs/state.
  EXPECT_TRUE(BlockEq(reinterpret_cast<unsigned char *>(s1.buf),
                      reinterpret_cast<unsigned char *>(s2.buf),
                      sizeof(s1.buf) / sizeof(s1.buf[0])));

  // Also the internal state array should match if both runs started identical.
  EXPECT_TRUE(BlockEq(reinterpret_cast<unsigned char *>(s1.state),
                      reinterpret_cast<unsigned char *>(s2.state),
                      sizeof(s1.state) / sizeof(s1.state[0])));
}

TEST_F(Aes256EncryptBlockTest_1615, DifferentInputProducesDifferentOutputBuffer_1615) {
  DecryptAES256State base;
  InitStateDeterministic(&base, /*seedW=*/0x0BADF00Du, /*seedBuf=*/0x66u, /*initialBufIdx=*/3);

  DecryptAES256State sA;
  DecryptAES256State sB;
  CopyState(base, &sA);
  CopyState(base, &sB);

  unsigned char inA[kBlockSize];
  unsigned char inB[kBlockSize];
  FillWithPattern<unsigned char>(inA, kBlockSize, /*seed=*/0x10u);
  FillWithPattern<unsigned char>(inB, kBlockSize, /*seed=*/0x10u);

  // Flip one byte to ensure inputs differ.
  inB[0] = static_cast<unsigned char>(inB[0] ^ 0x01u);

  aes256EncryptBlock(&sA, inA);
  aes256EncryptBlock(&sB, inB);

  EXPECT_EQ(sA.bufIdx, 0);
  EXPECT_EQ(sB.bufIdx, 0);

  // For a fixed round-key schedule and fixed initial chaining buffer, different plaintext blocks
  // should yield different output blocks.
  EXPECT_FALSE(BlockEq(reinterpret_cast<unsigned char *>(sA.buf),
                       reinterpret_cast<unsigned char *>(sB.buf),
                       sizeof(sA.buf) / sizeof(sA.buf[0])));
}

TEST_F(Aes256EncryptBlockTest_1615, DifferentInitialChainingBufferAffectsOutput_1615) {
  DecryptAES256State s1;
  DecryptAES256State s2;
  InitStateDeterministic(&s1, /*seedW=*/0x13572468u, /*seedBuf=*/0x77u, /*initialBufIdx=*/0);
  InitStateDeterministic(&s2, /*seedW=*/0x13572468u, /*seedBuf=*/0x78u, /*initialBufIdx=*/0); // buf differs

  unsigned char in[kBlockSize];
  FillWithPattern<unsigned char>(in, kBlockSize, /*seed=*/0x99u);

  aes256EncryptBlock(&s1, in);
  aes256EncryptBlock(&s2, in);

  EXPECT_EQ(s1.bufIdx, 0);
  EXPECT_EQ(s2.bufIdx, 0);

  // With identical round keys and plaintext, differing initial chaining buffer should produce
  // differing output chaining buffer.
  EXPECT_FALSE(BlockEq(reinterpret_cast<unsigned char *>(s1.buf),
                       reinterpret_cast<unsigned char *>(s2.buf),
                       sizeof(s1.buf) / sizeof(s1.buf[0])));
}

} // namespace