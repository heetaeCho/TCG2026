#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper to extract fixed32 from a string at a given offset
static uint32_t DecodeFixed32(const char* ptr) {
  return static_cast<uint32_t>(static_cast<unsigned char>(ptr[0])) |
         (static_cast<uint32_t>(static_cast<unsigned char>(ptr[1])) << 8) |
         (static_cast<uint32_t>(static_cast<unsigned char>(ptr[2])) << 16) |
         (static_cast<uint32_t>(static_cast<unsigned char>(ptr[3])) << 24);
}

class FooterTest_398 : public ::testing::Test {
 protected:
  Footer footer_;
};

// Test that EncodeTo produces the correct encoded length
TEST_F(FooterTest_398, EncodeToProducesCorrectLength_398) {
  std::string dst;
  footer_.EncodeTo(&dst);
  // kEncodedLength = 2 * BlockHandle::kMaxEncodedLength + 8
  // BlockHandle::kMaxEncodedLength = 10 (varint64 max) + 10 = 20
  // kEncodedLength = 2 * 10 + 8 = 48
  EXPECT_EQ(dst.size(), Footer::kEncodedLength);
}

// Test that encoding the default footer produces a fixed-size output
TEST_F(FooterTest_398, DefaultFooterEncodeSize_398) {
  std::string dst;
  footer_.EncodeTo(&dst);
  EXPECT_EQ(dst.size(), Footer::kEncodedLength);
}

// Test that the magic number is correctly encoded at the end
TEST_F(FooterTest_398, MagicNumberAtEnd_398) {
  std::string dst;
  footer_.EncodeTo(&dst);

  // Last 8 bytes should contain the magic number
  size_t len = dst.size();
  ASSERT_GE(len, 8u);
  uint32_t lo = DecodeFixed32(dst.data() + len - 8);
  uint32_t hi = DecodeFixed32(dst.data() + len - 4);
  uint64_t magic = (static_cast<uint64_t>(hi) << 32) | static_cast<uint64_t>(lo);
  EXPECT_EQ(magic, kTableMagicNumber);
}

// Test round-trip encode/decode with default handles
TEST_F(FooterTest_398, RoundTripDefault_398) {
  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Default block handles should round-trip
  // After decode, the metaindex and index handles should match the originals
  EXPECT_EQ(decoded.metaindex_handle().offset(), footer_.metaindex_handle().offset());
  EXPECT_EQ(decoded.metaindex_handle().size(), footer_.metaindex_handle().size());
  EXPECT_EQ(decoded.index_handle().offset(), footer_.index_handle().offset());
  EXPECT_EQ(decoded.index_handle().size(), footer_.index_handle().size());
}

// Test round-trip with specific handle values
TEST_F(FooterTest_398, RoundTripWithSpecificHandles_398) {
  BlockHandle metaindex;
  metaindex.set_offset(100);
  metaindex.set_size(200);
  footer_.set_metaindex_handle(metaindex);

  BlockHandle index;
  index.set_offset(300);
  index.set_size(400);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);
  EXPECT_EQ(encoded.size(), Footer::kEncodedLength);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(decoded.metaindex_handle().offset(), 100u);
  EXPECT_EQ(decoded.metaindex_handle().size(), 200u);
  EXPECT_EQ(decoded.index_handle().offset(), 300u);
  EXPECT_EQ(decoded.index_handle().size(), 400u);
}

// Test round-trip with zero values
TEST_F(FooterTest_398, RoundTripWithZeroHandles_398) {
  BlockHandle metaindex;
  metaindex.set_offset(0);
  metaindex.set_size(0);
  footer_.set_metaindex_handle(metaindex);

  BlockHandle index;
  index.set_offset(0);
  index.set_size(0);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);
  EXPECT_EQ(encoded.size(), Footer::kEncodedLength);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(decoded.metaindex_handle().offset(), 0u);
  EXPECT_EQ(decoded.metaindex_handle().size(), 0u);
  EXPECT_EQ(decoded.index_handle().offset(), 0u);
  EXPECT_EQ(decoded.index_handle().size(), 0u);
}

// Test round-trip with large handle values
TEST_F(FooterTest_398, RoundTripWithLargeHandles_398) {
  BlockHandle metaindex;
  metaindex.set_offset(1ULL << 40);
  metaindex.set_size(1ULL << 50);
  footer_.set_metaindex_handle(metaindex);

  BlockHandle index;
  index.set_offset(1ULL << 55);
  index.set_size(1ULL << 60);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);
  EXPECT_EQ(encoded.size(), Footer::kEncodedLength);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(decoded.metaindex_handle().offset(), 1ULL << 40);
  EXPECT_EQ(decoded.metaindex_handle().size(), 1ULL << 50);
  EXPECT_EQ(decoded.index_handle().offset(), 1ULL << 55);
  EXPECT_EQ(decoded.index_handle().size(), 1ULL << 60);
}

// Test that encoding appends to an existing string correctly
TEST_F(FooterTest_398, EncodeToAppendsToExistingString_398) {
  std::string dst = "prefix";
  size_t prefix_len = dst.size();
  footer_.EncodeTo(&dst);
  EXPECT_EQ(dst.size(), prefix_len + Footer::kEncodedLength);
  EXPECT_EQ(dst.substr(0, prefix_len), "prefix");
}

// Test decoding with corrupted magic number fails
TEST_F(FooterTest_398, DecodeFromCorruptedMagicNumber_398) {
  BlockHandle metaindex;
  metaindex.set_offset(10);
  metaindex.set_size(20);
  footer_.set_metaindex_handle(metaindex);

  BlockHandle index;
  index.set_offset(30);
  index.set_size(40);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);
  ASSERT_EQ(encoded.size(), Footer::kEncodedLength);

  // Corrupt the last byte (part of magic number)
  encoded[encoded.size() - 1] ^= 0xFF;

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test decoding with truncated input fails
TEST_F(FooterTest_398, DecodeFromTruncatedInput_398) {
  std::string encoded;
  footer_.EncodeTo(&encoded);

  // Truncate the encoded data
  std::string truncated = encoded.substr(0, Footer::kEncodedLength - 1);

  Footer decoded;
  Slice input(truncated);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test set and get for metaindex_handle
TEST_F(FooterTest_398, SetGetMetaindexHandle_398) {
  BlockHandle h;
  h.set_offset(42);
  h.set_size(84);
  footer_.set_metaindex_handle(h);
  EXPECT_EQ(footer_.metaindex_handle().offset(), 42u);
  EXPECT_EQ(footer_.metaindex_handle().size(), 84u);
}

// Test set and get for index_handle
TEST_F(FooterTest_398, SetGetIndexHandle_398) {
  BlockHandle h;
  h.set_offset(123);
  h.set_size(456);
  footer_.set_index_handle(h);
  EXPECT_EQ(footer_.index_handle().offset(), 123u);
  EXPECT_EQ(footer_.index_handle().size(), 456u);
}

// Test encoding two different footers produce different results (except padding)
TEST_F(FooterTest_398, DifferentHandlesProduceDifferentEncodings_398) {
  Footer f1;
  BlockHandle h1;
  h1.set_offset(1);
  h1.set_size(2);
  f1.set_metaindex_handle(h1);
  f1.set_index_handle(h1);

  Footer f2;
  BlockHandle h2;
  h2.set_offset(100);
  h2.set_size(200);
  f2.set_metaindex_handle(h2);
  f2.set_index_handle(h2);

  std::string enc1, enc2;
  f1.EncodeTo(&enc1);
  f2.EncodeTo(&enc2);

  EXPECT_EQ(enc1.size(), enc2.size());
  EXPECT_NE(enc1, enc2);
}

// Test BlockHandle default constructor
TEST(BlockHandleTest_398, DefaultConstructor_398) {
  BlockHandle h;
  // Default values should be ~0 (uninitialized sentinel)
  EXPECT_EQ(h.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(h.size(), ~static_cast<uint64_t>(0));
}

// Test BlockHandle encode/decode round-trip
TEST(BlockHandleTest_398, RoundTrip_398) {
  BlockHandle h;
  h.set_offset(12345);
  h.set_size(67890);

  std::string encoded;
  h.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 12345u);
  EXPECT_EQ(decoded.size(), 67890u);
}

// Test BlockHandle set/get
TEST(BlockHandleTest_398, SetGet_398) {
  BlockHandle h;
  h.set_offset(999);
  EXPECT_EQ(h.offset(), 999u);
  h.set_size(888);
  EXPECT_EQ(h.size(), 888u);
}

// Test decoding an empty slice for footer fails
TEST_F(FooterTest_398, DecodeFromEmptySlice_398) {
  Footer decoded;
  Slice input("");
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test multiple encodes produce the same result
TEST_F(FooterTest_398, MultipleEncodesConsistent_398) {
  BlockHandle metaindex;
  metaindex.set_offset(50);
  metaindex.set_size(60);
  footer_.set_metaindex_handle(metaindex);

  BlockHandle index;
  index.set_offset(70);
  index.set_size(80);
  footer_.set_index_handle(index);

  std::string enc1, enc2;
  footer_.EncodeTo(&enc1);
  footer_.EncodeTo(&enc2);
  EXPECT_EQ(enc1, enc2);
}

}  // namespace leveldb
