// util/coding_getvarint64ptr_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <string>

namespace leveldb {
  // Forward-declare the function under test (treating implementation as a black box).
  const char* GetVarint64Ptr(const char* p, const char* limit, uint64_t* value);
}

using leveldb::GetVarint64Ptr;

class GetVarint64PtrTest_448 : public ::testing::Test {
protected:
  // Helper to run the decode and return the pointer result.
  static const char* Decode(const std::string& bytes, uint64_t* out) {
    const char* p = bytes.data();
    const char* limit = p + bytes.size();
    return GetVarint64Ptr(p, limit, out);
  }
};

// Normal: single-byte zero
TEST_F(GetVarint64PtrTest_448, DecodeSingleByteZero_448) {
  std::string in = std::string(1, char(0x00)); // 0
  uint64_t value = 123456789;                  // sentinel; should be overwritten on success
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + in.size(), &value);

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(value, 0u);
  EXPECT_EQ(ret, p + 1);
}

// Normal: single-byte max (127)
TEST_F(GetVarint64PtrTest_448, DecodeSingleByteMax_448) {
  std::string in = std::string(1, char(0x7F)); // 127
  uint64_t value = 0;
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + in.size(), &value);

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(value, 127u);
  EXPECT_EQ(ret, p + 1);
}

// Normal: multi-byte (e.g., 300 → 0xAC 0x02)
TEST_F(GetVarint64PtrTest_448, DecodeTwoBytes_448) {
  std::string in;
  in.push_back(char(0xAC)); // 172, continuation
  in.push_back(char(0x02)); // final
  uint64_t value = 0;
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + in.size(), &value);

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(value, 300u);
  EXPECT_EQ(ret, p + 2);
}

// Boundary: maximum uint64_t (10-byte varint: FF FF FF FF FF FF FF FF FF 01)
TEST_F(GetVarint64PtrTest_448, DecodeMaxUint64_448) {
  std::string in(9, char(0xFF));
  in.push_back(char(0x01));
  uint64_t value = 0;
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + in.size(), &value);

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(value, std::numeric_limits<uint64_t>::max());
  EXPECT_EQ(ret, p + 10);
}

// Error: empty input (p == limit) → nullptr, value unchanged
TEST_F(GetVarint64PtrTest_448, EmptyInputReturnsNull_448) {
  std::string in; // empty
  uint64_t value = 42; // sentinel
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + in.size(), &value);

  EXPECT_EQ(ret, nullptr);
  EXPECT_EQ(value, 42u); // must remain unchanged on failure
}

// Error: truncated multi-byte (needs more, but limit stops early) → nullptr, value unchanged
TEST_F(GetVarint64PtrTest_448, TruncatedContinuationReturnsNull_448) {
  // First byte indicates continuation; second byte missing due to limit.
  std::string in;
  in.push_back(char(0xAC)); // 0b10101100 (continuation set)
  uint64_t value = 777;     // sentinel
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + 1, &value); // limit at 1 byte

  EXPECT_EQ(ret, nullptr);
  EXPECT_EQ(value, 777u);
}

// Error: overlong/never-terminating within allowed shifts (10 continuation bytes) → nullptr
TEST_F(GetVarint64PtrTest_448, OverlongNoTerminatorReturnsNull_448) {
  // Ten bytes with MSB set and zero payload; loop exhausts shift budget and returns nullptr.
  std::string in(10, char(0x80));
  uint64_t value = 9001; // sentinel
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + in.size(), &value);

  EXPECT_EQ(ret, nullptr);
  EXPECT_EQ(value, 9001u);
}

// Boundary: valid one-byte value with tight limit exactly at end → success
TEST_F(GetVarint64PtrTest_448, ExactLimitAfterValidByte_448) {
  std::string in;
  in.push_back(char(0x01)); // value = 1
  uint64_t value = 0;
  const char* p = in.data();
  const char* ret = GetVarint64Ptr(p, p + 1, &value); // limit exactly after the byte

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(value, 1u);
  EXPECT_EQ(ret, p + 1);
}
