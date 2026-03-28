#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

// Helper: Create a MemIo-based image for testing static methods and basic functionality
// Since Image is abstract (has pure virtual methods), we need a concrete subclass for some tests.
// However, many methods we test are static and don't require instantiation.

class ImageStaticTest_1055 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== isPrintXMP tests ====================

TEST_F(ImageStaticTest_1055, IsPrintXMP_TypeIs700AndOptionIsKpsXMP_ReturnsTrue_1055) {
    EXPECT_TRUE(Image::isPrintXMP(700, kpsXMP));
}

TEST_F(ImageStaticTest_1055, IsPrintXMP_TypeIs700AndOptionIsNotKpsXMP_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintXMP(700, kpsNone));
    EXPECT_FALSE(Image::isPrintXMP(700, kpsBasic));
    EXPECT_FALSE(Image::isPrintXMP(700, kpsRecursive));
    EXPECT_FALSE(Image::isPrintXMP(700, kpsIccProfile));
    EXPECT_FALSE(Image::isPrintXMP(700, kpsIptcErase));
}

TEST_F(ImageStaticTest_1055, IsPrintXMP_TypeIsNot700AndOptionIsKpsXMP_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintXMP(0, kpsXMP));
    EXPECT_FALSE(Image::isPrintXMP(1, kpsXMP));
    EXPECT_FALSE(Image::isPrintXMP(699, kpsXMP));
    EXPECT_FALSE(Image::isPrintXMP(701, kpsXMP));
    EXPECT_FALSE(Image::isPrintXMP(65535, kpsXMP));
}

TEST_F(ImageStaticTest_1055, IsPrintXMP_TypeIsNot700AndOptionIsNotKpsXMP_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintXMP(0, kpsNone));
    EXPECT_FALSE(Image::isPrintXMP(100, kpsBasic));
    EXPECT_FALSE(Image::isPrintXMP(65535, kpsIccProfile));
}

// ==================== isPrintICC tests ====================

TEST_F(ImageStaticTest_1055, IsPrintICC_CorrectTypeAndOption_ReturnsTrue_1055) {
    // isPrintICC should return true for type==700 and option==kpsIccProfile based on naming convention
    EXPECT_TRUE(Image::isPrintICC(700, kpsIccProfile));
}

TEST_F(ImageStaticTest_1055, IsPrintICC_WrongOption_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintICC(700, kpsXMP));
    EXPECT_FALSE(Image::isPrintICC(700, kpsNone));
    EXPECT_FALSE(Image::isPrintICC(700, kpsBasic));
}

TEST_F(ImageStaticTest_1055, IsPrintICC_WrongType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintICC(0, kpsIccProfile));
    EXPECT_FALSE(Image::isPrintICC(699, kpsIccProfile));
    EXPECT_FALSE(Image::isPrintICC(701, kpsIccProfile));
}

// ==================== isStringType tests ====================

TEST_F(ImageStaticTest_1055, IsStringType_ValidStringType_ReturnsTrue_1055) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Image::isStringType(2));
}

TEST_F(ImageStaticTest_1055, IsStringType_NonStringType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isStringType(0));
    EXPECT_FALSE(Image::isStringType(1));  // BYTE
    EXPECT_FALSE(Image::isStringType(3));  // SHORT
    EXPECT_FALSE(Image::isStringType(4));  // LONG
}

// ==================== isShortType tests ====================

TEST_F(ImageStaticTest_1055, IsShortType_ShortType_ReturnsTrue_1055) {
    // TIFF SHORT type is 3, SSHORT is 8
    EXPECT_TRUE(Image::isShortType(3));
    EXPECT_TRUE(Image::isShortType(8));
}

TEST_F(ImageStaticTest_1055, IsShortType_NonShortType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isShortType(0));
    EXPECT_FALSE(Image::isShortType(1));
    EXPECT_FALSE(Image::isShortType(2));
    EXPECT_FALSE(Image::isShortType(4));
}

// ==================== isLongType tests ====================

TEST_F(ImageStaticTest_1055, IsLongType_LongType_ReturnsTrue_1055) {
    // TIFF LONG type is 4, SLONG is 9
    EXPECT_TRUE(Image::isLongType(4));
    EXPECT_TRUE(Image::isLongType(9));
}

TEST_F(ImageStaticTest_1055, IsLongType_NonLongType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isLongType(0));
    EXPECT_FALSE(Image::isLongType(1));
    EXPECT_FALSE(Image::isLongType(3));
    EXPECT_FALSE(Image::isLongType(5));
}

// ==================== isRationalType tests ====================

TEST_F(ImageStaticTest_1055, IsRationalType_RationalType_ReturnsTrue_1055) {
    // TIFF RATIONAL type is 5, SRATIONAL is 10
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_TRUE(Image::isRationalType(10));
}

TEST_F(ImageStaticTest_1055, IsRationalType_NonRationalType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isRationalType(0));
    EXPECT_FALSE(Image::isRationalType(1));
    EXPECT_FALSE(Image::isRationalType(4));
    EXPECT_FALSE(Image::isRationalType(6));
}

// ==================== isLongLongType tests ====================

TEST_F(ImageStaticTest_1055, IsLongLongType_LongLongTypes_ReturnsTrue_1055) {
    // Typically type 16 (LONG8) and 17 (SLONG8) for BigTIFF
    // We test the known ones
    EXPECT_TRUE(Image::isLongLongType(16));
    EXPECT_TRUE(Image::isLongLongType(17));
}

TEST_F(ImageStaticTest_1055, IsLongLongType_NonLongLongType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isLongLongType(0));
    EXPECT_FALSE(Image::isLongLongType(4));
    EXPECT_FALSE(Image::isLongLongType(9));
}

// ==================== is2ByteType tests ====================

TEST_F(ImageStaticTest_1055, Is2ByteType_ShortTypes_ReturnsTrue_1055) {
    EXPECT_TRUE(Image::is2ByteType(3));  // SHORT
    EXPECT_TRUE(Image::is2ByteType(8));  // SSHORT
}

TEST_F(ImageStaticTest_1055, Is2ByteType_NonShortType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::is2ByteType(0));
    EXPECT_FALSE(Image::is2ByteType(1));
    EXPECT_FALSE(Image::is2ByteType(4));
}

// ==================== is4ByteType tests ====================

TEST_F(ImageStaticTest_1055, Is4ByteType_FourByteTypes_ReturnsTrue_1055) {
    EXPECT_TRUE(Image::is4ByteType(4));   // LONG
    EXPECT_TRUE(Image::is4ByteType(9));   // SLONG
    EXPECT_TRUE(Image::is4ByteType(11));  // FLOAT
}

TEST_F(ImageStaticTest_1055, Is4ByteType_NonFourByteType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::is4ByteType(0));
    EXPECT_FALSE(Image::is4ByteType(1));
    EXPECT_FALSE(Image::is4ByteType(3));
}

// ==================== is8ByteType tests ====================

TEST_F(ImageStaticTest_1055, Is8ByteType_EightByteTypes_ReturnsTrue_1055) {
    EXPECT_TRUE(Image::is8ByteType(5));   // RATIONAL
    EXPECT_TRUE(Image::is8ByteType(10));  // SRATIONAL
    EXPECT_TRUE(Image::is8ByteType(12));  // DOUBLE
}

TEST_F(ImageStaticTest_1055, Is8ByteType_NonEightByteType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::is8ByteType(0));
    EXPECT_FALSE(Image::is8ByteType(1));
    EXPECT_FALSE(Image::is8ByteType(4));
}

// ==================== Platform endianness tests ====================

TEST_F(ImageStaticTest_1055, PlatformEndianness_MutuallyExclusive_1055) {
    // One and only one should be true
    bool isBig = Image::isBigEndianPlatform();
    bool isLittle = Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

TEST_F(ImageStaticTest_1055, IsLittleEndianPlatform_ConsistentResult_1055) {
    // Calling multiple times should give the same result
    EXPECT_EQ(Image::isLittleEndianPlatform(), Image::isLittleEndianPlatform());
}

TEST_F(ImageStaticTest_1055, IsBigEndianPlatform_ConsistentResult_1055) {
    EXPECT_EQ(Image::isBigEndianPlatform(), Image::isBigEndianPlatform());
}

// ==================== byteSwap tests ====================

TEST_F(ImageStaticTest_1055, ByteSwap16_NoSwap_ReturnsSameValue_1055) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1055, ByteSwap16_Swap_ReturnsSwappedValue_1055) {
    uint16_t val = 0x1234;
    uint16_t expected = 0x3412;
    EXPECT_EQ(Image::byteSwap(val, true), expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap16_SwapZero_ReturnsZero_1055) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), true), static_cast<uint16_t>(0));
}

TEST_F(ImageStaticTest_1055, ByteSwap16_SwapFFFF_ReturnsFFFF_1055) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0xFFFF), true), static_cast<uint16_t>(0xFFFF));
}

TEST_F(ImageStaticTest_1055, ByteSwap32_NoSwap_ReturnsSameValue_1055) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1055, ByteSwap32_Swap_ReturnsSwappedValue_1055) {
    uint32_t val = 0x12345678;
    uint32_t expected = 0x78563412;
    EXPECT_EQ(Image::byteSwap(val, true), expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap32_SwapZero_ReturnsZero_1055) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), true), static_cast<uint32_t>(0));
}

TEST_F(ImageStaticTest_1055, ByteSwap64_NoSwap_ReturnsSameValue_1055) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1055, ByteSwap64_Swap_ReturnsSwappedValue_1055) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t expected = 0x0807060504030201ULL;
    EXPECT_EQ(Image::byteSwap(val, true), expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap64_SwapZero_ReturnsZero_1055) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), static_cast<uint64_t>(0));
}

// ==================== byteSwap2/4/8 with DataBuf tests ====================

TEST_F(ImageStaticTest_1055, ByteSwap2_NoSwap_ReturnsCorrectValue_1055) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t result = Image::byteSwap2(buf, 0, false);
    // Without swap, interpret bytes as-is in memory order
    uint16_t expected_no_swap;
    std::memcpy(&expected_no_swap, buf.c_data(), 2);
    EXPECT_EQ(result, expected_no_swap);
}

TEST_F(ImageStaticTest_1055, ByteSwap2_Swap_ReturnsSwappedValue_1055) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t no_swap = Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(no_swap, true));
}

TEST_F(ImageStaticTest_1055, ByteSwap4_NoSwap_ReturnsCorrectValue_1055) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t result = Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap4_Swap_ReturnsSwappedValue_1055) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t no_swap = Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(no_swap, true));
}

TEST_F(ImageStaticTest_1055, ByteSwap8_NoSwap_ReturnsCorrectValue_1055) {
    DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    uint64_t result = Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), 8);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap8_Swap_ReturnsSwappedValue_1055) {
    DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    uint64_t no_swap = Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(no_swap, true));
}

// ==================== byteSwap2/4/8 with offset tests ====================

TEST_F(ImageStaticTest_1055, ByteSwap2_WithOffset_ReturnsCorrectValue_1055) {
    DataBuf buf(8);
    buf.write_uint8(2, 0xAB);
    buf.write_uint8(3, 0xCD);
    uint16_t result = Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.c_data() + 2, 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap4_WithOffset_ReturnsCorrectValue_1055) {
    DataBuf buf(12);
    buf.write_uint8(4, 0x11);
    buf.write_uint8(5, 0x22);
    buf.write_uint8(6, 0x33);
    buf.write_uint8(7, 0x44);
    uint32_t result = Image::byteSwap4(buf, 4, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data() + 4, 4);
    EXPECT_EQ(result, expected);
}

// ==================== Double swap identity tests ====================

TEST_F(ImageStaticTest_1055, ByteSwap16_DoubleSwap_ReturnsOriginal_1055) {
    uint16_t val = 0xABCD;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

TEST_F(ImageStaticTest_1055, ByteSwap32_DoubleSwap_ReturnsOriginal_1055) {
    uint32_t val = 0xDEADBEEF;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

TEST_F(ImageStaticTest_1055, ByteSwap64_DoubleSwap_ReturnsOriginal_1055) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

// ==================== isPrintXMP boundary tests ====================

TEST_F(ImageStaticTest_1055, IsPrintXMP_BoundaryType699_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintXMP(699, kpsXMP));
}

TEST_F(ImageStaticTest_1055, IsPrintXMP_BoundaryType701_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintXMP(701, kpsXMP));
}

TEST_F(ImageStaticTest_1055, IsPrintXMP_MaxUint16Type_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintXMP(65535, kpsXMP));
}

TEST_F(ImageStaticTest_1055, IsPrintXMP_ZeroType_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isPrintXMP(0, kpsXMP));
}

// ==================== Type classification boundary/edge cases ====================

TEST_F(ImageStaticTest_1055, IsStringType_MaxUint16_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isStringType(65535));
}

TEST_F(ImageStaticTest_1055, IsShortType_MaxUint16_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isShortType(65535));
}

TEST_F(ImageStaticTest_1055, IsLongType_MaxUint16_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isLongType(65535));
}

TEST_F(ImageStaticTest_1055, IsRationalType_MaxUint16_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::isRationalType(65535));
}

TEST_F(ImageStaticTest_1055, Is2ByteType_MaxUint16_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::is2ByteType(65535));
}

TEST_F(ImageStaticTest_1055, Is4ByteType_MaxUint16_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::is4ByteType(65535));
}

TEST_F(ImageStaticTest_1055, Is8ByteType_MaxUint16_ReturnsFalse_1055) {
    EXPECT_FALSE(Image::is8ByteType(65535));
}

// ==================== ByteSwap edge cases ====================

TEST_F(ImageStaticTest_1055, ByteSwap16_SwapOneByteValue_1055) {
    uint16_t val = 0x00FF;
    uint16_t expected = 0xFF00;
    EXPECT_EQ(Image::byteSwap(val, true), expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap32_SwapOneByteValue_1055) {
    uint32_t val = 0x000000FF;
    uint32_t expected = 0xFF000000;
    EXPECT_EQ(Image::byteSwap(val, true), expected);
}

TEST_F(ImageStaticTest_1055, ByteSwap64_MaxValue_1055) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Image::byteSwap(val, true), val);
}
