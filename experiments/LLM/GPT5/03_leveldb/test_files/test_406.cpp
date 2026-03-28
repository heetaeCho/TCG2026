// File: table/decode_entry_test.cc
#include "gtest/gtest.h"

// Pull in the function under test. It's a file-local helper in block.cc,
// so we include the implementation unit directly to make it visible to tests.
#include "table/block.cc"

#include <cstdint>
#include <vector>
#include <cstring>

namespace {

// Minimal helper to encode a Varint32 value into a byte buffer for inputs
// that exercise the varint path. This is test-side scaffolding only and
// does not re-implement or rely on the class-under-test internals.
static void EncodeVarint32(uint32_t v, std::string& out) {
  while (v >= 128) {
    out.push_back(static_cast<char>(v | 0x80));
    v >>= 7;
  }
  out.push_back(static_cast<char>(v));
}

}  // namespace

using leveldb::DecodeEntry;

class DecodeEntryTest_406 : public ::testing::Test {};

// --- Error & boundary: fewer than 3 bytes -> nullptr, outputs untouched
TEST_F(DecodeEntryTest_406, ReturnsNullWhenFewerThan3Bytes_406) {
  const char buf[2] = {0x01, 0x02};
  uint32_t shared = 111, non_shared = 222, value_length = 333;

  const char* p = buf;
  const char* limit = buf + sizeof(buf);
  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);

  EXPECT_EQ(res, nullptr);
  // Since input is too short, observable behavior is that outputs are not changed.
  EXPECT_EQ(shared, 111u);
  EXPECT_EQ(non_shared, 222u);
  EXPECT_EQ(value_length, 333u);
}

// --- Normal (fast path): 3 one-byte fields, enough payload -> success
TEST_F(DecodeEntryTest_406, FastPath_SucceedsAndReturnsPayloadPtr_406) {
  // header: shared=3, non_shared=2, value_length=4 (<128, triggers fast path)
  // payload: 2 + 4 bytes of arbitrary data
  std::vector<char> buf = {3, 2, 4, 'K', 'E', 'V', 'A', 'L'};
  ASSERT_EQ(buf.size(), 3 + 6);

  uint32_t shared = 0, non_shared = 0, value_length = 0;
  const char* p = buf.data();
  const char* limit = p + buf.size();

  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(shared, 3u);
  EXPECT_EQ(non_shared, 2u);
  EXPECT_EQ(value_length, 4u);
  // Should point to payload start just after the fixed 3-byte header
  EXPECT_EQ(res, p + 3);
  // And there should be at least non_shared + value_length bytes available
  EXPECT_EQ(std::memcmp(res, "KEVAL", 5), 0);  // spot check first 5 payload bytes
}

// --- Boundary: exactly enough payload bytes -> success
TEST_F(DecodeEntryTest_406, FastPath_ExactBoundary_Succeeds_406) {
  // header: shared=0, non_shared=1, value_length=2
  // payload: exactly 1 + 2 bytes
  std::vector<char> buf = {0, 1, 2, 'X', 'Y', 'Z'};
  uint32_t shared = 9, non_shared = 9, value_length = 9;

  const char* p = buf.data();
  const char* limit = p + buf.size();
  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);

  ASSERT_NE(res, nullptr);
  EXPECT_EQ(shared, 0u);
  EXPECT_EQ(non_shared, 1u);
  EXPECT_EQ(value_length, 2u);
  EXPECT_EQ(res, p + 3);  // payload starts immediately after header
}

// --- Error: fast path header but insufficient remaining bytes -> nullptr
TEST_F(DecodeEntryTest_406, FastPath_FailsWhenInsufficientPayload_406) {
  // header says non_shared=5, value_length=5 => need 10 payload bytes, provide 9
  std::vector<char> buf = {0, 5, 5};
  buf.insert(buf.end(), 9, 'P');

  uint32_t shared = 123, non_shared = 456, value_length = 789;

  const char* p = buf.data();
  const char* limit = p + buf.size();
  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);

  EXPECT_EQ(res, nullptr);
  // On failure after size check, outputs should not reflect a successful parse.
  // We avoid asserting on their values beyond the null return (black-box).
}

// --- Normal (varint path): fields >= 128 force varint decoding -> success
TEST_F(DecodeEntryTest_406, VarintHeader_Succeeds_406) {
  // Use values that require varint encoding
  const uint32_t shared_v = 130;       // 0x82 0x01
  const uint32_t non_shared_v = 129;   // 0x81 0x01
  const uint32_t value_length_v = 133; // 0x85 0x01

  std::string header;
  EncodeVarint32(shared_v, header);
  EncodeVarint32(non_shared_v, header);
  EncodeVarint32(value_length_v, header);

  std::string payload(non_shared_v + value_length_v, 'Q');
  std::string buf = header + payload;

  uint32_t shared = 0, non_shared = 0, value_length = 0;

  const char* p = buf.data();
  const char* limit = p + buf.size();
  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);

  ASSERT_NE(res, nullptr);
  EXPECT_EQ(shared, shared_v);
  EXPECT_EQ(non_shared, non_shared_v);
  EXPECT_EQ(value_length, value_length_v);
  // Pointer must advance exactly by the varint header length
  EXPECT_EQ(res, p + static_cast<ptrdiff_t>(header.size()));
  // Spot-check payload continuity
  ASSERT_GT(static_cast<size_t>(limit - res), 0u);
  EXPECT_EQ(*res, 'Q');
}

// --- Error: truncated varint field -> nullptr
TEST_F(DecodeEntryTest_406, VarintHeader_TruncatedFirstField_Fails_406) {
  // First field should be 130 => 0x82 0x01, but we truncate at 0x82
  std::string buf;
  buf.push_back(static_cast<char>(0x82));  // continuation bit set, but no following byte
  // Even if we add more bytes afterward, the first varint cannot be parsed.
  buf.push_back(0x00);  // random byte; still invalid sequence for the first varint overall

  uint32_t shared = 1, non_shared = 2, value_length = 3;

  const char* p = buf.data();
  const char* limit = p + buf.size();
  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);

  EXPECT_EQ(res, nullptr);
}

// --- Boundary: zero-length fields are allowed (total needed bytes = 0) -> success
TEST_F(DecodeEntryTest_406, ZeroLengthsAllowed_ReturnsNextPtr_406) {
  // header: shared=0, non_shared=0, value_length=0 (fast path)
  const char buf[3] = {0, 0, 0};

  uint32_t shared = 7, non_shared = 8, value_length = 9;

  const char* p = buf;
  const char* limit = buf + sizeof(buf);
  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);

  ASSERT_NE(res, nullptr);
  EXPECT_EQ(shared, 0u);
  EXPECT_EQ(non_shared, 0u);
  EXPECT_EQ(value_length, 0u);
  EXPECT_EQ(res, p + 3);
}

// --- Error: exactly 3 bytes available but lengths require more payload -> nullptr
TEST_F(DecodeEntryTest_406, ThreeBytesOnlyButNonZeroLengths_Fails_406) {
  // header claims non_shared=1, value_length=1, but no payload present
  const char buf[3] = {0, 1, 1};

  uint32_t shared = 0, non_shared = 0, value_length = 0;

  const char* p = buf;
  const char* limit = buf + sizeof(buf);
  const char* res = DecodeEntry(p, limit, &shared, &non_shared, &value_length);

  EXPECT_EQ(res, nullptr);
}
