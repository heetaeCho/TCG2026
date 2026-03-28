#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include <string>
#include <cstdint>

namespace leveldb {

// Test fixture for BlockHandle tests
class BlockHandleTest_390 : public ::testing::Test {
 protected:
  BlockHandle handle_;
};

// Test default construction initializes with max uint64 values
TEST_F(BlockHandleTest_390, DefaultConstructorOffset_390) {
  EXPECT_EQ(handle_.offset(), ~static_cast<uint64_t>(0));
}

TEST_F(BlockHandleTest_390, DefaultConstructorSize_390) {
  EXPECT_EQ(handle_.size(), ~static_cast<uint64_t>(0));
}

// Test set_offset and offset
TEST_F(BlockHandleTest_390, SetAndGetOffset_390) {
  handle_.set_offset(0);
  EXPECT_EQ(handle_.offset(), 0);
}

TEST_F(BlockHandleTest_390, SetAndGetOffsetNonZero_390) {
  handle_.set_offset(12345);
  EXPECT_EQ(handle_.offset(), 12345);
}

TEST_F(BlockHandleTest_390, SetAndGetOffsetLargeValue_390) {
  handle_.set_offset(UINT64_MAX - 1);
  EXPECT_EQ(handle_.offset(), UINT64_MAX - 1);
}

TEST_F(BlockHandleTest_390, SetAndGetOffsetMaxValue_390) {
  handle_.set_offset(UINT64_MAX);
  EXPECT_EQ(handle_.offset(), UINT64_MAX);
}

// Test set_size and size
TEST_F(BlockHandleTest_390, SetAndGetSize_390) {
  handle_.set_size(0);
  EXPECT_EQ(handle_.size(), 0);
}

TEST_F(BlockHandleTest_390, SetAndGetSizeNonZero_390) {
  handle_.set_size(67890);
  EXPECT_EQ(handle_.size(), 67890);
}

TEST_F(BlockHandleTest_390, SetAndGetSizeLargeValue_390) {
  handle_.set_size(UINT64_MAX - 1);
  EXPECT_EQ(handle_.size(), UINT64_MAX - 1);
}

TEST_F(BlockHandleTest_390, SetAndGetSizeMaxValue_390) {
  handle_.set_size(UINT64_MAX);
  EXPECT_EQ(handle_.size(), UINT64_MAX);
}

// Test setting both offset and size
TEST_F(BlockHandleTest_390, SetBothOffsetAndSize_390) {
  handle_.set_offset(100);
  handle_.set_size(200);
  EXPECT_EQ(handle_.offset(), 100);
  EXPECT_EQ(handle_.size(), 200);
}

// Test overwriting offset and size
TEST_F(BlockHandleTest_390, OverwriteOffset_390) {
  handle_.set_offset(100);
  EXPECT_EQ(handle_.offset(), 100);
  handle_.set_offset(999);
  EXPECT_EQ(handle_.offset(), 999);
}

TEST_F(BlockHandleTest_390, OverwriteSize_390) {
  handle_.set_size(100);
  EXPECT_EQ(handle_.size(), 100);
  handle_.set_size(999);
  EXPECT_EQ(handle_.size(), 999);
}

// Test EncodeTo and DecodeFrom roundtrip
TEST_F(BlockHandleTest_390, EncodeDecodeRoundtrip_390) {
  handle_.set_offset(100);
  handle_.set_size(200);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 100);
  EXPECT_EQ(decoded.size(), 200);
}

TEST_F(BlockHandleTest_390, EncodeDecodeZeroValues_390) {
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

TEST_F(BlockHandleTest_390, EncodeDecodeLargeValues_390) {
  uint64_t large_offset = 1ULL << 40;
  uint64_t large_size = 1ULL << 32;
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

// Test DecodeFrom with truncated/invalid data
TEST_F(BlockHandleTest_390, DecodeFromEmptySlice_390) {
  BlockHandle decoded;
  Slice input("");
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST_F(BlockHandleTest_390, DecodeFromTruncatedData_390) {
  // Encode a valid handle, then truncate the encoded string
  handle_.set_offset(100);
  handle_.set_size(200);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  // Truncate to just 1 byte
  std::string truncated = encoded.substr(0, 1);
  BlockHandle decoded;
  Slice input(truncated);
  Status s = decoded.DecodeFrom(&input);
  // With only 1 byte, decoding the second varint should fail
  // (the first varint for offset might succeed if it's a single byte,
  //  but the second for size should fail)
  // Actually, offset=100 fits in 1 byte varint, but then size varint is missing
  EXPECT_FALSE(s.ok());
}

// Test that EncodeTo appends to existing string
TEST_F(BlockHandleTest_390, EncodeToAppends_390) {
  handle_.set_offset(10);
  handle_.set_size(20);

  std::string encoded;
  handle_.EncodeTo(&encoded);
  size_t first_len = encoded.size();

  // Encode again - should append
  handle_.EncodeTo(&encoded);
  EXPECT_EQ(encoded.size(), first_len * 2);
}

// Test multiple different handles encode/decode correctly
TEST_F(BlockHandleTest_390, MultipleHandlesEncodeDecode_390) {
  BlockHandle h1, h2;
  h1.set_offset(0);
  h1.set_size(100);
  h2.set_offset(100);
  h2.set_size(200);

  std::string encoded1, encoded2;
  h1.EncodeTo(&encoded1);
  h2.EncodeTo(&encoded2);

  BlockHandle d1, d2;
  Slice s1(encoded1);
  Slice s2(encoded2);

  EXPECT_TRUE(d1.DecodeFrom(&s1).ok());
  EXPECT_TRUE(d2.DecodeFrom(&s2).ok());

  EXPECT_EQ(d1.offset(), 0);
  EXPECT_EQ(d1.size(), 100);
  EXPECT_EQ(d2.offset(), 100);
  EXPECT_EQ(d2.size(), 200);
}

// Test that DecodeFrom consumes exactly the right amount of input
TEST_F(BlockHandleTest_390, DecodeFromConsumesCorrectly_390) {
  handle_.set_offset(42);
  handle_.set_size(84);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  // Append extra data
  std::string with_extra = encoded + "extradata";
  Slice input(with_extra);

  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 42);
  EXPECT_EQ(decoded.size(), 84);

  // The slice should have been advanced past the encoded handle
  EXPECT_EQ(input.size(), 9);  // "extradata" is 9 bytes
}

}  // namespace leveldb
