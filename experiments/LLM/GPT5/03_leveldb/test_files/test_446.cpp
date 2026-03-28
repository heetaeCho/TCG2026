// File: util/get_varint32_ptr_fallback_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

namespace leveldb {
// Forward declaration from util/coding.cc (interface-only usage)
const char* GetVarint32PtrFallback(const char* p, const char* limit, uint32_t* value);
}

// Test suite: GetVarint32PtrFallback behaves as a black box parser that
// reads a varint32 from [p, limit) and returns the pointer just past the
// parsed value on success, or nullptr on failure.

using leveldb::GetVarint32PtrFallback;

class GetVarint32PtrFallbackTest_446 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(GetVarint32PtrFallbackTest_446, ParsesSingleByteValues_446) {
  // 0x00 -> 0 (single byte)
  const uint8_t buf0[] = {0x00};
  uint32_t val0 = 0xDEADBEEF;
  const char* p0 = reinterpret_cast<const char*>(buf0);
  const char* end0 = p0 + sizeof(buf0);

  const char* res0 = GetVarint32PtrFallback(p0, end0, &val0);
  ASSERT_NE(res0, nullptr);
  EXPECT_EQ(val0, 0u);
  EXPECT_EQ(res0, end0);

  // 0x7F -> 127 (single byte, max single-byte varint)
  const uint8_t buf1[] = {0x7F};
  uint32_t val1 = 0xDEADBEEF;
  const char* p1 = reinterpret_cast<const char*>(buf1);
  const char* end1 = p1 + sizeof(buf1);

  const char* res1 = GetVarint32PtrFallback(p1, end1, &val1);
  ASSERT_NE(res1, nullptr);
  EXPECT_EQ(val1, 127u);
  EXPECT_EQ(res1, end1);
}

TEST_F(GetVarint32PtrFallbackTest_446, ParsesTwoByteValue_446) {
  // 128 -> 0x80 0x01
  const uint8_t buf[] = {0x80, 0x01};
  uint32_t value = 0xDEADBEEF;
  const char* p = reinterpret_cast<const char*>(buf);
  const char* end = p + sizeof(buf);

  const char* res = GetVarint32PtrFallback(p, end, &value);
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(value, 128u);
  EXPECT_EQ(res, p + 2);
}

TEST_F(GetVarint32PtrFallbackTest_446, ParsesThreeByteValue_446) {
  // 16384 -> 0x80 0x80 0x01
  const uint8_t buf[] = {0x80, 0x80, 0x01};
  uint32_t value = 0xDEADBEEF;
  const char* p = reinterpret_cast<const char*>(buf);
  const char* end = p + sizeof(buf);

  const char* res = GetVarint32PtrFallback(p, end, &value);
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(value, 16384u);
  EXPECT_EQ(res, p + 3);
}

TEST_F(GetVarint32PtrFallbackTest_446, ParsesMaxUint32_446) {
  // 0xFFFFFFFF (4294967295) -> 0xFF 0xFF 0xFF 0xFF 0x0F
  const uint8_t buf[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x0F};
  uint32_t value = 0xAAAAAAAA;
  const char* p = reinterpret_cast<const char*>(buf);
  const char* end = p + sizeof(buf);

  const char* res = GetVarint32PtrFallback(p, end, &value);
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(value, 0xFFFFFFFFu);
  EXPECT_EQ(res, p + 5);
}

// --- Boundary conditions / error cases ---

TEST_F(GetVarint32PtrFallbackTest_446, FailsOnTruncatedAfterContinuationByte_446) {
  // Starts a multi-byte varint (0x80) but truncated (no terminating byte)
  const uint8_t buf[] = {0x80};
  uint32_t value = 0xCAFEBABE;  // sentinel
  const char* p = reinterpret_cast<const char*>(buf);
  const char* end = p + sizeof(buf);

  const char* res = GetVarint32PtrFallback(p, end, &value);
  EXPECT_EQ(res, nullptr);
  // On failure, value should remain unchanged (observable behavior of this implementation)
  EXPECT_EQ(value, 0xCAFEBABEu);
}

TEST_F(GetVarint32PtrFallbackTest_446, FailsWhenLimitStopsMidValue_446) {
  // 128 normally needs two bytes: 0x80 0x01
  // Provide only the first byte in [p, limit) so decode must fail.
  const uint8_t buf[] = {0x80, 0x01};  // second byte exists in memory, but "limit" prohibits access
  uint32_t value = 123456u;            // sentinel
  const char* p = reinterpret_cast<const char*>(buf);
  const char* limit = p + 1;           // stop at first byte

  const char* res = GetVarint32PtrFallback(p, limit, &value);
  EXPECT_EQ(res, nullptr);
  EXPECT_EQ(value, 123456u);
}

TEST_F(GetVarint32PtrFallbackTest_446, FailsWithFiveContinuationBytesNoTerminator_446) {
  // Five bytes with MSB set and no terminating byte within limit
  const uint8_t buf[] = {0x80, 0x80, 0x80, 0x80, 0x80};
  uint32_t value = 0x13579BDFu;  // sentinel
  const char* p = reinterpret_cast<const char*>(buf);
  const char* end = p + sizeof(buf);

  const char* res = GetVarint32PtrFallback(p, end, &value);
  EXPECT_EQ(res, nullptr);
  EXPECT_EQ(value, 0x13579BDFu);
}
