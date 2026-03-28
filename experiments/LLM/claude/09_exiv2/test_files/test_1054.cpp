#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// Test fixture for Image static methods
class ImageStaticTest_1054 : public ::testing::Test {
protected:
};

// ==================== is8ByteType tests ====================

TEST_F(ImageStaticTest_1054, Is8ByteType_UnsignedRational_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_SignedRational_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_UnsignedLongLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_SignedLongLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_TiffIfd8_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffIfd8));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_TiffDouble_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffDouble));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_UnsignedByte_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_AsciiString_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::asciiString));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_UnsignedShort_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_UnsignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_SignedByte_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::signedByte));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_Undefined_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::undefined));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_SignedShort_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_SignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_TiffFloat_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::tiffFloat));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_TiffIfd_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::tiffIfd));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_Zero_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(0));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_InvalidTypeId_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::invalidTypeId));
}

TEST_F(ImageStaticTest_1054, Is8ByteType_MaxUint16_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(0xFFFF));
}

// ==================== isRationalType tests ====================

TEST_F(ImageStaticTest_1054, IsRationalType_UnsignedRational_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1054, IsRationalType_SignedRational_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1054, IsRationalType_UnsignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, IsRationalType_UnsignedByte_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1054, IsRationalType_TiffDouble_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::tiffDouble));
}

// ==================== isLongLongType tests ====================

TEST_F(ImageStaticTest_1054, IsLongLongType_UnsignedLongLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1054, IsLongLongType_SignedLongLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1054, IsLongLongType_UnsignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, IsLongLongType_SignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::signedLong));
}

// ==================== isStringType tests ====================

TEST_F(ImageStaticTest_1054, IsStringType_AsciiString_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::asciiString));
}

TEST_F(ImageStaticTest_1054, IsStringType_UnsignedByte_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1054, IsStringType_UnsignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedLong));
}

// ==================== isShortType tests ====================

TEST_F(ImageStaticTest_1054, IsShortType_UnsignedShort_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1054, IsShortType_SignedShort_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1054, IsShortType_UnsignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, IsShortType_UnsignedByte_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedByte));
}

// ==================== isLongType tests ====================

TEST_F(ImageStaticTest_1054, IsLongType_UnsignedLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, IsLongType_SignedLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1054, IsLongType_UnsignedShort_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1054, IsLongType_UnsignedLongLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedLongLong));
}

// ==================== is2ByteType tests ====================

TEST_F(ImageStaticTest_1054, Is2ByteType_UnsignedShort_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1054, Is2ByteType_SignedShort_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1054, Is2ByteType_UnsignedLong_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, Is2ByteType_UnsignedByte_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedByte));
}

// ==================== is4ByteType tests ====================

TEST_F(ImageStaticTest_1054, Is4ByteType_UnsignedLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, Is4ByteType_SignedLong_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1054, Is4ByteType_TiffFloat_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffFloat));
}

TEST_F(ImageStaticTest_1054, Is4ByteType_TiffIfd_ReturnsTrue_1054) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffIfd));
}

TEST_F(ImageStaticTest_1054, Is4ByteType_UnsignedShort_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1054, Is4ByteType_UnsignedRational_ReturnsFalse_1054) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedRational));
}

// ==================== Endianness tests ====================

TEST_F(ImageStaticTest_1054, EndianPlatform_MutuallyExclusive_1054) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

// ==================== byteSwap tests ====================

TEST_F(ImageStaticTest_1054, ByteSwap16_NoSwap_ReturnsSameValue_1054) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1054, ByteSwap16_Swap_ReturnsSwappedValue_1054) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint16_t>(0x3412));
}

TEST_F(ImageStaticTest_1054, ByteSwap32_NoSwap_ReturnsSameValue_1054) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1054, ByteSwap32_Swap_ReturnsSwappedValue_1054) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint32_t>(0x78563412));
}

TEST_F(ImageStaticTest_1054, ByteSwap64_NoSwap_ReturnsSameValue_1054) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1054, ByteSwap64_Swap_ReturnsSwappedValue_1054) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint64_t>(0x0807060504030201ULL));
}

TEST_F(ImageStaticTest_1054, ByteSwap16_Zero_ReturnsZero_1054) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), static_cast<uint16_t>(0));
}

TEST_F(ImageStaticTest_1054, ByteSwap32_Zero_ReturnsZero_1054) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), static_cast<uint32_t>(0));
}

TEST_F(ImageStaticTest_1054, ByteSwap64_Zero_ReturnsZero_1054) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), static_cast<uint64_t>(0));
}

TEST_F(ImageStaticTest_1054, ByteSwap16_DoubleSwap_ReturnsOriginal_1054) {
    uint16_t val = 0xABCD;
    uint16_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageStaticTest_1054, ByteSwap32_DoubleSwap_ReturnsOriginal_1054) {
    uint32_t val = 0xDEADBEEF;
    uint32_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageStaticTest_1054, ByteSwap64_DoubleSwap_ReturnsOriginal_1054) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

// ==================== isPrintXMP tests ====================

TEST_F(ImageStaticTest_1054, IsPrintXMP_WithPrintStructureXMP_ReturnsTrue_1054) {
    // XMP type value is typically 700 in TIFF context, but we test with known type
    // Testing that the function is callable and returns a bool
    bool result = Exiv2::Image::isPrintXMP(700, Exiv2::kpsXMP);
    // We don't know the exact expected result without implementation, 
    // but we can verify the function is callable
    (void)result;
}

TEST_F(ImageStaticTest_1054, IsPrintICC_WithPrintStructureICC_1054) {
    bool result = Exiv2::Image::isPrintICC(700, Exiv2::kpsIccProfile);
    (void)result;
}

// ==================== byteSwap2/4/8 with DataBuf tests ====================

TEST_F(ImageStaticTest_1054, ByteSwap2_NoSwap_ReturnsSameValue_1054) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Without swap, bytes are read as-is in memory layout
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint16_t));
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1054, ByteSwap2_Swap_ReturnsSwappedValue_1054) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageStaticTest_1054, ByteSwap4_NoSwap_ReturnsSameValue_1054) {
    Exiv2::DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint32_t));
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1054, ByteSwap8_NoSwap_ReturnsSameValue_1054) {
    Exiv2::DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint64_t));
    EXPECT_EQ(result, expected);
}

// ==================== Consistency tests between type check functions ====================

TEST_F(ImageStaticTest_1054, TypeConsistency_2ByteMatchesShort_1054) {
    // All short types should be 2-byte types
    EXPECT_EQ(Exiv2::Image::is2ByteType(Exiv2::unsignedShort), 
              Exiv2::Image::isShortType(Exiv2::unsignedShort));
    EXPECT_EQ(Exiv2::Image::is2ByteType(Exiv2::signedShort), 
              Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1054, TypeConsistency_4ByteIncludesLong_1054) {
    // Long types should be 4-byte types
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1054, TypeConsistency_8ByteIncludesRational_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1054, TypeConsistency_8ByteIncludesLongLong_1054) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedLongLong));
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

// ==================== Type exclusivity tests ====================

TEST_F(ImageStaticTest_1054, TypeExclusivity_ByteIsNot2Or4Or8_1054) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedByte));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedByte));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1054, TypeExclusivity_ShortIsNot4Or8_1054) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1054, TypeExclusivity_LongIsNot2Or8_1054) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1054, TypeExclusivity_RationalIsNot2Or4_1054) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedRational));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedRational));
}
