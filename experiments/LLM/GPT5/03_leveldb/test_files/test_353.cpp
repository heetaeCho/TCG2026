// File: db/get_length_prefixed_slice_test_353.cc

#include "gtest/gtest.h"

// Bring in the function-under-test. Since it's declared `static` inside the .cc,
// including the .cc here defines it in this TU so we can call it.
#include "db/memtable.cc"

#include "leveldb/slice.h"
#include "util/coding.h"

#include <cstring>
#include <string>

namespace leveldb {

class GetLengthPrefixedSliceTest_353 : public ::testing::Test {};

// [Normal] Small payload encodes to single-byte varint; slice should match payload.
TEST_F(GetLengthPrefixedSliceTest_353, ReturnsExactPayload_SmallSingleByteLen_353) {
  const std::string payload = "hello";
  std::string buf;
  PutLengthPrefixedSlice(&buf, Slice(payload));

  Slice s = GetLengthPrefixedSlice(buf.data());

  EXPECT_EQ(s.size(), payload.size());
  EXPECT_EQ(s.ToString(), payload);
}

// [Boundary] Zero-length payload: slice.size()==0 and data pointer is right after the prefix.
TEST_F(GetLengthPrefixedSliceTest_353, ZeroLength_ReturnsEmptySlice_AndCorrectStart_353) {
  const std::string payload;  // empty
  std::string buf;
  PutLengthPrefixedSlice(&buf, Slice(payload));

  // Determine expected prefix length using public varint encoder.
  std::string varint_len_only;
  PutVarint32(&varint_len_only, 0);

  Slice s = GetLengthPrefixedSlice(buf.data());

  EXPECT_EQ(s.size(), 0u);
  // The returned data pointer should point immediately after the varint length prefix.
  EXPECT_EQ(s.data(), buf.data() + varint_len_only.size());
}

// [Boundary] Multi-byte varint length: ensure correct parsing and content.
TEST_F(GetLengthPrefixedSliceTest_353, MultiByteVarintLength_ParsesCorrectly_353) {
  const size_t n = 300;  // requires multi-byte varint
  std::string payload(n, 'x');
  std::string buf;
  PutLengthPrefixedSlice(&buf, Slice(payload));

  // Compute prefix length independently using public encoder.
  std::string varint_len_only;
  PutVarint32(&varint_len_only, static_cast<uint32_t>(n));

  Slice s = GetLengthPrefixedSlice(buf.data());

  EXPECT_EQ(s.size(), n);
  EXPECT_EQ(s.data(), buf.data() + varint_len_only.size());
  EXPECT_EQ(s.ToString(), payload);
}

// [Normal/Robustness] Binary data (including NULs) should be preserved exactly.
TEST_F(GetLengthPrefixedSliceTest_353, BinaryPayload_WithNullBytes_PreservedExactly_353) {
  std::string payload;
  payload.resize(10);
  for (size_t i = 0; i < payload.size(); ++i) {
    payload[i] = static_cast<char>(i);  // includes '\0', '\1', ...
  }

  std::string buf;
  PutLengthPrefixedSlice(&buf, Slice(payload.data(), payload.size()));

  Slice s = GetLengthPrefixedSlice(buf.data());

  ASSERT_EQ(s.size(), payload.size());
  EXPECT_EQ(std::memcmp(s.data(), payload.data(), payload.size()), 0);
}

}  // namespace leveldb
