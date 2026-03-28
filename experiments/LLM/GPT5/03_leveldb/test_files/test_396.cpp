// File: table/format_encode_to_test_396.cc
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <gtest/gtest.h>
#include <limits>
#include <string>

namespace {

using leveldb::BlockHandle;
using leveldb::Slice;
using leveldb::Status;

class BlockHandleEncodeToTest_396 : public ::testing::Test {
protected:
  static BlockHandle Make(uint64_t off, uint64_t sz) {
    BlockHandle h;
    h.set_offset(off);
    h.set_size(sz);
    return h;
  }

  // Decode helper that uses only the public interface
  static Status DecodeBlockHandle(const std::string& encoded, BlockHandle* out) {
    Slice s(encoded);
    return out->DecodeFrom(&s);
  }
};

// Normal operation: round-trip via EncodeTo → DecodeFrom
TEST_F(BlockHandleEncodeToTest_396, EncodeThenDecode_RoundTrip_396) {
  const uint64_t kOff = 12345;
  const uint64_t kSize = 67890;

  BlockHandle h = Make(kOff, kSize);
  std::string buf;
  h.EncodeTo(&buf);

  BlockHandle parsed;
  Status st = DecodeBlockHandle(buf, &parsed);
  ASSERT_TRUE(st.ok());
  EXPECT_EQ(parsed.offset(), kOff);
  EXPECT_EQ(parsed.size(), kSize);
}

// Boundary: zero values should encode/decode correctly
TEST_F(BlockHandleEncodeToTest_396, EncodesZeroOffsetAndSize_396) {
  BlockHandle h = Make(/*off=*/0, /*sz=*/0);
  std::string buf;
  h.EncodeTo(&buf);

  BlockHandle parsed;
  Status st = DecodeBlockHandle(buf, &parsed);
  ASSERT_TRUE(st.ok());
  EXPECT_EQ(parsed.offset(), 0u);
  EXPECT_EQ(parsed.size(), 0u);
}

// Boundary: very large values (just below uint64_t max) round-trip
TEST_F(BlockHandleEncodeToTest_396, EncodesNearUint64Max_396) {
  const uint64_t kMaxMinus1 = std::numeric_limits<uint64_t>::max() - 1;
  BlockHandle h = Make(kMaxMinus1, kMaxMinus1);

  std::string buf;
  h.EncodeTo(&buf);

  BlockHandle parsed;
  Status st = DecodeBlockHandle(buf, &parsed);
  ASSERT_TRUE(st.ok());
  EXPECT_EQ(parsed.offset(), kMaxMinus1);
  EXPECT_EQ(parsed.size(),   kMaxMinus1);
}

// Observable behavior: EncodeTo appends to an existing string (does not clear)
TEST_F(BlockHandleEncodeToTest_396, AppendsToDestinationString_396) {
  BlockHandle h = Make(11, 22);

  std::string dst = "xxx";  // pre-existing content
  const size_t before = dst.size();
  h.EncodeTo(&dst);
  ASSERT_GT(dst.size(), before);

  // Decode only the appended portion to verify correctness
  std::string appended = dst.substr(before);
  BlockHandle parsed;
  Status st = DecodeBlockHandle(appended, &parsed);
  ASSERT_TRUE(st.ok());
  EXPECT_EQ(parsed.offset(), 11u);
  EXPECT_EQ(parsed.size(), 22u);

  // Ensure the prefix is preserved
  EXPECT_EQ(dst.substr(0, before), "xxx");
}

// Error/exceptional (via assertions): offset unset → death
#ifndef NDEBUG  // Assertions are active only in debug builds
TEST_F(BlockHandleEncodeToTest_396, DiesIfOffsetNotSet_396) {
  BlockHandle h;            // both unset by default
  h.set_size(7);            // leave offset unset
  std::string buf;
  ASSERT_DEATH({ h.EncodeTo(&buf); }, ".*");
}

// Error/exceptional (via assertions): size unset → death
TEST_F(BlockHandleEncodeToTest_396, DiesIfSizeNotSet_396) {
  BlockHandle h;            // both unset by default
  h.set_offset(5);          // leave size unset
  std::string buf;
  ASSERT_DEATH({ h.EncodeTo(&buf); }, ".*");
}
#endif  // NDEBUG

} // namespace
