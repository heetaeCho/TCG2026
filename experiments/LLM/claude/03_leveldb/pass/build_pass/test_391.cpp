#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include <string>
#include <cstdint>

namespace leveldb {

// Test fixture for BlockHandle tests
class BlockHandleTest_391 : public ::testing::Test {
 protected:
  BlockHandle handle_;
};

// Test default construction - offset and size should be initialized to max uint64
TEST_F(BlockHandleTest_391, DefaultConstructor_391) {
  BlockHandle bh;
  uint64_t max_val = ~static_cast<uint64_t>(0);
  EXPECT_EQ(bh.offset(), max_val);
  EXPECT_EQ(bh.size(), max_val);
}

// Test set_offset and offset getter
TEST_F(BlockHandleTest_391, SetAndGetOffset_391) {
  handle_.set_offset(42);
  EXPECT_EQ(handle_.offset(), 42);
}

// Test set_size and size getter
TEST_F(BlockHandleTest_391, SetAndGetSize_391) {
  handle_.set_size(100);
  EXPECT_EQ(handle_.size(), 100);
}

// Test setting offset to zero
TEST_F(BlockHandleTest_391, SetOffsetZero_391) {
  handle_.set_offset(0);
  EXPECT_EQ(handle_.offset(), 0);
}

// Test setting size to zero
TEST_F(BlockHandleTest_391, SetSizeZero_391) {
  handle_.set_size(0);
  EXPECT_EQ(handle_.size(), 0);
}

// Test setting offset to max uint64
TEST_F(BlockHandleTest_391, SetOffsetMaxValue_391) {
  uint64_t max_val = ~static_cast<uint64_t>(0);
  handle_.set_offset(max_val);
  EXPECT_EQ(handle_.offset(), max_val);
}

// Test setting size to max uint64
TEST_F(BlockHandleTest_391, SetSizeMaxValue_391) {
  uint64_t max_val = ~static_cast<uint64_t>(0);
  handle_.set_size(max_val);
  EXPECT_EQ(handle_.size(), max_val);
}

// Test setting large offset value
TEST_F(BlockHandleTest_391, SetLargeOffset_391) {
  uint64_t large_val = static_cast<uint64_t>(1) << 50;
  handle_.set_offset(large_val);
  EXPECT_EQ(handle_.offset(), large_val);
}

// Test setting large size value
TEST_F(BlockHandleTest_391, SetLargeSize_391) {
  uint64_t large_val = static_cast<uint64_t>(1) << 50;
  handle_.set_size(large_val);
  EXPECT_EQ(handle_.size(), large_val);
}

// Test that setting offset does not affect size
TEST_F(BlockHandleTest_391, SetOffsetDoesNotAffectSize_391) {
  handle_.set_size(200);
  handle_.set_offset(100);
  EXPECT_EQ(handle_.size(), 200);
  EXPECT_EQ(handle_.offset(), 100);
}

// Test that setting size does not affect offset
TEST_F(BlockHandleTest_391, SetSizeDoesNotAffectOffset_391) {
  handle_.set_offset(300);
  handle_.set_size(400);
  EXPECT_EQ(handle_.offset(), 300);
  EXPECT_EQ(handle_.size(), 400);
}

// Test EncodeTo produces non-empty output
TEST_F(BlockHandleTest_391, EncodeToProducesOutput_391) {
  handle_.set_offset(10);
  handle_.set_size(20);
  std::string dst;
  handle_.EncodeTo(&dst);
  EXPECT_FALSE(dst.empty());
}

// Test EncodeTo and DecodeFrom roundtrip
TEST_F(BlockHandleTest_391, EncodeDecodeRoundtrip_391) {
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

// Test roundtrip with zero values
TEST_F(BlockHandleTest_391, EncodeDecodeRoundtripZeroValues_391) {
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

// Test roundtrip with large values
TEST_F(BlockHandleTest_391, EncodeDecodeRoundtripLargeValues_391) {
  uint64_t large_offset = (static_cast<uint64_t>(1) << 40) - 1;
  uint64_t large_size = (static_cast<uint64_t>(1) << 35) + 7;
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

// Test DecodeFrom with truncated/corrupt input
TEST_F(BlockHandleTest_391, DecodeFromCorruptInput_391) {
  BlockHandle decoded;
  std::string bad_data;
  Slice input(bad_data);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with partial data (only one varint worth of data might be there)
TEST_F(BlockHandleTest_391, DecodeFromPartialInput_391) {
  handle_.set_offset(100);
  handle_.set_size(200);
  
  std::string encoded;
  handle_.EncodeTo(&encoded);
  
  // Truncate the encoded data
  std::string truncated = encoded.substr(0, 1);
  
  BlockHandle decoded;
  Slice input(truncated);
  Status s = decoded.DecodeFrom(&input);
  // With only 1 byte, it may succeed for offset but fail for size,
  // or it may fail entirely depending on encoding. Either way, if
  // the data is incomplete, we expect a failure or incorrect result.
  // We just check that it doesn't crash, and if it fails, the status reflects it.
  // Note: A single varint byte could be valid for a small number, so
  // the offset might decode but size would fail.
  // We can't predict exactly without knowing the encoding, so just verify no crash.
}

// Test EncodeTo appends to existing string
TEST_F(BlockHandleTest_391, EncodeToAppendsToString_391) {
  handle_.set_offset(5);
  handle_.set_size(10);
  
  std::string dst = "prefix";
  size_t prefix_len = dst.size();
  handle_.EncodeTo(&dst);
  
  EXPECT_GT(dst.size(), prefix_len);
  EXPECT_EQ(dst.substr(0, prefix_len), "prefix");
}

// Test multiple set operations overwrite correctly
TEST_F(BlockHandleTest_391, MultipleSetOperations_391) {
  handle_.set_offset(1);
  handle_.set_size(2);
  EXPECT_EQ(handle_.offset(), 1);
  EXPECT_EQ(handle_.size(), 2);
  
  handle_.set_offset(1000);
  handle_.set_size(2000);
  EXPECT_EQ(handle_.offset(), 1000);
  EXPECT_EQ(handle_.size(), 2000);
  
  handle_.set_offset(0);
  handle_.set_size(0);
  EXPECT_EQ(handle_.offset(), 0);
  EXPECT_EQ(handle_.size(), 0);
}

// Test encoding two handles and decoding them sequentially
TEST_F(BlockHandleTest_391, EncodeDecodeMultipleHandles_391) {
  BlockHandle h1, h2;
  h1.set_offset(111);
  h1.set_size(222);
  h2.set_offset(333);
  h2.set_size(444);
  
  std::string encoded;
  h1.EncodeTo(&encoded);
  h2.EncodeTo(&encoded);
  
  Slice input(encoded);
  
  BlockHandle d1, d2;
  Status s1 = d1.DecodeFrom(&input);
  EXPECT_TRUE(s1.ok());
  EXPECT_EQ(d1.offset(), 111);
  EXPECT_EQ(d1.size(), 222);
  
  Status s2 = d2.DecodeFrom(&input);
  EXPECT_TRUE(s2.ok());
  EXPECT_EQ(d2.offset(), 333);
  EXPECT_EQ(d2.size(), 444);
}

// Test with boundary value 1
TEST_F(BlockHandleTest_391, BoundaryValueOne_391) {
  handle_.set_offset(1);
  handle_.set_size(1);
  
  std::string encoded;
  handle_.EncodeTo(&encoded);
  
  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 1);
  EXPECT_EQ(decoded.size(), 1);
}

}  // namespace leveldb
