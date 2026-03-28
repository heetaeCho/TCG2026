#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class FooterTest_392 : public ::testing::Test {
 protected:
  Footer footer_;
};

// Test default construction - metaindex_handle and index_handle should have
// default BlockHandle values
TEST_F(FooterTest_392, DefaultConstruction_392) {
  BlockHandle metaindex = footer_.metaindex_handle();
  BlockHandle index = footer_.index_handle();
  // Default BlockHandle should have offset and size of 0 (or some default)
  // We just verify the accessors don't crash on default construction
  (void)metaindex;
  (void)index;
}

// Test set_metaindex_handle and metaindex_handle getter
TEST_F(FooterTest_392, SetAndGetMetaindexHandle_392) {
  BlockHandle handle;
  handle.set_offset(100);
  handle.set_size(200);
  footer_.set_metaindex_handle(handle);

  const BlockHandle& result = footer_.metaindex_handle();
  EXPECT_EQ(result.offset(), 100);
  EXPECT_EQ(result.size(), 200);
}

// Test set_index_handle and index_handle getter
TEST_F(FooterTest_392, SetAndGetIndexHandle_392) {
  BlockHandle handle;
  handle.set_offset(300);
  handle.set_size(400);
  footer_.set_index_handle(handle);

  const BlockHandle& result = footer_.index_handle();
  EXPECT_EQ(result.offset(), 300);
  EXPECT_EQ(result.size(), 400);
}

// Test EncodeTo and DecodeFrom round-trip
TEST_F(FooterTest_392, EncodeDecodeRoundTrip_392) {
  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(10);
  metaindex_handle.set_size(20);

  BlockHandle index_handle;
  index_handle.set_offset(30);
  index_handle.set_size(40);

  footer_.set_metaindex_handle(metaindex_handle);
  footer_.set_index_handle(index_handle);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded_footer;
  Slice input(encoded);
  Status s = decoded_footer.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(decoded_footer.metaindex_handle().offset(), 10);
  EXPECT_EQ(decoded_footer.metaindex_handle().size(), 20);
  EXPECT_EQ(decoded_footer.index_handle().offset(), 30);
  EXPECT_EQ(decoded_footer.index_handle().size(), 40);
}

// Test that encoded footer has a fixed size (kEncodedLength = 48)
TEST_F(FooterTest_392, EncodedLength_392) {
  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(0);
  metaindex_handle.set_size(0);

  BlockHandle index_handle;
  index_handle.set_offset(0);
  index_handle.set_size(0);

  footer_.set_metaindex_handle(metaindex_handle);
  footer_.set_index_handle(index_handle);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  // Footer encoded length is always 48 bytes (2 * BlockHandle::kMaxEncodedLength + 8 for magic)
  EXPECT_EQ(encoded.size(), static_cast<size_t>(48));
}

// Test DecodeFrom with corrupted data (too short input)
TEST_F(FooterTest_392, DecodeFromTooShortInput_392) {
  Footer decoded_footer;
  std::string short_data(10, '\0');
  Slice input(short_data);
  Status s = decoded_footer.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with corrupted magic number
TEST_F(FooterTest_392, DecodeFromCorruptedMagic_392) {
  // Create a valid footer first
  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(0);
  metaindex_handle.set_size(0);
  BlockHandle index_handle;
  index_handle.set_offset(0);
  index_handle.set_size(0);

  footer_.set_metaindex_handle(metaindex_handle);
  footer_.set_index_handle(index_handle);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  // Corrupt the magic number (last 8 bytes)
  ASSERT_GE(encoded.size(), static_cast<size_t>(8));
  for (size_t i = encoded.size() - 8; i < encoded.size(); i++) {
    encoded[i] = 0xFF;
  }

  Footer decoded_footer;
  Slice input(encoded);
  Status s = decoded_footer.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test round-trip with large offsets and sizes
TEST_F(FooterTest_392, EncodeDecodeLargeValues_392) {
  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(1000000000ULL);
  metaindex_handle.set_size(500000000ULL);

  BlockHandle index_handle;
  index_handle.set_offset(2000000000ULL);
  index_handle.set_size(999999999ULL);

  footer_.set_metaindex_handle(metaindex_handle);
  footer_.set_index_handle(index_handle);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded_footer;
  Slice input(encoded);
  Status s = decoded_footer.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(decoded_footer.metaindex_handle().offset(), 1000000000ULL);
  EXPECT_EQ(decoded_footer.metaindex_handle().size(), 500000000ULL);
  EXPECT_EQ(decoded_footer.index_handle().offset(), 2000000000ULL);
  EXPECT_EQ(decoded_footer.index_handle().size(), 999999999ULL);
}

// Test that setting handles multiple times works correctly (last write wins)
TEST_F(FooterTest_392, OverwriteHandles_392) {
  BlockHandle handle1;
  handle1.set_offset(1);
  handle1.set_size(2);
  footer_.set_metaindex_handle(handle1);

  BlockHandle handle2;
  handle2.set_offset(3);
  handle2.set_size(4);
  footer_.set_metaindex_handle(handle2);

  EXPECT_EQ(footer_.metaindex_handle().offset(), 3);
  EXPECT_EQ(footer_.metaindex_handle().size(), 4);
}

// Test setting metaindex and index handles independently
TEST_F(FooterTest_392, IndependentHandles_392) {
  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(111);
  metaindex_handle.set_size(222);
  footer_.set_metaindex_handle(metaindex_handle);

  BlockHandle index_handle;
  index_handle.set_offset(333);
  index_handle.set_size(444);
  footer_.set_index_handle(index_handle);

  // Verify they are independent
  EXPECT_EQ(footer_.metaindex_handle().offset(), 111);
  EXPECT_EQ(footer_.metaindex_handle().size(), 222);
  EXPECT_EQ(footer_.index_handle().offset(), 333);
  EXPECT_EQ(footer_.index_handle().size(), 444);
}

// Test DecodeFrom with exactly 48 bytes of zeros (invalid magic)
TEST_F(FooterTest_392, DecodeFromZeroedData_392) {
  std::string zeroed(48, '\0');
  Footer decoded_footer;
  Slice input(zeroed);
  Status s = decoded_footer.DecodeFrom(&input);
  // Magic number won't match, so this should fail
  EXPECT_FALSE(s.ok());
}

// Test multiple encode operations append to string
TEST_F(FooterTest_392, EncodeToAppendsToString_392) {
  BlockHandle handle;
  handle.set_offset(0);
  handle.set_size(0);
  footer_.set_metaindex_handle(handle);
  footer_.set_index_handle(handle);

  std::string prefix = "prefix";
  std::string encoded = prefix;
  footer_.EncodeTo(&encoded);

  // The encoded data should be appended after the prefix
  EXPECT_GE(encoded.size(), prefix.size() + 48);
  EXPECT_EQ(encoded.substr(0, prefix.size()), prefix);
}

}  // namespace leveldb
