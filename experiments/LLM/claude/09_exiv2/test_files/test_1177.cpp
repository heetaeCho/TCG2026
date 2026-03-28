#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>

// Include the necessary headers from exiv2
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffHeaderBase is abstract-like but not pure virtual, we can instantiate it directly
// or create a minimal derived class if needed. Based on the interface, TiffHeaderBase
// has a public constructor, so we can instantiate it directly.

class TiffHeaderBaseTest_1177 : public ::testing::Test {
protected:
    // Common tag values for TIFF
    static constexpr uint16_t kTiffTag = 0x002a;  // Standard TIFF tag
    static constexpr uint32_t kDefaultSize = 8;
    static constexpr uint32_t kDefaultOffset = 8;
};

// Test that tag() returns the tag passed to the constructor
TEST_F(TiffHeaderBaseTest_1177, TagReturnsConstructorValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(kTiffTag, header.tag());
}

// Test tag with zero value
TEST_F(TiffHeaderBaseTest_1177, TagReturnsZero_1177) {
    TiffHeaderBase header(0x0000, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(0x0000, header.tag());
}

// Test tag with max uint16_t value
TEST_F(TiffHeaderBaseTest_1177, TagReturnsMaxUint16_1177) {
    TiffHeaderBase header(0xFFFF, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(0xFFFF, header.tag());
}

// Test that byteOrder() returns the byte order passed to the constructor
TEST_F(TiffHeaderBaseTest_1177, ByteOrderReturnsConstructorValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(littleEndian, header.byteOrder());
}

// Test big endian byte order
TEST_F(TiffHeaderBaseTest_1177, ByteOrderReturnsBigEndian_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, bigEndian, kDefaultOffset);
    EXPECT_EQ(bigEndian, header.byteOrder());
}

// Test that setByteOrder changes the byte order
TEST_F(TiffHeaderBaseTest_1177, SetByteOrderChangesValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(littleEndian, header.byteOrder());
    header.setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, header.byteOrder());
}

// Test that offset() returns the offset passed to the constructor
TEST_F(TiffHeaderBaseTest_1177, OffsetReturnsConstructorValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(kDefaultOffset, header.offset());
}

// Test offset with zero value
TEST_F(TiffHeaderBaseTest_1177, OffsetReturnsZero_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, 0);
    EXPECT_EQ(0u, header.offset());
}

// Test offset with large value
TEST_F(TiffHeaderBaseTest_1177, OffsetReturnsLargeValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, 0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFF, header.offset());
}

// Test that setOffset changes the offset
TEST_F(TiffHeaderBaseTest_1177, SetOffsetChangesValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(kDefaultOffset, header.offset());
    header.setOffset(16);
    EXPECT_EQ(16u, header.offset());
}

// Test that size() returns the size passed to the constructor
TEST_F(TiffHeaderBaseTest_1177, SizeReturnsConstructorValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(kDefaultSize, header.size());
}

// Test size with zero value
TEST_F(TiffHeaderBaseTest_1177, SizeReturnsZero_1177) {
    TiffHeaderBase header(kTiffTag, 0, littleEndian, kDefaultOffset);
    EXPECT_EQ(0u, header.size());
}

// Test size with large value
TEST_F(TiffHeaderBaseTest_1177, SizeReturnsLargeValue_1177) {
    TiffHeaderBase header(kTiffTag, 0xFFFFFFFF, littleEndian, kDefaultOffset);
    EXPECT_EQ(0xFFFFFFFF, header.size());
}

// Test that read returns false when data is too small
TEST_F(TiffHeaderBaseTest_1177, ReadReturnsFalseWhenDataTooSmall_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    byte data[4] = {0x49, 0x49, 0x2a, 0x00};
    EXPECT_FALSE(header.read(data, 4));
}

// Test read with valid little-endian TIFF header
TEST_F(TiffHeaderBaseTest_1177, ReadValidLittleEndianTiffHeader_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    // II (little endian), 0x002a (tag), offset 8
    byte data[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(littleEndian, header.byteOrder());
    EXPECT_EQ(8u, header.offset());
}

// Test read with valid big-endian TIFF header
TEST_F(TiffHeaderBaseTest_1177, ReadValidBigEndianTiffHeader_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, bigEndian, kDefaultOffset);
    // MM (big endian), 0x002a (tag), offset 8
    byte data[8] = {0x4d, 0x4d, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x08};
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(bigEndian, header.byteOrder());
    EXPECT_EQ(8u, header.offset());
}

// Test read with nullptr should handle gracefully or return false
TEST_F(TiffHeaderBaseTest_1177, ReadWithZeroSizeReturnsFalse_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    byte data[1] = {0x00};
    EXPECT_FALSE(header.read(data, 0));
}

// Test write produces non-empty DataBuf
TEST_F(TiffHeaderBaseTest_1177, WriteProducesData_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    DataBuf buf = header.write();
    EXPECT_EQ(kDefaultSize, buf.size());
}

// Test write with big endian
TEST_F(TiffHeaderBaseTest_1177, WriteProducesDataBigEndian_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, bigEndian, kDefaultOffset);
    DataBuf buf = header.write();
    EXPECT_EQ(kDefaultSize, buf.size());
}

// Test print does not crash
TEST_F(TiffHeaderBaseTest_1177, PrintDoesNotCrash_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    std::ostringstream oss;
    EXPECT_NO_THROW(header.print(oss, ""));
    EXPECT_FALSE(oss.str().empty());
}

// Test print with prefix
TEST_F(TiffHeaderBaseTest_1177, PrintWithPrefix_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    std::ostringstream oss;
    EXPECT_NO_THROW(header.print(oss, "PREFIX: "));
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test isImageTag default implementation returns false
TEST_F(TiffHeaderBaseTest_1177, IsImageTagReturnsFalse_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    PrimaryGroups primaryGroups;
    EXPECT_FALSE(header.isImageTag(0x0100, IfdId::ifd0Id, primaryGroups));
}

// Test isImageTag with various parameters always returns false for base
TEST_F(TiffHeaderBaseTest_1177, IsImageTagAlwaysFalseForBase_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    PrimaryGroups primaryGroups;
    EXPECT_FALSE(header.isImageTag(0x0000, IfdId::ifd0Id, primaryGroups));
    EXPECT_FALSE(header.isImageTag(0xFFFF, IfdId::ifd0Id, primaryGroups));
}

// Test read with invalid byte order marker
TEST_F(TiffHeaderBaseTest_1177, ReadInvalidByteOrderMarker_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    // Invalid byte order marker (not II or MM)
    byte data[8] = {0x00, 0x00, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_FALSE(header.read(data, 8));
}

// Test read with wrong tag value
TEST_F(TiffHeaderBaseTest_1177, ReadWrongTagValue_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    // II byte order, but wrong tag (0x0000 instead of 0x002a)
    byte data[8] = {0x49, 0x49, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_FALSE(header.read(data, 8));
}

// Test multiple setByteOrder calls
TEST_F(TiffHeaderBaseTest_1177, MultipleSetByteOrderCalls_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, header.byteOrder());
    header.setByteOrder(littleEndian);
    EXPECT_EQ(littleEndian, header.byteOrder());
    header.setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, header.byteOrder());
}

// Test multiple setOffset calls
TEST_F(TiffHeaderBaseTest_1177, MultipleSetOffsetCalls_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    header.setOffset(0);
    EXPECT_EQ(0u, header.offset());
    header.setOffset(100);
    EXPECT_EQ(100u, header.offset());
    header.setOffset(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFF, header.offset());
}

// Test that write after read reflects updated state
TEST_F(TiffHeaderBaseTest_1177, WriteAfterReadReflectsState_1177) {
    TiffHeaderBase header(kTiffTag, kDefaultSize, littleEndian, kDefaultOffset);
    byte data[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    ASSERT_TRUE(header.read(data, 8));
    
    DataBuf buf = header.write();
    EXPECT_EQ(kDefaultSize, buf.size());
}

// Test construction with different tag values
TEST_F(TiffHeaderBaseTest_1177, ConstructWithDifferentTags_1177) {
    // BigTIFF magic number
    TiffHeaderBase header1(0x002b, 16, littleEndian, 16);
    EXPECT_EQ(0x002b, header1.tag());
    EXPECT_EQ(16u, header1.size());
    
    // Standard TIFF
    TiffHeaderBase header2(0x002a, 8, bigEndian, 8);
    EXPECT_EQ(0x002a, header2.tag());
    EXPECT_EQ(8u, header2.size());
}
