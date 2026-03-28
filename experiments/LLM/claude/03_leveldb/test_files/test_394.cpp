#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class FooterTest_394 : public ::testing::Test {
 protected:
  Footer footer_;
};

// Test that a default-constructed Footer has default index_handle
TEST_F(FooterTest_394, DefaultIndexHandle_394) {
  BlockHandle handle = footer_.index_handle();
  // Default BlockHandle should have offset and size of 0 (or some default)
  // We just verify it's accessible without crashing
  (void)handle.offset();
  (void)handle.size();
}

// Test that a default-constructed Footer has default metaindex_handle
TEST_F(FooterTest_394, DefaultMetaindexHandle_394) {
  BlockHandle handle = footer_.metaindex_handle();
  (void)handle.offset();
  (void)handle.size();
}

// Test set_index_handle and index_handle round-trip
TEST_F(FooterTest_394, SetAndGetIndexHandle_394) {
  BlockHandle h;
  h.set_offset(100);
  h.set_size(200);
  footer_.set_index_handle(h);

  const BlockHandle& result = footer_.index_handle();
  EXPECT_EQ(100, result.offset());
  EXPECT_EQ(200, result.size());
}

// Test set_metaindex_handle and metaindex_handle round-trip
TEST_F(FooterTest_394, SetAndGetMetaindexHandle_394) {
  BlockHandle h;
  h.set_offset(300);
  h.set_size(400);
  footer_.set_metaindex_handle(h);

  const BlockHandle& result = footer_.metaindex_handle();
  EXPECT_EQ(300, result.offset());
  EXPECT_EQ(400, result.size());
}

// Test EncodeTo and DecodeFrom round-trip
TEST_F(FooterTest_394, EncodeDecodeRoundTrip_394) {
  BlockHandle index_h;
  index_h.set_offset(50);
  index_h.set_size(150);
  footer_.set_index_handle(index_h);

  BlockHandle meta_h;
  meta_h.set_offset(250);
  meta_h.set_size(350);
  footer_.set_metaindex_handle(meta_h);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded_footer;
  Slice input(encoded);
  Status s = decoded_footer.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(50, decoded_footer.index_handle().offset());
  EXPECT_EQ(150, decoded_footer.index_handle().size());
  EXPECT_EQ(250, decoded_footer.metaindex_handle().offset());
  EXPECT_EQ(350, decoded_footer.metaindex_handle().size());
}

// Test EncodeTo produces consistent output
TEST_F(FooterTest_394, EncodeToConsistency_394) {
  BlockHandle index_h;
  index_h.set_offset(10);
  index_h.set_size(20);
  footer_.set_index_handle(index_h);

  BlockHandle meta_h;
  meta_h.set_offset(30);
  meta_h.set_size(40);
  footer_.set_metaindex_handle(meta_h);

  std::string encoded1;
  footer_.EncodeTo(&encoded1);

  std::string encoded2;
  footer_.EncodeTo(&encoded2);

  EXPECT_EQ(encoded1, encoded2);
}

// Test DecodeFrom with corrupted/truncated data
TEST_F(FooterTest_394, DecodeFromCorruptedData_394) {
  std::string bad_data("short");
  Slice input(bad_data);
  Footer decoded_footer;
  Status s = decoded_footer.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(FooterTest_394, DecodeFromEmptyData_394) {
  std::string empty;
  Slice input(empty);
  Footer decoded_footer;
  Status s = decoded_footer.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

// Test with large offset and size values
TEST_F(FooterTest_394, LargeValues_394) {
  BlockHandle index_h;
  index_h.set_offset(static_cast<uint64_t>(1) << 40);
  index_h.set_size(static_cast<uint64_t>(1) << 35);
  footer_.set_index_handle(index_h);

  BlockHandle meta_h;
  meta_h.set_offset(static_cast<uint64_t>(1) << 42);
  meta_h.set_size(static_cast<uint64_t>(1) << 30);
  footer_.set_metaindex_handle(meta_h);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded_footer;
  Slice input(encoded);
  Status s = decoded_footer.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(static_cast<uint64_t>(1) << 40, decoded_footer.index_handle().offset());
  EXPECT_EQ(static_cast<uint64_t>(1) << 35, decoded_footer.index_handle().size());
  EXPECT_EQ(static_cast<uint64_t>(1) << 42, decoded_footer.metaindex_handle().offset());
  EXPECT_EQ(static_cast<uint64_t>(1) << 30, decoded_footer.metaindex_handle().size());
}

// Test with zero offset and size
TEST_F(FooterTest_394, ZeroValues_394) {
  BlockHandle index_h;
  index_h.set_offset(0);
  index_h.set_size(0);
  footer_.set_index_handle(index_h);

  BlockHandle meta_h;
  meta_h.set_offset(0);
  meta_h.set_size(0);
  footer_.set_metaindex_handle(meta_h);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded_footer;
  Slice input(encoded);
  Status s = decoded_footer.DecodeFrom(&input);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(0, decoded_footer.index_handle().offset());
  EXPECT_EQ(0, decoded_footer.index_handle().size());
  EXPECT_EQ(0, decoded_footer.metaindex_handle().offset());
  EXPECT_EQ(0, decoded_footer.metaindex_handle().size());
}

// Test that setting index_handle does not affect metaindex_handle
TEST_F(FooterTest_394, IndependentHandles_394) {
  BlockHandle index_h;
  index_h.set_offset(111);
  index_h.set_size(222);
  footer_.set_index_handle(index_h);

  BlockHandle meta_h;
  meta_h.set_offset(333);
  meta_h.set_size(444);
  footer_.set_metaindex_handle(meta_h);

  // Verify they are independent
  EXPECT_EQ(111, footer_.index_handle().offset());
  EXPECT_EQ(222, footer_.index_handle().size());
  EXPECT_EQ(333, footer_.metaindex_handle().offset());
  EXPECT_EQ(444, footer_.metaindex_handle().size());

  // Update only index
  BlockHandle new_index_h;
  new_index_h.set_offset(555);
  new_index_h.set_size(666);
  footer_.set_index_handle(new_index_h);

  EXPECT_EQ(555, footer_.index_handle().offset());
  EXPECT_EQ(666, footer_.index_handle().size());
  // metaindex should remain unchanged
  EXPECT_EQ(333, footer_.metaindex_handle().offset());
  EXPECT_EQ(444, footer_.metaindex_handle().size());
}

// Test that the encoded footer has a fixed size (kEncodedLength which is 48 bytes for leveldb)
TEST_F(FooterTest_394, EncodedSize_394) {
  BlockHandle index_h;
  index_h.set_offset(1);
  index_h.set_size(2);
  footer_.set_index_handle(index_h);

  BlockHandle meta_h;
  meta_h.set_offset(3);
  meta_h.set_size(4);
  footer_.set_metaindex_handle(meta_h);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  // Footer encoded length is fixed at 48 bytes in leveldb
  // (2 * BlockHandle::kMaxEncodedLength + 8 bytes magic number)
  // BlockHandle::kMaxEncodedLength = 10 + 10 = 20, so 20 + 20 + 8 = 48
  EXPECT_EQ(48u, encoded.size());
}

}  // namespace leveldb
