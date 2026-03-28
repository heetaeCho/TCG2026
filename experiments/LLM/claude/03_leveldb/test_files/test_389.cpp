#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include <string>
#include <cstdint>

namespace leveldb {

// Test fixture for BlockHandle tests
class BlockHandleTest_389 : public ::testing::Test {
 protected:
  BlockHandle handle_;
};

// Test default construction - offset and size should be initialized to max uint64
TEST_F(BlockHandleTest_389, DefaultConstruction_389) {
  BlockHandle bh;
  // Default values are ~0ULL based on the constructor
  EXPECT_EQ(bh.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(bh.size(), ~static_cast<uint64_t>(0));
}

// Test set_offset and offset getter
TEST_F(BlockHandleTest_389, SetAndGetOffset_389) {
  handle_.set_offset(42);
  EXPECT_EQ(handle_.offset(), 42);
}

// Test set_size and size getter
TEST_F(BlockHandleTest_389, SetAndGetSize_389) {
  handle_.set_size(100);
  EXPECT_EQ(handle_.size(), 100);
}

// Test setting offset to zero
TEST_F(BlockHandleTest_389, SetOffsetToZero_389) {
  handle_.set_offset(0);
  EXPECT_EQ(handle_.offset(), 0);
}

// Test setting size to zero
TEST_F(BlockHandleTest_389, SetSizeToZero_389) {
  handle_.set_size(0);
  EXPECT_EQ(handle_.size(), 0);
}

// Test setting offset to a large value
TEST_F(BlockHandleTest_389, SetOffsetLargeValue_389) {
  uint64_t large_val = static_cast<uint64_t>(1) << 40;
  handle_.set_offset(large_val);
  EXPECT_EQ(handle_.offset(), large_val);
}

// Test setting size to a large value
TEST_F(BlockHandleTest_389, SetSizeLargeValue_389) {
  uint64_t large_val = static_cast<uint64_t>(1) << 40;
  handle_.set_size(large_val);
  EXPECT_EQ(handle_.size(), large_val);
}

// Test setting offset to max uint64
TEST_F(BlockHandleTest_389, SetOffsetMaxValue_389) {
  handle_.set_offset(UINT64_MAX);
  EXPECT_EQ(handle_.offset(), UINT64_MAX);
}

// Test setting size to max uint64
TEST_F(BlockHandleTest_389, SetSizeMaxValue_389) {
  handle_.set_size(UINT64_MAX);
  EXPECT_EQ(handle_.size(), UINT64_MAX);
}

// Test overwriting offset
TEST_F(BlockHandleTest_389, OverwriteOffset_389) {
  handle_.set_offset(10);
  EXPECT_EQ(handle_.offset(), 10);
  handle_.set_offset(20);
  EXPECT_EQ(handle_.offset(), 20);
}

// Test overwriting size
TEST_F(BlockHandleTest_389, OverwriteSize_389) {
  handle_.set_size(10);
  EXPECT_EQ(handle_.size(), 10);
  handle_.set_size(20);
  EXPECT_EQ(handle_.size(), 20);
}

// Test EncodeTo produces non-empty output
TEST_F(BlockHandleTest_389, EncodeToProducesOutput_389) {
  handle_.set_offset(100);
  handle_.set_size(200);
  std::string dst;
  handle_.EncodeTo(&dst);
  EXPECT_FALSE(dst.empty());
}

// Test EncodeTo then DecodeFrom round-trip
TEST_F(BlockHandleTest_389, EncodeDecodeRoundTrip_389) {
  handle_.set_offset(12345);
  handle_.set_size(67890);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 12345);
  EXPECT_EQ(decoded.size(), 67890);
}

// Test round-trip with zero values
TEST_F(BlockHandleTest_389, EncodeDecodeRoundTripZero_389) {
  handle_.set_offset(0);
  handle_.set_size(0);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 0);
  EXPECT_EQ(decoded.size(), 0);
}

// Test round-trip with large values
TEST_F(BlockHandleTest_389, EncodeDecodeRoundTripLarge_389) {
  uint64_t large_offset = (static_cast<uint64_t>(1) << 50) - 1;
  uint64_t large_size = (static_cast<uint64_t>(1) << 48) + 7;
  handle_.set_offset(large_offset);
  handle_.set_size(large_size);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), large_offset);
  EXPECT_EQ(decoded.size(), large_size);
}

// Test DecodeFrom with truncated/empty input should fail
TEST_F(BlockHandleTest_389, DecodeFromEmptyInput_389) {
  BlockHandle decoded;
  Slice input("");
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with corrupted (too short) input
TEST_F(BlockHandleTest_389, DecodeFromTruncatedInput_389) {
  // Encode a valid handle, then truncate
  handle_.set_offset(100);
  handle_.set_size(200);
  std::string encoded;
  handle_.EncodeTo(&encoded);

  // Truncate to 1 byte (should not be enough for two varints)
  std::string truncated = encoded.substr(0, 1);
  BlockHandle decoded;
  Slice input(truncated);
  Status s = decoded.DecodeFrom(&input);
  // With only 1 byte, decoding the second varint might fail
  // (depends on varint encoding, but if offset is small enough, 
  //  1 byte might decode offset but not size)
  // We just check it either succeeds or fails gracefully
  // Actually with offset=100 that's 1 byte, size=200 that's 2 bytes,
  // so 1 byte should decode offset but fail on size
  EXPECT_FALSE(s.ok());
}

// Test that EncodeTo appends to existing string
TEST_F(BlockHandleTest_389, EncodeToAppends_389) {
  handle_.set_offset(1);
  handle_.set_size(2);

  std::string dst = "prefix";
  size_t prefix_len = dst.size();
  handle_.EncodeTo(&dst);
  EXPECT_GT(dst.size(), prefix_len);
  // Verify the prefix is preserved
  EXPECT_EQ(dst.substr(0, prefix_len), "prefix");
}

// Test multiple encodes into same string
TEST_F(BlockHandleTest_389, MultipleEncodes_389) {
  BlockHandle h1, h2;
  h1.set_offset(10);
  h1.set_size(20);
  h2.set_offset(30);
  h2.set_size(40);

  std::string encoded;
  h1.EncodeTo(&encoded);
  size_t first_len = encoded.size();
  h2.EncodeTo(&encoded);
  EXPECT_GT(encoded.size(), first_len);

  // Decode both back
  Slice input(encoded);
  BlockHandle d1, d2;
  Status s1 = d1.DecodeFrom(&input);
  EXPECT_TRUE(s1.ok());
  EXPECT_EQ(d1.offset(), 10);
  EXPECT_EQ(d1.size(), 20);

  Status s2 = d2.DecodeFrom(&input);
  EXPECT_TRUE(s2.ok());
  EXPECT_EQ(d2.offset(), 30);
  EXPECT_EQ(d2.size(), 40);
}

// Test setting offset does not affect size and vice versa
TEST_F(BlockHandleTest_389, OffsetAndSizeIndependent_389) {
  handle_.set_offset(111);
  handle_.set_size(222);
  EXPECT_EQ(handle_.offset(), 111);
  EXPECT_EQ(handle_.size(), 222);

  handle_.set_offset(333);
  EXPECT_EQ(handle_.offset(), 333);
  EXPECT_EQ(handle_.size(), 222);  // size unchanged

  handle_.set_size(444);
  EXPECT_EQ(handle_.offset(), 333);  // offset unchanged
  EXPECT_EQ(handle_.size(), 444);
}

}  // namespace leveldb
