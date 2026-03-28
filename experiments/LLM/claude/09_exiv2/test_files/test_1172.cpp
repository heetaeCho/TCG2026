#include <gtest/gtest.h>
#include <sstream>
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper subclass to instantiate TiffHeaderBase for testing
// Since TiffHeaderBase may have pure virtual methods or be abstract,
// we use it directly if possible, or create a minimal concrete subclass.
class TestableTiffHeader : public TiffHeaderBase {
public:
    TestableTiffHeader(uint16_t tag, uint32_t size, ByteOrder byteOrder, uint32_t offset)
        : TiffHeaderBase(tag, size, byteOrder, offset) {}
};

class TiffHeaderBaseTest_1172 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that byteOrder returns the byte order set during construction (littleEndian)
TEST_F(TiffHeaderBaseTest_1172, ConstructWithLittleEndian_ReturnsLittleEndian_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    EXPECT_EQ(littleEndian, header.byteOrder());
}

// Test that byteOrder returns the byte order set during construction (bigEndian)
TEST_F(TiffHeaderBaseTest_1172, ConstructWithBigEndian_ReturnsBigEndian_1172) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 8);
    EXPECT_EQ(bigEndian, header.byteOrder());
}

// Test that setByteOrder changes the byte order
TEST_F(TiffHeaderBaseTest_1172, SetByteOrder_ChangesToBigEndian_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    EXPECT_EQ(littleEndian, header.byteOrder());
    header.setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, header.byteOrder());
}

// Test that setByteOrder changes from big to little endian
TEST_F(TiffHeaderBaseTest_1172, SetByteOrder_ChangesToLittleEndian_1172) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 8);
    header.setByteOrder(littleEndian);
    EXPECT_EQ(littleEndian, header.byteOrder());
}

// Test that offset returns the offset set during construction
TEST_F(TiffHeaderBaseTest_1172, ConstructWithOffset_ReturnsCorrectOffset_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 16);
    EXPECT_EQ(16u, header.offset());
}

// Test that setOffset changes the offset
TEST_F(TiffHeaderBaseTest_1172, SetOffset_ChangesOffset_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    header.setOffset(128);
    EXPECT_EQ(128u, header.offset());
}

// Test that size returns the size set during construction
TEST_F(TiffHeaderBaseTest_1172, ConstructWithSize_ReturnsCorrectSize_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    EXPECT_EQ(8u, header.size());
}

// Test that tag returns the tag set during construction
TEST_F(TiffHeaderBaseTest_1172, ConstructWithTag_ReturnsCorrectTag_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    EXPECT_EQ(0x002A, header.tag());
}

// Test with different tag value
TEST_F(TiffHeaderBaseTest_1172, ConstructWithDifferentTag_ReturnsCorrectTag_1172) {
    TestableTiffHeader header(0x002B, 16, bigEndian, 0);
    EXPECT_EQ(0x002B, header.tag());
}

// Test offset zero (boundary)
TEST_F(TiffHeaderBaseTest_1172, ConstructWithZeroOffset_ReturnsZero_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0);
    EXPECT_EQ(0u, header.offset());
}

// Test with maximum uint32_t offset (boundary)
TEST_F(TiffHeaderBaseTest_1172, ConstructWithMaxOffset_ReturnsMaxOffset_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFF, header.offset());
}

// Test setOffset to zero
TEST_F(TiffHeaderBaseTest_1172, SetOffsetToZero_ReturnsZero_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 100);
    header.setOffset(0);
    EXPECT_EQ(0u, header.offset());
}

// Test isImageTag returns false by default
TEST_F(TiffHeaderBaseTest_1172, IsImageTag_ReturnsFalseByDefault_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    PrimaryGroups primaryGroups;
    EXPECT_FALSE(header.isImageTag(0x0100, IfdId::ifd0Id, primaryGroups));
}

// Test read with data that is too small (less than size)
TEST_F(TiffHeaderBaseTest_1172, ReadWithInsufficientData_ReturnsFalse_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    const byte data[] = {0x49, 0x49, 0x2A, 0x00};
    // Data size (4) is less than header size (8), should fail
    EXPECT_FALSE(header.read(data, 4));
}

// Test read with valid TIFF little-endian header
TEST_F(TiffHeaderBaseTest_1172, ReadWithValidLittleEndianData_ReturnsTrue_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    // II (little-endian), 0x002A (TIFF magic), offset 8
    const byte data[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(littleEndian, header.byteOrder());
}

// Test read with valid TIFF big-endian header
TEST_F(TiffHeaderBaseTest_1172, ReadWithValidBigEndianData_ReturnsTrue_1172) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 8);
    // MM (big-endian), 0x002A (TIFF magic), offset 8
    const byte data[] = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(bigEndian, header.byteOrder());
}

// Test print does not crash
TEST_F(TiffHeaderBaseTest_1172, Print_DoesNotCrash_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    std::ostringstream os;
    EXPECT_NO_THROW(header.print(os, "TIFF"));
    // Print should produce some output
    EXPECT_FALSE(os.str().empty());
}

// Test write returns a DataBuf
TEST_F(TiffHeaderBaseTest_1172, Write_ReturnsNonEmptyDataBuf_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    DataBuf buf = header.write();
    EXPECT_GT(buf.size(), 0u);
}

// Test that size is consistent with write output
TEST_F(TiffHeaderBaseTest_1172, Write_SizeMatchesHeaderSize_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    DataBuf buf = header.write();
    EXPECT_EQ(header.size(), static_cast<uint32_t>(buf.size()));
}

// Test construction with size zero (boundary)
TEST_F(TiffHeaderBaseTest_1172, ConstructWithZeroSize_ReturnsZeroSize_1172) {
    TestableTiffHeader header(0x002A, 0, littleEndian, 0);
    EXPECT_EQ(0u, header.size());
}

// Test setting byte order to the same value
TEST_F(TiffHeaderBaseTest_1172, SetByteOrderSameValue_RemainsUnchanged_1172) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 8);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, header.byteOrder());
}

// Test read with invalid byte order marker
TEST_F(TiffHeaderBaseTest_1172, ReadWithInvalidByteOrderMarker_ReturnsFalse_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    // Invalid byte order marker (XX instead of II or MM)
    const byte data[] = {0x58, 0x58, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_FALSE(header.read(data, 8));
}

// Test read with wrong tag
TEST_F(TiffHeaderBaseTest_1172, ReadWithWrongTag_ReturnsFalse_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    // Correct byte order (II) but wrong tag (0x0000 instead of 0x002A)
    const byte data[] = {0x49, 0x49, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_FALSE(header.read(data, 8));
}

// Test print with a prefix
TEST_F(TiffHeaderBaseTest_1172, PrintWithPrefix_ContainsPrefix_1172) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 8);
    std::ostringstream os;
    header.print(os, "TestPrefix");
    std::string output = os.str();
    // The prefix should appear in the output
    EXPECT_NE(std::string::npos, output.find("TestPrefix"));
}
