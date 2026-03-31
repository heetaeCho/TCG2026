#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// ==================== BlockHandle Tests ====================

class BlockHandleTest_393 : public ::testing::Test {
 protected:
  BlockHandle handle_;
};

TEST_F(BlockHandleTest_393, DefaultConstructor_393) {
  // Default constructed BlockHandle should have max uint64 values
  // indicating they are unset
  EXPECT_EQ(handle_.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(handle_.size(), ~static_cast<uint64_t>(0));
}

TEST_F(BlockHandleTest_393, SetAndGetOffset_393) {
  handle_.set_offset(100);
  EXPECT_EQ(handle_.offset(), 100);
}

TEST_F(BlockHandleTest_393, SetAndGetSize_393) {
  handle_.set_size(200);
  EXPECT_EQ(handle_.size(), 200);
}

TEST_F(BlockHandleTest_393, SetOffsetZero_393) {
  handle_.set_offset(0);
  EXPECT_EQ(handle_.offset(), 0);
}

TEST_F(BlockHandleTest_393, SetSizeZero_393) {
  handle_.set_size(0);
  EXPECT_EQ(handle_.size(), 0);
}

TEST_F(BlockHandleTest_393, SetOffsetMaxValue_393) {
  handle_.set_offset(UINT64_MAX);
  EXPECT_EQ(handle_.offset(), UINT64_MAX);
}

TEST_F(BlockHandleTest_393, SetSizeMaxValue_393) {
  handle_.set_size(UINT64_MAX);
  EXPECT_EQ(handle_.size(), UINT64_MAX);
}

TEST_F(BlockHandleTest_393, SetOffsetLargeValue_393) {
  uint64_t large_val = static_cast<uint64_t>(1) << 50;
  handle_.set_offset(large_val);
  EXPECT_EQ(handle_.offset(), large_val);
}

TEST_F(BlockHandleTest_393, SetSizeLargeValue_393) {
  uint64_t large_val = static_cast<uint64_t>(1) << 50;
  handle_.set_size(large_val);
  EXPECT_EQ(handle_.size(), large_val);
}

TEST_F(BlockHandleTest_393, EncodeAndDecode_393) {
  handle_.set_offset(42);
  handle_.set_size(84);

  std::string encoded;
  handle_.EncodeTo(&encoded);
  EXPECT_FALSE(encoded.empty());

  BlockHandle decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.offset(), 42);
  EXPECT_EQ(decoded.size(), 84);
}

TEST_F(BlockHandleTest_393, EncodeAndDecodeZeroValues_393) {
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

TEST_F(BlockHandleTest_393, DecodeFromEmptyInput_393) {
  BlockHandle decoded;
  Slice input("");
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST_F(BlockHandleTest_393, DecodeFromTruncatedInput_393) {
  handle_.set_offset(100);
  handle_.set_size(200);

  std::string encoded;
  handle_.EncodeTo(&encoded);

  // Truncate the encoded data
  std::string truncated = encoded.substr(0, 1);
  BlockHandle decoded;
  Slice input(truncated);
  Status s = decoded.DecodeFrom(&input);
  // With only 1 byte, it might succeed for small varint or fail
  // We just check it doesn't crash. If offset was small enough for 1 byte varint,
  // the size part would still be missing.
  // Actually 100 fits in 1 byte varint, so offset decode succeeds but size fails
  EXPECT_FALSE(s.ok());
}

TEST_F(BlockHandleTest_393, MultipleSetCalls_393) {
  handle_.set_offset(10);
  handle_.set_size(20);
  EXPECT_EQ(handle_.offset(), 10);
  EXPECT_EQ(handle_.size(), 20);

  handle_.set_offset(30);
  handle_.set_size(40);
  EXPECT_EQ(handle_.offset(), 30);
  EXPECT_EQ(handle_.size(), 40);
}

// ==================== Footer Tests ====================

class FooterTest_393 : public ::testing::Test {
 protected:
  Footer footer_;
};

TEST_F(FooterTest_393, DefaultConstructor_393) {
  // Default footer should have default BlockHandles
  const BlockHandle& meta = footer_.metaindex_handle();
  const BlockHandle& index = footer_.index_handle();
  EXPECT_EQ(meta.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(meta.size(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(index.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(index.size(), ~static_cast<uint64_t>(0));
}

TEST_F(FooterTest_393, SetAndGetMetaindexHandle_393) {
  BlockHandle h;
  h.set_offset(10);
  h.set_size(20);
  footer_.set_metaindex_handle(h);

  const BlockHandle& result = footer_.metaindex_handle();
  EXPECT_EQ(result.offset(), 10);
  EXPECT_EQ(result.size(), 20);
}

TEST_F(FooterTest_393, SetAndGetIndexHandle_393) {
  BlockHandle h;
  h.set_offset(30);
  h.set_size(40);
  footer_.set_index_handle(h);

  const BlockHandle& result = footer_.index_handle();
  EXPECT_EQ(result.offset(), 30);
  EXPECT_EQ(result.size(), 40);
}

TEST_F(FooterTest_393, SetMetaindexDoesNotAffectIndex_393) {
  BlockHandle meta;
  meta.set_offset(10);
  meta.set_size(20);
  footer_.set_metaindex_handle(meta);

  const BlockHandle& index = footer_.index_handle();
  // index_handle should still be default
  EXPECT_EQ(index.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(index.size(), ~static_cast<uint64_t>(0));
}

TEST_F(FooterTest_393, SetIndexDoesNotAffectMetaindex_393) {
  BlockHandle index;
  index.set_offset(30);
  index.set_size(40);
  footer_.set_index_handle(index);

  const BlockHandle& meta = footer_.metaindex_handle();
  EXPECT_EQ(meta.offset(), ~static_cast<uint64_t>(0));
  EXPECT_EQ(meta.size(), ~static_cast<uint64_t>(0));
}

TEST_F(FooterTest_393, EncodeAndDecode_393) {
  BlockHandle meta;
  meta.set_offset(100);
  meta.set_size(200);
  footer_.set_metaindex_handle(meta);

  BlockHandle index;
  index.set_offset(300);
  index.set_size(400);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);
  EXPECT_FALSE(encoded.empty());

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.metaindex_handle().offset(), 100);
  EXPECT_EQ(decoded.metaindex_handle().size(), 200);
  EXPECT_EQ(decoded.index_handle().offset(), 300);
  EXPECT_EQ(decoded.index_handle().size(), 400);
}

TEST_F(FooterTest_393, EncodeAndDecodeZeroValues_393) {
  BlockHandle meta;
  meta.set_offset(0);
  meta.set_size(0);
  footer_.set_metaindex_handle(meta);

  BlockHandle index;
  index.set_offset(0);
  index.set_size(0);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.metaindex_handle().offset(), 0);
  EXPECT_EQ(decoded.metaindex_handle().size(), 0);
  EXPECT_EQ(decoded.index_handle().offset(), 0);
  EXPECT_EQ(decoded.index_handle().size(), 0);
}

TEST_F(FooterTest_393, DecodeFromCorruptedData_393) {
  Footer decoded;
  std::string bad_data(48, '\xff');  // Footer is typically 48 bytes
  Slice input(bad_data);
  Status s = decoded.DecodeFrom(&input);
  // Corrupted magic number should cause failure
  EXPECT_FALSE(s.ok());
}

TEST_F(FooterTest_393, DecodeFromEmptyInput_393) {
  Footer decoded;
  Slice input("");
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST_F(FooterTest_393, DecodeFromTooShortInput_393) {
  Footer decoded;
  std::string short_data(10, '\0');
  Slice input(short_data);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_FALSE(s.ok());
}

TEST_F(FooterTest_393, EncodedFooterHasFixedSize_393) {
  // Footer encoding should always be exactly 48 bytes (kEncodedLength)
  BlockHandle meta;
  meta.set_offset(0);
  meta.set_size(0);
  footer_.set_metaindex_handle(meta);

  BlockHandle index;
  index.set_offset(0);
  index.set_size(0);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);
  // Footer size: 2 * BlockHandle::kMaxEncodedLength (20 bytes each) + 8 bytes magic = 48
  EXPECT_EQ(encoded.size(), 48u);
}

TEST_F(FooterTest_393, SetMetaindexHandleOverwrite_393) {
  BlockHandle h1;
  h1.set_offset(10);
  h1.set_size(20);
  footer_.set_metaindex_handle(h1);

  BlockHandle h2;
  h2.set_offset(50);
  h2.set_size(60);
  footer_.set_metaindex_handle(h2);

  EXPECT_EQ(footer_.metaindex_handle().offset(), 50);
  EXPECT_EQ(footer_.metaindex_handle().size(), 60);
}

TEST_F(FooterTest_393, SetIndexHandleOverwrite_393) {
  BlockHandle h1;
  h1.set_offset(10);
  h1.set_size(20);
  footer_.set_index_handle(h1);

  BlockHandle h2;
  h2.set_offset(50);
  h2.set_size(60);
  footer_.set_index_handle(h2);

  EXPECT_EQ(footer_.index_handle().offset(), 50);
  EXPECT_EQ(footer_.index_handle().size(), 60);
}

TEST_F(FooterTest_393, EncodeDecodeWithLargeValues_393) {
  BlockHandle meta;
  meta.set_offset(static_cast<uint64_t>(1) << 40);
  meta.set_size(static_cast<uint64_t>(1) << 35);
  footer_.set_metaindex_handle(meta);

  BlockHandle index;
  index.set_offset(static_cast<uint64_t>(1) << 45);
  index.set_size(static_cast<uint64_t>(1) << 30);
  footer_.set_index_handle(index);

  std::string encoded;
  footer_.EncodeTo(&encoded);

  Footer decoded;
  Slice input(encoded);
  Status s = decoded.DecodeFrom(&input);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(decoded.metaindex_handle().offset(), static_cast<uint64_t>(1) << 40);
  EXPECT_EQ(decoded.metaindex_handle().size(), static_cast<uint64_t>(1) << 35);
  EXPECT_EQ(decoded.index_handle().offset(), static_cast<uint64_t>(1) << 45);
  EXPECT_EQ(decoded.index_handle().size(), static_cast<uint64_t>(1) << 30);
}

TEST_F(FooterTest_393, EncodeDecodeRoundTrip_393) {
  // Multiple round trips should produce consistent results
  BlockHandle meta;
  meta.set_offset(12345);
  meta.set_size(67890);
  footer_.set_metaindex_handle(meta);

  BlockHandle index;
  index.set_offset(11111);
  index.set_size(22222);
  footer_.set_index_handle(index);

  std::string encoded1;
  footer_.EncodeTo(&encoded1);

  Footer decoded1;
  Slice input1(encoded1);
  EXPECT_TRUE(decoded1.DecodeFrom(&input1).ok());

  std::string encoded2;
  decoded1.EncodeTo(&encoded2);

  EXPECT_EQ(encoded1, encoded2);
}

}  // namespace leveldb
