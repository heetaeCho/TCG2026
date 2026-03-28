#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "util/coding.h"

#include <string>
#include <cstdint>

namespace leveldb {

class BlockHandleTest_397 : public ::testing::Test {
 protected:
  BlockHandle handle_;
};

// Test default construction - offset and size should have default values
TEST_F(BlockHandleTest_397, DefaultConstruction_397) {
  BlockHandle bh;
  // Default values are ~0ULL based on the header
  EXPECT_EQ(bh.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(bh.size(), ~static_cast<uint64_t>(0));
}

// Test set_offset and offset
TEST_F(BlockHandleTest_397, SetAndGetOffset_397) {
  handle_.set_offset(42);
  EXPECT_EQ(handle_.offset(), 42);
}

// Test set_size and size
TEST_F(BlockHandleTest_397, SetAndGetSize_397) {
  handle_.set_size(100);
  EXPECT_EQ(handle_.size(), 100);
}

// Test EncodeTo and DecodeFrom round-trip with typical values
TEST_F(BlockHandleTest_397, EncodeDecodeRoundTrip_397) {
  handle_.set_offset(12345);
  handle_.set_size(67890);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 12345);
  EXPECT_EQ(decoded.size(), 67890);
}

// Test round-trip with zero values
TEST_F(BlockHandleTest_397, EncodeDecodeZeroValues_397) {
  handle_.set_offset(0);
  handle_.set_size(0);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 0);
  EXPECT_EQ(decoded.size(), 0);
}

// Test round-trip with large values
TEST_F(BlockHandleTest_397, EncodeDecodeLargeValues_397) {
  uint64_t large_offset = static_cast<uint64_t>(1) << 40;
  uint64_t large_size = static_cast<uint64_t>(1) << 32;
  handle_.set_offset(large_offset);
  handle_.set_size(large_size);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), large_offset);
  EXPECT_EQ(decoded.size(), large_size);
}

// Test round-trip with max uint64 values
TEST_F(BlockHandleTest_397, EncodeDecodeMaxValues_397) {
  uint64_t max_val = std::numeric_limits<uint64_t>::max();
  handle_.set_offset(max_val);
  handle_.set_size(max_val);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), max_val);
  EXPECT_EQ(decoded.size(), max_val);
}

// Test DecodeFrom with empty input returns corruption
TEST_F(BlockHandleTest_397, DecodeFromEmptyInput_397) {
  Slice input;
  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  ASSERT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test DecodeFrom with truncated input (only offset, no size)
TEST_F(BlockHandleTest_397, DecodeFromTruncatedInput_397) {
  // Encode only one varint (the offset)
  std::string partial;
  PutVarint64(&partial, 100);
  // Don't encode size — this should fail

  Slice input(partial);
  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  ASSERT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test that DecodeFrom consumes the correct bytes from the slice
TEST_F(BlockHandleTest_397, DecodeFromConsumesBytes_397) {
  handle_.set_offset(10);
  handle_.set_size(20);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  // Append extra data after the encoded handle
  std::string with_extra = encoded + "extra";
  Slice input(with_extra);
  size_t original_size = input.size();

  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 10);
  EXPECT_EQ(decoded.size(), 20);

  // The input slice should have been advanced past the encoded handle
  EXPECT_EQ(input.size(), 5);  // "extra" is 5 bytes
  EXPECT_EQ(std::string(input.data(), input.size()), "extra");
}

// Test EncodeTo appends to existing string
TEST_F(BlockHandleTest_397, EncodeToAppendsToExistingString_397) {
  handle_.set_offset(1);
  handle_.set_size(2);

  std::string dst = "prefix";
  handle_.EncodeTo(&dst);

  EXPECT_GE(dst.size(), 6);  // "prefix" is 6 bytes
  EXPECT_EQ(dst.substr(0, 6), "prefix");

  // Decode from the portion after "prefix"
  Slice input(dst.data() + 6, dst.size() - 6);
  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 1);
  EXPECT_EQ(decoded.size(), 2);
}

// Test multiple encode/decode sequences
TEST_F(BlockHandleTest_397, MultipleEncodeDecodeSequential_397) {
  std::string encoded;

  BlockHandle h1;
  h1.set_offset(100);
  h1.set_size(200);
  h1.EncodeTo(&encoded);

  BlockHandle h2;
  h2.set_offset(300);
  h2.set_size(400);
  h2.EncodeTo(&encoded);

  Slice input(encoded);

  BlockHandle d1;
  Status s1 = d1.DecodeFrom(&input);
  ASSERT_TRUE(s1.ok());
  EXPECT_EQ(d1.offset(), 100);
  EXPECT_EQ(d1.size(), 200);

  BlockHandle d2;
  Status s2 = d2.DecodeFrom(&input);
  ASSERT_TRUE(s2.ok());
  EXPECT_EQ(d2.offset(), 300);
  EXPECT_EQ(d2.size(), 400);
}

// Test DecodeFrom with corrupted/invalid varint data
TEST_F(BlockHandleTest_397, DecodeFromCorruptedData_397) {
  // Create a byte sequence that might not be a valid varint pair
  // A varint byte with continuation bit set but nothing following
  std::string bad_data;
  bad_data.push_back(static_cast<char>(0x80));  // continuation bit set, no follow-up

  Slice input(bad_data);
  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  ASSERT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// Test setting offset and size multiple times
TEST_F(BlockHandleTest_397, SetOffsetAndSizeMultipleTimes_397) {
  handle_.set_offset(1);
  handle_.set_size(2);
  EXPECT_EQ(handle_.offset(), 1);
  EXPECT_EQ(handle_.size(), 2);

  handle_.set_offset(999);
  handle_.set_size(1000);
  EXPECT_EQ(handle_.offset(), 999);
  EXPECT_EQ(handle_.size(), 1000);
}

// Test round-trip with value 1
TEST_F(BlockHandleTest_397, EncodeDecodeSmallValues_397) {
  handle_.set_offset(1);
  handle_.set_size(1);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 1);
  EXPECT_EQ(decoded.size(), 1);
}

// Test round-trip with 127 (max single-byte varint)
TEST_F(BlockHandleTest_397, EncodeDecodeSingleByteVarintBoundary_397) {
  handle_.set_offset(127);
  handle_.set_size(127);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 127);
  EXPECT_EQ(decoded.size(), 127);
}

// Test round-trip with 128 (first two-byte varint)
TEST_F(BlockHandleTest_397, EncodeDecodeTwoByteVarintBoundary_397) {
  handle_.set_offset(128);
  handle_.set_size(128);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 128);
  EXPECT_EQ(decoded.size(), 128);
}

}  // namespace leveldb
