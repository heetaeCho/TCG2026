// Filename: memtable_encode_key_test.cc

#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"
#include "util/coding.h"

// Include the .cc directly so we can access the file-local static function.
// We are not re-implementing logic; we're exercising the real implementation.
#include "db/memtable.cc"

using leveldb::EncodeKey;       // from the included .cc
using leveldb::Slice;
using leveldb::GetVarint32Ptr;

// Helper: decode a varint32 prefix from a std::string produced by EncodeKey,
// returning bytes_consumed and the decoded value via out_len.
// We use LevelDB's own public varint decoder (no re-implementation).
static size_t DecodeVarintPrefix(const std::string& s, uint32_t* out_len) {
  const char* p = s.data();
  const char* limit = p + s.size();
  const char* q = GetVarint32Ptr(p, limit, out_len);
  if (q == nullptr) return 0;  // decoding failed
  return static_cast<size_t>(q - p);
}

class EncodeKeyTest_356 : public ::testing::Test {
protected:
  std::string scratch_;
};

// Normal operation: small payload encodes as [varint(len)=1 byte][payload]
TEST_F(EncodeKeyTest_356, EncodesSmallPayload_356) {
  Slice target("abc"); // len=3
  const char* ret = EncodeKey(&scratch_, target);

  // Returned pointer should be scratch_.data()
  ASSERT_EQ(ret, scratch_.data());

  uint32_t decoded_len = 0;
  size_t varint_len = DecodeVarintPrefix(scratch_, &decoded_len);
  ASSERT_GT(varint_len, 0u);
  EXPECT_EQ(decoded_len, target.size());

  // Remaining bytes must match payload
  ASSERT_GE(scratch_.size(), varint_len + target.size());
  std::string payload = scratch_.substr(varint_len, target.size());
  EXPECT_EQ(payload, std::string(target.data(), target.size()));
}

// Edge case: empty slice (len=0) still writes a varint prefix and no payload
TEST_F(EncodeKeyTest_356, EncodesEmptySlice_356) {
  // Pre-fill scratch to check it gets cleared
  scratch_.assign("garbage");

  Slice target("", 0);
  const char* ret = EncodeKey(&scratch_, target);
  ASSERT_EQ(ret, scratch_.data());

  uint32_t decoded_len = 0;
  size_t varint_len = DecodeVarintPrefix(scratch_, &decoded_len);
  ASSERT_GT(varint_len, 0u);
  EXPECT_EQ(decoded_len, 0u);
  EXPECT_EQ(scratch_.size(), varint_len);  // no payload bytes
}

// Verifies that scratch is cleared (observable via size/content after call)
TEST_F(EncodeKeyTest_356, ClearsExistingScratch_356) {
  // Make scratch deliberately large
  scratch_.assign(100, 'Z');
  const size_t old_size = scratch_.size();

  std::string msg = "hello";
  Slice target(msg);

  const char* ret = EncodeKey(&scratch_, target);
  ASSERT_EQ(ret, scratch_.data());

  uint32_t decoded_len = 0;
  size_t varint_len = DecodeVarintPrefix(scratch_, &decoded_len);
  ASSERT_GT(varint_len, 0u);
  EXPECT_EQ(decoded_len, target.size());

  // New size must be exactly varint_len + payload_len (not old content appended)
  EXPECT_EQ(scratch_.size(), varint_len + target.size());

  // Payload equals target
  EXPECT_EQ(scratch_.substr(varint_len, target.size()), msg);
  // And since the new size is typically smaller than old_size (100),
  // this also demonstrates the previous content is not preserved.
  EXPECT_NE(scratch_.size(), old_size);
}

// Boundary: len=127 should encode into 1-byte varint
TEST_F(EncodeKeyTest_356, Boundary127Len_EncodesCorrectly_356) {
  std::string payload(127, 'a'); // 127 bytes
  Slice target(payload);

  EncodeKey(&scratch_, target);

  uint32_t decoded_len = 0;
  size_t varint_len = DecodeVarintPrefix(scratch_, &decoded_len);
  ASSERT_GT(varint_len, 0u);
  EXPECT_EQ(decoded_len, target.size());
  EXPECT_EQ(varint_len, 1u) << "Varint for 127 should be 1 byte";

  EXPECT_EQ(scratch_.substr(varint_len, payload.size()), payload);
}

// Boundary: len=128 should encode into multi-byte varint (2+ bytes)
TEST_F(EncodeKeyTest_356, Boundary128Len_EncodesCorrectly_356) {
  std::string payload(128, 'b'); // 128 bytes
  Slice target(payload);

  EncodeKey(&scratch_, target);

  uint32_t decoded_len = 0;
  size_t varint_len = DecodeVarintPrefix(scratch_, &decoded_len);
  ASSERT_GT(varint_len, 0u);
  EXPECT_EQ(decoded_len, target.size());
  EXPECT_GE(varint_len, 2u) << "Varint for 128 should be at least 2 bytes";

  EXPECT_EQ(scratch_.substr(varint_len, payload.size()), payload);
}

// Larger size (e.g., 300) to exercise multi-byte varint and full payload copy
TEST_F(EncodeKeyTest_356, LargerLenMultiByteVarint_356) {
  const size_t N = 300;
  std::string payload(N, 'x');
  Slice target(payload);

  EncodeKey(&scratch_, target);

  uint32_t decoded_len = 0;
  size_t varint_len = DecodeVarintPrefix(scratch_, &decoded_len);
  ASSERT_GT(varint_len, 0u);
  EXPECT_EQ(decoded_len, target.size());
  EXPECT_GE(varint_len, 2u);

  EXPECT_EQ(scratch_.substr(varint_len, payload.size()), payload);
}

// Sanity: returned pointer equals scratch data and target remains unchanged
TEST_F(EncodeKeyTest_356, ReturnsPointerToScratch_AndDoesNotModifyTarget_356) {
  std::string payload = "unchanged";
  Slice target(payload);
  const char* before_ptr = target.data();
  const size_t before_size = target.size();

  const char* ret = EncodeKey(&scratch_, target);
  ASSERT_EQ(ret, scratch_.data());      // pointer to start of scratch
  ASSERT_NE(ret, nullptr);

  // Target must be unchanged (observable via data pointer & size)
  EXPECT_EQ(target.data(), before_ptr);
  EXPECT_EQ(target.size(), before_size);

  // Decode & verify payload as usual
  uint32_t decoded_len = 0;
  size_t varint_len = DecodeVarintPrefix(scratch_, &decoded_len);
  ASSERT_GT(varint_len, 0u);
  EXPECT_EQ(decoded_len, before_size);
  EXPECT_EQ(scratch_.substr(varint_len, before_size), payload);
}
