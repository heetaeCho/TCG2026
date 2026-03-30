// File: util/coding_get_length_prefixed_slice_test.cc

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "leveldb/slice.h"

// Forward declare the function under test (or include "util/coding.h" if available)
namespace leveldb {
  // bool GetLengthPrefixedSlice(Slice* input, Slice* result);
  // Declared here to make the test compile in isolation with the provided partial code.
  bool GetLengthPrefixedSlice(Slice* input, Slice* result);
}

namespace {

// Small helper to encode a uint32_t as a varint32 (test data preparation only).
static void EncodeVarint32ForTest(uint32_t v, std::string* out) {
  while (v >= 0x80) {
    out->push_back(static_cast<char>(v | 0x80));
    v >>= 7;
  }
  out->push_back(static_cast<char>(v));
}

// Helper to append a single length-prefixed record to a buffer.
static void AppendLengthPrefixed(std::string payload, std::string* dst) {
  EncodeVarint32ForTest(static_cast<uint32_t>(payload.size()), dst);
  dst->append(payload);
}

}  // namespace

using leveldb::GetLengthPrefixedSlice;
using leveldb::Slice;

// ------------------------------------------------------------
// Normal operation: length header present, payload complete
// ------------------------------------------------------------
TEST(GetLengthPrefixedSliceTest_450, SucceedsWithExactData_450) {
  std::string buffer;
  AppendLengthPrefixed("abc", &buffer);  // varint(3) + "abc"

  Slice input(buffer);
  Slice result;

  // Call under test
  const bool ok = GetLengthPrefixedSlice(&input, &result);

  // Observable behavior
  EXPECT_TRUE(ok);
  EXPECT_EQ(result.size(), 3u);
  EXPECT_EQ(std::string(result.data(), result.size()), "abc");

  // Input should be advanced past header + payload (i.e., fully consumed)
  EXPECT_EQ(input.size(), 0u);
}

// ------------------------------------------------------------
// Boundary: zero-length payload should succeed and produce empty result
// ------------------------------------------------------------
TEST(GetLengthPrefixedSliceTest_450, ZeroLengthPayload_450) {
  std::string buffer;
  AppendLengthPrefixed("", &buffer);  // varint(0)

  Slice input(buffer);
  Slice result;

  const bool ok = GetLengthPrefixedSlice(&input, &result);

  EXPECT_TRUE(ok);
  EXPECT_EQ(result.size(), 0u);
  // Input should be advanced past just the header
  EXPECT_EQ(input.size(), 0u);
}

// ------------------------------------------------------------
// Exceptional/error: no header bytes at all -> varint decode fails
// ------------------------------------------------------------
TEST(GetLengthPrefixedSliceTest_450, FailsWhenNoVarintHeader_450) {
  std::string buffer;  // empty
  Slice input(buffer);
  Slice result;

  // Capture original state to ensure it's not (observably) changed on failure
  const char* orig_data = input.data();
  const size_t orig_size = input.size();

  const bool ok = GetLengthPrefixedSlice(&input, &result);

  EXPECT_FALSE(ok);
  // With no bytes, input should remain as-is
  EXPECT_EQ(input.data(), orig_data);
  EXPECT_EQ(input.size(), orig_size);
}

// ------------------------------------------------------------
// Error: header decodes but payload is shorter than declared length
// The function should return false and leave input advanced past header
// (since header parsing succeeded), without consuming payload bytes.
// ------------------------------------------------------------
TEST(GetLengthPrefixedSliceTest_450, FailsWhenPayloadShorterThanLength_450) {
  // Declare length = 5, but only provide "abc" (3 bytes)
  std::string buffer;
  EncodeVarint32ForTest(5, &buffer);
  buffer.append("abc");  // only 3 bytes provided

  Slice input(buffer);
  Slice result;

  // After the call, we expect failure and that input has been advanced
  // by exactly the varint header size (payload remains).
  // Compute header size to check observable advancement precisely.
  std::string header_only;
  EncodeVarint32ForTest(5, &header_only);
  const size_t header_size = header_only.size();

  const bool ok = GetLengthPrefixedSlice(&input, &result);

  EXPECT_FALSE(ok);

  // Input now should expose only the incomplete payload ("abc")
  EXPECT_EQ(input.size(), buffer.size() - header_size);
  EXPECT_EQ(std::string(input.data(), input.size()), "abc");
}

// ------------------------------------------------------------
// Normal operation: parse two consecutive length-prefixed slices
// ------------------------------------------------------------
TEST(GetLengthPrefixedSliceTest_450, ParsesTwoBackToBackRecords_450) {
  std::string buffer;
  AppendLengthPrefixed("hello", &buffer);
  AppendLengthPrefixed("world", &buffer);

  Slice input(buffer);

  // First record
  Slice r1;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &r1));
  EXPECT_EQ(std::string(r1.data(), r1.size()), "hello");

  // Second record
  Slice r2;
  ASSERT_TRUE(GetLengthPrefixedSlice(&input, &r2));
  EXPECT_EQ(std::string(r2.data(), r2.size()), "world");

  // All consumed
  EXPECT_EQ(input.size(), 0u);
}
