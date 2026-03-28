#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>

// Include the necessary headers from the exiv2 project
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffHeaderBase
class TiffHeaderBaseTest_1174 : public ::testing::Test {
protected:
    // Common tag and size values used in tests
    static constexpr uint16_t kDefaultTag = 0x002A;  // Standard TIFF tag
    static constexpr uint32_t kDefaultSize = 8;
    static constexpr uint32_t kDefaultOffset = 8;
};

// Test that offset() returns the offset set during construction
TEST_F(TiffHeaderBaseTest_1174, OffsetReturnsConstructedValue_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, 0x00000008);
    EXPECT_EQ(header.offset(), 0x00000008u);
}

// Test that offset() returns zero when constructed with zero offset
TEST_F(TiffHeaderBaseTest_1174, OffsetReturnsZeroWhenConstructedWithZero_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, 0);
    EXPECT_EQ(header.offset(), 0u);
}

// Test that offset() returns max uint32_t value
TEST_F(TiffHeaderBaseTest_1174, OffsetReturnsMaxUint32_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, 0xFFFFFFFF);
    EXPECT_EQ(header.offset(), 0xFFFFFFFFu);
}

// Test that setOffset changes the offset value
TEST_F(TiffHeaderBaseTest_1174, SetOffsetChangesOffset_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(header.offset(), kDefaultOffset);
    
    header.setOffset(0x00001000);
    EXPECT_EQ(header.offset(), 0x00001000u);
}

// Test that setOffset to zero works
TEST_F(TiffHeaderBaseTest_1174, SetOffsetToZero_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    header.setOffset(0);
    EXPECT_EQ(header.offset(), 0u);
}

// Test that setOffset to max uint32 works
TEST_F(TiffHeaderBaseTest_1174, SetOffsetToMaxValue_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    header.setOffset(0xFFFFFFFF);
    EXPECT_EQ(header.offset(), 0xFFFFFFFFu);
}

// Test that tag() returns the tag set during construction
TEST_F(TiffHeaderBaseTest_1174, TagReturnsConstructedValue_1174) {
    TiffHeaderBase header(0x002A, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(header.tag(), 0x002Au);
}

// Test that size() returns the size set during construction
TEST_F(TiffHeaderBaseTest_1174, SizeReturnsConstructedValue_1174) {
    TiffHeaderBase header(kDefaultTag, 8, littleEndian, kDefaultOffset);
    EXPECT_EQ(header.size(), 8u);
}

// Test that byteOrder() returns the byte order set during construction
TEST_F(TiffHeaderBaseTest_1174, ByteOrderReturnsConstructedValue_LittleEndian_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test that byteOrder() returns big endian when constructed with big endian
TEST_F(TiffHeaderBaseTest_1174, ByteOrderReturnsConstructedValue_BigEndian_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, bigEndian, kDefaultOffset);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test that setByteOrder changes the byte order
TEST_F(TiffHeaderBaseTest_1174, SetByteOrderChangesValue_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test multiple setOffset calls - last one should stick
TEST_F(TiffHeaderBaseTest_1174, MultipleSetOffsetCallsRetainLastValue_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    
    header.setOffset(100);
    EXPECT_EQ(header.offset(), 100u);
    
    header.setOffset(200);
    EXPECT_EQ(header.offset(), 200u);
    
    header.setOffset(300);
    EXPECT_EQ(header.offset(), 300u);
}

// Test with different offset values to ensure independence from other fields
TEST_F(TiffHeaderBaseTest_1174, OffsetIndependentFromOtherFields_1174) {
    TiffHeaderBase header1(0x0001, 4, littleEndian, 42);
    TiffHeaderBase header2(0x0002, 16, bigEndian, 42);
    
    EXPECT_EQ(header1.offset(), header2.offset());
    EXPECT_EQ(header1.offset(), 42u);
}

// Test that write() produces a non-empty DataBuf for a valid header
TEST_F(TiffHeaderBaseTest_1174, WriteProducesData_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    DataBuf buf = header.write();
    EXPECT_GT(buf.size(), 0u);
}

// Test print doesn't crash
TEST_F(TiffHeaderBaseTest_1174, PrintDoesNotCrash_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    std::ostringstream os;
    EXPECT_NO_THROW(header.print(os, ""));
}

// Test print with a prefix
TEST_F(TiffHeaderBaseTest_1174, PrintWithPrefix_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    std::ostringstream os;
    EXPECT_NO_THROW(header.print(os, "TestPrefix: "));
    // We just check that something was written
    EXPECT_FALSE(os.str().empty());
}

// Test read with valid TIFF header data (little endian)
TEST_F(TiffHeaderBaseTest_1174, ReadValidLittleEndianHeader_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    // Little endian TIFF header: "II" + 0x002A + offset 8
    const byte tiffData[] = {
        0x49, 0x49,       // "II" - little endian
        0x2A, 0x00,       // Tag 42
        0x08, 0x00, 0x00, 0x00  // Offset = 8
    };
    bool result = header.read(tiffData, sizeof(tiffData));
    EXPECT_TRUE(result);
}

// Test read with valid TIFF header data (big endian)
TEST_F(TiffHeaderBaseTest_1174, ReadValidBigEndianHeader_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, bigEndian, kDefaultOffset);
    // Big endian TIFF header: "MM" + 0x002A + offset 8
    const byte tiffData[] = {
        0x4D, 0x4D,       // "MM" - big endian
        0x00, 0x2A,       // Tag 42
        0x00, 0x00, 0x00, 0x08  // Offset = 8
    };
    bool result = header.read(tiffData, sizeof(tiffData));
    EXPECT_TRUE(result);
}

// Test read with insufficient data
TEST_F(TiffHeaderBaseTest_1174, ReadWithInsufficientData_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    const byte tiffData[] = { 0x49, 0x49 };  // Too short
    bool result = header.read(tiffData, sizeof(tiffData));
    EXPECT_FALSE(result);
}

// Test read with zero size
TEST_F(TiffHeaderBaseTest_1174, ReadWithZeroSize_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    const byte tiffData[] = { 0x00 };
    bool result = header.read(tiffData, 0);
    EXPECT_FALSE(result);
}

// Test isImageTag returns false by default (base class behavior)
TEST_F(TiffHeaderBaseTest_1174, IsImageTagReturnsFalse_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, kDefaultOffset);
    PrimaryGroups primaryGroups;
    bool result = header.isImageTag(0x0100, IfdId::ifd0Id, primaryGroups);
    EXPECT_FALSE(result);
}

// Test offset boundary: value 1
TEST_F(TiffHeaderBaseTest_1174, OffsetBoundaryValueOne_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, 1);
    EXPECT_EQ(header.offset(), 1u);
}

// Test with various large offset values
TEST_F(TiffHeaderBaseTest_1174, OffsetLargeValue_1174) {
    TiffHeaderBase header(kDefaultTag, kDefaultSize, littleEndian, 0x7FFFFFFF);
    EXPECT_EQ(header.offset(), 0x7FFFFFFFu);
}
