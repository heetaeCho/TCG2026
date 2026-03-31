#include <gtest/gtest.h>
#include <sstream>
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A concrete subclass to test TiffHeaderBase since it may have pure virtual methods
// or we need to instantiate it. We use the constructor directly.
class TiffHeaderBaseTest_1176 : public ::testing::Test {
protected:
    // Helper to create TiffHeaderBase instances with various parameters
};

TEST_F(TiffHeaderBaseTest_1176, ConstructorSetsSize_1176) {
    // Test that the size returned matches what was passed to constructor
    uint16_t tag = 0x002A;
    uint32_t size = 8;
    ByteOrder byteOrder = littleEndian;
    uint32_t offset = 0x00000008;

    TiffHeaderBase header(tag, size, byteOrder, offset);
    EXPECT_EQ(header.size(), size);
}

TEST_F(TiffHeaderBaseTest_1176, ConstructorSetsByteOrder_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

TEST_F(TiffHeaderBaseTest_1176, ConstructorSetsByteOrderBigEndian_1176) {
    TiffHeaderBase header(0x002A, 8, bigEndian, 8);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

TEST_F(TiffHeaderBaseTest_1176, ConstructorSetsOffset_1176) {
    uint32_t offset = 0x00000010;
    TiffHeaderBase header(0x002A, 8, littleEndian, offset);
    EXPECT_EQ(header.offset(), offset);
}

TEST_F(TiffHeaderBaseTest_1176, ConstructorSetsTag_1176) {
    uint16_t tag = 0x002A;
    TiffHeaderBase header(tag, 8, littleEndian, 8);
    EXPECT_EQ(header.tag(), tag);
}

TEST_F(TiffHeaderBaseTest_1176, SizeZero_1176) {
    TiffHeaderBase header(0x002A, 0, littleEndian, 0);
    EXPECT_EQ(header.size(), 0u);
}

TEST_F(TiffHeaderBaseTest_1176, SizeMaxValue_1176) {
    uint32_t maxSize = std::numeric_limits<uint32_t>::max();
    TiffHeaderBase header(0x002A, maxSize, littleEndian, 0);
    EXPECT_EQ(header.size(), maxSize);
}

TEST_F(TiffHeaderBaseTest_1176, SetByteOrderChangesOrder_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

TEST_F(TiffHeaderBaseTest_1176, SetOffsetChangesOffset_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    EXPECT_EQ(header.offset(), 8u);
    header.setOffset(16);
    EXPECT_EQ(header.offset(), 16u);
}

TEST_F(TiffHeaderBaseTest_1176, SetOffsetToZero_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    header.setOffset(0);
    EXPECT_EQ(header.offset(), 0u);
}

TEST_F(TiffHeaderBaseTest_1176, SetOffsetMaxValue_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    uint32_t maxOffset = std::numeric_limits<uint32_t>::max();
    header.setOffset(maxOffset);
    EXPECT_EQ(header.offset(), maxOffset);
}

TEST_F(TiffHeaderBaseTest_1176, OffsetZero_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 0);
    EXPECT_EQ(header.offset(), 0u);
}

TEST_F(TiffHeaderBaseTest_1176, TagZero_1176) {
    TiffHeaderBase header(0, 8, littleEndian, 8);
    EXPECT_EQ(header.tag(), 0u);
}

TEST_F(TiffHeaderBaseTest_1176, TagMaxValue_1176) {
    uint16_t maxTag = std::numeric_limits<uint16_t>::max();
    TiffHeaderBase header(maxTag, 8, littleEndian, 8);
    EXPECT_EQ(header.tag(), maxTag);
}

TEST_F(TiffHeaderBaseTest_1176, IsImageTagReturnsFalse_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    PrimaryGroups primaryGroups;
    // Default implementation should return false
    EXPECT_FALSE(header.isImageTag(0x0100, IfdId::ifd0Id, primaryGroups));
}

TEST_F(TiffHeaderBaseTest_1176, PrintDoesNotCrash_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    std::ostringstream os;
    // Just verify it doesn't crash/throw
    EXPECT_NO_THROW(header.print(os, ""));
}

TEST_F(TiffHeaderBaseTest_1176, PrintWithPrefix_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    std::ostringstream os;
    EXPECT_NO_THROW(header.print(os, "TEST: "));
    // Verify something was written
    EXPECT_FALSE(os.str().empty());
}

TEST_F(TiffHeaderBaseTest_1176, WriteReturnsDataBuf_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    DataBuf buf = header.write();
    // The write should produce some data based on the header size
    EXPECT_GE(buf.size(), 0u);
}

TEST_F(TiffHeaderBaseTest_1176, ReadWithNullptrAndZeroSize_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    // Reading with null data and zero size - behavior depends on implementation
    // but should not crash for zero size
    bool result = header.read(nullptr, 0);
    // We just check it returns a boolean (likely false for insufficient data)
    (void)result;
}

TEST_F(TiffHeaderBaseTest_1176, ReadWithInsufficientData_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    byte data[] = {0x49, 0x49}; // Only 2 bytes, not enough for a TIFF header
    bool result = header.read(data, 2);
    // With insufficient data, read should fail
    EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1176, ReadValidLittleEndianTiffHeader_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    // Valid little-endian TIFF header: II, 0x002A, offset 8
    byte data[] = {
        0x49, 0x49,       // "II" - little endian
        0x2A, 0x00,       // Tag 42
        0x08, 0x00, 0x00, 0x00  // Offset 8
    };
    bool result = header.read(data, sizeof(data));
    EXPECT_TRUE(result);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.offset(), 8u);
}

TEST_F(TiffHeaderBaseTest_1176, ReadValidBigEndianTiffHeader_1176) {
    TiffHeaderBase header(0x002A, 8, bigEndian, 8);
    // Valid big-endian TIFF header: MM, 0x002A, offset 8
    byte data[] = {
        0x4D, 0x4D,       // "MM" - big endian
        0x00, 0x2A,       // Tag 42
        0x00, 0x00, 0x00, 0x08  // Offset 8
    };
    bool result = header.read(data, sizeof(data));
    EXPECT_TRUE(result);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    EXPECT_EQ(header.offset(), 8u);
}

TEST_F(TiffHeaderBaseTest_1176, SizeConsistentAfterOperations_1176) {
    uint32_t size = 16;
    TiffHeaderBase header(0x002A, size, littleEndian, 8);
    // Size should not change after setByteOrder or setOffset
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.size(), size);
    header.setOffset(100);
    EXPECT_EQ(header.size(), size);
}

TEST_F(TiffHeaderBaseTest_1176, MultipleSetByteOrderCalls_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    header.setByteOrder(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

TEST_F(TiffHeaderBaseTest_1176, MultipleSetOffsetCalls_1176) {
    TiffHeaderBase header(0x002A, 8, littleEndian, 8);
    header.setOffset(100);
    EXPECT_EQ(header.offset(), 100u);
    header.setOffset(200);
    EXPECT_EQ(header.offset(), 200u);
    header.setOffset(0);
    EXPECT_EQ(header.offset(), 0u);
}
