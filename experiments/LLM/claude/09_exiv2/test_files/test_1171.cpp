#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include necessary headers
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffHeaderBase is abstract-like but has a concrete constructor,
// we need a concrete derived class for testing if TiffHeaderBase cannot be instantiated directly.
// Based on the interface, TiffHeaderBase has a public constructor, so we can try to use it directly.
// However, it has virtual methods, so we create a minimal concrete subclass if needed.

class TestableTiffHeader : public TiffHeaderBase {
public:
    TestableTiffHeader(uint16_t tag, uint32_t size, ByteOrder byteOrder, uint32_t offset)
        : TiffHeaderBase(tag, size, byteOrder, offset) {}
};

class TiffHeaderBaseTest_1171 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test print with little endian byte order
TEST_F(TiffHeaderBaseTest_1171, PrintLittleEndian_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    // Should contain offset in hex
    EXPECT_NE(output.find("00000008"), std::string::npos);
    // Should contain "little endian"
    EXPECT_NE(output.find("little endian"), std::string::npos);
}

// Test print with big endian byte order
TEST_F(TiffHeaderBaseTest_1171, PrintBigEndian_1171) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 0x00000008);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_NE(output.find("big endian"), std::string::npos);
}

// Test print with invalid byte order
TEST_F(TiffHeaderBaseTest_1171, PrintInvalidByteOrder_1171) {
    TestableTiffHeader header(0x002A, 8, invalidByteOrder, 0x00000008);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    // Should NOT contain "little endian" or "big endian"
    EXPECT_EQ(output.find("little endian"), std::string::npos);
    EXPECT_EQ(output.find("big endian"), std::string::npos);
    // Should end with newline
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test print with a prefix
TEST_F(TiffHeaderBaseTest_1171, PrintWithPrefix_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000010);
    std::ostringstream os;
    header.print(os, "  ");
    std::string output = os.str();
    // Should start with the prefix
    EXPECT_EQ(output.substr(0, 2), "  ");
    // Should contain offset 0x00000010
    EXPECT_NE(output.find("00000010"), std::string::npos);
}

// Test print with zero offset
TEST_F(TiffHeaderBaseTest_1171, PrintZeroOffset_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000000);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_NE(output.find("00000000"), std::string::npos);
}

// Test print with large offset
TEST_F(TiffHeaderBaseTest_1171, PrintLargeOffset_1171) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 0xFFFFFFFF);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_NE(output.find("ffffffff"), std::string::npos);
}

// Test print output ends with newline
TEST_F(TiffHeaderBaseTest_1171, PrintEndsWithNewline_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test byteOrder getter
TEST_F(TiffHeaderBaseTest_1171, ByteOrderGetter_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test byteOrder getter with big endian
TEST_F(TiffHeaderBaseTest_1171, ByteOrderGetterBigEndian_1171) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 0x00000008);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test byteOrder getter with invalid byte order
TEST_F(TiffHeaderBaseTest_1171, ByteOrderGetterInvalid_1171) {
    TestableTiffHeader header(0x002A, 8, invalidByteOrder, 0x00000008);
    EXPECT_EQ(header.byteOrder(), invalidByteOrder);
}

// Test offset getter
TEST_F(TiffHeaderBaseTest_1171, OffsetGetter_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header.offset(), 0x00000008u);
}

// Test offset getter with zero
TEST_F(TiffHeaderBaseTest_1171, OffsetGetterZero_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0);
    EXPECT_EQ(header.offset(), 0u);
}

// Test size getter
TEST_F(TiffHeaderBaseTest_1171, SizeGetter_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header.size(), 8u);
}

// Test tag getter
TEST_F(TiffHeaderBaseTest_1171, TagGetter_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header.tag(), 0x002Au);
}

// Test setByteOrder
TEST_F(TiffHeaderBaseTest_1171, SetByteOrder_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test setOffset
TEST_F(TiffHeaderBaseTest_1171, SetOffset_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header.offset(), 0x00000008u);
    header.setOffset(0x00001000);
    EXPECT_EQ(header.offset(), 0x00001000u);
}

// Test setByteOrder then print reflects change
TEST_F(TiffHeaderBaseTest_1171, SetByteOrderAffectsPrint_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    header.setByteOrder(bigEndian);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_NE(output.find("big endian"), std::string::npos);
    EXPECT_EQ(output.find("little endian"), std::string::npos);
}

// Test setOffset then print reflects change
TEST_F(TiffHeaderBaseTest_1171, SetOffsetAffectsPrint_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    header.setOffset(0x0000ABCD);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_NE(output.find("0000abcd"), std::string::npos);
}

// Test print with empty prefix
TEST_F(TiffHeaderBaseTest_1171, PrintEmptyPrefix_1171) {
    TestableTiffHeader header(0x002A, 8, bigEndian, 0x00000100);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_NE(output.find("00000100"), std::string::npos);
    EXPECT_NE(output.find("big endian"), std::string::npos);
}

// Test that print contains "TIFF header" text
TEST_F(TiffHeaderBaseTest_1171, PrintContainsTiffHeader_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    // The output should contain some indication of TIFF header
    // Based on the i18n _("TIFF header, offset") this should appear
    EXPECT_NE(output.find("0x00000008"), std::string::npos);
}

// Test isImageTag returns false by default
TEST_F(TiffHeaderBaseTest_1171, IsImageTagDefaultFalse_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    PrimaryGroups pg;
    EXPECT_FALSE(header.isImageTag(0x0100, IfdId::ifd0Id, pg));
}

// Test different tag values
TEST_F(TiffHeaderBaseTest_1171, DifferentTagValues_1171) {
    TestableTiffHeader header1(0x002A, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header1.tag(), 0x002Au);

    TestableTiffHeader header2(0x002B, 16, bigEndian, 0x00000010);
    EXPECT_EQ(header2.tag(), 0x002Bu);
    EXPECT_EQ(header2.size(), 16u);
}

// Test size with zero
TEST_F(TiffHeaderBaseTest_1171, SizeZero_1171) {
    TestableTiffHeader header(0x002A, 0, littleEndian, 0);
    EXPECT_EQ(header.size(), 0u);
}

// Test maximum uint16 tag value
TEST_F(TiffHeaderBaseTest_1171, MaxTagValue_1171) {
    TestableTiffHeader header(0xFFFF, 8, littleEndian, 0x00000008);
    EXPECT_EQ(header.tag(), 0xFFFFu);
}

// Test setByteOrder to invalidByteOrder
TEST_F(TiffHeaderBaseTest_1171, SetByteOrderToInvalid_1171) {
    TestableTiffHeader header(0x002A, 8, littleEndian, 0x00000008);
    header.setByteOrder(invalidByteOrder);
    EXPECT_EQ(header.byteOrder(), invalidByteOrder);
    
    std::ostringstream os;
    header.print(os, "");
    std::string output = os.str();
    EXPECT_EQ(output.find("little endian"), std::string::npos);
    EXPECT_EQ(output.find("big endian"), std::string::npos);
}
