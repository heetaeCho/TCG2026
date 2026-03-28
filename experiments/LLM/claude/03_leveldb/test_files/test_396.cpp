#include "gtest/gtest.h"
#include "table/format.h"
#include "util/coding.h"

namespace leveldb {

class BlockHandleTest_396 : public ::testing::Test {
 protected:
  BlockHandle handle_;
};

// Test that a default-constructed BlockHandle has uninitialized sentinel values
TEST_F(BlockHandleTest_396, DefaultConstructor_396) {
  // Default constructed handle should have sentinel values
  // We can verify by attempting to set and get values
  BlockHandle bh;
  // The default values are ~0ULL which means EncodeTo would assert
  // We just verify we can construct it
}

// Test set_offset and offset getter
TEST_F(BlockHandleTest_396, SetAndGetOffset_396) {
  handle_.set_offset(100);
  EXPECT_EQ(100, handle_.offset());
}

// Test set_size and size getter
TEST_F(BlockHandleTest_396, SetAndGetSize_396) {
  handle_.set_size(200);
  EXPECT_EQ(200, handle_.size());
}

// Test setting offset to zero
TEST_F(BlockHandleTest_396, SetOffsetZero_396) {
  handle_.set_offset(0);
  EXPECT_EQ(0, handle_.offset());
}

// Test setting size to zero
TEST_F(BlockHandleTest_396, SetSizeZero_396) {
  handle_.set_size(0);
  EXPECT_EQ(0, handle_.size());
}

// Test setting large values for offset and size
TEST_F(BlockHandleTest_396, LargeValues_396) {
  uint64_t large_val = 1ULL << 40;  // 1 TB offset
  handle_.set_offset(large_val);
  handle_.set_size(large_val + 1);
  EXPECT_EQ(large_val, handle_.offset());
  EXPECT_EQ(large_val + 1, handle_.size());
}

// Test EncodeTo produces non-empty string
TEST_F(BlockHandleTest_396, EncodeToProducesNonEmptyString_396) {
  handle_.set_offset(0);
  handle_.set_size(0);
  std::string dst;
  handle_.EncodeTo(&dst);
  EXPECT_FALSE(dst.empty());
}

// Test EncodeTo followed by DecodeFrom recovers original values
TEST_F(BlockHandleTest_396, EncodeDecodeRoundTrip_396) {
  handle_.set_offset(12345);
  handle_.set_size(67890);
  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(12345, decoded.offset());
  EXPECT_EQ(67890, decoded.size());
}

// Test EncodeTo with zero offset and size, then decode
TEST_F(BlockHandleTest_396, EncodeDecodeZeroValues_396) {
  handle_.set_offset(0);
  handle_.set_size(0);
  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(0, decoded.offset());
  EXPECT_EQ(0, decoded.size());
}

// Test EncodeTo with large offset and size, then decode
TEST_F(BlockHandleTest_396, EncodeDecodeLargeValues_396) {
  uint64_t large_offset = (1ULL << 50) - 1;
  uint64_t large_size = (1ULL << 48) + 42;
  handle_.set_offset(large_offset);
  handle_.set_size(large_size);
  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(large_offset, decoded.offset());
  EXPECT_EQ(large_size, decoded.size());
}

// Test EncodeTo appends to existing string content
TEST_F(BlockHandleTest_396, EncodeToAppendsToExistingString_396) {
  handle_.set_offset(10);
  handle_.set_size(20);
  std::string dst = "prefix";
  size_t prefix_len = dst.size();
  handle_.EncodeTo(&dst);
  EXPECT_GT(dst.size(), prefix_len);
  // The prefix should still be there
  EXPECT_EQ("prefix", dst.substr(0, prefix_len));
}

// Test DecodeFrom with empty input fails
TEST_F(BlockHandleTest_396, DecodeFromEmptyInputFails_396) {
  BlockHandle decoded;
  Slice input("");
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with truncated input fails
TEST_F(BlockHandleTest_396, DecodeFromTruncatedInputFails_396) {
  handle_.set_offset(100);
  handle_.set_size(200);
  std::string encoded;
  handle_.EncodeTo(&encoded);

  // Truncate the encoded data
  std::string truncated = encoded.substr(0, 1);
  BlockHandle decoded;
  Slice input(truncated);
  Status s = decoded.DecodeFrom(&input);
  // This may or may not fail depending on whether one varint is decodable
  // but size won't be. Let's try with truly minimal data.
  // Actually with just 1 byte, offset varint (value 100) needs 1 byte,
  // but size varint won't be present. Let's check.
  // The first varint for offset=100 is 1 byte. So after decoding offset,
  // there's no data for size. Should fail.
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with corrupted/invalid data
TEST_F(BlockHandleTest_396, DecodeFromInvalidData_396) {
  // Create data that looks like an incomplete varint (high bit set but no continuation)
  std::string bad_data(1, '\xff');
  BlockHandle decoded;
  Slice input(bad_data);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test multiple encode-decode cycles
TEST_F(BlockHandleTest_396, MultipleEncodeDecodeCycles_396) {
  for (uint64_t i = 0; i < 10; i++) {
    BlockHandle original;
    original.set_offset(i * 1000);
    original.set_size(i * 500 + 1);

    std::string encoded;
    original.EncodeTo(&encoded);

    BlockHandle decoded;
    Slice input(encoded);
    Status s = decoded.DecodeFrom(&input);
    EXPECT_TRUE(s.ok());
    EXPECT_EQ(original.offset(), decoded.offset());
    EXPECT_EQ(original.size(), decoded.size());
  }
}

// Test that DecodeFrom consumes exactly the right amount of input
TEST_F(BlockHandleTest_396, DecodeFromConsumesCorrectAmount_396) {
  handle_.set_offset(42);
  handle_.set_size(84);
  std::string encoded;
  handle_.EncodeTo(&encoded);

  // Add extra bytes after the encoded data
  std::string with_extra = encoded + "extra";
  Slice input(with_extra);
  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(42, decoded.offset());
  EXPECT_EQ(84, decoded.size());
  // The remaining input should be "extra"
  EXPECT_EQ("extra", input.ToString());
}

// Test encoding two handles consecutively and decoding them
TEST_F(BlockHandleTest_396, TwoHandlesEncodedConsecutively_396) {
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
  EXPECT_TRUE(d1.DecodeFrom(&input).ok());
  EXPECT_TRUE(d2.DecodeFrom(&input).ok());
  EXPECT_EQ(111, d1.offset());
  EXPECT_EQ(222, d1.size());
  EXPECT_EQ(333, d2.offset());
  EXPECT_EQ(444, d2.size());
}

// Test with maximum safe varint64 values
TEST_F(BlockHandleTest_396, MaxVarint64Values_396) {
  // Use a value that is close to max but not the sentinel
  uint64_t max_val = (1ULL << 63) - 1;
  handle_.set_offset(max_val);
  handle_.set_size(max_val);
  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(max_val, decoded.offset());
  EXPECT_EQ(max_val, decoded.size());
}

// Test setting values multiple times
TEST_F(BlockHandleTest_396, OverwriteValues_396) {
  handle_.set_offset(1);
  handle_.set_size(2);
  EXPECT_EQ(1, handle_.offset());
  EXPECT_EQ(2, handle_.size());

  handle_.set_offset(100);
  handle_.set_size(200);
  EXPECT_EQ(100, handle_.offset());
  EXPECT_EQ(200, handle_.size());
}

}  // namespace leveldb
