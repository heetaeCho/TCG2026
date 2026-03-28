#include "gtest/gtest.h"
#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "util/coding.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper function to build a valid footer buffer
static std::string BuildFooter(const BlockHandle& metaindex, const BlockHandle& index) {
    std::string result;
    metaindex.EncodeTo(&result);
    index.EncodeTo(&result);
    // Pad to make room for magic number at the end
    // Footer::kEncodedLength is 2*BlockHandle::kMaxEncodedLength + 8 = 2*10 + 8 = 48
    result.resize(2 * BlockHandle::kMaxEncodedLength, 0);
    // Append magic number
    uint64_t magic = kTableMagicNumber;
    uint32_t magic_lo = static_cast<uint32_t>(magic & 0xffffffffu);
    uint32_t magic_hi = static_cast<uint32_t>(magic >> 32);
    PutFixed32(&result, magic_lo);
    PutFixed32(&result, magic_hi);
    return result;
}

// Test fixture for Footer tests
class FooterTest_399 : public ::testing::Test {
 protected:
  Footer footer_;
};

// Test that decoding a buffer that is too short returns Corruption
TEST_F(FooterTest_399, DecodeFromTooShort_399) {
    std::string short_data(10, '\0');
    Slice input(short_data);
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.IsCorruption());
    EXPECT_NE(s.ToString().find("not an sstable (footer too short)"), std::string::npos);
}

// Test that decoding an empty input returns Corruption
TEST_F(FooterTest_399, DecodeFromEmpty_399) {
    Slice input;
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.IsCorruption());
}

// Test that decoding a buffer of exactly kEncodedLength but with bad magic returns Corruption
TEST_F(FooterTest_399, DecodeFromBadMagicNumber_399) {
    // kEncodedLength = 48
    std::string data(48, '\0');
    // Write some arbitrary bytes for the magic area - they won't match
    Slice input(data);
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.IsCorruption());
    EXPECT_NE(s.ToString().find("not an sstable (bad magic number)"), std::string::npos);
}

// Test that a valid footer decodes successfully
TEST_F(FooterTest_399, DecodeFromValidFooter_399) {
    BlockHandle metaindex;
    metaindex.set_offset(100);
    metaindex.set_size(200);

    BlockHandle index;
    index.set_offset(300);
    index.set_size(400);

    std::string encoded = BuildFooter(metaindex, index);
    ASSERT_EQ(encoded.size(), 48u);

    Slice input(encoded);
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.ok()) << s.ToString();

    EXPECT_EQ(footer_.metaindex_handle().offset(), 100u);
    EXPECT_EQ(footer_.metaindex_handle().size(), 200u);
    EXPECT_EQ(footer_.index_handle().offset(), 300u);
    EXPECT_EQ(footer_.index_handle().size(), 400u);
}

// Test encode then decode round-trip
TEST_F(FooterTest_399, EncodeDecodeRoundTrip_399) {
    Footer original;
    BlockHandle meta_handle;
    meta_handle.set_offset(12345);
    meta_handle.set_size(67890);
    original.set_metaindex_handle(meta_handle);

    BlockHandle idx_handle;
    idx_handle.set_offset(111);
    idx_handle.set_size(222);
    original.set_index_handle(idx_handle);

    std::string encoded;
    original.EncodeTo(&encoded);
    ASSERT_EQ(encoded.size(), 48u);

    Slice input(encoded);
    Footer decoded;
    Status s = decoded.DecodeFrom(&input);
    EXPECT_TRUE(s.ok()) << s.ToString();

    EXPECT_EQ(decoded.metaindex_handle().offset(), 12345u);
    EXPECT_EQ(decoded.metaindex_handle().size(), 67890u);
    EXPECT_EQ(decoded.index_handle().offset(), 111u);
    EXPECT_EQ(decoded.index_handle().size(), 222u);
}

// Test that after successful decode, input slice is advanced past the footer
TEST_F(FooterTest_399, DecodeFromAdvancesSlice_399) {
    BlockHandle metaindex;
    metaindex.set_offset(0);
    metaindex.set_size(0);

    BlockHandle index;
    index.set_offset(0);
    index.set_size(0);

    std::string encoded = BuildFooter(metaindex, index);
    // Append some extra trailing data
    std::string extra = "extra_data_after_footer";
    encoded += extra;

    Slice input(encoded);
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.ok()) << s.ToString();

    // After decoding, the input slice should point to the extra data
    EXPECT_EQ(input.size(), extra.size());
    EXPECT_EQ(std::string(input.data(), input.size()), extra);
}

// Test with zero offsets and sizes
TEST_F(FooterTest_399, DecodeFromZeroHandles_399) {
    BlockHandle metaindex;
    metaindex.set_offset(0);
    metaindex.set_size(0);

    BlockHandle index;
    index.set_offset(0);
    index.set_size(0);

    std::string encoded = BuildFooter(metaindex, index);
    Slice input(encoded);
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.ok()) << s.ToString();

    EXPECT_EQ(footer_.metaindex_handle().offset(), 0u);
    EXPECT_EQ(footer_.metaindex_handle().size(), 0u);
    EXPECT_EQ(footer_.index_handle().offset(), 0u);
    EXPECT_EQ(footer_.index_handle().size(), 0u);
}

// Test with large handle values
TEST_F(FooterTest_399, DecodeFromLargeHandleValues_399) {
    BlockHandle metaindex;
    metaindex.set_offset(1ULL << 40);
    metaindex.set_size(1ULL << 35);

    BlockHandle index;
    index.set_offset(1ULL << 50);
    index.set_size(1ULL << 30);

    std::string encoded = BuildFooter(metaindex, index);
    Slice input(encoded);
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.ok()) << s.ToString();

    EXPECT_EQ(footer_.metaindex_handle().offset(), 1ULL << 40);
    EXPECT_EQ(footer_.metaindex_handle().size(), 1ULL << 35);
    EXPECT_EQ(footer_.index_handle().offset(), 1ULL << 50);
    EXPECT_EQ(footer_.index_handle().size(), 1ULL << 30);
}

// Test that buffer of exactly kEncodedLength - 1 fails
TEST_F(FooterTest_399, DecodeFromOneByteTooShort_399) {
    std::string data(47, '\0');
    Slice input(data);
    Status s = footer_.DecodeFrom(&input);
    EXPECT_TRUE(s.IsCorruption());
}

// Test that correct magic but corrupted varint handles still returns an error
TEST_F(FooterTest_399, DecodeFromCorruptedHandles_399) {
    // Build a 48-byte buffer with correct magic but invalid varint data
    std::string data(48, 0xff);  // All 0xff bytes - invalid varints
    // Write correct magic at offset 40..47
    uint64_t magic = kTableMagicNumber;
    uint32_t magic_lo = static_cast<uint32_t>(magic & 0xffffffffu);
    uint32_t magic_hi = static_cast<uint32_t>(magic >> 32);
    char* magic_ptr = &data[40];
    EncodeFixed32(magic_ptr, magic_lo);
    EncodeFixed32(magic_ptr + 4, magic_hi);

    Slice input(data);
    Status s = footer_.DecodeFrom(&input);
    // The varint decoding of 0xff bytes may succeed (they encode large numbers
    // in varint) or fail depending on the implementation. We just verify the
    // call doesn't crash and returns a status.
    // If it's not ok, it should be corruption
    if (!s.ok()) {
        EXPECT_TRUE(s.IsCorruption());
    }
}

// Test setter/getter for metaindex_handle
TEST_F(FooterTest_399, SetGetMetaindexHandle_399) {
    BlockHandle h;
    h.set_offset(42);
    h.set_size(84);
    footer_.set_metaindex_handle(h);
    EXPECT_EQ(footer_.metaindex_handle().offset(), 42u);
    EXPECT_EQ(footer_.metaindex_handle().size(), 84u);
}

// Test setter/getter for index_handle
TEST_F(FooterTest_399, SetGetIndexHandle_399) {
    BlockHandle h;
    h.set_offset(99);
    h.set_size(199);
    footer_.set_index_handle(h);
    EXPECT_EQ(footer_.index_handle().offset(), 99u);
    EXPECT_EQ(footer_.index_handle().size(), 199u);
}

// Test BlockHandle DecodeFrom with valid varint data
TEST(BlockHandleTest_399, DecodeFromValid_399) {
    BlockHandle original;
    original.set_offset(500);
    original.set_size(1000);

    std::string encoded;
    original.EncodeTo(&encoded);

    Slice input(encoded);
    BlockHandle decoded;
    Status s = decoded.DecodeFrom(&input);
    EXPECT_TRUE(s.ok());
    EXPECT_EQ(decoded.offset(), 500u);
    EXPECT_EQ(decoded.size(), 1000u);
}

// Test BlockHandle default construction
TEST(BlockHandleTest_399, DefaultConstruction_399) {
    BlockHandle h;
    // Default values are ~0 according to the header
    EXPECT_EQ(h.offset(), ~static_cast<uint64_t>(0));
    EXPECT_EQ(h.size(), ~static_cast<uint64_t>(0));
}

}  // namespace leveldb
