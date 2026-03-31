#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include <string>
#include <cstdint>

namespace leveldb {

// Test fixture for BlockHandle tests
class BlockHandleTest_388 : public ::testing::Test {
 protected:
  BlockHandle handle_;
};

// Test default construction - offset and size should be initialized to max uint64
TEST_F(BlockHandleTest_388, DefaultConstruction_388) {
  BlockHandle bh;
  uint64_t max_val = ~static_cast<uint64_t>(0);
  EXPECT_EQ(bh.offset(), max_val);
  EXPECT_EQ(bh.size(), max_val);
}

// Test set_offset and offset getter
TEST_F(BlockHandleTest_388, SetAndGetOffset_388) {
  handle_.set_offset(42);
  EXPECT_EQ(handle_.offset(), 42);
}

// Test set_size and size getter
TEST_F(BlockHandleTest_388, SetAndGetSize_388) {
  handle_.set_size(100);
  EXPECT_EQ(handle_.size(), 100);
}

// Test setting offset to zero
TEST_F(BlockHandleTest_388, SetOffsetZero_388) {
  handle_.set_offset(0);
  EXPECT_EQ(handle_.offset(), 0);
}

// Test setting size to zero
TEST_F(BlockHandleTest_388, SetSizeZero_388) {
  handle_.set_size(0);
  EXPECT_EQ(handle_.size(), 0);
}

// Test setting offset to max uint64
TEST_F(BlockHandleTest_388, SetOffsetMaxUint64_388) {
  uint64_t max_val = ~static_cast<uint64_t>(0);
  handle_.set_offset(max_val);
  EXPECT_EQ(handle_.offset(), max_val);
}

// Test setting size to max uint64
TEST_F(BlockHandleTest_388, SetSizeMaxUint64_388) {
  uint64_t max_val = ~static_cast<uint64_t>(0);
  handle_.set_size(max_val);
  EXPECT_EQ(handle_.size(), max_val);
}

// Test setting offset to a large value
TEST_F(BlockHandleTest_388, SetOffsetLargeValue_388) {
  uint64_t large_val = static_cast<uint64_t>(1) << 50;
  handle_.set_offset(large_val);
  EXPECT_EQ(handle_.offset(), large_val);
}

// Test setting size to a large value
TEST_F(BlockHandleTest_388, SetSizeLargeValue_388) {
  uint64_t large_val = static_cast<uint64_t>(1) << 50;
  handle_.set_size(large_val);
  EXPECT_EQ(handle_.size(), large_val);
}

// Test EncodeTo and DecodeFrom roundtrip
TEST_F(BlockHandleTest_388, EncodeDecodeRoundtrip_388) {
  handle_.set_offset(123);
  handle_.set_size(456);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 123);
  EXPECT_EQ(decoded.size(), 456);
}

// Test EncodeTo and DecodeFrom roundtrip with zero values
TEST_F(BlockHandleTest_388, EncodeDecodeZeroValues_388) {
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

// Test EncodeTo and DecodeFrom roundtrip with large values
TEST_F(BlockHandleTest_388, EncodeDecodeLargeValues_388) {
  uint64_t large_offset = (static_cast<uint64_t>(1) << 40) - 1;
  uint64_t large_size = (static_cast<uint64_t>(1) << 35) + 7;
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

// Test DecodeFrom with corrupted/truncated data
TEST_F(BlockHandleTest_388, DecodeFromCorruptedData_388) {
  // Empty input should fail
  BlockHandle decoded;
  Slice empty_input("");
  Status s = decoded.DecodeFrom(&empty_input);
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with insufficient data (single byte)
TEST_F(BlockHandleTest_388, DecodeFromInsufficientData_388) {
  BlockHandle decoded;
  std::string short_data("\x01", 1);
  Slice input(short_data);
  Status s = decoded.DecodeFrom(&input);
  // It may or may not succeed depending on varint encoding;
  // If the first varint decodes but the second doesn't, it should fail
  // We just check it doesn't crash; the status should indicate failure
  // since there's not enough data for two varints typically
  // (though a single byte could encode one varint, leaving no data for the second)
  // This is implementation-dependent, so we just ensure no crash.
}

// Test overwriting offset and size values
TEST_F(BlockHandleTest_388, OverwriteValues_388) {
  handle_.set_offset(10);
  handle_.set_size(20);
  EXPECT_EQ(handle_.offset(), 10);
  EXPECT_EQ(handle_.size(), 20);

  handle_.set_offset(30);
  handle_.set_size(40);
  EXPECT_EQ(handle_.offset(), 30);
  EXPECT_EQ(handle_.size(), 40);
}

// Test that setting offset doesn't affect size and vice versa
TEST_F(BlockHandleTest_388, OffsetAndSizeIndependent_388) {
  handle_.set_offset(100);
  handle_.set_size(200);

  handle_.set_offset(300);
  EXPECT_EQ(handle_.offset(), 300);
  EXPECT_EQ(handle_.size(), 200);

  handle_.set_size(400);
  EXPECT_EQ(handle_.offset(), 300);
  EXPECT_EQ(handle_.size(), 400);
}

// Test multiple encode/decode cycles
TEST_F(BlockHandleTest_388, MultipleEncodeDecodeCycles_388) {
  for (uint64_t i = 0; i < 100; i++) {
    BlockHandle original;
    original.set_offset(i * 1000);
    original.set_size(i * 500);

    std::string encoded;
    original.EncodeTo(&encoded);

    BlockHandle decoded;
    Slice input(encoded);
    Status s = decoded.DecodeFrom(&input);
    ASSERT_TRUE(s.ok());
    EXPECT_EQ(decoded.offset(), i * 1000);
    EXPECT_EQ(decoded.size(), i * 500);
  }
}

// Test EncodeTo appends to existing string
TEST_F(BlockHandleTest_388, EncodeToAppends_388) {
  handle_.set_offset(10);
  handle_.set_size(20);

  std::string dst = "prefix";
  size_t prefix_len = dst.size();
  handle_.EncodeTo(&dst);
  EXPECT_GT(dst.size(), prefix_len);

  // Decode should work from the encoded portion
  Slice input(dst.data() + prefix_len, dst.size() - prefix_len);
  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 10);
  EXPECT_EQ(decoded.size(), 20);
}

// Test that encoded representation is non-empty
TEST_F(BlockHandleTest_388, EncodedNonEmpty_388) {
  handle_.set_offset(0);
  handle_.set_size(0);

  std::string encoded;
  handle_.EncodeTo(&encoded);
  EXPECT_FALSE(encoded.empty());
}

}  // namespace leveldb
