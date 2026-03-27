// Decrypt_md5ProcessBlock_test_1623.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>

// NOTE:
// md5ProcessBlock is declared "static" inside Decrypt.cc (internal linkage).
// Including the .cc file makes the symbol visible within this test translation unit.
#include "Decrypt.cc"

namespace {

static void FillBuf(MD5State &st, uint8_t seed) {
  for (int i = 0; i < 64; ++i) {
    st.buf[i] = static_cast<unsigned char>(seed + i);
  }
}

static void FillDigest(MD5State &st, uint8_t v) {
  for (int i = 0; i < 16; ++i) {
    st.digest[i] = static_cast<unsigned char>(v);
  }
}

static std::array<unsigned char, 64> CopyBuf(const MD5State &st) {
  std::array<unsigned char, 64> out{};
  std::copy(st.buf, st.buf + 64, out.begin());
  return out;
}

static std::array<unsigned char, 16> CopyDigest(const MD5State &st) {
  std::array<unsigned char, 16> out{};
  std::copy(st.digest, st.digest + 16, out.begin());
  return out;
}

class Md5ProcessBlockTest_1623 : public ::testing::Test {
protected:
  static MD5State MakeState(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int msgLen, int bufLen,
                            uint8_t bufSeed, uint8_t digestFill) {
    MD5State st{};
    st.a = a;
    st.b = b;
    st.c = c;
    st.d = d;
    st.msgLen = msgLen;
    st.bufLen = bufLen;
    FillBuf(st, bufSeed);
    FillDigest(st, digestFill);
    return st;
  }

  static bool AnyWordDiff(const MD5State &x, const MD5State &y) {
    return (x.a != y.a) || (x.b != y.b) || (x.c != y.c) || (x.d != y.d);
  }
};

} // namespace

TEST_F(Md5ProcessBlockTest_1623, ResetsBufLenToZero_1623) {
  MD5State st = MakeState(0x01234567u, 0x89abcdefu, 0xfedcba98u, 0x76543210u,
                          /*msgLen=*/123, /*bufLen=*/64,
                          /*bufSeed=*/0x10, /*digestFill=*/0xAA);

  ASSERT_NE(st.bufLen, 0);
  md5ProcessBlock(&st);
  EXPECT_EQ(st.bufLen, 0);
}

TEST_F(Md5ProcessBlockTest_1623, DoesNotModifyMsgLenDigestOrInputBuffer_1623) {
  MD5State st = MakeState(0x0u, 0x1u, 0x2u, 0x3u,
                          /*msgLen=*/777, /*bufLen=*/64,
                          /*bufSeed=*/0x22, /*digestFill=*/0x5A);

  const int msgLenBefore = st.msgLen;
  const auto bufBefore = CopyBuf(st);
  const auto digestBefore = CopyDigest(st);

  md5ProcessBlock(&st);

  EXPECT_EQ(st.msgLen, msgLenBefore);
  EXPECT_EQ(CopyBuf(st), bufBefore);
  EXPECT_EQ(CopyDigest(st), digestBefore);
}

TEST_F(Md5ProcessBlockTest_1623, DeterministicForSameInitialStateAndBuffer_1623) {
  MD5State st1 = MakeState(0x11111111u, 0x22222222u, 0x33333333u, 0x44444444u,
                           /*msgLen=*/0, /*bufLen=*/64,
                           /*bufSeed=*/0x01, /*digestFill=*/0x00);
  MD5State st2 = st1;

  md5ProcessBlock(&st1);
  md5ProcessBlock(&st2);

  EXPECT_EQ(st1.a, st2.a);
  EXPECT_EQ(st1.b, st2.b);
  EXPECT_EQ(st1.c, st2.c);
  EXPECT_EQ(st1.d, st2.d);
  EXPECT_EQ(st1.bufLen, 0);
  EXPECT_EQ(st2.bufLen, 0);
}

TEST_F(Md5ProcessBlockTest_1623, ChangingOneByteInBufferChangesStateWords_1623) {
  MD5State base = MakeState(0x0a0b0c0du, 0x01020304u, 0x05060708u, 0x090a0b0cu,
                            /*msgLen=*/9, /*bufLen=*/64,
                            /*bufSeed=*/0x30, /*digestFill=*/0xCC);
  MD5State st1 = base;
  MD5State st2 = base;

  // Flip one byte (boundary-like perturbation).
  st2.buf[63] = static_cast<unsigned char>(st2.buf[63] ^ 0x01);

  md5ProcessBlock(&st1);
  md5ProcessBlock(&st2);

  EXPECT_TRUE(AnyWordDiff(st1, st2));
}

TEST_F(Md5ProcessBlockTest_1623, SecondCallWithSameBufferFurtherChangesState_1623) {
  MD5State st = MakeState(0xdeadbeefu, 0xcafebabeu, 0x13579bdfu, 0x2468ace0u,
                          /*msgLen=*/42, /*bufLen=*/64,
                          /*bufSeed=*/0x77, /*digestFill=*/0x11);

  md5ProcessBlock(&st);
  const unsigned long a1 = st.a;
  const unsigned long b1 = st.b;
  const unsigned long c1 = st.c;
  const unsigned long d1 = st.d;

  // Refill bufLen to emulate "another complete block available" without relying on internals.
  st.bufLen = 64;
  md5ProcessBlock(&st);

  EXPECT_TRUE((st.a != a1) || (st.b != b1) || (st.c != c1) || (st.d != d1));
  EXPECT_EQ(st.bufLen, 0);
}

TEST_F(Md5ProcessBlockTest_1623, BoundaryPatternsAllZeroVsAllFFProduceDifferentState_1623) {
  MD5State zero = MakeState(0x01020304u, 0x05060708u, 0x090a0b0cu, 0x0d0e0f10u,
                            /*msgLen=*/0, /*bufLen=*/64,
                            /*bufSeed=*/0x00, /*digestFill=*/0x00);
  for (int i = 0; i < 64; ++i) zero.buf[i] = 0x00;

  MD5State ff = zero;
  for (int i = 0; i < 64; ++i) ff.buf[i] = 0xFF;

  md5ProcessBlock(&zero);
  md5ProcessBlock(&ff);

  EXPECT_TRUE(AnyWordDiff(zero, ff));
  EXPECT_EQ(zero.bufLen, 0);
  EXPECT_EQ(ff.bufLen, 0);
}