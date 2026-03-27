// md5Append_test_1624.cc
// Unit tests for md5Append() in poppler/Decrypt.cc
//
// NOTE:
// - md5Append() is declared `static` in Decrypt.cc, so it is not link-visible from other TUs.
// - These tests include Decrypt.cc directly to place the tests in the same translation unit,
//   allowing the `static` function to be called.
// - The tests only validate observable effects on MD5State for cases where no full 64-byte
//   block processing is triggered (i.e., state->bufLen + dataLen < 64), avoiding assumptions
//   about md5ProcessBlock() behavior.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>

// Include implementation to access the `static` md5Append symbol.
// Adjust include path if your test target uses different include roots.
#include "Decrypt.cc"

namespace {

class Md5AppendTest_1624 : public ::testing::Test {
protected:
  static void FillPattern(unsigned char *p, size_t n, unsigned char v) {
    std::memset(p, v, n);
  }
};

TEST_F(Md5AppendTest_1624, AppendsSmallDataIntoEmptyBuffer_1624) {
  MD5State st;
  std::memset(&st, 0, sizeof(st));
  FillPattern(st.buf, sizeof(st.buf), 0xAA);

  const unsigned char data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
  const int dataLen = static_cast<int>(sizeof(data));

  md5Append(&st, data, dataLen);

  // Observable effects when no full 64-byte block is reached:
  // - buf[0..dataLen) matches data
  // - bufLen increased by dataLen
  // - msgLen increased by dataLen
  EXPECT_EQ(st.bufLen, dataLen);
  EXPECT_EQ(st.msgLen, dataLen);
  EXPECT_EQ(0, std::memcmp(st.buf, data, sizeof(data)));

  // Ensure bytes after appended region are unchanged.
  for (size_t i = sizeof(data); i < sizeof(st.buf); ++i) {
    ASSERT_EQ(st.buf[i], 0xAA) << "byte " << i << " unexpectedly changed";
  }
}

TEST_F(Md5AppendTest_1624, MultipleAppendsAccumulateUntilBelowBlockSize_1624) {
  MD5State st;
  std::memset(&st, 0, sizeof(st));
  FillPattern(st.buf, sizeof(st.buf), 0xCC);

  const unsigned char a[] = {0x01, 0x02, 0x03};
  const unsigned char b[] = {0x11, 0x12, 0x13, 0x14};
  const unsigned char c[] = {0x21};

  md5Append(&st, a, static_cast<int>(sizeof(a)));
  ASSERT_EQ(st.bufLen, static_cast<int>(sizeof(a)));
  ASSERT_EQ(st.msgLen, static_cast<int>(sizeof(a)));
  ASSERT_EQ(0, std::memcmp(st.buf, a, sizeof(a)));

  md5Append(&st, b, static_cast<int>(sizeof(b)));
  ASSERT_EQ(st.bufLen, static_cast<int>(sizeof(a) + sizeof(b)));
  ASSERT_EQ(st.msgLen, static_cast<int>(sizeof(a) + sizeof(b)));
  ASSERT_EQ(0, std::memcmp(st.buf, a, sizeof(a)));
  ASSERT_EQ(0, std::memcmp(st.buf + sizeof(a), b, sizeof(b)));

  md5Append(&st, c, static_cast<int>(sizeof(c)));
  EXPECT_EQ(st.bufLen, static_cast<int>(sizeof(a) + sizeof(b) + sizeof(c)));
  EXPECT_EQ(st.msgLen, static_cast<int>(sizeof(a) + sizeof(b) + sizeof(c)));
  EXPECT_EQ(0, std::memcmp(st.buf, a, sizeof(a)));
  EXPECT_EQ(0, std::memcmp(st.buf + sizeof(a), b, sizeof(b)));
  EXPECT_EQ(0, std::memcmp(st.buf + sizeof(a) + sizeof(b), c, sizeof(c)));

  // Remaining bytes should still be the original fill value.
  for (size_t i = sizeof(a) + sizeof(b) + sizeof(c); i < sizeof(st.buf); ++i) {
    ASSERT_EQ(st.buf[i], 0xCC) << "byte " << i << " unexpectedly changed";
  }
}

TEST_F(Md5AppendTest_1624, ZeroLengthAppendDoesNotModifyBufferAndKeepsLengths_1624) {
  MD5State st;
  std::memset(&st, 0, sizeof(st));
  FillPattern(st.buf, sizeof(st.buf), 0x5A);

  st.bufLen = 7;
  st.msgLen = 1234;

  // Passing nullptr should be safe when dataLen==0 (no copy should occur).
  md5Append(&st, nullptr, 0);

  EXPECT_EQ(st.bufLen, 7);
  EXPECT_EQ(st.msgLen, 1234);

  for (size_t i = 0; i < sizeof(st.buf); ++i) {
    ASSERT_EQ(st.buf[i], 0x5A) << "byte " << i << " unexpectedly changed";
  }
}

TEST_F(Md5AppendTest_1624, AppendsAtNonZeroOffsetWhenBufferPartiallyFilled_1624) {
  MD5State st;
  std::memset(&st, 0, sizeof(st));
  FillPattern(st.buf, sizeof(st.buf), 0xEE);

  // Pre-fill first 60 bytes with a known pattern to simulate existing buffered data.
  st.bufLen = 60;
  st.msgLen = 9;
  for (int i = 0; i < st.bufLen; ++i) {
    st.buf[i] = static_cast<unsigned char>(i);
  }

  // Append 3 bytes so total is 63 (<64): should not require a full-block process.
  const unsigned char tail[] = {0xA0, 0xB1, 0xC2};
  md5Append(&st, tail, static_cast<int>(sizeof(tail)));

  EXPECT_EQ(st.bufLen, 63);
  EXPECT_EQ(st.msgLen, 9 + static_cast<int>(sizeof(tail)));

  // Existing prefix should remain unchanged.
  for (int i = 0; i < 60; ++i) {
    ASSERT_EQ(st.buf[i], static_cast<unsigned char>(i)) << "prefix byte " << i << " changed";
  }

  // Newly appended bytes should appear at offset 60.
  EXPECT_EQ(0, std::memcmp(st.buf + 60, tail, sizeof(tail)));

  // Bytes after bufLen should be unchanged fill.
  for (size_t i = 63; i < sizeof(st.buf); ++i) {
    ASSERT_EQ(st.buf[i], 0xEE) << "byte " << i << " unexpectedly changed";
  }
}

} // namespace