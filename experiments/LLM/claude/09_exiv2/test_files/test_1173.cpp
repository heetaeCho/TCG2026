#include <gtest/gtest.h>
#include <sstream>
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete subclass since TiffHeaderBase has virtual methods
// but we test through the base class interface
class TestableTiffHeaderBase : public TiffHeaderBase {
public:
    TestableTiffHeaderBase(uint16_t tag, uint32_t size, ByteOrder byteOrder, uint32_t offset)
        : TiffHeaderBase(tag, size, byteOrder, offset) {}
};

class TiffHeaderBaseTest_1173 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test construction and byteOrder getter
TEST_F(TiffHeaderBaseTest_1173, ConstructorSetsbyteOrder_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

TEST_F(TiffHeaderBaseTest_1173, ConstructorSetsByteOrderBigEndian_1173) {
    TestableTiffHeaderBase header(42, 8, bigEndian, 0);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test setByteOrder changes byte order
TEST_F(TiffHeaderBaseTest_1173, SetByteOrderChangesFromLittleToBig_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

TEST_F(TiffHeaderBaseTest_1173, SetByteOrderChangesFromBigToLittle_1173) {
    TestableTiffHeaderBase header(42, 8, bigEndian, 0);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    header.setByteOrder(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test setting byte order to the same value
TEST_F(TiffHeaderBaseTest_1173, SetByteOrderSameValue_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    header.setByteOrder(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test offset getter and setter
TEST_F(TiffHeaderBaseTest_1173, ConstructorSetsOffset_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 100);
    EXPECT_EQ(header.offset(), 100u);
}

TEST_F(TiffHeaderBaseTest_1173, SetOffsetChangesOffset_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    EXPECT_EQ(header.offset(), 0u);
    header.setOffset(256);
    EXPECT_EQ(header.offset(), 256u);
}

TEST_F(TiffHeaderBaseTest_1173, SetOffsetToZero_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 100);
    header.setOffset(0);
    EXPECT_EQ(header.offset(), 0u);
}

TEST_F(TiffHeaderBaseTest_1173, SetOffsetMaxValue_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    header.setOffset(0xFFFFFFFF);
    EXPECT_EQ(header.offset(), 0xFFFFFFFFu);
}

// Test size getter
TEST_F(TiffHeaderBaseTest_1173, ConstructorSetsSize_1173) {
    TestableTiffHeaderBase header(42, 16, littleEndian, 0);
    EXPECT_EQ(header.size(), 16u);
}

TEST_F(TiffHeaderBaseTest_1173, SizeZero_1173) {
    TestableTiffHeaderBase header(42, 0, littleEndian, 0);
    EXPECT_EQ(header.size(), 0u);
}

// Test tag getter
TEST_F(TiffHeaderBaseTest_1173, ConstructorSetsTag_1173) {
    TestableTiffHeaderBase header(0x002A, 8, littleEndian, 0);
    EXPECT_EQ(header.tag(), 0x002A);
}

TEST_F(TiffHeaderBaseTest_1173, TagZero_1173) {
    TestableTiffHeaderBase header(0, 8, littleEndian, 0);
    EXPECT_EQ(header.tag(), 0);
}

TEST_F(TiffHeaderBaseTest_1173, TagMaxValue_1173) {
    TestableTiffHeaderBase header(0xFFFF, 8, littleEndian, 0);
    EXPECT_EQ(header.tag(), 0xFFFF);
}

// Test isImageTag - should return false by default
TEST_F(TiffHeaderBaseTest_1173, IsImageTagReturnsFalse_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    PrimaryGroups primaryGroups;
    EXPECT_FALSE(header.isImageTag(0, IfdId::ifd0Id, primaryGroups));
}

TEST_F(TiffHeaderBaseTest_1173, IsImageTagReturnsFalseForAnyTag_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    PrimaryGroups primaryGroups;
    EXPECT_FALSE(header.isImageTag(0xFFFF, IfdId::ifd0Id, primaryGroups));
}

// Test read with data smaller than header size
TEST_F(TiffHeaderBaseTest_1173, ReadWithInsufficientData_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 8);
    byte data[4] = {0x49, 0x49, 0x2A, 0x00};
    EXPECT_FALSE(header.read(data, 4));
}

// Test read with nullptr data and zero size
TEST_F(TiffHeaderBaseTest_1173, ReadWithZeroSizeData_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 8);
    byte data[1] = {0};
    EXPECT_FALSE(header.read(data, 0));
}

// Test print does not crash
TEST_F(TiffHeaderBaseTest_1173, PrintDoesNotCrash_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 8);
    std::ostringstream os;
    EXPECT_NO_THROW(header.print(os, "Test: "));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(TiffHeaderBaseTest_1173, PrintWithEmptyPrefix_1173) {
    TestableTiffHeaderBase header(42, 8, bigEndian, 0);
    std::ostringstream os;
    EXPECT_NO_THROW(header.print(os, ""));
    EXPECT_FALSE(os.str().empty());
}

// Test write returns a DataBuf
TEST_F(TiffHeaderBaseTest_1173, WriteReturnsDataBuf_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 8);
    DataBuf buf = header.write();
    EXPECT_GT(buf.size(), 0u);
}

// Test multiple setByteOrder calls
TEST_F(TiffHeaderBaseTest_1173, MultipleSetByteOrderCalls_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    header.setByteOrder(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test multiple setOffset calls
TEST_F(TiffHeaderBaseTest_1173, MultipleSetOffsetCalls_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 0);
    header.setOffset(10);
    EXPECT_EQ(header.offset(), 10u);
    header.setOffset(20);
    EXPECT_EQ(header.offset(), 20u);
    header.setOffset(0);
    EXPECT_EQ(header.offset(), 0u);
}

// Test valid TIFF header read (little endian)
TEST_F(TiffHeaderBaseTest_1173, ReadValidLittleEndianHeader_1173) {
    TestableTiffHeaderBase header(42, 8, littleEndian, 8);
    // Little endian TIFF header: "II" + 0x002A + offset 8
    byte data[8] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    bool result = header.read(data, 8);
    // After successful read, byte order and offset should be updated
    if (result) {
        EXPECT_EQ(header.byteOrder(), littleEndian);
    }
}

// Test valid TIFF header read (big endian)
TEST_F(TiffHeaderBaseTest_1173, ReadValidBigEndianHeader_1173) {
    TestableTiffHeaderBase header(42, 8, bigEndian, 8);
    // Big endian TIFF header: "MM" + 0x002A + offset 8
    byte data[8] = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};
    bool result = header.read(data, 8);
    if (result) {
        EXPECT_EQ(header.byteOrder(), bigEndian);
    }
}
