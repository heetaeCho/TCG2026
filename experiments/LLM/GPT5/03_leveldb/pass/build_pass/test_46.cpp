// File: util/getvarint32ptr_test.cc
#include "util/coding.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

using leveldb::GetVarint32Ptr;

namespace {

// Small helper to build a contiguous byte buffer we can address by pointer.
static std::vector<uint8_t> Bytes(std::initializer_list<uint8_t> init) {
  return std::vector<uint8_t>(init);
}

}  // namespace

// === Normal operation: single-byte values (MSB==0) ===
TEST(GetVarint32PtrTest_46, DecodesSingleByteZero_46) {
  auto buf = Bytes({0x00});  // value = 0
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p + buf.size();

  uint32_t value = 12345;  // sentinel to ensure it actually writes
  const char* next = GetVarint32Ptr(p, limit, &value);

  ASSERT_NE(next, nullptr);
  EXPECT_EQ(next, p + 1);
  EXPECT_EQ(value, 0u);
}

TEST(GetVarint32PtrTest_46, DecodesSingleByte127_46) {
  auto buf = Bytes({0x7F});  // value = 127
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p + buf.size();

  uint32_t value = 0;
  const char* next = GetVarint32Ptr(p, limit, &value);

  ASSERT_NE(next, nullptr);
  EXPECT_EQ(next, p + 1);
  EXPECT_EQ(value, 127u);
}

// === Normal operation: multi-byte values (handled via fallback path internally) ===
TEST(GetVarint32PtrTest_46, DecodesTwoByte128_46) {
  // 128 encoded as LEB128 varint32: 0x80 0x01
  auto buf = Bytes({0x80, 0x01});
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p + buf.size();

  uint32_t value = 0;
  const char* next = GetVarint32Ptr(p, limit, &value);

  ASSERT_NE(next, nullptr);
  EXPECT_EQ(next, p + 2);
  EXPECT_EQ(value, 128u);
}

TEST(GetVarint32PtrTest_46, DecodesTwoByte300_46) {
  // 300 encoded as LEB128 varint32: 0xAC 0x02 (172, 2)
  auto buf = Bytes({0xAC, 0x02});
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p + buf.size();

  uint32_t value = 0;
  const char* next = GetVarint32Ptr(p, limit, &value);

  ASSERT_NE(next, nullptr);
  EXPECT_EQ(next, p + 2);
  EXPECT_EQ(value, 300u);
}

// === Boundary conditions ===
TEST(GetVarint32PtrTest_46, FailsOnEmptyInputReturnsNull_46) {
  // p == limit -> no bytes available
  std::vector<uint8_t> buf;  // empty
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p;  // equal

  uint32_t value = 777u;
  const char* next = GetVarint32Ptr(p, limit, &value);

  EXPECT_EQ(next, nullptr);
  // We intentionally do not assert on |value| after failure (black-box contract).
}

TEST(GetVarint32PtrTest_46, FailsOnTruncatedSequenceReturnsNull_46) {
  // First byte indicates continuation but buffer ends early.
  auto buf = Bytes({0x80});  // needs another byte
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p + 1;

  uint32_t value = 999u;
  const char* next = GetVarint32Ptr(p, limit, &value);

  EXPECT_EQ(next, nullptr);
}

// === Limit handling: ensure no over-read past limit for single-byte case ===
TEST(GetVarint32PtrTest_46, RespectsLimitForSingleByte_46) {
  // Provide an extra byte after the single-byte varint; limit should stop read at first byte.
  auto buf = Bytes({0x05, 0xAA});
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p + 1;  // only first byte is within limit

  uint32_t value = 0;
  const char* next = GetVarint32Ptr(p, limit, &value);

  ASSERT_NE(next, nullptr);
  EXPECT_EQ(next, p + 1);  // advanced exactly one byte
  EXPECT_EQ(value, 5u);
}

// === Large value (max 32-bit) via 5-byte varint ===
TEST(GetVarint32PtrTest_46, DecodesMaxUint32_46) {
  // 0xFFFFFFFF => LEB128: FF FF FF FF 0F
  auto buf = Bytes({0xFF, 0xFF, 0xFF, 0xFF, 0x0F});
  const char* p = reinterpret_cast<const char*>(buf.data());
  const char* limit = p + buf.size();

  uint32_t value = 0;
  const char* next = GetVarint32Ptr(p, limit, &value);

  ASSERT_NE(next, nullptr);
  EXPECT_EQ(next, p + 5);
  EXPECT_EQ(value, 0xFFFFFFFFu);
}
