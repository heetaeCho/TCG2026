#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include <string>

namespace leveldb {

// ==================== BlockHandle Tests ====================

TEST(BlockHandleTest_395, DefaultConstructor_395) {
  BlockHandle handle;
  // Default constructed handle should have maximum uint64_t values
  EXPECT_EQ(handle.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(handle.size(), ~static_cast<uint64_t>(0));
}

TEST(BlockHandleTest_395, SetAndGetOffset_395) {
  BlockHandle handle;
  handle.set_offset(100);
  EXPECT_EQ(handle.offset(), 100);
}

TEST(BlockHandleTest_395, SetAndGetSize_395) {
  BlockHandle handle;
  handle.set_size(200);
  EXPECT_EQ(handle.size(), 200);
}

TEST(BlockHandleTest_395, SetOffsetZero_395) {
  BlockHandle handle;
  handle.set_offset(0);
  EXPECT_EQ(handle.offset(), 0);
}

TEST(BlockHandleTest_395, SetSizeZero_395) {
  BlockHandle handle;
  handle.set_size(0);
  EXPECT_EQ(handle.size(), 0);
}

TEST(BlockHandleTest_395, SetLargeOffset_395) {
  BlockHandle handle;
  handle.set_offset(UINT64_MAX - 1);
  EXPECT_EQ(handle.offset(), UINT64_MAX - 1);
}

TEST(BlockHandleTest_395, SetLargeSize_395) {
  BlockHandle handle;
  handle.set_size(UINT64_MAX - 1);
  EXPECT_EQ(handle.size(), UINT64_MAX - 1);
}

TEST(BlockHandleTest_395, EncodeAndDecode_395) {
  BlockHandle original;
  original.set_offset(12345);
  original.set_size(67890);

  std::string encoded;
  original.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 12345);
  EXPECT_EQ(decoded.size(), 67890);
}

TEST(BlockHandleTest_395, EncodeAndDecodeZeroValues_395) {
  BlockHandle original;
  original.set_offset(0);
  original.set_size(0);

  std::string encoded;
  original.EncodeTo(&encoded);

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 0);
  EXPECT_EQ(decoded.size(), 0);
}

TEST(BlockHandleTest_395, DecodeFromEmptySlice_395) {
  BlockHandle handle;
  Slice input("");
  Status s = handle.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST(BlockHandleTest_395, DecodeFromTruncatedData_395) {
  BlockHandle original;
  original.set_offset(100);
  original.set_size(200);

  std::string encoded;
  original.EncodeTo(&encoded);

  // Truncate the encoded data
  std::string truncated = encoded.substr(0, 1);
  Slice input(truncated);

  BlockHandle decoded;
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST(BlockHandleTest_395, MultipleSetCalls_395) {
  BlockHandle handle;
  handle.set_offset(10);
  handle.set_size(20);
  EXPECT_EQ(handle.offset(), 10);
  EXPECT_EQ(handle.size(), 20);

  handle.set_offset(30);
  handle.set_size(40);
  EXPECT_EQ(handle.offset(), 30);
  EXPECT_EQ(handle.size(), 40);
}

// ==================== Footer Tests ====================

TEST(FooterTest_395, DefaultConstructor_395) {
  Footer footer;
  // Default footer should have default BlockHandle values
  EXPECT_EQ(footer.metaindex_handle().offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(footer.metaindex_handle().size(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(footer.index_handle().offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(footer.index_handle().size(), ~static_cast<uint64_t>(0));
}

TEST(FooterTest_395, SetAndGetIndexHandle_395) {
  Footer footer;
  BlockHandle index_handle;
  index_handle.set_offset(100);
  index_handle.set_size(200);
  footer.set_index_handle(index_handle);

  EXPECT_EQ(footer.index_handle().offset(), 100);
  EXPECT_EQ(footer.index_handle().size(), 200);
}

TEST(FooterTest_395, SetAndGetMetaindexHandle_395) {
  Footer footer;
  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(300);
  metaindex_handle.set_size(400);
  footer.set_metaindex_handle(metaindex_handle);

  EXPECT_EQ(footer.metaindex_handle().offset(), 300);
  EXPECT_EQ(footer.metaindex_handle().size(), 400);
}

TEST(FooterTest_395, SetBothHandles_395) {
  Footer footer;

  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(10);
  metaindex_handle.set_size(20);
  footer.set_metaindex_handle(metaindex_handle);

  BlockHandle index_handle;
  index_handle.set_offset(30);
  index_handle.set_size(40);
  footer.set_index_handle(index_handle);

  EXPECT_EQ(footer.metaindex_handle().offset(), 10);
  EXPECT_EQ(footer.metaindex_handle().size(), 20);
  EXPECT_EQ(footer.index_handle().offset(), 30);
  EXPECT_EQ(footer.index_handle().size(), 40);
}

TEST(FooterTest_395, EncodeAndDecode_395) {
  Footer original;

  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(100);
  metaindex_handle.set_size(200);
  original.set_metaindex_handle(metaindex_handle);

  BlockHandle index_handle;
  index_handle.set_offset(300);
  index_handle.set_size(400);
  original.set_index_handle(index_handle);

  std::string encoded;
  original.EncodeTo(&encoded);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.metaindex_handle().offset(), 100);
  EXPECT_EQ(decoded.metaindex_handle().size(), 200);
  EXPECT_EQ(decoded.index_handle().offset(), 300);
  EXPECT_EQ(decoded.index_handle().size(), 400);
}

TEST(FooterTest_395, EncodeAndDecodeZeroHandles_395) {
  Footer original;

  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(0);
  metaindex_handle.set_size(0);
  original.set_metaindex_handle(metaindex_handle);

  BlockHandle index_handle;
  index_handle.set_offset(0);
  index_handle.set_size(0);
  original.set_index_handle(index_handle);

  std::string encoded;
  original.EncodeTo(&encoded);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.metaindex_handle().offset(), 0);
  EXPECT_EQ(decoded.metaindex_handle().size(), 0);
  EXPECT_EQ(decoded.index_handle().offset(), 0);
  EXPECT_EQ(decoded.index_handle().size(), 0);
}

TEST(FooterTest_395, DecodeFromCorruptedData_395) {
  Footer footer;
  std::string corrupt_data(48, 'x');  // Footer is 48 bytes, but with garbage
  Slice input(corrupt_data);
  Status s = footer.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST(FooterTest_395, DecodeFromTooShortData_395) {
  Footer footer;
  std::string short_data(10, '\0');
  Slice input(short_data);
  Status s = footer.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST(FooterTest_395, DecodeFromEmptySlice_395) {
  Footer footer;
  Slice input("");
  Status s = footer.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST(FooterTest_395, SetIndexHandleDoesNotAffectMetaindexHandle_395) {
  Footer footer;

  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(111);
  metaindex_handle.set_size(222);
  footer.set_metaindex_handle(metaindex_handle);

  BlockHandle index_handle;
  index_handle.set_offset(333);
  index_handle.set_size(444);
  footer.set_index_handle(index_handle);

  // Verify metaindex was not changed
  EXPECT_EQ(footer.metaindex_handle().offset(), 111);
  EXPECT_EQ(footer.metaindex_handle().size(), 222);
}

TEST(FooterTest_395, SetMetaindexHandleDoesNotAffectIndexHandle_395) {
  Footer footer;

  BlockHandle index_handle;
  index_handle.set_offset(555);
  index_handle.set_size(666);
  footer.set_index_handle(index_handle);

  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(777);
  metaindex_handle.set_size(888);
  footer.set_metaindex_handle(metaindex_handle);

  // Verify index was not changed
  EXPECT_EQ(footer.index_handle().offset(), 555);
  EXPECT_EQ(footer.index_handle().size(), 666);
}

TEST(FooterTest_395, OverwriteHandles_395) {
  Footer footer;

  BlockHandle handle1;
  handle1.set_offset(1);
  handle1.set_size(2);
  footer.set_index_handle(handle1);

  EXPECT_EQ(footer.index_handle().offset(), 1);
  EXPECT_EQ(footer.index_handle().size(), 2);

  BlockHandle handle2;
  handle2.set_offset(3);
  handle2.set_size(4);
  footer.set_index_handle(handle2);

  EXPECT_EQ(footer.index_handle().offset(), 3);
  EXPECT_EQ(footer.index_handle().size(), 4);
}

TEST(FooterTest_395, EncodeProducesFixedSizeOutput_395) {
  Footer footer1;
  BlockHandle h1;
  h1.set_offset(0);
  h1.set_size(0);
  footer1.set_metaindex_handle(h1);
  footer1.set_index_handle(h1);

  std::string encoded1;
  footer1.EncodeTo(&encoded1);

  Footer footer2;
  BlockHandle h2;
  h2.set_offset(123456789);
  h2.set_size(987654321);
  footer2.set_metaindex_handle(h2);
  footer2.set_index_handle(h2);

  std::string encoded2;
  footer2.EncodeTo(&encoded2);

  // Footer encoding should always produce the same size (48 bytes)
  EXPECT_EQ(encoded1.size(), encoded2.size());
  EXPECT_EQ(encoded1.size(), 48u);
}

TEST(FooterTest_395, RoundTripWithLargeValues_395) {
  Footer original;

  BlockHandle metaindex_handle;
  metaindex_handle.set_offset(1ULL << 40);
  metaindex_handle.set_size(1ULL << 35);
  original.set_metaindex_handle(metaindex_handle);

  BlockHandle index_handle;
  index_handle.set_offset(1ULL << 50);
  index_handle.set_size(1ULL << 45);
  original.set_index_handle(index_handle);

  std::string encoded;
  original.EncodeTo(&encoded);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.metaindex_handle().offset(), 1ULL << 40);
  EXPECT_EQ(decoded.metaindex_handle().size(), 1ULL << 35);
  EXPECT_EQ(decoded.index_handle().offset(), 1ULL << 50);
  EXPECT_EQ(decoded.index_handle().size(), 1ULL << 45);
}

}  // namespace leveldb
