// Decrypt_md5Finish_test_1625.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>

// Test seam: redirect md5ProcessBlock() calls from Decrypt.cc into our hook so
// md5Finish() behavior can be observed deterministically without relying on
// internal block processing.
namespace {
int g_md5ProcessBlockCalls = 0;

} // namespace

#define md5ProcessBlock md5ProcessBlock_TestHook
static void md5ProcessBlock_TestHook(MD5State *state) {
  (void)state;
  ++g_md5ProcessBlockCalls;
}

// Include the implementation file so we can access the internal static function.
#include "TestProjects/poppler/poppler/Decrypt.cc"
#undef md5ProcessBlock

namespace {

class Md5FinishTest_1625 : public ::testing::Test {
protected:
  void SetUp() override { g_md5ProcessBlockCalls = 0; }

  static std::array<unsigned char, 5> ExpectedLenBytes5(int msgLen) {
    // Mirrors what md5Finish writes into buf[56..60]:
    // buf[56] = (unsigned char)(msgLen << 3);
    // buf[57] = (unsigned char)(msgLen >> 5);
    // buf[58] = (unsigned char)(msgLen >> 13);
    // buf[59] = (unsigned char)(msgLen >> 21);
    // buf[60] = (unsigned char)(msgLen >> 29);
    std::array<unsigned char, 5> out{};
    out[0] = static_cast<unsigned char>(static_cast<uint32_t>(msgLen) << 3);
    out[1] = static_cast<unsigned char>(static_cast<uint32_t>(msgLen) >> 5);
    out[2] = static_cast<unsigned char>(static_cast<uint32_t>(msgLen) >> 13);
    out[3] = static_cast<unsigned char>(static_cast<uint32_t>(msgLen) >> 21);
    out[4] = static_cast<unsigned char>(static_cast<uint32_t>(msgLen) >> 29);
    return out;
  }

  static void FillBuf(MD5State &st, unsigned char value) {
    std::fill(std::begin(st.buf), std::end(st.buf), value);
  }
};

TEST_F(Md5FinishTest_1625, PadsWithinSingleBlockWhenBufLenAtMost55_1625) {
  MD5State st{};
  FillBuf(st, 0xAA);

  st.bufLen = 0;
  st.msgLen = 0;

  md5Finish(&st);

  EXPECT_EQ(g_md5ProcessBlockCalls, 1);
  EXPECT_EQ(st.bufLen, 64);

  // Padding starts with 0x80 at original position, then zeros up to 56.
  EXPECT_EQ(st.buf[0], 0x80);
  for (int i = 1; i < 56; ++i) {
    EXPECT_EQ(st.buf[i], 0x00) << "i=" << i;
  }

  // Length bytes and trailing zeros.
  auto len5 = ExpectedLenBytes5(st.msgLen);
  EXPECT_EQ(st.buf[56], len5[0]);
  EXPECT_EQ(st.buf[57], len5[1]);
  EXPECT_EQ(st.buf[58], len5[2]);
  EXPECT_EQ(st.buf[59], len5[3]);
  EXPECT_EQ(st.buf[60], len5[4]);
  EXPECT_EQ(st.buf[61], 0x00);
  EXPECT_EQ(st.buf[62], 0x00);
  EXPECT_EQ(st.buf[63], 0x00);
}

TEST_F(Md5FinishTest_1625, PadsInTwoBlocksWhenBufLenExactly56_1625) {
  MD5State st{};
  FillBuf(st, 0xCC);

  st.bufLen = 56;
  st.msgLen = 1;

  md5Finish(&st);

  EXPECT_EQ(g_md5ProcessBlockCalls, 2);
  EXPECT_EQ(st.bufLen, 64);

  // After finalization, buffer holds the last processed block:
  // zeros up to 56, then the length bytes.
  for (int i = 0; i < 56; ++i) {
    EXPECT_EQ(st.buf[i], 0x00) << "i=" << i;
  }

  auto len5 = ExpectedLenBytes5(st.msgLen);
  EXPECT_EQ(st.buf[56], len5[0]);
  EXPECT_EQ(st.buf[57], len5[1]);
  EXPECT_EQ(st.buf[58], len5[2]);
  EXPECT_EQ(st.buf[59], len5[3]);
  EXPECT_EQ(st.buf[60], len5[4]);
  EXPECT_EQ(st.buf[61], 0x00);
  EXPECT_EQ(st.buf[62], 0x00);
  EXPECT_EQ(st.buf[63], 0x00);
}

TEST_F(Md5FinishTest_1625, BoundaryBufLen55UsesSingleBlock_1625) {
  MD5State st{};
  FillBuf(st, 0x11);

  st.bufLen = 55;
  st.msgLen = 7;

  md5Finish(&st);

  EXPECT_EQ(g_md5ProcessBlockCalls, 1);
  EXPECT_EQ(st.bufLen, 64);

  // 0..54 unchanged? md5Finish writes starting at buf[55], and zeros after.
  for (int i = 0; i < 55; ++i) {
    EXPECT_EQ(st.buf[i], 0x11) << "i=" << i;
  }
  EXPECT_EQ(st.buf[55], 0x80);

  for (int i = 56; i < 56; ++i) {
    // (no-op; included for clarity)
  }

  auto len5 = ExpectedLenBytes5(st.msgLen);
  EXPECT_EQ(st.buf[56], len5[0]);
  EXPECT_EQ(st.buf[57], len5[1]);
  EXPECT_EQ(st.buf[58], len5[2]);
  EXPECT_EQ(st.buf[59], len5[3]);
  EXPECT_EQ(st.buf[60], len5[4]);
  EXPECT_EQ(st.buf[61], 0x00);
  EXPECT_EQ(st.buf[62], 0x00);
  EXPECT_EQ(st.buf[63], 0x00);
}

TEST_F(Md5FinishTest_1625, BoundaryBufLen57UsesTwoBlocksAndFinalBlockHasLength_1625) {
  MD5State st{};
  FillBuf(st, 0x22);

  st.bufLen = 57;
  st.msgLen = 12345;

  md5Finish(&st);

  EXPECT_EQ(g_md5ProcessBlockCalls, 2);
  EXPECT_EQ(st.bufLen, 64);

  // Final block is zeros up to 56, then length bytes.
  for (int i = 0; i < 56; ++i) {
    EXPECT_EQ(st.buf[i], 0x00) << "i=" << i;
  }
  auto len5 = ExpectedLenBytes5(st.msgLen);
  EXPECT_EQ(st.buf[56], len5[0]);
  EXPECT_EQ(st.buf[57], len5[1]);
  EXPECT_EQ(st.buf[58], len5[2]);
  EXPECT_EQ(st.buf[59], len5[3]);
  EXPECT_EQ(st.buf[60], len5[4]);
  EXPECT_EQ(st.buf[61], 0x00);
  EXPECT_EQ(st.buf[62], 0x00);
  EXPECT_EQ(st.buf[63], 0x00);
}

TEST_F(Md5FinishTest_1625, WritesDigestAsLittleEndianWordsAfterProcessing_1625) {
  MD5State st{};
  FillBuf(st, 0x00);

  // Choose values where byte order is obvious.
  st.a = static_cast<unsigned long>(0x11223344UL);
  st.b = static_cast<unsigned long>(0x55667788UL);
  st.c = static_cast<unsigned long>(0x99AABBCCUL);
  st.d = static_cast<unsigned long>(0xDDEEFF00UL);

  st.bufLen = 0;
  st.msgLen = 0;

  md5Finish(&st);

  // Our hook doesn't modify a/b/c/d, so digest should reflect these values.
  EXPECT_EQ(st.digest[0], 0x44);
  EXPECT_EQ(st.digest[1], 0x33);
  EXPECT_EQ(st.digest[2], 0x22);
  EXPECT_EQ(st.digest[3], 0x11);

  EXPECT_EQ(st.digest[4], 0x88);
  EXPECT_EQ(st.digest[5], 0x77);
  EXPECT_EQ(st.digest[6], 0x66);
  EXPECT_EQ(st.digest[7], 0x55);

  EXPECT_EQ(st.digest[8], 0xCC);
  EXPECT_EQ(st.digest[9], 0xBB);
  EXPECT_EQ(st.digest[10], 0xAA);
  EXPECT_EQ(st.digest[11], 0x99);

  EXPECT_EQ(st.digest[12], 0x00);
  EXPECT_EQ(st.digest[13], 0xFF);
  EXPECT_EQ(st.digest[14], 0xEE);
  EXPECT_EQ(st.digest[15], 0xDD);
}

TEST_F(Md5FinishTest_1625, HandlesNonZeroMsgLenEncodingIntoLengthFields_1625) {
  MD5State st{};
  FillBuf(st, 0x77);

  st.bufLen = 10;
  st.msgLen = 0x1ABCDE; // arbitrary non-trivial length

  md5Finish(&st);

  EXPECT_EQ(g_md5ProcessBlockCalls, 1);
  EXPECT_EQ(st.bufLen, 64);

  // buf[10] becomes 0x80, then zeros until 56.
  EXPECT_EQ(st.buf[10], 0x80);
  for (int i = 11; i < 56; ++i) {
    EXPECT_EQ(st.buf[i], 0x00) << "i=" << i;
  }

  auto len5 = ExpectedLenBytes5(st.msgLen);
  EXPECT_EQ(st.buf[56], len5[0]);
  EXPECT_EQ(st.buf[57], len5[1]);
  EXPECT_EQ(st.buf[58], len5[2]);
  EXPECT_EQ(st.buf[59], len5[3]);
  EXPECT_EQ(st.buf[60], len5[4]);
  EXPECT_EQ(st.buf[61], 0x00);
  EXPECT_EQ(st.buf[62], 0x00);
  EXPECT_EQ(st.buf[63], 0x00);
}

} // namespace